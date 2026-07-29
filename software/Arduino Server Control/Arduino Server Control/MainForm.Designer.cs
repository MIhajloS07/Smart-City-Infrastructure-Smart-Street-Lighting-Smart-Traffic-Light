namespace Arduino_Server_Control
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.datetimeLbl = new System.Windows.Forms.Label();
            this.btnExit = new System.Windows.Forms.Button();
            this.panelMain = new System.Windows.Forms.Panel();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.lbladmin = new System.Windows.Forms.Label();
            this.digitalOutputPanel = new System.Windows.Forms.Panel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.checkBoxD11 = new System.Windows.Forms.CheckBox();
            this.checkBoxD10 = new System.Windows.Forms.CheckBox();
            this.checkBoxD9 = new System.Windows.Forms.CheckBox();
            this.checkBoxD6 = new System.Windows.Forms.CheckBox();
            this.labeldo = new System.Windows.Forms.Label();
            this.datetimeTimer = new System.Windows.Forms.Timer(this.components);
            this.panelHC1 = new System.Windows.Forms.Panel();
            this.labelDistanceHC1 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.labelhc1 = new System.Windows.Forms.Label();
            this.panelHC2 = new System.Windows.Forms.Panel();
            this.labelDistanceHC2 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.labelhc2 = new System.Windows.Forms.Label();
            this.panelHC4 = new System.Windows.Forms.Panel();
            this.labelDistanceHC4 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.labelhc4 = new System.Windows.Forms.Label();
            this.panelHC3 = new System.Windows.Forms.Panel();
            this.labelDistanceHC3 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.labelhc3 = new System.Windows.Forms.Label();
            this.chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.pictureBox4 = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.panelMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.digitalOutputPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.panelHC1.SuspendLayout();
            this.panelHC2.SuspendLayout();
            this.panelHC4.SuspendLayout();
            this.panelHC3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.SuspendLayout();
            // 
            // datetimeLbl
            // 
            this.datetimeLbl.AutoSize = true;
            this.datetimeLbl.Font = new System.Drawing.Font("Lucida Sans Unicode", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.datetimeLbl.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(79)))), ((int)(((byte)(87)))), ((int)(((byte)(105)))));
            this.datetimeLbl.Location = new System.Drawing.Point(686, 25);
            this.datetimeLbl.Name = "datetimeLbl";
            this.datetimeLbl.Size = new System.Drawing.Size(0, 20);
            this.datetimeLbl.TabIndex = 1;
            // 
            // btnExit
            // 
            this.btnExit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.btnExit.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnExit.FlatAppearance.BorderColor = System.Drawing.Color.Gray;
            this.btnExit.FlatAppearance.BorderSize = 0;
            this.btnExit.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnExit.Font = new System.Drawing.Font("Lucida Sans Unicode", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnExit.ForeColor = System.Drawing.Color.White;
            this.btnExit.Location = new System.Drawing.Point(1268, 16);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(85, 34);
            this.btnExit.TabIndex = 2;
            this.btnExit.Text = "Exit";
            this.btnExit.UseVisualStyleBackColor = false;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // panelMain
            // 
            this.panelMain.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(53)))));
            this.panelMain.Controls.Add(this.pictureBox2);
            this.panelMain.Controls.Add(this.btnExit);
            this.panelMain.Controls.Add(this.datetimeLbl);
            this.panelMain.Controls.Add(this.lbladmin);
            this.panelMain.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(24)))), ((int)(((byte)(39)))));
            this.panelMain.Location = new System.Drawing.Point(27, 12);
            this.panelMain.Name = "panelMain";
            this.panelMain.Size = new System.Drawing.Size(1385, 70);
            this.panelMain.TabIndex = 0;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = global::Arduino_Server_Control.Properties.Resources._406_4066806_clipart_circle_green_green_circle_image_png_transparent;
            this.pictureBox2.Location = new System.Drawing.Point(17, 28);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(20, 15);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 5;
            this.pictureBox2.TabStop = false;
            // 
            // lbladmin
            // 
            this.lbladmin.AutoSize = true;
            this.lbladmin.Font = new System.Drawing.Font("Lucida Sans Unicode", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbladmin.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(150)))), ((int)(((byte)(190)))));
            this.lbladmin.Location = new System.Drawing.Point(43, 16);
            this.lbladmin.Name = "lbladmin";
            this.lbladmin.Size = new System.Drawing.Size(101, 34);
            this.lbladmin.TabIndex = 0;
            this.lbladmin.Text = "Admin";
            // 
            // digitalOutputPanel
            // 
            this.digitalOutputPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(60)))));
            this.digitalOutputPanel.Controls.Add(this.pictureBox1);
            this.digitalOutputPanel.Controls.Add(this.checkBoxD11);
            this.digitalOutputPanel.Controls.Add(this.checkBoxD10);
            this.digitalOutputPanel.Controls.Add(this.checkBoxD9);
            this.digitalOutputPanel.Controls.Add(this.checkBoxD6);
            this.digitalOutputPanel.Controls.Add(this.labeldo);
            this.digitalOutputPanel.Location = new System.Drawing.Point(31, 108);
            this.digitalOutputPanel.Name = "digitalOutputPanel";
            this.digitalOutputPanel.Size = new System.Drawing.Size(282, 249);
            this.digitalOutputPanel.TabIndex = 1;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::Arduino_Server_Control.Properties.Resources._406_4066806_clipart_circle_green_green_circle_image_png_transparent;
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(20, 15);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // checkBoxD11
            // 
            this.checkBoxD11.AutoSize = true;
            this.checkBoxD11.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxD11.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(150)))), ((int)(((byte)(190)))));
            this.checkBoxD11.Location = new System.Drawing.Point(61, 203);
            this.checkBoxD11.Name = "checkBoxD11";
            this.checkBoxD11.Size = new System.Drawing.Size(137, 20);
            this.checkBoxD11.TabIndex = 4;
            this.checkBoxD11.Text = "LED DIODE - D11";
            this.checkBoxD11.UseVisualStyleBackColor = true;
            // 
            // checkBoxD10
            // 
            this.checkBoxD10.AutoSize = true;
            this.checkBoxD10.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxD10.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(150)))), ((int)(((byte)(190)))));
            this.checkBoxD10.Location = new System.Drawing.Point(61, 155);
            this.checkBoxD10.Name = "checkBoxD10";
            this.checkBoxD10.Size = new System.Drawing.Size(137, 20);
            this.checkBoxD10.TabIndex = 3;
            this.checkBoxD10.Text = "LED DIODE - D10";
            this.checkBoxD10.UseVisualStyleBackColor = true;
            // 
            // checkBoxD9
            // 
            this.checkBoxD9.AutoSize = true;
            this.checkBoxD9.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxD9.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(150)))), ((int)(((byte)(190)))));
            this.checkBoxD9.Location = new System.Drawing.Point(61, 104);
            this.checkBoxD9.Name = "checkBoxD9";
            this.checkBoxD9.Size = new System.Drawing.Size(129, 20);
            this.checkBoxD9.TabIndex = 2;
            this.checkBoxD9.Text = "LED DIODE - D9";
            this.checkBoxD9.UseVisualStyleBackColor = true;
            // 
            // checkBoxD6
            // 
            this.checkBoxD6.AutoSize = true;
            this.checkBoxD6.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBoxD6.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(150)))), ((int)(((byte)(190)))));
            this.checkBoxD6.Location = new System.Drawing.Point(61, 55);
            this.checkBoxD6.Name = "checkBoxD6";
            this.checkBoxD6.Size = new System.Drawing.Size(129, 20);
            this.checkBoxD6.TabIndex = 1;
            this.checkBoxD6.Text = "LED DIODE - D6";
            this.checkBoxD6.UseVisualStyleBackColor = true;
            // 
            // labeldo
            // 
            this.labeldo.AutoSize = true;
            this.labeldo.Font = new System.Drawing.Font("Lucida Sans Unicode", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labeldo.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(150)))), ((int)(((byte)(190)))));
            this.labeldo.Location = new System.Drawing.Point(40, 9);
            this.labeldo.Name = "labeldo";
            this.labeldo.Size = new System.Drawing.Size(150, 20);
            this.labeldo.TabIndex = 0;
            this.labeldo.Text = "DIGITAL OUTPUTS";
            // 
            // datetimeTimer
            // 
            this.datetimeTimer.Interval = 1000;
            this.datetimeTimer.Tick += new System.EventHandler(this.datetimeTimer_Tick);
            // 
            // panelHC1
            // 
            this.panelHC1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(60)))));
            this.panelHC1.Controls.Add(this.labelDistanceHC1);
            this.panelHC1.Controls.Add(this.label5);
            this.panelHC1.Controls.Add(this.label4);
            this.panelHC1.Controls.Add(this.labelhc1);
            this.panelHC1.Location = new System.Drawing.Point(353, 117);
            this.panelHC1.Name = "panelHC1";
            this.panelHC1.Size = new System.Drawing.Size(518, 113);
            this.panelHC1.TabIndex = 3;
            // 
            // labelDistanceHC1
            // 
            this.labelDistanceHC1.AutoSize = true;
            this.labelDistanceHC1.Font = new System.Drawing.Font("Lucida Sans Unicode", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelDistanceHC1.ForeColor = System.Drawing.SystemColors.Control;
            this.labelDistanceHC1.Location = new System.Drawing.Point(16, 48);
            this.labelDistanceHC1.Name = "labelDistanceHC1";
            this.labelDistanceHC1.Size = new System.Drawing.Size(0, 25);
            this.labelDistanceHC1.TabIndex = 17;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(79)))), ((int)(((byte)(87)))), ((int)(((byte)(105)))));
            this.label5.Location = new System.Drawing.Point(18, 77);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(83, 16);
            this.label5.TabIndex = 10;
            this.label5.Text = "cm distance";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.LimeGreen;
            this.label4.Location = new System.Drawing.Point(14, 90);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(259, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "__________________________________________";
            // 
            // labelhc1
            // 
            this.labelhc1.AutoSize = true;
            this.labelhc1.Font = new System.Drawing.Font("Lucida Sans Unicode", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelhc1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(248)))), ((int)(((byte)(130)))), ((int)(((byte)(87)))));
            this.labelhc1.Location = new System.Drawing.Point(13, 9);
            this.labelhc1.Name = "labelhc1";
            this.labelhc1.Size = new System.Drawing.Size(49, 23);
            this.labelhc1.TabIndex = 0;
            this.labelhc1.Text = "HC1";
            // 
            // panelHC2
            // 
            this.panelHC2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(60)))));
            this.panelHC2.Controls.Add(this.labelDistanceHC2);
            this.panelHC2.Controls.Add(this.label8);
            this.panelHC2.Controls.Add(this.label2);
            this.panelHC2.Controls.Add(this.labelhc2);
            this.panelHC2.Location = new System.Drawing.Point(888, 117);
            this.panelHC2.Name = "panelHC2";
            this.panelHC2.Size = new System.Drawing.Size(514, 113);
            this.panelHC2.TabIndex = 4;
            // 
            // labelDistanceHC2
            // 
            this.labelDistanceHC2.AutoSize = true;
            this.labelDistanceHC2.Font = new System.Drawing.Font("Lucida Sans Unicode", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelDistanceHC2.ForeColor = System.Drawing.SystemColors.Control;
            this.labelDistanceHC2.Location = new System.Drawing.Point(18, 48);
            this.labelDistanceHC2.Name = "labelDistanceHC2";
            this.labelDistanceHC2.Size = new System.Drawing.Size(0, 25);
            this.labelDistanceHC2.TabIndex = 14;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(79)))), ((int)(((byte)(87)))), ((int)(((byte)(105)))));
            this.label8.Location = new System.Drawing.Point(22, 77);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(83, 16);
            this.label8.TabIndex = 13;
            this.label8.Text = "cm distance";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.LimeGreen;
            this.label2.Location = new System.Drawing.Point(20, 90);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(259, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "__________________________________________";
            // 
            // labelhc2
            // 
            this.labelhc2.AutoSize = true;
            this.labelhc2.Font = new System.Drawing.Font("Lucida Sans Unicode", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelhc2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(248)))), ((int)(((byte)(130)))), ((int)(((byte)(87)))));
            this.labelhc2.Location = new System.Drawing.Point(16, 12);
            this.labelhc2.Name = "labelhc2";
            this.labelhc2.Size = new System.Drawing.Size(49, 23);
            this.labelhc2.TabIndex = 1;
            this.labelhc2.Text = "HC2";
            // 
            // panelHC4
            // 
            this.panelHC4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(60)))));
            this.panelHC4.Controls.Add(this.labelDistanceHC4);
            this.panelHC4.Controls.Add(this.label7);
            this.panelHC4.Controls.Add(this.label1);
            this.panelHC4.Controls.Add(this.labelhc4);
            this.panelHC4.Location = new System.Drawing.Point(888, 244);
            this.panelHC4.Name = "panelHC4";
            this.panelHC4.Size = new System.Drawing.Size(514, 113);
            this.panelHC4.TabIndex = 6;
            // 
            // labelDistanceHC4
            // 
            this.labelDistanceHC4.AutoSize = true;
            this.labelDistanceHC4.Font = new System.Drawing.Font("Lucida Sans Unicode", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelDistanceHC4.ForeColor = System.Drawing.SystemColors.Control;
            this.labelDistanceHC4.Location = new System.Drawing.Point(20, 52);
            this.labelDistanceHC4.Name = "labelDistanceHC4";
            this.labelDistanceHC4.Size = new System.Drawing.Size(0, 25);
            this.labelDistanceHC4.TabIndex = 15;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(79)))), ((int)(((byte)(87)))), ((int)(((byte)(105)))));
            this.label7.Location = new System.Drawing.Point(22, 77);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(83, 16);
            this.label7.TabIndex = 12;
            this.label7.Text = "cm distance";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.LimeGreen;
            this.label1.Location = new System.Drawing.Point(19, 92);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(259, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "__________________________________________";
            // 
            // labelhc4
            // 
            this.labelhc4.AutoSize = true;
            this.labelhc4.Font = new System.Drawing.Font("Lucida Sans Unicode", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelhc4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(248)))), ((int)(((byte)(130)))), ((int)(((byte)(87)))));
            this.labelhc4.Location = new System.Drawing.Point(16, 19);
            this.labelhc4.Name = "labelhc4";
            this.labelhc4.Size = new System.Drawing.Size(49, 23);
            this.labelhc4.TabIndex = 3;
            this.labelhc4.Text = "HC4";
            // 
            // panelHC3
            // 
            this.panelHC3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(60)))));
            this.panelHC3.Controls.Add(this.labelDistanceHC3);
            this.panelHC3.Controls.Add(this.label6);
            this.panelHC3.Controls.Add(this.label3);
            this.panelHC3.Controls.Add(this.labelhc3);
            this.panelHC3.Location = new System.Drawing.Point(353, 244);
            this.panelHC3.Name = "panelHC3";
            this.panelHC3.Size = new System.Drawing.Size(518, 113);
            this.panelHC3.TabIndex = 5;
            // 
            // labelDistanceHC3
            // 
            this.labelDistanceHC3.AutoSize = true;
            this.labelDistanceHC3.Font = new System.Drawing.Font("Lucida Sans Unicode", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelDistanceHC3.ForeColor = System.Drawing.SystemColors.Control;
            this.labelDistanceHC3.Location = new System.Drawing.Point(16, 52);
            this.labelDistanceHC3.Name = "labelDistanceHC3";
            this.labelDistanceHC3.Size = new System.Drawing.Size(0, 25);
            this.labelDistanceHC3.TabIndex = 16;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Lucida Sans Unicode", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(79)))), ((int)(((byte)(87)))), ((int)(((byte)(105)))));
            this.label6.Location = new System.Drawing.Point(18, 76);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(83, 16);
            this.label6.TabIndex = 11;
            this.label6.Text = "cm distance";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.LimeGreen;
            this.label3.Location = new System.Drawing.Point(14, 92);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(259, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "__________________________________________";
            // 
            // labelhc3
            // 
            this.labelhc3.AutoSize = true;
            this.labelhc3.Font = new System.Drawing.Font("Lucida Sans Unicode", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelhc3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(248)))), ((int)(((byte)(130)))), ((int)(((byte)(87)))));
            this.labelhc3.Location = new System.Drawing.Point(13, 14);
            this.labelhc3.Name = "labelhc3";
            this.labelhc3.Size = new System.Drawing.Size(49, 23);
            this.labelhc3.TabIndex = 2;
            this.labelhc3.Text = "HC3";
            // 
            // chart
            // 
            this.chart.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(46)))));
            this.chart.BorderlineColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(46)))));
            chartArea2.Name = "ChartArea1";
            this.chart.ChartAreas.Add(chartArea2);
            legend2.Name = "Legend1";
            this.chart.Legends.Add(legend2);
            this.chart.Location = new System.Drawing.Point(395, 411);
            this.chart.Name = "chart";
            series2.ChartArea = "ChartArea1";
            series2.Legend = "Legend1";
            series2.Name = "Series1";
            this.chart.Series.Add(series2);
            this.chart.Size = new System.Drawing.Size(1007, 330);
            this.chart.TabIndex = 7;
            this.chart.Text = "chart1";
            // 
            // pictureBox4
            // 
            this.pictureBox4.Image = global::Arduino_Server_Control.Properties.Resources.dac34104_cd01_4be9_beb0_5d1776d4130b;
            this.pictureBox4.Location = new System.Drawing.Point(27, 462);
            this.pictureBox4.Name = "pictureBox4";
            this.pictureBox4.Size = new System.Drawing.Size(342, 245);
            this.pictureBox4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox4.TabIndex = 8;
            this.pictureBox4.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.Image = global::Arduino_Server_Control.Properties.Resources.hcsensor;
            this.pictureBox3.Location = new System.Drawing.Point(1323, 760);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(89, 48);
            this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox3.TabIndex = 2;
            this.pictureBox3.TabStop = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(27)))), ((int)(((byte)(46)))));
            this.ClientSize = new System.Drawing.Size(1438, 869);
            this.Controls.Add(this.pictureBox4);
            this.Controls.Add(this.pictureBox3);
            this.Controls.Add(this.chart);
            this.Controls.Add(this.panelHC4);
            this.Controls.Add(this.panelHC1);
            this.Controls.Add(this.panelHC3);
            this.Controls.Add(this.panelHC2);
            this.Controls.Add(this.digitalOutputPanel);
            this.Controls.Add(this.panelMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "MainForm";
            this.panelMain.ResumeLayout(false);
            this.panelMain.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.digitalOutputPanel.ResumeLayout(false);
            this.digitalOutputPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.panelHC1.ResumeLayout(false);
            this.panelHC1.PerformLayout();
            this.panelHC2.ResumeLayout(false);
            this.panelHC2.PerformLayout();
            this.panelHC4.ResumeLayout(false);
            this.panelHC4.PerformLayout();
            this.panelHC3.ResumeLayout(false);
            this.panelHC3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label datetimeLbl;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Panel panelMain;
        private System.Windows.Forms.Label lbladmin;
        private System.Windows.Forms.Panel digitalOutputPanel;
        private System.Windows.Forms.Label labeldo;
        private System.Windows.Forms.CheckBox checkBoxD11;
        private System.Windows.Forms.CheckBox checkBoxD10;
        private System.Windows.Forms.CheckBox checkBoxD9;
        private System.Windows.Forms.CheckBox checkBoxD6;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Timer datetimeTimer;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.Panel panelHC1;
        private System.Windows.Forms.Panel panelHC2;
        private System.Windows.Forms.Panel panelHC4;
        private System.Windows.Forms.Panel panelHC3;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart;
        private System.Windows.Forms.Label labelhc1;
        private System.Windows.Forms.Label labelhc2;
        private System.Windows.Forms.Label labelhc4;
        private System.Windows.Forms.Label labelhc3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.PictureBox pictureBox4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label labelDistanceHC1;
        private System.Windows.Forms.Label labelDistanceHC2;
        private System.Windows.Forms.Label labelDistanceHC4;
        private System.Windows.Forms.Label labelDistanceHC3;
    }
}