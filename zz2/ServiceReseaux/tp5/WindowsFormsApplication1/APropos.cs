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
    /// Fenètre d'à propos
    /// </summary>
    public partial class APropos : Form
    {
        private IHM _principal;

        /// <summary>
        /// Constructeur de la fenètre
        /// </summary>
        /// <param name="principal"> IHM principal</param>
        public APropos(IHM principal)
        {
            _principal = principal;
            InitializeComponent();
        }

        /// <summary>
        /// Bouton pour quitter le "Apropos"
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Méthode appelée à la fermeture de l'à propos
        /// </summary>
        private void APropos_FormClosed(object sender, FormClosedEventArgs e)
        {
            _principal.Enabled = true;
        }
    }
}
