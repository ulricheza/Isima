using System;
using System.Collections.Generic;
using System.Text;
using BusinessLayer.Interfaces;

namespace BusinessLayer.Metier
{
    public class Livre:ILivre
    {
        //Attribut
        private int _GUID;
        private string     _titre;
        private DateTime   _datesortie;
        private IAuteur   _auteur;
        private IEditeur     _editeur;
        private double    _prix;
        private string     _genre;
        private string _description;

        public void afficher()
        {
            Console.WriteLine("Titre: " + _titre + " Auteurs: " + _auteur + " Editeur: " + _editeur + " Date de sortie: " + _datesortie.ToShortDateString() + " genre :" + _genre);
        }

        // -------------------------------------------
        // constructeurs
        // -------------------------------------------
        public Livre(string titre, DateTime datesortie, Auteur auteur, Editeur editeur, double prix, string genre)
        {
            _titre = titre;
            _datesortie = datesortie;
            _auteur = auteur;
            _editeur = editeur;
            _prix = prix;
            _genre = genre;
        }

        // -------------------------------------------
        // propriété
        // -------------------------------------------
        public string Titre
        {
            get { return _titre;}
            set { _titre = value;}
        }

        public DateTime Datesortie
        {
            get { return _datesortie; }
            set { _datesortie = value; }
        }

        public IAuteur Ecrivain
        {
            get { return _auteur; }
            set { _auteur = value; }
        }

        public IEditeur Editeur
        {
            get { return _editeur;  }
            set { _editeur = value; }
        }

        public string Genre
        {
            get { return _genre; }
            set { _genre = value; }
        }

        public double Prix
        {
            get { return _prix; }
            set { _prix = value; }
        }

        public string Description
        {
            get { return _description; }
            set { _description = value; }
        }


        public int GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }


    }
}
