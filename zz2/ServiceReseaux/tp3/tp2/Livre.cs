using System;
using System.Collections.Generic;
using System.Text;
using BussinesLayer.Interfaces;

namespace BussinesLayer.Metier
{
    public class Livre:ILivre
    {
        //Attribut
        private string     _titre;
        private DateTime   _datesortie;
        private Auteur[]   _auteur;
        private string     _editeur;
        private decimal    _prix;
        private string     _genre;
        private DateTime date;



        //methode
        //constructeur
        Livre(string titre, DateTime datesortie, Auteur[] auteur, string editeur, decimal prix, string genre)
        {
            _titre = titre;
            _datesortie = datesortie;
            _auteur = auteur;
            _editeur = editeur;
            _prix = prix;
            _genre = genre;
        }

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

        public Auteur[] Ecrivain
        {
            get { return _auteur; }
            set { _auteur = value; }
        }

        public string Editeur
        {
            get { return _editeur;  }
            set { _editeur = value; }
        }

        public string Genre
        {
            get { return _genre; }
            set { _genre = value; }
        }

        public decimal Prix
        {
            get { return _prix; }
            set { _prix = value; }
        }

        public void afficher()
        {
            string aut = "";
            foreach (Auteur i in _auteur)
            {
                   aut += i.Name;
            }
            Console.WriteLine("Titre: " + _titre + " Auteurs: " + aut + " Editeur: " + _editeur + " Date de sortie: " + _datesortie.ToShortDateString() + " genre :" + _genre);
        }
    }
}
