using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;

namespace BusinessLayer.Metier
{
    /// <summary>
    /// Représente un livre
    /// </summary>
    public class Livre:ILivre
    {
        //Attribut

        private string _GUID;
        private string _titre;
        private string _datesortie;
        private IAuteur _auteur;
        private IEditeur _editeur;
        private double _prix;
        private IGenre _genre;
        private string _description;

        // -------------------------------------------
        // constructeurs
        // -------------------------------------------
        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="inGuid"> GUID</param>
        /// <param name="titre">Titre</param>
        /// <param name="datesortie">Date de sortie</param>
        /// <param name="auteur">Auteur</param>
        /// <param name="editeur">Editeur</param>
        /// <param name="prix">Prix</param>
        /// <param name="genre">Genre</param>
        /// <param name="description">Description</param>
        public Livre(string inGuid, string titre, string datesortie, IAuteur auteur, IEditeur editeur,
                        double prix, IGenre genre, string description)
        {
            _GUID = inGuid;
            _titre = titre;
            _datesortie = datesortie;
            _auteur = auteur;
            _editeur = editeur;
            _prix = prix;
            _genre = genre;
            _description = description;
        }

        // -------------------------------------------
        // propriétés
        // -------------------------------------------
        /// <summary>
        /// Titre du livre
        /// </summary>
        public string Titre
        {
            get { return _titre;}
            set { _titre = value;}
        }

        /// <summary>
        /// Date de sortie
        /// </summary>
        public string Datesortie
        {
            get { return _datesortie; }
            set { _datesortie = value; }
        }

        /// <summary>
        /// Ecrivain
        /// </summary>
        public IAuteur Ecrivain
        {
            get { return _auteur; }
            set { _auteur = value; }
        }

        /// <summary>
        /// Editeur
        /// </summary>
        public IEditeur Editeur
        {
            get { return _editeur;  }
            set { _editeur = value; }
        }

        /// <summary>
        /// Genre
        /// </summary>
        public IGenre Genre
        {
            get { return _genre; }
            set { _genre = value; }
        }

        /// <summary>
        /// Prix
        /// </summary>
        public double Prix
        {
            get { return _prix; }
            set { _prix = value; }
        }

        /// <summary>
        /// Description
        /// </summary>
        public string Description
        {
            get { return _description; }
            set { _description = value; }
        }

        /// <summary>
        /// Guid
        /// </summary>
        public string GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }


    }
}
