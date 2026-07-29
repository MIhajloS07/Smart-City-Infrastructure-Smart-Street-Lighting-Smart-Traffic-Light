using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.IO.Ports;
using System.Threading;

namespace Arduino_Server_Control
{
    public partial class MainForm : Form
    {
        SerialPort _serial;
        bool _connected = false;
        int _chartX = 0;

        double _lastHC1, _lastHC2, _lastHC3, _lastHC4;
        bool _hc1Got, _hc2Got, _hc3Got, _hc4Got;

        Thread _readThread;
        volatile bool _readRunning = false;

        StringBuilder _lineBuffer = new StringBuilder();

        public MainForm()
        {
            InitializeComponent();

            #region Rounded Corners
            RoundPanel(panelMain);
            RoundPanel(digitalOutputPanel);
            RoundPanel(panelHC1);
            RoundPanel(panelHC2);
            RoundPanel(panelHC3);
            RoundPanel(panelHC4);
            datetimeTimer.Start();
            #endregion

            #region Chart setup
            chart.Series.Clear();
            chart.BackColor = Color.FromArgb(18, 18, 28);
            chart.ChartAreas[0].BackColor = Color.FromArgb(18, 18, 28);
            chart.ChartAreas[0].BorderColor = Color.FromArgb(50, 50, 70);
            chart.ChartAreas[0].AxisX.LineColor = Color.FromArgb(50, 50, 70);
            chart.ChartAreas[0].AxisY.LineColor = Color.FromArgb(50, 50, 70);
            chart.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.FromArgb(40, 40, 60);
            chart.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.FromArgb(40, 40, 60);
            chart.ChartAreas[0].AxisX.LabelStyle.ForeColor = Color.White;
            chart.ChartAreas[0].AxisY.LabelStyle.ForeColor = Color.White;
            chart.Legends[0].BackColor = Color.FromArgb(18, 18, 28);
            chart.Legends[0].ForeColor = Color.White;
            chart.ChartAreas[0].AxisY.Maximum = 200;
            chart.ChartAreas[0].AxisY.Minimum = 0;

            string[] seriesNames = { "HC1", "HC2", "HC3", "HC4" };
            Color[] seriesColors = {
                Color.FromArgb(245, 166,  35),
                Color.FromArgb( 56, 189, 248),
                Color.FromArgb( 74, 222, 128),
                Color.FromArgb(248, 113, 113)
            };
            for (int i = 0; i < 4; i++)
            {
                var s = new Series(seriesNames[i])
                {
                    ChartType = SeriesChartType.Line,
                    Color = seriesColors[i],
                    BorderWidth = 2,
                    ChartArea = "ChartArea1",
                    Legend = "Legend1"
                };
                chart.Series.Add(s);
            }
            #endregion

            #region Serial UI
            var cmbPort = new ComboBox
            {
                DropDownStyle = ComboBoxStyle.DropDownList,
                Width = 90,
                BackColor = Color.FromArgb(30, 30, 50),
                ForeColor = Color.White,
                FlatStyle = FlatStyle.Flat,
                Font = new Font("Segoe UI", 9)
            };
            RefreshPorts(cmbPort);

            var btnConnect = new Button
            {
                Text = "CONNECT",
                Width = 85,
                Height = 26,
                FlatStyle = FlatStyle.Flat,
                BackColor = Color.FromArgb(245, 166, 35),
                ForeColor = Color.Black,
                Font = new Font("Segoe UI", 8, FontStyle.Bold),
                Cursor = Cursors.Hand
            };
            btnConnect.FlatAppearance.BorderSize = 0;

            var btnRefresh = new Button
            {
                Text = "↻",
                Width = 30,
                Height = 26,
                FlatStyle = FlatStyle.Flat,
                BackColor = Color.FromArgb(30, 30, 50),
                ForeColor = Color.White,
                Font = new Font("Segoe UI", 11),
                Cursor = Cursors.Hand
            };
            btnRefresh.FlatAppearance.BorderSize = 0;
            btnRefresh.Click += (s, e) => RefreshPorts(cmbPort);

            var statusDot = new Panel
            {
                Size = new Size(14, 14),
                BackColor = Color.Transparent,
                Cursor = Cursors.Default
            };
            statusDot.Paint += (s, e) =>
            {
                e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                var color = _connected ? Color.LimeGreen : Color.Red;
                using (var br = new SolidBrush(color))
                    e.Graphics.FillEllipse(br, 0, 0, 13, 13);
            };

            var lblStatus = new Label
            {
                Text = "Not connected",
                ForeColor = Color.Red,
                Font = new Font("Segoe UI", 8),
                AutoSize = true,
                BackColor = Color.Transparent
            };

            panelMain.Controls.Add(cmbPort);
            panelMain.Controls.Add(btnRefresh);
            panelMain.Controls.Add(btnConnect);
            panelMain.Controls.Add(statusDot);
            panelMain.Controls.Add(lblStatus);

            Action layoutControls = () =>
            {
                int re = panelMain.Width - 20;
                int cy = (panelMain.Height - btnConnect.Height) / 2;
                lblStatus.Location = new Point(re - 350, (panelMain.Height - lblStatus.Height) / 2);
                statusDot.Location = new Point(re - 370, (panelMain.Height - statusDot.Height) / 2);
                btnConnect.Location = new Point(re - 900, cy);
                cmbPort.Location = new Point(re - 1050, (panelMain.Height - cmbPort.Height) / 2);
                btnRefresh.Location = new Point(re - 1100, cy);
            };
            layoutControls();
            panelMain.Resize += (s, e) => layoutControls();

            btnConnect.Click += (s, e) =>
            {
                if (_connected)
                {
                    Disconnect();
                    btnConnect.Text = "CONNECT";
                    btnConnect.BackColor = Color.FromArgb(245, 166, 35);
                    btnConnect.ForeColor = Color.Black;
                    lblStatus.Text = "Not connected";
                    lblStatus.ForeColor = Color.Red;
                    statusDot.Invalidate();
                }
                else
                {
                    string port = cmbPort.SelectedItem?.ToString();
                    if (port == null) { MessageBox.Show("Select port!"); return; }
                    try
                    {
                        _serial = new SerialPort(port, 9600)
                        {
                            DtrEnable = true,   
                            RtsEnable = false,
                            ReadTimeout = 2000
                        };
                        _serial.Open();

                        Thread.Sleep(2000);
                        _serial.DiscardInBuffer();
                        _lineBuffer.Clear();
                        _hc1Got = _hc2Got = _hc3Got = _hc4Got = false;

                        _connected = true;
                        _readRunning = true;

                        _readThread = new Thread(ReadLoop)
                        {
                            IsBackground = true,
                            Name = "SerialReadThread"
                        };
                        _readThread.Start();

                        btnConnect.Text = "DISCONNECT";
                        btnConnect.BackColor = Color.FromArgb(180, 40, 40);
                        btnConnect.ForeColor = Color.White;
                        lblStatus.Text = port + " — connected";
                        lblStatus.ForeColor = Color.LimeGreen;
                        statusDot.Invalidate();
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Error: " + ex.Message);
                    }
                }
            };
            #endregion

            checkBoxD6.CheckedChanged += (s, e) => SendLed(1, checkBoxD6.Checked);
            checkBoxD9.CheckedChanged += (s, e) => SendLed(2, checkBoxD9.Checked);
            checkBoxD10.CheckedChanged += (s, e) => SendLed(3, checkBoxD10.Checked);
            checkBoxD11.CheckedChanged += (s, e) => SendLed(4, checkBoxD11.Checked);
        }

