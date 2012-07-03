using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using BusinessLayer.Metier;
using BusinessLayer.Interfaces;

namespace IHMBook
{
    /// <summary>
    /// Fenenètre du panier
    /// </summary>
    public partial class Panier : Form
    {
        private Bibliotheque _biblio;// Bibliothèque

        /// <summary>
        /// Constructeur du panier
        /// </summary>
        /// <param name="biblio">Bibliothèque utilisée</param>
        public Panier(Bibliotheque biblio)
        {
            InitializeComponent();
            _biblio = biblio;
            UpdateTree();  
        }

        /// <summary>
        /// Permet de mettre à jour l'arbre
        /// </summary>
        public void UpdateTree()
        {
            
            foreach (BusinessLayer.Interfaces.ILivre l in _biblio.Panier)
            {
                TreeNode n = new TreeNode(l.Titre);
                n.Tag = l;
                treeViewPanier.Nodes.Add(n);
            }
        }

        /// <summary>
        /// Bouton qui supprime un livre du panier
        /// </summary>
        private void buttonSupprimer_Click(object sender, EventArgs e)
        {
            if(treeViewPanier.SelectedNode !=null)
                _biblio.SuppPanier((ILivre)treeViewPanier.SelectedNode.Tag);
            treeViewPanier.Nodes.Clear();
            UpdateTree();
        }
    }
}
