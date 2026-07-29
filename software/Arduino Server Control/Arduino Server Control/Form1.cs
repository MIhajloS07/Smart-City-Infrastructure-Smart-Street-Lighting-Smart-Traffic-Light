using System;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Arduino_Server_Control
{
    public partial class LoginForm : Form
    {
        [DllImport("user32.dll")]
        static extern bool ReleaseCapture();

        [DllImport("user32.dll")]
        static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

        private string username = "admin", password = "admin";

        public LoginForm()
        {
            InitializeComponent();
            btnLogIn.Cursor = Cursors.Hand;
            txtPassword.PasswordChar = '●';
            panelError.Visible = false;
            FormBorderStyle = FormBorderStyle.None;
            this.Resize += (s, e) => ApplyRoundRegion();
            ApplyRoundRegion();
            MakeDraggable(this);
        }

        void MakeDraggable(Control control)
        {
            // Skip buttons and input fields
            if (control is Button || control is TextBox || control is ComboBox)
                return;

            control.MouseDown += (s, e) =>
            {
                if (e.Button == MouseButtons.Left)
                {
                    ReleaseCapture();
                    SendMessage(Handle, 0xA1, 0x2, 0);
                }
            };

            foreach (Control child in control.Controls)
                MakeDraggable(child);
        }
        void ApplyRoundRegion()
        {
            var path = new System.Drawing.Drawing2D.GraphicsPath();
            int r = 16;
            path.AddArc(0, 0, r * 2, r * 2, 180, 90);
            path.AddArc(Width - r * 2, 0, r * 2, r * 2, 270, 90);
            path.AddArc(Width - r * 2, Height - r * 2, r * 2, r * 2, 0, 90);
            path.AddArc(0, Height - r * 2, r * 2, r * 2, 90, 90);
            path.CloseFigure();
            Region = new Region(path);
        }

        private void btnLogIn_Click(object sender, EventArgs e)
        {
            if (txtUserName.Text == username && txtPassword.Text == password)
            {
                MessageBox.Show(
                    "Welcome to information system - admin!",
                    "Login successful",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information
                );
                MainForm mainForm = new MainForm();
                mainForm.FormClosed += (s, args) => Application.Exit();
                mainForm.Show(); this.Hide();
            }
            else
            {
                panelError.Visible = true;
                panelHeader.BackColor = Color.FromArgb(196, 67, 45);
            }
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show(
                "Are u sure u want to exit?", 
                "Exit confirmation", 
                MessageBoxButtons.YesNo, 
                MessageBoxIcon.Question
            );
            if (result == DialogResult.Yes)
                Application.Exit();
        }
    }
}