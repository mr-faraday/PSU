namespace SystemInfo {
  partial class MainWimdow {
    /// <summary>
    /// Обязательная переменная конструктора.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Освободить все используемые ресурсы.
    /// </summary>
    /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
    protected override void Dispose (bool disposing) {
      if (disposing && (components != null)) {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Код, автоматически созданный конструктором форм Windows

    /// <summary>
    /// Требуемый метод для поддержки конструктора — не изменяйте 
    /// содержимое этого метода с помощью редактора кода.
    /// </summary>
    private void InitializeComponent () {
      this.TabControl = new System.Windows.Forms.TabControl();
      this.TabSystemInfo = new System.Windows.Forms.TabPage();
      this.GPUs_driverVersion = new System.Windows.Forms.TextBox();
      this.GPUs_vramType = new System.Windows.Forms.TextBox();
      this.GPUs_vramSize = new System.Windows.Forms.TextBox();
      this.GPUs_architecture = new System.Windows.Forms.TextBox();
      this.GPUs_proccessor = new System.Windows.Forms.TextBox();
      this.GPUs_deviceId = new System.Windows.Forms.TextBox();
      this.GPUs_name = new System.Windows.Forms.TextBox();
      this.label17 = new System.Windows.Forms.Label();
      this.label16 = new System.Windows.Forms.Label();
      this.label15 = new System.Windows.Forms.Label();
      this.label14 = new System.Windows.Forms.Label();
      this.label13 = new System.Windows.Forms.Label();
      this.label12 = new System.Windows.Forms.Label();
      this.label11 = new System.Windows.Forms.Label();
      this.label6 = new System.Windows.Forms.Label();
      this.GPUs = new System.Windows.Forms.ListBox();
      this.cpuFrequency = new System.Windows.Forms.TextBox();
      this.cpuType = new System.Windows.Forms.TextBox();
      this.screenResolution = new System.Windows.Forms.TextBox();
      this.vramSize = new System.Windows.Forms.TextBox();
      this.ramSize = new System.Windows.Forms.TextBox();
      this.biosDate = new System.Windows.Forms.TextBox();
      this.userName = new System.Windows.Forms.TextBox();
      this.machineName = new System.Windows.Forms.TextBox();
      this.label10 = new System.Windows.Forms.Label();
      this.label9 = new System.Windows.Forms.Label();
      this.label7 = new System.Windows.Forms.Label();
      this.label5 = new System.Windows.Forms.Label();
      this.label4 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label1 = new System.Windows.Forms.Label();
      this.TabProccesses = new System.Windows.Forms.TabPage();
      this.Processes = new System.Windows.Forms.ListView();
      this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
      this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
      this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
      this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
      this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
      this.processesRefresh = new System.Windows.Forms.Button();
      this.TabControl.SuspendLayout();
      this.TabSystemInfo.SuspendLayout();
      this.TabProccesses.SuspendLayout();
      this.SuspendLayout();
      // 
      // TabControl
      // 
      this.TabControl.Controls.Add(this.TabSystemInfo);
      this.TabControl.Controls.Add(this.TabProccesses);
      this.TabControl.Location = new System.Drawing.Point(0, 0);
      this.TabControl.Name = "TabControl";
      this.TabControl.SelectedIndex = 0;
      this.TabControl.Size = new System.Drawing.Size(463, 510);
      this.TabControl.TabIndex = 0;
      // 
      // TabSystemInfo
      // 
      this.TabSystemInfo.Controls.Add(this.GPUs_driverVersion);
      this.TabSystemInfo.Controls.Add(this.GPUs_vramType);
      this.TabSystemInfo.Controls.Add(this.GPUs_vramSize);
      this.TabSystemInfo.Controls.Add(this.GPUs_architecture);
      this.TabSystemInfo.Controls.Add(this.GPUs_proccessor);
      this.TabSystemInfo.Controls.Add(this.GPUs_deviceId);
      this.TabSystemInfo.Controls.Add(this.GPUs_name);
      this.TabSystemInfo.Controls.Add(this.label17);
      this.TabSystemInfo.Controls.Add(this.label16);
      this.TabSystemInfo.Controls.Add(this.label15);
      this.TabSystemInfo.Controls.Add(this.label14);
      this.TabSystemInfo.Controls.Add(this.label13);
      this.TabSystemInfo.Controls.Add(this.label12);
      this.TabSystemInfo.Controls.Add(this.label11);
      this.TabSystemInfo.Controls.Add(this.label6);
      this.TabSystemInfo.Controls.Add(this.GPUs);
      this.TabSystemInfo.Controls.Add(this.cpuFrequency);
      this.TabSystemInfo.Controls.Add(this.cpuType);
      this.TabSystemInfo.Controls.Add(this.screenResolution);
      this.TabSystemInfo.Controls.Add(this.vramSize);
      this.TabSystemInfo.Controls.Add(this.ramSize);
      this.TabSystemInfo.Controls.Add(this.biosDate);
      this.TabSystemInfo.Controls.Add(this.userName);
      this.TabSystemInfo.Controls.Add(this.machineName);
      this.TabSystemInfo.Controls.Add(this.label10);
      this.TabSystemInfo.Controls.Add(this.label9);
      this.TabSystemInfo.Controls.Add(this.label7);
      this.TabSystemInfo.Controls.Add(this.label5);
      this.TabSystemInfo.Controls.Add(this.label4);
      this.TabSystemInfo.Controls.Add(this.label3);
      this.TabSystemInfo.Controls.Add(this.label2);
      this.TabSystemInfo.Controls.Add(this.label1);
      this.TabSystemInfo.Location = new System.Drawing.Point(4, 22);
      this.TabSystemInfo.Name = "TabSystemInfo";
      this.TabSystemInfo.Padding = new System.Windows.Forms.Padding(3);
      this.TabSystemInfo.Size = new System.Drawing.Size(455, 484);
      this.TabSystemInfo.TabIndex = 0;
      this.TabSystemInfo.Text = "Информация о компьютере";
      this.TabSystemInfo.UseVisualStyleBackColor = true;
      // 
      // GPUs_driverVersion
      // 
      this.GPUs_driverVersion.Location = new System.Drawing.Point(291, 445);
      this.GPUs_driverVersion.Name = "GPUs_driverVersion";
      this.GPUs_driverVersion.ReadOnly = true;
      this.GPUs_driverVersion.Size = new System.Drawing.Size(136, 20);
      this.GPUs_driverVersion.TabIndex = 35;
      // 
      // GPUs_vramType
      // 
      this.GPUs_vramType.Location = new System.Drawing.Point(291, 421);
      this.GPUs_vramType.Name = "GPUs_vramType";
      this.GPUs_vramType.ReadOnly = true;
      this.GPUs_vramType.Size = new System.Drawing.Size(136, 20);
      this.GPUs_vramType.TabIndex = 34;
      // 
      // GPUs_vramSize
      // 
      this.GPUs_vramSize.Location = new System.Drawing.Point(291, 397);
      this.GPUs_vramSize.Name = "GPUs_vramSize";
      this.GPUs_vramSize.ReadOnly = true;
      this.GPUs_vramSize.Size = new System.Drawing.Size(136, 20);
      this.GPUs_vramSize.TabIndex = 33;
      // 
      // GPUs_architecture
      // 
      this.GPUs_architecture.Location = new System.Drawing.Point(291, 373);
      this.GPUs_architecture.Name = "GPUs_architecture";
      this.GPUs_architecture.ReadOnly = true;
      this.GPUs_architecture.Size = new System.Drawing.Size(136, 20);
      this.GPUs_architecture.TabIndex = 32;
      // 
      // GPUs_proccessor
      // 
      this.GPUs_proccessor.Location = new System.Drawing.Point(291, 349);
      this.GPUs_proccessor.Name = "GPUs_proccessor";
      this.GPUs_proccessor.ReadOnly = true;
      this.GPUs_proccessor.Size = new System.Drawing.Size(136, 20);
      this.GPUs_proccessor.TabIndex = 31;
      // 
      // GPUs_deviceId
      // 
      this.GPUs_deviceId.Location = new System.Drawing.Point(291, 325);
      this.GPUs_deviceId.Name = "GPUs_deviceId";
      this.GPUs_deviceId.ReadOnly = true;
      this.GPUs_deviceId.Size = new System.Drawing.Size(136, 20);
      this.GPUs_deviceId.TabIndex = 30;
      // 
      // GPUs_name
      // 
      this.GPUs_name.Location = new System.Drawing.Point(291, 301);
      this.GPUs_name.Name = "GPUs_name";
      this.GPUs_name.ReadOnly = true;
      this.GPUs_name.Size = new System.Drawing.Size(136, 20);
      this.GPUs_name.TabIndex = 29;
      // 
      // label17
      // 
      this.label17.AutoSize = true;
      this.label17.Location = new System.Drawing.Point(191, 377);
      this.label17.Name = "label17";
      this.label17.Size = new System.Drawing.Size(70, 13);
      this.label17.TabIndex = 28;
      this.label17.Text = "Архитектура";
      // 
      // label16
      // 
      this.label16.AutoSize = true;
      this.label16.Location = new System.Drawing.Point(191, 425);
      this.label16.Name = "label16";
      this.label16.Size = new System.Drawing.Size(66, 13);
      this.label16.TabIndex = 27;
      this.label16.Text = "Тип памяти";
      // 
      // label15
      // 
      this.label15.AutoSize = true;
      this.label15.Location = new System.Drawing.Point(191, 449);
      this.label15.Name = "label15";
      this.label15.Size = new System.Drawing.Size(95, 13);
      this.label15.TabIndex = 26;
      this.label15.Text = "Версия драйвера";
      // 
      // label14
      // 
      this.label14.AutoSize = true;
      this.label14.Location = new System.Drawing.Point(191, 353);
      this.label14.Name = "label14";
      this.label14.Size = new System.Drawing.Size(63, 13);
      this.label14.TabIndex = 25;
      this.label14.Text = "Процессор";
      // 
      // label13
      // 
      this.label13.AutoSize = true;
      this.label13.Location = new System.Drawing.Point(191, 401);
      this.label13.Name = "label13";
      this.label13.Size = new System.Drawing.Size(82, 13);
      this.label13.TabIndex = 24;
      this.label13.Text = "Объём памяти";
      // 
      // label12
      // 
      this.label12.AutoSize = true;
      this.label12.Location = new System.Drawing.Point(191, 329);
      this.label12.Name = "label12";
      this.label12.Size = new System.Drawing.Size(52, 13);
      this.label12.TabIndex = 23;
      this.label12.Text = "DeviceID";
      // 
      // label11
      // 
      this.label11.AutoSize = true;
      this.label11.Location = new System.Drawing.Point(191, 305);
      this.label11.Name = "label11";
      this.label11.Size = new System.Drawing.Size(46, 13);
      this.label11.TabIndex = 22;
      this.label11.Text = "Модель";
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(23, 289);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(81, 13);
      this.label6.TabIndex = 21;
      this.label6.Text = "Видеодаптеры";
      // 
      // GPUs
      // 
      this.GPUs.DisplayMember = "Name";
      this.GPUs.FormattingEnabled = true;
      this.GPUs.Location = new System.Drawing.Point(26, 308);
      this.GPUs.Name = "GPUs";
      this.GPUs.Size = new System.Drawing.Size(158, 160);
      this.GPUs.TabIndex = 20;
      this.GPUs.SelectedIndexChanged += new System.EventHandler(this.GPUs_SelectedIndexChanged);
      // 
      // cpuFrequency
      // 
      this.cpuFrequency.Location = new System.Drawing.Point(195, 211);
      this.cpuFrequency.Name = "cpuFrequency";
      this.cpuFrequency.ReadOnly = true;
      this.cpuFrequency.Size = new System.Drawing.Size(232, 20);
      this.cpuFrequency.TabIndex = 19;
      // 
      // cpuType
      // 
      this.cpuType.Location = new System.Drawing.Point(195, 182);
      this.cpuType.Name = "cpuType";
      this.cpuType.ReadOnly = true;
      this.cpuType.Size = new System.Drawing.Size(232, 20);
      this.cpuType.TabIndex = 18;
      // 
      // screenResolution
      // 
      this.screenResolution.Location = new System.Drawing.Point(195, 257);
      this.screenResolution.Name = "screenResolution";
      this.screenResolution.ReadOnly = true;
      this.screenResolution.Size = new System.Drawing.Size(232, 20);
      this.screenResolution.TabIndex = 16;
      // 
      // vramSize
      // 
      this.vramSize.Location = new System.Drawing.Point(195, 134);
      this.vramSize.Name = "vramSize";
      this.vramSize.ReadOnly = true;
      this.vramSize.Size = new System.Drawing.Size(232, 20);
      this.vramSize.TabIndex = 14;
      // 
      // ramSize
      // 
      this.ramSize.Location = new System.Drawing.Point(195, 105);
      this.ramSize.Name = "ramSize";
      this.ramSize.ReadOnly = true;
      this.ramSize.Size = new System.Drawing.Size(232, 20);
      this.ramSize.TabIndex = 13;
      // 
      // biosDate
      // 
      this.biosDate.Location = new System.Drawing.Point(195, 76);
      this.biosDate.Name = "biosDate";
      this.biosDate.ReadOnly = true;
      this.biosDate.Size = new System.Drawing.Size(232, 20);
      this.biosDate.TabIndex = 12;
      // 
      // userName
      // 
      this.userName.Location = new System.Drawing.Point(195, 47);
      this.userName.Name = "userName";
      this.userName.ReadOnly = true;
      this.userName.Size = new System.Drawing.Size(232, 20);
      this.userName.TabIndex = 11;
      // 
      // machineName
      // 
      this.machineName.Location = new System.Drawing.Point(195, 18);
      this.machineName.Name = "machineName";
      this.machineName.ReadOnly = true;
      this.machineName.Size = new System.Drawing.Size(232, 20);
      this.machineName.TabIndex = 10;
      // 
      // label10
      // 
      this.label10.AutoSize = true;
      this.label10.Location = new System.Drawing.Point(23, 215);
      this.label10.Name = "label10";
      this.label10.Size = new System.Drawing.Size(160, 13);
      this.label10.TabIndex = 9;
      this.label10.Text = "Тактовая частота процессора";
      // 
      // label9
      // 
      this.label9.AutoSize = true;
      this.label9.Location = new System.Drawing.Point(23, 186);
      this.label9.Name = "label9";
      this.label9.Size = new System.Drawing.Size(89, 13);
      this.label9.TabIndex = 8;
      this.label9.Text = "Тип процессора";
      // 
      // label7
      // 
      this.label7.AutoSize = true;
      this.label7.Location = new System.Drawing.Point(23, 261);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(109, 13);
      this.label7.TabIndex = 6;
      this.label7.Text = "Разрешение экрана";
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(23, 138);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(144, 13);
      this.label5.TabIndex = 4;
      this.label5.Text = "Виртуальная память (байт)";
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(23, 109);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(146, 13);
      this.label4.TabIndex = 3;
      this.label4.Text = "Оперативная память (байт)";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(23, 80);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(61, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Дата BIOS";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(23, 51);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(103, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Имя пользователя";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(23, 22);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(95, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Имя компьютера";
      // 
      // TabProccesses
      // 
      this.TabProccesses.Controls.Add(this.processesRefresh);
      this.TabProccesses.Controls.Add(this.Processes);
      this.TabProccesses.Location = new System.Drawing.Point(4, 22);
      this.TabProccesses.Name = "TabProccesses";
      this.TabProccesses.Padding = new System.Windows.Forms.Padding(3);
      this.TabProccesses.Size = new System.Drawing.Size(455, 484);
      this.TabProccesses.TabIndex = 1;
      this.TabProccesses.Text = "Информация о запущенных процессах Windows";
      this.TabProccesses.UseVisualStyleBackColor = true;
      // 
      // Processes
      // 
      this.Processes.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2,
            this.columnHeader3,
            this.columnHeader5,
            this.columnHeader4});
      this.Processes.FullRowSelect = true;
      this.Processes.GridLines = true;
      this.Processes.HideSelection = false;
      this.Processes.Location = new System.Drawing.Point(0, 36);
      this.Processes.Name = "Processes";
      this.Processes.Size = new System.Drawing.Size(455, 448);
      this.Processes.TabIndex = 0;
      this.Processes.UseCompatibleStateImageBehavior = false;
      this.Processes.View = System.Windows.Forms.View.Details;
      // 
      // columnHeader1
      // 
      this.columnHeader1.Text = "ID";
      this.columnHeader1.Width = 44;
      // 
      // columnHeader2
      // 
      this.columnHeader2.Text = "Имя процесса";
      this.columnHeader2.Width = 120;
      // 
      // columnHeader3
      // 
      this.columnHeader3.Text = "Название окна";
      this.columnHeader3.Width = 120;
      // 
      // columnHeader5
      // 
      this.columnHeader5.Text = "Память";
      this.columnHeader5.Width = 70;
      // 
      // columnHeader4
      // 
      this.columnHeader4.Text = "Приоретет";
      this.columnHeader4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
      this.columnHeader4.Width = 67;
      // 
      // processesRefresh
      // 
      this.processesRefresh.Location = new System.Drawing.Point(368, 7);
      this.processesRefresh.Name = "processesRefresh";
      this.processesRefresh.Size = new System.Drawing.Size(75, 23);
      this.processesRefresh.TabIndex = 1;
      this.processesRefresh.Text = "Обновить";
      this.processesRefresh.UseVisualStyleBackColor = true;
      this.processesRefresh.Click += new System.EventHandler(this.processesRefresh_Click);
      // 
      // MainWimdow
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(459, 510);
      this.Controls.Add(this.TabControl);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
      this.MaximizeBox = false;
      this.Name = "MainWimdow";
      this.Text = "Информация о компьютере";
      this.TabControl.ResumeLayout(false);
      this.TabSystemInfo.ResumeLayout(false);
      this.TabSystemInfo.PerformLayout();
      this.TabProccesses.ResumeLayout(false);
      this.ResumeLayout(false);

    }

        #endregion

        private System.Windows.Forms.TabControl TabControl;
        private System.Windows.Forms.TabPage TabSystemInfo;
        private System.Windows.Forms.TabPage TabProccesses;
    private System.Windows.Forms.TextBox cpuFrequency;
    private System.Windows.Forms.TextBox cpuType;
    private System.Windows.Forms.TextBox screenResolution;
    private System.Windows.Forms.TextBox vramSize;
    private System.Windows.Forms.TextBox ramSize;
    private System.Windows.Forms.TextBox biosDate;
    private System.Windows.Forms.TextBox userName;
    private System.Windows.Forms.TextBox machineName;
    private System.Windows.Forms.Label label10;
    private System.Windows.Forms.Label label9;
    private System.Windows.Forms.Label label7;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.ListBox GPUs;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.Label label11;
    private System.Windows.Forms.Label label12;
    private System.Windows.Forms.Label label13;
    private System.Windows.Forms.Label label14;
    private System.Windows.Forms.Label label15;
    private System.Windows.Forms.Label label16;
    private System.Windows.Forms.TextBox GPUs_driverVersion;
    private System.Windows.Forms.TextBox GPUs_vramType;
    private System.Windows.Forms.TextBox GPUs_vramSize;
    private System.Windows.Forms.TextBox GPUs_architecture;
    private System.Windows.Forms.TextBox GPUs_proccessor;
    private System.Windows.Forms.TextBox GPUs_deviceId;
    private System.Windows.Forms.TextBox GPUs_name;
    private System.Windows.Forms.Label label17;
    private System.Windows.Forms.ListView Processes;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.ColumnHeader columnHeader5;
    private System.Windows.Forms.Button processesRefresh;
  }
}

