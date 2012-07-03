using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using BusinessLayer.Interfaces;

namespace ServiceReseaux
{
    public partial class LivreView : UserControl
    {
        public LivreView()
        {
            InitializeComponent();
        }

        public void AfficherLivre(ILivre livre)
        {
            labelAuteur.Text = livre.Ecrivain.Name;
            labelPrix.Text = livre.Prix.ToString();
            labelTitre.Text = livre.Titre;
            labelEditeur.Text = livre.Editeur.Name;
        }
    }
}
