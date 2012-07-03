using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using BusinessLayer.Interfaces;

namespace IHMBook
{
    public partial class IHM : Form
    {
        public IHM()
        {
            InitializeComponent();
        }

        private void aProposToolStripMenuItem_Click(object sender, EventArgs e)
        {
            APropos apropros = new APropos();
            apropros.Show();
        }

        private void IHM_Load(object sender, EventArgs e)
        {
            //deserialisation des parametres de la fenetre
            Serializer load = new Serializer();
            SaveForm param_fenetre = load.DeserialiserFenetre();
            //TODO passer par la couche business
            if (param_fenetre != null)
            {
                this.Size = new System.Drawing.Size(param_fenetre.Weightform, param_fenetre.Heightform);
                this.splitContainer1.SplitterDistance = param_fenetre.Splitterdistance;
                this.Location = new System.Drawing.Point(param_fenetre.LocalisationX, param_fenetre.LocalisationY);
            }


            BusinessLayer.Metier.Bibliotheque b =new BusinessLayer.Metier.Bibliotheque();
            b.UpdateBdd();
            foreach (BusinessLayer.Interfaces.ILivre l in b.Livre) 
            {
                TreeNode n = new TreeNode(l.Titre);
                n.Tag = l;
                treeView1.Nodes.Add(n);
            }
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            livreView1.AfficherLivre((ILivre)e.Node.Tag);
        }

        private void IHM_FormClosing(object sender, FormClosingEventArgs e)
        {
            Serializer save = new Serializer();
            save.SerialiserFenetre(this.Size.Width, this.Size.Height, this.splitContainer1.SplitterDistance, this.Location.X, this.Location.Y);
        }
    }
}
