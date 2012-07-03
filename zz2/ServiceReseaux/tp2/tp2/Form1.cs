using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using BussinesLayer.Metier;
using BussinesLayer.Interfaces;

namespace tp2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Auteur Auteur1 = new Auteur();
            Auteur1.Name = "Victor Hugo";
            Auteur Auteur2 = new Auteur();
            Auteur2.Name = "Tolkien";
            Auteur Auteur3 = new Auteur();
            Auteur1.Name = "Rene Barjavel";
            double prix = 10.0;


            Livre Livre1 = new Livre("LOTR", DateTime.Now, Auteur2, "Larousse", prix, "Fantasy");
            Livre Livre2 = new Livre("Les miserables", DateTime.Now, Auteur1, " Galimar", 15.0, " Classique");
            Livre Livre3 = new Livre("Ravage", DateTime.Today, Auteur3, "Folio", 12.0, "Fantasy");

            IBibliotheque lib = new Bibliotheque();
            lib.AddAuteur(Auteur1);
            lib.AddAuteur(Auteur2);
            lib.AddAuteur(Auteur3);
            lib.AddLivre(Livre1);
            lib.AddLivre(Livre2);
            lib.AddLivre(Livre3);

        }

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
