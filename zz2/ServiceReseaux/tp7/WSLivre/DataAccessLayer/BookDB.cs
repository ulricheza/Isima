using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer
{
    /// <summary>
    /// Livre vu de la base de donnée
    /// </summary>
    public class BookDB
    {
        private string guid;
        private string title;
        private string releasedate;
        private string isbn10;
        private string isbn13;
        private string editor;
        private double price;
        private string kind;
        private string description;
        private string guidAuthor;


        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="guid">GUID</param>
        /// <param name="titre">Titre</param>
        /// <param name="releasedate">Date de sortie</param>
        /// <param name="isbn10">ISBN10</param>
        /// <param name="isbn13">ISBN13</param>
        /// <param name="editor">Editeur</param>
        /// <param name="price">Prix</param>
        /// <param name="kind">Genre</param>
        /// <param name="description">Description</param>
        public BookDB(string guid, string titre, string releasedate, string isbn10, string isbn13,
                        string editor, string price, string kind, string description)
        {
            this.guid = guid;
            this.title = titre;
            this.releasedate = releasedate;
            this.isbn10 = isbn10;
            this.isbn13 = isbn13;
            this.editor = editor;
            this.price = Double.Parse(price);
            this.kind = kind;
        }

        //proprietes
        public string GuidAuthor
        {
            get { return guidAuthor; }
            set { guidAuthor = value; }
        }


        public string Title
        {
            get { return title;}
            set { title = value;}
        }

        public string ReleaseDate
        {
            get { return releasedate; }
            set { releasedate = value; }
        }

        public string Editor
        {
            get { return editor;  }
            set { editor = value; }
        }

        public string Kind
        {
            get { return kind; }
            set { kind = value; }
        }

        public double Price
        {
            get { return price; }
            set { price = value; }
        }

        public string Description
        {
            get { return description; }
            set { description = value; }
        }


        public string GUID
        {
            get { return guid; }
            set { guid = value; }
        }

        public string Isbn10
        {
            get { return isbn10; }
            set { isbn10 = value; }
        }

        public string Isbn13
        {
            get { return isbn13; }
            set { isbn13 = value; }
        }
    }
}
