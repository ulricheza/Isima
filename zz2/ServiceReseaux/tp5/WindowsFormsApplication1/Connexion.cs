using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace IHMBook
{
    /// <summary>
    /// Fenètre de connexion
    /// </summary>
    public partial class Connexion : Form
    {
        private SaveConnection param_connect;

        /// <summary>
        /// Constructeur de la construction
        /// </summary>
        public Connexion()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Bouton pour la connexion
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            Serializer b = new Serializer();
            b.SerialiserConnectBDD(textBox1.Text,textBox2.Text);
            IHM main = new IHM(this);
            this.Hide();
            main.Show();

        }

        /// <summary>
        /// Méthode appelée au chargement de la fenètre
        /// </summary>
        private void Connexion_Load(object sender, EventArgs e)
        {
            //deserialisation des parametres de la connection
            Serializer load = new Serializer();
            param_connect = load.DeserialiserConnectBDD();
            //TODO passer par la couche business
            if (param_connect != null)
            {
                textBox1.Text = param_connect.Username;
                textBox2.Text = param_connect.Password;
            }
        }

    }
}
