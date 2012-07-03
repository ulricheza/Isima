using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using BusinessLayer.Interfaces;
using BusinessLayer.Metier;


namespace IHMBook
{
    /// <summary>
    /// Fenètre d'ajout et de modification 
    /// </summary>
    public partial class ajouterLivre : Form
    {
        private Bibliotheque _biblio;
        private bool modif; // True si fenètre de modif, false sinon
        private IHM _ihm;

        /// <summary>
        /// Contructeur d'un fenètre d'ajout
        /// </summary>
        /// <param name="biblio"> Bibliothèque utilisée</param>
        /// <param name="ih"> Ihm principale </param>
        public ajouterLivre(BusinessLayer.Metier.Bibliotheque biblio, IHM ih)
        {
            _biblio = biblio;
            InitializeComponent();

            // Remplir le comboBoxAuteur et editeur
            foreach (IAuteur auteur in _biblio.Ecrivain)
            {
                comboBoxAuteur.Items.Add(auteur);

            }
            foreach (IEditeur edit in _biblio.Editeur)
            {
                comboBoxEditeur.Items.Add(edit);

            }
            foreach (IGenre genre in _biblio.Genre)
            {
                comboBoxGenre.Items.Add(genre);

            }

            modif = false;
            _ihm = ih;
            ih.Enabled = false;
        }

        /// <summary>
        /// Contructeur d'un fenètre de modifiaction
        /// </summary>
        /// <param name="biblio"> Bibliothèque utilisée</param>
        /// <param name="ih"> Ihm principale </param>
        /// <param name="livre"> Livre à modifier</param>
        public ajouterLivre(BusinessLayer.Metier.Bibliotheque biblio, IHM ih, ILivre livre)
        {
            _biblio = biblio;
            InitializeComponent();

            textBoxGUID.Text = (string)livre.GUID;
            textBoxPrix.Text = livre.Prix.ToString();
            textBoxTitre.Text = livre.Titre;

            // Remplir le comboBoxAuteur et editeur
            foreach (IAuteur auteur in _biblio.Ecrivain)
            {
                comboBoxAuteur.Items.Add(auteur);

            }
            foreach (IEditeur edit in _biblio.Editeur)
            {
                comboBoxEditeur.Items.Add(edit);

            }
            foreach (IGenre genre in _biblio.Genre)
            {
                comboBoxGenre.Items.Add(genre);

            }

            comboBoxAuteur.SelectedItem = livre.Ecrivain;
            comboBoxEditeur.SelectedItem = livre.Editeur;
            comboBoxGenre.SelectedItem = livre.Genre;
            
            buttonAjouter.Text = "Modifier";
            modif = true;

            _ihm = ih;
            _ihm.Enabled = false;
            
        }

        /// <summary>
        /// Bouton pour ajouter ou modifier un livre 
        /// </summary>
        private void buttonAjouter_Click(object sender, EventArgs e)
        {
            if (comboBoxAuteur.Text != "" && comboBoxEditeur.Text != "" &&
                comboBoxGenre.Text != "" && textBoxTitre.Text != "" && textBoxPrix.Text != ""
                && textBoxGUID.Text != "")
            {
                if (!modif)
                {
                    _biblio.AddLivreBdd(textBoxGUID.Text, textBoxTitre.Text, Double.Parse(textBoxPrix.Text), (IAuteur)comboBoxAuteur.SelectedItem,
                    (IEditeur)comboBoxEditeur.SelectedItem, (IGenre)comboBoxGenre.SelectedItem);
                    
                    _ihm.UpdateTree();
                    _ihm.Enabled = true;
                    this.Close();
                    
                }
                else
                {
                    _biblio.UpdateLivreBdd(textBoxGUID.Text, textBoxTitre.Text, Double.Parse(textBoxPrix.Text), (IAuteur)comboBoxAuteur.SelectedItem,
                    (IEditeur)comboBoxEditeur.SelectedItem, (IGenre)comboBoxGenre.SelectedItem);
                    
                    _ihm.UpdateTree();
                    _ihm.Enabled = true;
                    this.Close();
                    
                }
                

            }
            else label7.Text = "Attention, tout les champs ne sont pas remplis ! ";
        }

        /// <summary>
        /// Méthode appelée à la fermeture de la fenètre
        /// </summary>
        private void ajouterLivre_FormClosed(object sender, FormClosedEventArgs e)
        {
            _ihm.Enabled = true;
        }

    }
}
