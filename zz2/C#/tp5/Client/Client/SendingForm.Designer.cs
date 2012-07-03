namespace Client
{
    partial class SendingForm
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
            this.DesttextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.MessagetextBox = new System.Windows.Forms.TextBox();
            this.labelError = new System.Windows.Forms.Label();
            this.buttonSend = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(251, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Destinataire : (Laissez vide pour un message public)";
            // 
            // DesttextBox
            // 
            this.DesttextBox.Location = new System.Drawing.Point(15, 38);
            this.DesttextBox.Name = "DesttextBox";
            this.DesttextBox.Size = new System.Drawing.Size(248, 20);
            this.DesttextBox.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 78);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Texte:";
            // 
            // MessagetextBox
            // 
            this.MessagetextBox.Location = new System.Drawing.Point(15, 103);
            this.MessagetextBox.Multiline = true;
            this.MessagetextBox.Name = "MessagetextBox";
            this.MessagetextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.MessagetextBox.Size = new System.Drawing.Size(343, 294);
            this.MessagetextBox.TabIndex = 3;
            // 
            // labelError
            // 
            this.labelError.AutoSize = true;
            this.labelError.ForeColor = System.Drawing.Color.Red;
            this.labelError.Location = new System.Drawing.Point(12, 450);
            this.labelError.Name = "labelError";
            this.labelError.Size = new System.Drawing.Size(0, 13);
            this.labelError.TabIndex = 4;
            // 
            // buttonSend
            // 
            this.buttonSend.Location = new System.Drawing.Point(136, 403);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(95, 34);
            this.buttonSend.TabIndex = 5;
            this.buttonSend.Text = "Envoyer";
            this.buttonSend.UseVisualStyleBackColor = true;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // SendingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(370, 489);
            this.Controls.Add(this.buttonSend);
            this.Controls.Add(this.labelError);
            this.Controls.Add(this.MessagetextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.DesttextBox);
            this.Controls.Add(this.label1);
            this.Name = "SendingForm";
            this.Text = "Envoyer un message";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SendingForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox DesttextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox MessagetextBox;
        private System.Windows.Forms.Label labelError;
        private System.Windows.Forms.Button buttonSend;
    }
}