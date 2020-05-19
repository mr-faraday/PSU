using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Interface {
  public partial class MainWindow : Form {
    public MainWindow () {
      InitializeComponent();
    }

    private void Form1_Load (object sender, EventArgs e) {}

    private void Encrypt_Button_Click (object sender, EventArgs e) {
      StringBuilder encryptedStr = new StringBuilder();

      Program.encrypt(
        encryptedStr,
        Decrypted_String.Text.Length,
        Decrypted_String.Text
      );

      Encrypted_String.Text = encryptedStr.ToString();
    }

    private void Decrypt_Button_Click (object sender, EventArgs e) {
      StringBuilder encryptedStr = new StringBuilder();

      Program.encrypt(
        encryptedStr,
        Encrypted_String.Text.Length,
        Encrypted_String.Text
      );

      Decrypted_String.Text = encryptedStr.ToString();
    }
  }
}
