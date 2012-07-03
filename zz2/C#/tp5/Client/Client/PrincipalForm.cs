using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Security.Cryptography;
using Client.Serialization;
using Client.ServeurChat;

namespace Client
{
    public partial class PrincipalForm : Form
    {
        private DSAParameters securitykey;
        private ServeurChatSoapClient client;
        private DSACryptoServiceProvider crypto;
        private string session;
        private Boolean connected;

        /// <summary>
        /// Constructeur par defaut
        /// </summary>
        public PrincipalForm()
        {
            InitializeComponent();
            SaveForm param_fenetre = Serializer.DeserialiserFenetre();
            if (param_fenetre != null)
            {
                this.Size = new System.Drawing.Size(param_fenetre.Weightform, param_fenetre.Heightform);
                this.splitContainer1.SplitterDistance = param_fenetre.Splitterdistance;
                this.Location = new System.Drawing.Point(param_fenetre.LocalisationX, param_fenetre.LocalisationY);
            }

            //initialisation de liaison avec le service 
            client = new ServeurChat.ServeurChatSoapClient();
            //generation des clé pour la session qui va etre lance
            crypto = new DSACryptoServiceProvider();
            securitykey = crypto.ExportParameters(false);
            connected = false;
        }

        /// <summary>
        /// Gestion de la fermeture du programmme
        /// </summary>
        private void PrincipalForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            Serializer.SerialiserFenetre(this.Size.Width, this.Size.Height, this.splitContainer1.SplitterDistance, this.Location.X, this.Location.Y);
        }

        /// <summary>
        /// Gere l'affichage des messages dans le controlleur treeview
        /// </summary>
        /// <param name="inload">Tableau de messages a afficher</param>
        private void LoadMessages(ServeurChat.Message[] inload)
        {
            treeView1.Nodes.Clear();
            if (inload != null)
            {
                foreach (ServeurChat.Message m in inload)
                {
                    TreeNode n = new TreeNode(m.Auteur + " " + m.Creation.ToString() + "  " + m.Text);
                    n.Tag = m;
                    treeView1.Nodes.Add(n);
                }
            }
        }

        /// <summary>
        /// Gestion de la deconnexion dans le menu
        /// </summary>
        private void logOutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //on supprime les affichages de la derniere session
            treeView1.Nodes.Clear();
            messageView1.ClearView();
            toolStripStatusLabel1.Text = "Vous etes en mode non-connecté(e)";
            connected = false;
        }


        /// <summary>
        /// Gere la creation d'un compte
        /// </summary>
        private void creerUnCompteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (connected == false) //si le client n'est pas déjà connecté(e) 
            {
                RegisterForm register = new RegisterForm(this);
                register.Show();
            }
            else
            {
                MessageBox.Show("Vous etes deja connecte(e)", "Attention");
            }
        }

        /// <summary>
        /// Gere le bouton fermer dans le menu
        /// </summary>
        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Gere le bouton de connection
        /// </summary>
        private void logInToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (connected == false)
            {
                ConnectionForm connection = new ConnectionForm(this);
                connection.Show();
            }
            else
            {
                MessageBox.Show("Vous etes deja connecte(e)", "Attention");
            }
        }


        /// <summary>
        /// Gere la recuperation et l'affichage des messages non lues
        /// </summary>
        private void consulterToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            try
            {
                if (connected == true)
                {
                    ASCIIEncoding encoding = new ASCIIEncoding();
                    byte[] nicksigned = crypto.SignData(encoding.GetBytes(session)); //on signe le login en cours
                    this.Text = "Messages non-lus";
                    LoadMessages(client.ReceiveMessageNonRead(session, nicksigned)); //affichage des messages
                }
                else
                {
                    MessageBox.Show("Vous devez etre connecte(e) pour consulter", "Attention");
                }
            }
            catch (System.ServiceModel.EndpointNotFoundException)
            {
                MessageBox.Show("Erreur de connexion,Verifiez votre connexion ", "Error");
            }
        }

        /// <summary>
        /// Gere la recuperation et l'affichage de tous les messages
        /// </summary>
        private void consulterTousLesMessagesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if (connected == true)
                {
                    ASCIIEncoding encoding = new ASCIIEncoding();
                    byte[] nicksigned = crypto.SignData(encoding.GetBytes(session)); //on crypte le login en cours
                    this.Text = "Tous les messages ";
                    LoadMessages(client.ReceiveAllMessage(session, nicksigned));
                }
                else
                {
                    MessageBox.Show("Vous devez etre connecte(e) pour consulter", "Attention");
                }
            }
            catch (System.ServiceModel.EndpointNotFoundException)
            {
                MessageBox.Show("Erreur de connexion,Verifiez votre connexion ", "Error");
            }
        }

        /// <summary>
        /// Gere la recuperation et l'affichage des messages privés
        /// </summary>
        private void consulterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if (connected == true)
                {

                    ASCIIEncoding encoding = new ASCIIEncoding();
                    byte[] nicksigned = crypto.SignData(encoding.GetBytes(session));
                    this.Text = "Tous les messages prives";
                    LoadMessages(client.ReceivePrivateMessage(session, nicksigned));
                }
                else
                {
                    MessageBox.Show("Vous devez etre connecte(e) pour consulter", "Attention");
                }
            }
            catch (System.ServiceModel.EndpointNotFoundException)
            {
                MessageBox.Show("Erreur de connexion,Verifiez votre connexion ", "Error");
            }
        }

        /// <summary>
        /// Methode qui permet d'afficher un message apres une selection dans le treeview
        /// </summary>
        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            messageView1.DisplayMessage((ServeurChat.Message)e.Node.Tag);
        }

        /// <summary>
        /// Gere la fenetre APropos
        /// </summary>
        private void aProposToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Enabled = false;
            AProposForm apropos = new AProposForm(this);
            apropos.Show();
        }

        /// <summary>
        /// Gere la fenetre d'envoi de messages
        /// </summary>
        private void buttonSendAMessage_Click(object sender, EventArgs e)
        {
            if (connected == true)
            {
                SendingForm sending = new SendingForm(this);
                sending.Show();
            }
            else
            {
                MessageBox.Show("Vous devez être connecté(e) pour envoyer un message", "Attention");
            } 
        }

        //proprietes de la classe
        public DSAParameters Securitykey
        {
            get { return securitykey; }
            set { securitykey = value; }
        }

        public ServeurChatSoapClient Client
        {
            get { return client; }
            set { client = value; }
        }

        public DSACryptoServiceProvider Crypto
        {
            get { return crypto; }
            set { crypto = value; }
        }

        public string Session
        {
            get { return session; }
            set
            {
                session = value;
                toolStripStatusLabel1.Text = value + " est connecte(e)";
                connected = true;
            }
        }

        private void changerDeLoginToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (connected == true)
            {
                ChangeNickForm changing = new ChangeNickForm(this);
                changing.Show();
            }
            else
            {
                MessageBox.Show("Vous devez être connecté(e) pour modifier le login", "Attention");
            } 
        }
    }
}
