using System;

namespace BusinessLayer
{
    /// <summary>
    /// Représente un livre
    /// </summary>
    [Serializable]
    public class Book
    {
        //Attribut

        private string  _GUID;
        private string  _title;
        private string  _releasedate;
        private Author _writer;
        private Editor _publisher;
        private double  _price;
        private Kind   _type;
        private string  _description;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="GUID"> GUID</param>
        /// <param name="title">Titre</param>
        /// <param name="releasedate">Date de sortie</param>
        /// <param name="writer">Auteur</param>
        /// <param name="publisher">Editeur</param>
        /// <param name="price">Prix</param>
        /// <param name="type">Genre</param>
        /// <param name="description">Description</param>
        public Book(string GUID, string title, string releasedate, Author writer, Editor publisher,
                        double price, Kind type, string description)
        {
            this._GUID = GUID;
            this._title = title;
            this._releasedate = releasedate;
            this._writer = writer;
            this._publisher = publisher;
            this._price = price;
            this._type = type;
            this._description = description;
        }

        /// <summary>
        /// Constructeur par defaut necessaire pour la serialisation du service web
        /// </summary>
        public Book()
        { 
        }

        /// <summary>
        /// Surcharge de la methode Equals pour les livres
        /// </summary>
        /// <param name="obj">libre </param>
        /// <returns></returns>
        public bool Equals(Book obj)
        {
            
            return (this.GUID == obj.GUID && this.Title == obj.Title
                                 && this.Writer.LastName == obj.Writer.LastName && this.Price == obj.Price
                                 && this.Publisher.Name == obj.Publisher.Name);
        }

        // proprietes
        public string Title
        {
            get { return _title; }
            set { _title = value; }
        }

        public string ReleaseDate
        {
            get { return _releasedate; }
            set { _releasedate = value; }
        }

        public Author Writer
        {
            get { return _writer; }
            set { _writer = value; }
        }

        public string NameWriter
        {
            get { return _writer.Name + " " +_writer.LastName; }
            set { }
        }

        public Editor Publisher
        {
            get { return _publisher; }
            set { _publisher = value; }
        }

        public Kind Type
        {
            get { return _type; }
            set { _type = value; }
        }

        public double Price
        {
            get { return _price; }
            set { _price = value; }
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
    }
}