        // ─── Background thread: reads byte by byte ────────────────────────────
        void ReadLoop()
        {
            while (_readRunning)
            {
                try
                {
                    if (_serial == null || !_serial.IsOpen) break;

                    int b = _serial.ReadByte();
                    if (b < 0) continue;

                    char c = (char)b;

                    if (c == '\n')
                    {
                        string line = _lineBuffer.ToString().Trim();
                        _lineBuffer.Clear();
                        if (line.Length > 0)
                            ProcessLine(line);
                    }
                    else if (c != '\r')
                    {
                        _lineBuffer.Append(c);
                    }
                }
                catch (TimeoutException) { continue; }
                catch (InvalidOperationException) { break; }
                catch { break; }
            }
        }

        // ─── Parsing line "HC1:102.7" ────────────────────────────────────
        void ProcessLine(string line)
        {
            if (!line.StartsWith("HC") || !line.Contains(":")) return;

            int colonIdx = line.IndexOf(':');
            string sensor = line.Substring(0, colonIdx).Trim();
            string valStr = line.Substring(colonIdx + 1).Trim();

            if (!double.TryParse(valStr,
                System.Globalization.NumberStyles.Float,
                System.Globalization.CultureInfo.InvariantCulture,
                out double value)) return;

            string display = value < 500 ? value.ToString("F1") + " cm" : "--- cm";
            double chartVal = value < 200 ? value : 200.0;

            SafeBeginInvoke(() =>
            {
                switch (sensor)
                {
                    case "HC1":
                        labelDistanceHC1.Text = display;
                        _lastHC1 = chartVal; _hc1Got = true;
                        break;
                    case "HC2":
                        labelDistanceHC2.Text = display;
                        _lastHC2 = chartVal; _hc2Got = true;
                        break;
                    case "HC3":
                        labelDistanceHC3.Text = display;
                        _lastHC3 = chartVal; _hc3Got = true;
                        break;
                    case "HC4":
                        labelDistanceHC4.Text = display;
                        _lastHC4 = chartVal; _hc4Got = true;
                        break;
                    default:
                        return;
                }

                if (_hc1Got && _hc2Got && _hc3Got && _hc4Got)
                {
                    AddToChart(_lastHC1, _lastHC2, _lastHC3, _lastHC4);
                    _hc1Got = _hc2Got = _hc3Got = _hc4Got = false;
                }
            });
        }

