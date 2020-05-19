namespace Interface {
  partial class MainWindow {
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
      this.Decrypt_Button = new System.Windows.Forms.Button();
      this.Encrypt_Button = new System.Windows.Forms.Button();
      this.label1 = new System.Windows.Forms.Label();
      this.Decrypted_String = new System.Windows.Forms.TextBox();
      this.Encrypted_String = new System.Windows.Forms.TextBox();
      this.label2 = new System.Windows.Forms.Label();
      this.SuspendLayout();
      // 
      // Decrypt_Button
      // 
      this.Decrypt_Button.Location = new System.Drawing.Point(148, 60);
      this.Decrypt_Button.Name = "Decrypt_Button";
      this.Decrypt_Button.Size = new System.Drawing.Size(46, 23);
      this.Decrypt_Button.TabIndex = 0;
      this.Decrypt_Button.Text = "↑";
      this.Decrypt_Button.UseVisualStyleBackColor = true;
      this.Decrypt_Button.Click += new System.EventHandler(this.Decrypt_Button_Click);
      // 
      // Encrypt_Button
      // 
      this.Encrypt_Button.Location = new System.Drawing.Point(205, 60);
      this.Encrypt_Button.Name = "Encrypt_Button";
      this.Encrypt_Button.Size = new System.Drawing.Size(46, 23);
      this.Encrypt_Button.TabIndex = 1;
      this.Encrypt_Button.Text = "↓";
      this.Encrypt_Button.UseVisualStyleBackColor = true;
      this.Encrypt_Button.Click += new System.EventHandler(this.Encrypt_Button_Click);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(15, 30);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(61, 13);
      this.label1.TabIndex = 2;
      this.label1.Text = "Base String";
      // 
      // Decrypted_String
      // 
      this.Decrypted_String.Location = new System.Drawing.Point(92, 26);
      this.Decrypted_String.Name = "Decrypted_String";
      this.Decrypted_String.Size = new System.Drawing.Size(216, 20);
      this.Decrypted_String.TabIndex = 4;
      // 
      // Encrypted_String
      // 
      this.Encrypted_String.Location = new System.Drawing.Point(92, 97);
      this.Encrypted_String.Name = "Encrypted_String";
      this.Encrypted_String.Size = new System.Drawing.Size(216, 20);
      this.Encrypted_String.TabIndex = 5;
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(21, 101);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(55, 13);
      this.label2.TabIndex = 6;
      this.label2.Text = "Encrypted";
      // 
      // MainWindow
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(346, 148);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.Encrypted_String);
      this.Controls.Add(this.Decrypted_String);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.Encrypt_Button);
      this.Controls.Add(this.Decrypt_Button);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
      this.MaximizeBox = false;
      this.Name = "MainWindow";
      this.Text = "String Encrypting";
      this.Load += new System.EventHandler(this.Form1_Load);
      this.ResumeLayout(false);
      this.PerformLayout();

    }

        #endregion

        private System.Windows.Forms.Button Decrypt_Button;
        private System.Windows.Forms.Button Encrypt_Button;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Decrypted_String;
        private System.Windows.Forms.TextBox Encrypted_String;
        private System.Windows.Forms.Label label2;
    }
}

