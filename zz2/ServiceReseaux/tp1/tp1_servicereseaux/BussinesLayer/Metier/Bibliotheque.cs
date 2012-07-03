using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BussinesLayer.Interfaces;


namespace BussinesLayer.Metier
{
    public class Bibliotheque:IBibliotheque
    {
        //attributs
        private List<Livre>  _stock = new List<Livre>();
        private List<Auteur> _auteur = new List<Auteur>();
        private List<Editeur> _editeur = new List<Editeur>();

        //methodes
        public void AddLivre(Livre add)
        {
            _stock.Add(add);
        }

        public List<Livre> Livre
        {
            get { return _stock; }
            set { _stock = value; }
        }

        public List<Auteur> Ecrivain
        {
            get { return _auteur; }
            set { _auteur = value; }
        }

        public void AddAuteur(Auteur add)
        {
            _auteur.Add(add);
        }

        public List<Editeur> Editeur
        {
            get { return _editeur; }
            set { _editeur = value; }
        }

        public void AddEditeur(Editeur add)
        {
            _editeur.Add(add);
        }
    }
}
