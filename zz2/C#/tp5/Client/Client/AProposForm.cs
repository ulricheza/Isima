using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Client
{
    /// <summary>
    /// Windowsform pour la fenetre a propos 
    /// </summary>
    public partial class AProposForm : Form
    {
        private PrincipalForm main;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="main">Fenetre principale</param>
        public AProposForm(PrincipalForm main)
        {
            InitializeComponent();
            this.main = main;
        }

        /// <summary>
        /// Gestion du bouton OK, ferme la fenetre a propos
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Redonne la main a la fenetre principale, pendant la fermeture de la fenetre
        /// </summary>
        private void AProposForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            main.Enabled = true;
        }


    }
}
