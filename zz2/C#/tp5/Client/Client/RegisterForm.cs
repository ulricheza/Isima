using System;
using System.Data;
using System.Text;
using System.Windows.Forms;
using Client.ServeurChat;
using System.Security.Cryptography;

namespace Client
{
    /// <summary>
    /// Fenetre qui permet la création d'un compte
    /// </summary>
    public partial class RegisterForm : Form
    {
        private PrincipalForm main;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="main">Fenetre principale</param>
        public RegisterForm(PrincipalForm main)
        {
            InitializeComponent();
            this.main = main;
            main.Enabled = false;
        }

        /// <summary>
        /// Gere le coutton d'enregistrement
        /// </summary>
        private void buttonRegister_Click_1(object sender, EventArgs e)
        {
            DSAParameters key = main.Securitykey;
            ASCIIEncoding encoding = new ASCIIEncoding();  

            string nick = textBoxLogin.Text;
            string password = textBoxPassword.Text;

            try
            {
                if (textBoxPassword.Text == "" || textBoxLogin.Text == "") //si le login et le password sont valide
                {
                    labelError.Text = "Login/password vide interdit";
                }
                else
                {
                    if (textBoxPassword.Text == textBoxConfirmPassword.Text) //si le la confirmation est identique au password
                    {
                        byte[] nicksigned = main.Crypto.SignData(encoding.GetBytes(nick)); //on signe le login
                        if (main.Client.Register(nick, password, nicksigned, key.Counter, key.G, key.J, key.P, key.Q, key.Seed, key.X, key.Y) == false)
                        {
                            labelError.Text = "Login deja utilise";
                        }
                        else
                        {
                            MessageBox.Show("Creation du compte reussi", "Creation reussi");
                            main.Session = nick;
                            main.Enabled = true;
                            this.Close();
                        }
                    }
                    else
                    {
                        labelError.Text = "Erreur verification mot de passe";
                    }
                }
            }
            catch (System.ServiceModel.EndpointNotFoundException)
            {
                MessageBox.Show("Erreur de connexion,Verifiez votre connexion ", "Error");
            }
        }

        /// <summary>
        /// Gere la fermeture de le fenetre
        /// </summary>
        private void RegisterForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            main.Enabled = true;
        }
    }
}
