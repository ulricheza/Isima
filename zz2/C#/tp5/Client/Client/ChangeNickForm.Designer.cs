namespace Client
{
    partial class ChangeNickForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.newlogintextBox = new System.Windows.Forms.TextBox();
            this.changenickbutton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Nouveau Login";
            // 
            // newlogintextBox
            // 
            this.newlogintextBox.Location = new System.Drawing.Point(98, 6);
            this.newlogintextBox.Name = "newlogintextBox";
            this.newlogintextBox.Size = new System.Drawing.Size(184, 20);
            this.newlogintextBox.TabIndex = 1;
            // 
            // changenickbutton
            // 
            this.changenickbutton.Location = new System.Drawing.Point(98, 32);
            this.changenickbutton.Name = "changenickbutton";
            this.changenickbutton.Size = new System.Drawing.Size(102, 27);
            this.changenickbutton.TabIndex = 2;
            this.changenickbutton.Text = "Modifier!";
            this.changenickbutton.UseVisualStyleBackColor = true;
            this.changenickbutton.Click += new System.EventHandler(this.changenickbutton_Click);
            // 
            // ChangeNickForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(288, 71);
            this.Controls.Add(this.changenickbutton);
            this.Controls.Add(this.newlogintextBox);
            this.Controls.Add(this.label1);
            this.Name = "ChangeNickForm";
            this.Text = "Changer de login";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ChangeNickForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox newlogintextBox;
        private System.Windows.Forms.Button changenickbutton;
    }
}