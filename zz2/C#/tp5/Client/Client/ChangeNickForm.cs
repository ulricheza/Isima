using System;
using System.Text;
using System.Windows.Forms;
using Client.ServeurChat;
using System.Security.Cryptography;

namespace Client
{
    public partial class ChangeNickForm : Form
    {
        private PrincipalForm main;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="main">Fentre principale</param>
        public ChangeNickForm(PrincipalForm main )
        {
            InitializeComponent();
            this.main = main;
            main.Enabled = false;
        }

        private void changenickbutton_Click(object sender, EventArgs e)
        {
            string newnick = newlogintextBox.Text;

            try
            {
                if (newnick != "")
                {
                    ASCIIEncoding encoding = new ASCIIEncoding();
                    DSAParameters key = main.Securitykey;
                    byte[] newnicksigned = main.Crypto.SignData(encoding.GetBytes(newnick));
                    if (main.Client.ChangeNick(main.Session, newnick, newnicksigned))
                    {
                        MessageBox.Show("Modification du login réussi", "Success");
                        main.Session = newnick;
                        this.Close();
                    }
                    else
                    {
                        MessageBox.Show("Login déjà utilisé", "Warning");
                    }
                }
                else
                {
                    MessageBox.Show("Nouveau login non valide", "Warning");
                }
            }
            catch (System.ServiceModel.EndpointNotFoundException)
            {
                MessageBox.Show("Erreur de connexion,Verifiez votre connexion ", "Error");
            }

        }

        private void ChangeNickForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            main.Enabled = true;
        }
    }
}
