using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using BusinessLayer.Interfaces;

namespace IHMBook
{
    /// <summary>
    /// Controleur qui affiche les informations d'un livre
    /// </summary>
    public partial class LivreView : UserControl
    {
        /// <summary>
        /// Constructeur du controleur
        /// </summary>
        public LivreView()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Affiche les informations du livre
        /// </summary>
        /// <param name="livre">Livre à afficher</param>
        public void AfficherLivre(ILivre livre)
        {
            labelAuteur.Text = livre.Ecrivain.FirstName;
            labelPrix.Text = livre.Prix.ToString();
            labelTitre.Text = livre.Titre;
            labelEditeur.Text = livre.Editeur.Name;
            labelGenre.Text = livre.Genre.ToString();
        }
    }
}
