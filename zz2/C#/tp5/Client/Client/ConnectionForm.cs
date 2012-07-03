using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using Client.ServeurChat;
using System.Security.Cryptography;

namespace Client
{
    /// <summary>
    /// Form qui permet de se connecter au serveur
    /// </summary>
    public partial class ConnectionForm : Form
    {
        private PrincipalForm main;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="main">Fenetre principale</param>
        public ConnectionForm(PrincipalForm main)
        {
            InitializeComponent();
            this.main = main;
            main.Enabled = false;
        }

        /// <summary>
        /// Methode qui gere le clic sur le bouton connexion
        /// </summary>
        private void buttonConnexion_Click(object sender, EventArgs e)
        {
            ASCIIEncoding encoding = new ASCIIEncoding();

            DSAParameters key = main.Securitykey;
            string nick = textBoxLogin.Text;       
            string password = textBoxPassword.Text;

            byte[] nicksigned = main.Crypto.SignData(encoding.GetBytes(nick)); //on signe le pseudo

            try
            {
                if (main.Client.LogIn(nick, password, nicksigned, key.Counter, key.G, key.J, key.P, key.Q, key.Seed, key.X, key.Y) == false) //erreur de connexion
                {
                    labelError.Text = " Login/password incorrect";
                }
                else
                {
                    MessageBox.Show("Connection réussie", "Connection réussie");
                    main.Session = nick;
                    this.Close();
                }
            }
            catch (System.ServiceModel.EndpointNotFoundException)
            {
                MessageBox.Show("Erreur de connexion,Verifiez votre connexion ", "Error");
            }
        }

        /// <summary>
        /// Methode qui rend a la main a la fentre principale 
        /// </summary>
        private void ConnectionForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            main.Enabled = true;
        }
    }
}
