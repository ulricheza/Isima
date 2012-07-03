namespace Client
{
    partial class PrincipalForm
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.logInToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.logOutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.changerDeLoginToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.messageriePubliqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.consulterToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.consulterTousLesMessagesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.messageriePersonelleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.consulterToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.creerUnCompteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aProposToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.messageView1 = new Client.MessageView();
            this.buttonSendAMessage = new System.Windows.Forms.Button();
            this.messageBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.messageBindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.messageBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.messageBindingSource1)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.messageriePubliqueToolStripMenuItem,
            this.messageriePersonelleToolStripMenuItem,
            this.creerUnCompteToolStripMenuItem,
            this.aProposToolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(593, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.logInToolStripMenuItem,
            this.logOutToolStripMenuItem,
            this.changerDeLoginToolStripMenuItem,
            this.closeToolStripMenuItem});
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(76, 20);
            this.fichierToolStripMenuItem.Text = "Connexion";
            // 
            // logInToolStripMenuItem
            // 
            this.logInToolStripMenuItem.Name = "logInToolStripMenuItem";
            this.logInToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.logInToolStripMenuItem.Text = "Connexion";
            this.logInToolStripMenuItem.Click += new System.EventHandler(this.logInToolStripMenuItem_Click);
            // 
            // logOutToolStripMenuItem
            // 
            this.logOutToolStripMenuItem.Name = "logOutToolStripMenuItem";
            this.logOutToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.logOutToolStripMenuItem.Text = "Deconnexion";
            this.logOutToolStripMenuItem.Click += new System.EventHandler(this.logOutToolStripMenuItem_Click);
            // 
            // changerDeLoginToolStripMenuItem
            // 
            this.changerDeLoginToolStripMenuItem.Name = "changerDeLoginToolStripMenuItem";
            this.changerDeLoginToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.changerDeLoginToolStripMenuItem.Text = "Changer le login du compte";
            this.changerDeLoginToolStripMenuItem.Click += new System.EventHandler(this.changerDeLoginToolStripMenuItem_Click);
            // 
            // closeToolStripMenuItem
            // 
            this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
            this.closeToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.closeToolStripMenuItem.Text = "Close";
            this.closeToolStripMenuItem.Click += new System.EventHandler(this.closeToolStripMenuItem_Click);
            // 
            // messageriePubliqueToolStripMenuItem
            // 
            this.messageriePubliqueToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.consulterToolStripMenuItem1,
            this.consulterTousLesMessagesToolStripMenuItem});
            this.messageriePubliqueToolStripMenuItem.Name = "messageriePubliqueToolStripMenuItem";
            this.messageriePubliqueToolStripMenuItem.Size = new System.Drawing.Size(128, 20);
            this.messageriePubliqueToolStripMenuItem.Text = "Messagerie Publique";
            // 
            // consulterToolStripMenuItem1
            // 
            this.consulterToolStripMenuItem1.Name = "consulterToolStripMenuItem1";
            this.consulterToolStripMenuItem1.Size = new System.Drawing.Size(222, 22);
            this.consulterToolStripMenuItem1.Text = "Consulter les non-lus";
            this.consulterToolStripMenuItem1.Click += new System.EventHandler(this.consulterToolStripMenuItem1_Click);
            // 
            // consulterTousLesMessagesToolStripMenuItem
            // 
            this.consulterTousLesMessagesToolStripMenuItem.Name = "consulterTousLesMessagesToolStripMenuItem";
            this.consulterTousLesMessagesToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.consulterTousLesMessagesToolStripMenuItem.Text = "Consulter tous les messages";
            this.consulterTousLesMessagesToolStripMenuItem.Click += new System.EventHandler(this.consulterTousLesMessagesToolStripMenuItem_Click);
            // 
            // messageriePersonelleToolStripMenuItem
            // 
            this.messageriePersonelleToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.consulterToolStripMenuItem});
            this.messageriePersonelleToolStripMenuItem.Name = "messageriePersonelleToolStripMenuItem";
            this.messageriePersonelleToolStripMenuItem.Size = new System.Drawing.Size(142, 20);
            this.messageriePersonelleToolStripMenuItem.Text = "Messagerie Personnelle";
            // 
            // consulterToolStripMenuItem
            // 
            this.consulterToolStripMenuItem.Name = "consulterToolStripMenuItem";
            this.consulterToolStripMenuItem.Size = new System.Drawing.Size(125, 22);
            this.consulterToolStripMenuItem.Text = "Consulter";
            this.consulterToolStripMenuItem.Click += new System.EventHandler(this.consulterToolStripMenuItem_Click);
            // 
            // creerUnCompteToolStripMenuItem
            // 
            this.creerUnCompteToolStripMenuItem.Name = "creerUnCompteToolStripMenuItem";
            this.creerUnCompteToolStripMenuItem.Size = new System.Drawing.Size(111, 20);
            this.creerUnCompteToolStripMenuItem.Text = "Creer un compte!";
            this.creerUnCompteToolStripMenuItem.Click += new System.EventHandler(this.creerUnCompteToolStripMenuItem_Click);
            // 
            // aProposToolStripMenuItem1
            // 
            this.aProposToolStripMenuItem1.Name = "aProposToolStripMenuItem1";
            this.aProposToolStripMenuItem1.Size = new System.Drawing.Size(67, 20);
            this.aProposToolStripMenuItem1.Text = "A Propos";
            this.aProposToolStripMenuItem1.Click += new System.EventHandler(this.aProposToolStripMenuItem1_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 455);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(593, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(199, 17);
            this.toolStripStatusLabel1.Text = "Vous etes en mode non-connecté(e)";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 24);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.treeView1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.messageView1);
            this.splitContainer1.Panel2.Controls.Add(this.buttonSendAMessage);
            this.splitContainer1.Size = new System.Drawing.Size(593, 431);
            this.splitContainer1.SplitterDistance = 216;
            this.splitContainer1.TabIndex = 2;
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView1.Location = new System.Drawing.Point(0, 0);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(216, 431);
            this.treeView1.TabIndex = 0;
            this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
            // 
            // messageView1
            // 
            this.messageView1.Location = new System.Drawing.Point(23, 3);
            this.messageView1.Name = "messageView1";
            this.messageView1.Size = new System.Drawing.Size(308, 335);
            this.messageView1.TabIndex = 2;
            // 
            // buttonSendAMessage
            // 
            this.buttonSendAMessage.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonSendAMessage.Location = new System.Drawing.Point(126, 344);
            this.buttonSendAMessage.Name = "buttonSendAMessage";
            this.buttonSendAMessage.Size = new System.Drawing.Size(153, 67);
            this.buttonSendAMessage.TabIndex = 1;
            this.buttonSendAMessage.Text = "Créer un message";
            this.buttonSendAMessage.UseVisualStyleBackColor = true;
            this.buttonSendAMessage.Click += new System.EventHandler(this.buttonSendAMessage_Click);
            // 
            // messageBindingSource
            // 
            this.messageBindingSource.DataSource = typeof(Client.ServeurChat.Message);
            // 
            // messageBindingSource1
            // 
            this.messageBindingSource1.DataSource = typeof(Client.ServeurChat.Message);
            // 
            // PrincipalForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(593, 477);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "PrincipalForm";
            this.Text = "Client To Chat v1.0";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PrincipalForm_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.messageBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.messageBindingSource1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem logInToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem logOutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem messageriePersonelleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem consulterToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aProposToolStripMenuItem1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TreeView treeView1;
        private System.Windows.Forms.BindingSource messageBindingSource;
        private System.Windows.Forms.BindingSource messageBindingSource1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.Button buttonSendAMessage;
        private MessageView messageView1;
        private System.Windows.Forms.ToolStripMenuItem creerUnCompteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem messageriePubliqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem consulterToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem consulterTousLesMessagesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem changerDeLoginToolStripMenuItem;

    }
}

