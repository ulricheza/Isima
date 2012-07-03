using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer.Metier
{
    /// <summary>
    /// Livre dans la base de donnée
    /// </summary>
    public class LivreBDD
    {
         //Attribut
        private string _GUID;
        private string _titre;
        private string _datesortie;
        private string _isbn10;
        private string _isbn13;
        private string _editeur;
        private double _prix;
        private string _genre;
        private string _description;
        private string _guidAuthor;


        // -------------------------------------------
        // constructeurs
        // -------------------------------------------
        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="inGUID">GUID</param>
        /// <param name="inTitre">Titre</param>
        /// <param name="inDatesortie">Date de sortie</param>
        /// <param name="inIsbn10">ISBN10</param>
        /// <param name="inIsbn13">ISBN13</param>
        /// <param name="inEditeur">Editeur</param>
        /// <param name="inPrix">Prix</param>
        /// <param name="inGenre">Genre</param>
        /// <param name="inDescription">Description</param>
        public LivreBDD(string inGUID, string inTitre, string inDatesortie, string inIsbn10, string inIsbn13,
                        string inEditeur, string inPrix, string inGenre, string inDescription)
        {
            GUID = inGUID;
            Titre = inTitre;
            Datesortie = inDatesortie;
            Isbn10 = inIsbn10;
            Isbn13 = inIsbn13;
            Editeur = inEditeur;
            Prix = Double.Parse(inPrix);
            Genre = inGenre;
            
        }

        // -------------------------------------------
        // propriété
        // -------------------------------------------
        public string GuidAuthor
        {
            get { return _guidAuthor; }
            set { _guidAuthor = value; }
        }


        public string Titre
        {
            get { return _titre;}
            set { _titre = value;}
        }

        public string Datesortie
        {
            get { return _datesortie; }
            set { _datesortie = value; }
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


        public string GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }

        public string Isbn10
        {
            get { return _isbn10; }
            set { _isbn10 = value; }
        }

        public string Isbn13
        {
            get { return _isbn13; }
            set { _isbn13 = value; }
        }
    }
}