        // ─── Chart ────────────────────────────────────────────────────────────
        void AddToChart(double hc1, double hc2, double hc3, double hc4)
        {
            double[] vals = { hc1, hc2, hc3, hc4 };
            for (int i = 0; i < 4; i++)
                chart.Series[i].Points.AddXY(_chartX, vals[i]);
            _chartX++;

            if (chart.Series[0].Points.Count > 30)
                for (int i = 0; i < 4; i++)
                    chart.Series[i].Points.RemoveAt(0);

            // Auto-scroll X coordinate — show last 30 dots
            chart.ChartAreas[0].AxisX.Minimum = _chartX - 30;
            chart.ChartAreas[0].AxisX.Maximum = _chartX;
        }

        // ─── Helpers ──────────────────────────────────────────────────────────
        void SafeBeginInvoke(Action action)
        {
            if (IsDisposed || !IsHandleCreated) return;
            try { BeginInvoke(action); }
            catch { }
        }

        void SendLed(int num, bool on)
        {
            if (!_connected || _serial == null || !_serial.IsOpen) return;
            try { _serial.WriteLine("LED" + num + ":" + (on ? 1 : 0)); }
            catch { }
        }

        void RefreshPorts(ComboBox cmb)
        {
            cmb.Items.Clear();
            foreach (var p in SerialPort.GetPortNames())
                cmb.Items.Add(p);
            if (cmb.Items.Count > 0) cmb.SelectedIndex = 0;
        }

        void Disconnect()
        {
            _readRunning = false;
            _connected = false;
            try { _serial?.Close(); } catch { }
        }

        void RoundPanel(Panel panel, int radius = 12)
        {
            panel.Paint += (s, e) =>
            {
                var g = e.Graphics;
                g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                var path = new System.Drawing.Drawing2D.GraphicsPath();
                int r = radius;
                var rect = new Rectangle(0, 0, panel.Width - 1, panel.Height - 1);
                path.AddArc(rect.X, rect.Y, r * 2, r * 2, 180, 90);
                path.AddArc(rect.Right - r * 2, rect.Y, r * 2, r * 2, 270, 90);
                path.AddArc(rect.Right - r * 2, rect.Bottom - r * 2, r * 2, r * 2, 0, 90);
                path.AddArc(rect.X, rect.Bottom - r * 2, r * 2, r * 2, 90, 90);
                path.CloseFigure();
                panel.Region = new Region(path);
            };
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            var result = MessageBox.Show(
                "Are u sure u want to exit?",
                "Exit confirmation",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);
            if (result == DialogResult.Yes)
                Application.Exit();
        }

        private void datetimeTimer_Tick(object sender, EventArgs e) =>
            datetimeLbl.Text = DateTime.Now.ToString("HH:mm:ss   dd.MM.yyyy.");

        protected override void OnFormClosed(FormClosedEventArgs e)
        {
            Disconnect();
            base.OnFormClosed(e);
        }
    }
}