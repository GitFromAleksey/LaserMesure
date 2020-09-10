namespace HoningMachineConfig
{
    partial class MainForm1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
        	this.components = new System.ComponentModel.Container();
        	this.menuStrip1 = new System.Windows.Forms.MenuStrip();
        	this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        	this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        	this.configToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        	this.portToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        	this.toolStripComboBox1 = new System.Windows.Forms.ToolStripComboBox();
        	this.openPortToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        	this.closePortToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        	this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        	this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
        	this.textBoxLog = new System.Windows.Forms.TextBox();
        	this.textBoxToSend = new System.Windows.Forms.TextBox();
        	this.button1 = new System.Windows.Forms.Button();
        	this.timer1 = new System.Windows.Forms.Timer(this.components);
        	this.buttonReadCurrentRecord = new System.Windows.Forms.Button();
        	this.buttonRead = new System.Windows.Forms.Button();
        	this.buttonPlus = new System.Windows.Forms.Button();
        	this.buttonMenu = new System.Windows.Forms.Button();
        	this.buttonMinus = new System.Windows.Forms.Button();
        	this.buttonArea = new System.Windows.Forms.Button();
        	this.buttonLevelBubble = new System.Windows.Forms.Button();
        	this.buttonPythegoras = new System.Windows.Forms.Button();
        	this.buttonTimer = new System.Windows.Forms.Button();
        	this.buttonClearOff = new System.Windows.Forms.Button();
        	this.buttonSave = new System.Windows.Forms.Button();
        	this.labelValue = new System.Windows.Forms.Label();
        	this.menuStrip1.SuspendLayout();
        	this.SuspendLayout();
        	// 
        	// menuStrip1
        	// 
        	this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
        	        	        	this.fileToolStripMenuItem,
        	        	        	this.configToolStripMenuItem,
        	        	        	this.helpToolStripMenuItem});
        	this.menuStrip1.Location = new System.Drawing.Point(0, 0);
        	this.menuStrip1.Name = "menuStrip1";
        	this.menuStrip1.Padding = new System.Windows.Forms.Padding(8, 2, 0, 2);
        	this.menuStrip1.Size = new System.Drawing.Size(882, 28);
        	this.menuStrip1.TabIndex = 0;
        	this.menuStrip1.Text = "menuStrip1";
        	// 
        	// fileToolStripMenuItem
        	// 
        	this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
        	        	        	this.exitToolStripMenuItem});
        	this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
        	this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
        	this.fileToolStripMenuItem.Text = "File";
        	// 
        	// exitToolStripMenuItem
        	// 
        	this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
        	this.exitToolStripMenuItem.Size = new System.Drawing.Size(102, 24);
        	this.exitToolStripMenuItem.Text = "Exit";
        	// 
        	// configToolStripMenuItem
        	// 
        	this.configToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
        	        	        	this.portToolStripMenuItem,
        	        	        	this.openPortToolStripMenuItem,
        	        	        	this.closePortToolStripMenuItem});
        	this.configToolStripMenuItem.Name = "configToolStripMenuItem";
        	this.configToolStripMenuItem.Size = new System.Drawing.Size(65, 24);
        	this.configToolStripMenuItem.Text = "Config";
        	// 
        	// portToolStripMenuItem
        	// 
        	this.portToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
        	        	        	this.toolStripComboBox1});
        	this.portToolStripMenuItem.Name = "portToolStripMenuItem";
        	this.portToolStripMenuItem.Size = new System.Drawing.Size(140, 24);
        	this.portToolStripMenuItem.Text = "Port";
        	this.portToolStripMenuItem.Click += new System.EventHandler(this.portToolStripMenuItem_Click);
        	// 
        	// toolStripComboBox1
        	// 
        	this.toolStripComboBox1.Name = "toolStripComboBox1";
        	this.toolStripComboBox1.Size = new System.Drawing.Size(121, 28);
        	this.toolStripComboBox1.TextChanged += new System.EventHandler(this.toolStripComboBox1_TextChanged);
        	// 
        	// openPortToolStripMenuItem
        	// 
        	this.openPortToolStripMenuItem.Name = "openPortToolStripMenuItem";
        	this.openPortToolStripMenuItem.Size = new System.Drawing.Size(140, 24);
        	this.openPortToolStripMenuItem.Text = "OpenPort";
        	this.openPortToolStripMenuItem.Click += new System.EventHandler(this.openPortToolStripMenuItem_Click);
        	// 
        	// closePortToolStripMenuItem
        	// 
        	this.closePortToolStripMenuItem.Name = "closePortToolStripMenuItem";
        	this.closePortToolStripMenuItem.Size = new System.Drawing.Size(140, 24);
        	this.closePortToolStripMenuItem.Text = "ClosePort";
        	this.closePortToolStripMenuItem.Click += new System.EventHandler(this.closePortToolStripMenuItem_Click);
        	// 
        	// helpToolStripMenuItem
        	// 
        	this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
        	this.helpToolStripMenuItem.Size = new System.Drawing.Size(53, 24);
        	this.helpToolStripMenuItem.Text = "Help";
        	// 
        	// serialPort1
        	// 
        	this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
        	// 
        	// textBoxLog
        	// 
        	this.textBoxLog.Location = new System.Drawing.Point(16, 81);
        	this.textBoxLog.Margin = new System.Windows.Forms.Padding(4);
        	this.textBoxLog.Multiline = true;
        	this.textBoxLog.Name = "textBoxLog";
        	this.textBoxLog.ScrollBars = System.Windows.Forms.ScrollBars.Both;
        	this.textBoxLog.Size = new System.Drawing.Size(443, 482);
        	this.textBoxLog.TabIndex = 1;
        	this.textBoxLog.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainForm1_KeyDown);
        	// 
        	// textBoxToSend
        	// 
        	this.textBoxToSend.Location = new System.Drawing.Point(16, 33);
        	this.textBoxToSend.Margin = new System.Windows.Forms.Padding(4);
        	this.textBoxToSend.Name = "textBoxToSend";
        	this.textBoxToSend.Size = new System.Drawing.Size(132, 22);
        	this.textBoxToSend.TabIndex = 2;
        	this.textBoxToSend.Text = "ATR001#";
        	// 
        	// button1
        	// 
        	this.button1.Location = new System.Drawing.Point(179, 30);
        	this.button1.Margin = new System.Windows.Forms.Padding(4);
        	this.button1.Name = "button1";
        	this.button1.Size = new System.Drawing.Size(141, 28);
        	this.button1.TabIndex = 3;
        	this.button1.Text = "buttonTestSend";
        	this.button1.UseVisualStyleBackColor = true;
        	this.button1.Click += new System.EventHandler(this.test_button_Click);
        	// 
        	// timer1
        	// 
        	this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
        	// 
        	// buttonReadCurrentRecord
        	// 
        	this.buttonReadCurrentRecord.Location = new System.Drawing.Point(689, 81);
        	this.buttonReadCurrentRecord.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonReadCurrentRecord.Name = "buttonReadCurrentRecord";
        	this.buttonReadCurrentRecord.Size = new System.Drawing.Size(171, 28);
        	this.buttonReadCurrentRecord.TabIndex = 18;
        	this.buttonReadCurrentRecord.Text = "Read Current Rcord";
        	this.buttonReadCurrentRecord.UseVisualStyleBackColor = true;
        	this.buttonReadCurrentRecord.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonRead
        	// 
        	this.buttonRead.Location = new System.Drawing.Point(467, 81);
        	this.buttonRead.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonRead.Name = "buttonRead";
        	this.buttonRead.Size = new System.Drawing.Size(171, 28);
        	this.buttonRead.TabIndex = 20;
        	this.buttonRead.Text = "ATK001# READ";
        	this.buttonRead.UseVisualStyleBackColor = true;
        	this.buttonRead.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonPlus
        	// 
        	this.buttonPlus.Location = new System.Drawing.Point(467, 117);
        	this.buttonPlus.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonPlus.Name = "buttonPlus";
        	this.buttonPlus.Size = new System.Drawing.Size(171, 28);
        	this.buttonPlus.TabIndex = 21;
        	this.buttonPlus.Text = "ATK002# \'+\'";
        	this.buttonPlus.UseVisualStyleBackColor = true;
        	this.buttonPlus.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonMenu
        	// 
        	this.buttonMenu.Location = new System.Drawing.Point(467, 153);
        	this.buttonMenu.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonMenu.Name = "buttonMenu";
        	this.buttonMenu.Size = new System.Drawing.Size(171, 28);
        	this.buttonMenu.TabIndex = 22;
        	this.buttonMenu.Text = "ATK003# MENU";
        	this.buttonMenu.UseVisualStyleBackColor = true;
        	this.buttonMenu.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonMinus
        	// 
        	this.buttonMinus.Location = new System.Drawing.Point(467, 189);
        	this.buttonMinus.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonMinus.Name = "buttonMinus";
        	this.buttonMinus.Size = new System.Drawing.Size(171, 28);
        	this.buttonMinus.TabIndex = 23;
        	this.buttonMinus.Text = "ATK004# \'-\'";
        	this.buttonMinus.UseVisualStyleBackColor = true;
        	this.buttonMinus.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonArea
        	// 
        	this.buttonArea.Location = new System.Drawing.Point(467, 225);
        	this.buttonArea.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonArea.Name = "buttonArea";
        	this.buttonArea.Size = new System.Drawing.Size(171, 28);
        	this.buttonArea.TabIndex = 24;
        	this.buttonArea.Text = "ATK005# AREA";
        	this.buttonArea.UseVisualStyleBackColor = true;
        	this.buttonArea.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonLevelBubble
        	// 
        	this.buttonLevelBubble.Location = new System.Drawing.Point(467, 261);
        	this.buttonLevelBubble.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonLevelBubble.Name = "buttonLevelBubble";
        	this.buttonLevelBubble.Size = new System.Drawing.Size(189, 28);
        	this.buttonLevelBubble.TabIndex = 25;
        	this.buttonLevelBubble.Text = "ATK006# LEVEL BUBBLE";
        	this.buttonLevelBubble.UseVisualStyleBackColor = true;
        	this.buttonLevelBubble.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonPythegoras
        	// 
        	this.buttonPythegoras.Location = new System.Drawing.Point(467, 296);
        	this.buttonPythegoras.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonPythegoras.Name = "buttonPythegoras";
        	this.buttonPythegoras.Size = new System.Drawing.Size(189, 28);
        	this.buttonPythegoras.TabIndex = 26;
        	this.buttonPythegoras.Text = "ATK007# PYTHAGORAS";
        	this.buttonPythegoras.UseVisualStyleBackColor = true;
        	this.buttonPythegoras.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonTimer
        	// 
        	this.buttonTimer.Location = new System.Drawing.Point(467, 332);
        	this.buttonTimer.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonTimer.Name = "buttonTimer";
        	this.buttonTimer.Size = new System.Drawing.Size(171, 28);
        	this.buttonTimer.TabIndex = 27;
        	this.buttonTimer.Text = "ATK008# TIMER";
        	this.buttonTimer.UseVisualStyleBackColor = true;
        	this.buttonTimer.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonClearOff
        	// 
        	this.buttonClearOff.Location = new System.Drawing.Point(467, 368);
        	this.buttonClearOff.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonClearOff.Name = "buttonClearOff";
        	this.buttonClearOff.Size = new System.Drawing.Size(171, 28);
        	this.buttonClearOff.TabIndex = 28;
        	this.buttonClearOff.Text = "ATK009# CLEAR OFF";
        	this.buttonClearOff.UseVisualStyleBackColor = true;
        	this.buttonClearOff.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// buttonSave
        	// 
        	this.buttonSave.Location = new System.Drawing.Point(467, 404);
        	this.buttonSave.Margin = new System.Windows.Forms.Padding(4);
        	this.buttonSave.Name = "buttonSave";
        	this.buttonSave.Size = new System.Drawing.Size(171, 28);
        	this.buttonSave.TabIndex = 29;
        	this.buttonSave.Text = "ATK00A# SAVE";
        	this.buttonSave.UseVisualStyleBackColor = true;
        	this.buttonSave.Click += new System.EventHandler(this.buttonsMachineDriving_Click);
        	// 
        	// labelValue
        	// 
        	this.labelValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
        	this.labelValue.Location = new System.Drawing.Point(689, 123);
        	this.labelValue.Name = "labelValue";
        	this.labelValue.Size = new System.Drawing.Size(171, 58);
        	this.labelValue.TabIndex = 30;
        	this.labelValue.Text = "labelValue";
        	// 
        	// MainForm1
        	// 
        	this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
        	this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        	this.ClientSize = new System.Drawing.Size(882, 582);
        	this.Controls.Add(this.labelValue);
        	this.Controls.Add(this.buttonSave);
        	this.Controls.Add(this.buttonClearOff);
        	this.Controls.Add(this.buttonTimer);
        	this.Controls.Add(this.buttonPythegoras);
        	this.Controls.Add(this.buttonLevelBubble);
        	this.Controls.Add(this.buttonArea);
        	this.Controls.Add(this.buttonMinus);
        	this.Controls.Add(this.buttonMenu);
        	this.Controls.Add(this.buttonPlus);
        	this.Controls.Add(this.buttonRead);
        	this.Controls.Add(this.buttonReadCurrentRecord);
        	this.Controls.Add(this.button1);
        	this.Controls.Add(this.textBoxToSend);
        	this.Controls.Add(this.textBoxLog);
        	this.Controls.Add(this.menuStrip1);
        	this.MainMenuStrip = this.menuStrip1;
        	this.Margin = new System.Windows.Forms.Padding(4);
        	this.Name = "MainForm1";
        	this.Text = "SNDWAY_SW-T4S";
        	this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainForm1_KeyDown);
        	this.menuStrip1.ResumeLayout(false);
        	this.menuStrip1.PerformLayout();
        	this.ResumeLayout(false);
        	this.PerformLayout();
        }
        private System.Windows.Forms.Label labelValue;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonClearOff;
        private System.Windows.Forms.Button buttonTimer;
        private System.Windows.Forms.Button buttonPythegoras;
        private System.Windows.Forms.Button buttonLevelBubble;
        private System.Windows.Forms.Button buttonArea;
        private System.Windows.Forms.Button buttonMinus;
        private System.Windows.Forms.Button buttonMenu;
        private System.Windows.Forms.Button buttonPlus;
        private System.Windows.Forms.Button buttonRead;

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem configToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem portToolStripMenuItem;
        private System.Windows.Forms.ToolStripComboBox toolStripComboBox1;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.IO.Ports.SerialPort serialPort1;
        public System.Windows.Forms.TextBox textBoxLog;
        private System.Windows.Forms.ToolStripMenuItem openPortToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closePortToolStripMenuItem;
        private System.Windows.Forms.TextBox textBoxToSend;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button buttonReadCurrentRecord;
    }
}

