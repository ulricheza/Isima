using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using BusinessLayer.Interfaces;

namespace IHMBook
{
    /// <summary>
    /// Form qui présente la liste des livres
    /// </summary>
    public partial class IHM : Form
    {
        BusinessLayer.Metier.Bibliotheque _biblio;
        Connexion _mainFrame;

        /// <summary>
        /// Constructeur de l'IHM
        /// </summary>
        /// <param name="mainFrame">Form de la connexion</param>
        public IHM(Connexion mainFrame)
        {
            this._mainFrame = mainFrame;
            InitializeComponent();
            _biblio = new BusinessLayer.Metier.Bibliotheque();
        }

        /// <summary>
        /// Evenement lorsque l'on clique sur a propos
        /// </summary>
        private void aProposToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Enabled = false;
            APropos apropros = new APropos(this);
            apropros.Show();
        }

        /// <summary>
        /// Méthode appelée au lancement
        /// </summary>
        private void IHM_Load(object sender, EventArgs e)
        {
            //deserialisation des parametres de la fenetre
            Serializer load = new Serializer();
            SaveForm param_fenetre = load.DeserialiserFenetre();
            if (param_fenetre != null)
            {
                this.Size = new System.Drawing.Size(param_fenetre.Weightform, param_fenetre.Heightform);
                this.splitContainer1.SplitterDistance = param_fenetre.Splitterdistance;
                this.Location = new System.Drawing.Point(param_fenetre.LocalisationX, param_fenetre.LocalisationY);
            }

            UpdateTree();

        }

        /// <summary>
        /// Met à jour l'arbre
        /// </summary>
        public void UpdateTree()
        {
            _biblio.UpdateBdd();
            treeView1.Nodes.Clear();
            foreach (BusinessLayer.Interfaces.ILivre l in _biblio.Livre)
            {
                TreeNode n = new TreeNode(l.Titre);
                n.Tag = l;
                treeView1.Nodes.Add(n);
            }
        }

        /// <summary>
        /// Evenenement après le clic sur un élément de l'arbre
        /// </summary>
        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            livreView1.AfficherLivre((ILivre)e.Node.Tag);
        }

        /// <summary>
        /// Methode appelée quand on ferme la fenètre
        /// </summary>
        private void IHM_FormClosing(object sender, FormClosingEventArgs e)
        {
            Serializer save = new Serializer();
            save.SerialiserFenetre(this.Size.Width, this.Size.Height, this.splitContainer1.SplitterDistance, this.Location.X, this.Location.Y);
            _mainFrame.Close();
        }

        /// <summary>
        /// Bouton pour ajouter/modifier un livre
        /// <summary>
        private void buttonAjouterPanier_Click(object sender, EventArgs e)
        {
            if (treeView1.SelectedNode != null)
            {
                ajouterLivre ajLivre = new ajouterLivre(_biblio, this, (ILivre)treeView1.SelectedNode.Tag);
                ajLivre.Show();
            }
        }

        /// <summary>
        /// Bouton pour ajouter un livre
        /// </summary>
        private void buttonAjouter_Click(object sender, EventArgs e)
        {
            ajouterLivre ajLivre = new ajouterLivre(_biblio, this);
            ajLivre.Show();
        }

        /// <summary>
        /// Bouton pour ajouter au panier
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            _biblio.AddPanier((ILivre)treeView1.SelectedNode.Tag);
        }

        /// <summary>
        /// Permet d'ouvrir le panier
        /// </summary>
        private void PanierStripMenuItem_Click(object sender, EventArgs e)
        {
            Panier pan = new Panier(_biblio);
            pan.Show();
        }

        /// <summary>
        /// Permet de supprimer un livre de l'arbre
        /// </summary>
        private void buttonSupp_Click(object sender, EventArgs e)
        {
            if (treeView1.SelectedNode != null)
            {
                _biblio.DeleteLivreBdd(((ILivre)treeView1.SelectedNode.Tag).GUID);
                treeView1.Nodes.Clear();
                UpdateTree();

            }
        }

        /// <summary>
        /// Permet de se déconnecter
        /// </summary>
        private void deconnecterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //suppression du fichier de serialisation de BDD
            try
            {
                File.Delete("Connection_serialisation.xml");
            }
            catch (Exception ex)
            {
            }
            this.Close();
        }

        /// <summary>
        /// Permet de fermer la fenètre
        /// </summary>
        private void fermerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

    }
}
