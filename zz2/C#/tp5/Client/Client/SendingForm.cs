using System;
using System.Text;
using System.Windows.Forms;
using Client.ServeurChat;
using System.Security.Cryptography;

namespace Client
{
    /// <summary>
    /// Fenetre d'envoie de message
    /// </summary>
    public partial class SendingForm : Form
    {
        private PrincipalForm main;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="main">Fenetre principale</param>
        public SendingForm(PrincipalForm main)
        {
            InitializeComponent();
            this.main = main;
            main.Enabled = false;
        }


        /// <summary>
        /// Gere la bouton Envoyer
        /// </summary>
        private void buttonSend_Click(object sender, EventArgs e)
        {
            ASCIIEncoding encoding = new ASCIIEncoding();
            string nick = main.Session;
            string dest = DesttextBox.Text;
            string message = MessagetextBox.Text;
            byte[] messagesigned = main.Crypto.SignData(encoding.GetBytes(message));

            try
            {
                if (dest == "") //message public 
                {
                    if (main.Client.SendMessage(nick, message, messagesigned) == true)
                    {
                        MessageBox.Show("Message envoyé avec succés ", "Success");
                        this.Close();
                    }
                    else
                    {
                        labelError.Text = "Erreur d'envoi";
                    }
                }
                else //message prive
                {
                    if (main.Client.SendPrivateMessage(nick, dest, message, messagesigned) == true)
                    {
                        MessageBox.Show("Message envoyé avec succés ", "Success");
                        this.Close();
                    }
                    else
                    {
                        labelError.Text = "Erreur d'envoi, verifiez le destinataire";
                    }
                }
            }
            catch (System.ServiceModel.EndpointNotFoundException)
            {
                MessageBox.Show("Erreur de connexion,Verifiez votre connexion ", "Error");
            }
        }

        /// <summary>
        /// Gere la fermeture de la fenetre
        /// </summary>
        private void SendingForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            main.Enabled = true;
        }


    }
}
