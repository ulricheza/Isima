using System;

namespace BusinessLayer
{
    /// <summary>
    /// Classe de la couche Metier representant un Auteur
    /// </summary>
    [Serializable]
    public class Author
    {
        private string _GUID;
        private string _name;
        private string _firstname;
        private string _lastname;
        private string _phonenumber;
        private string _adress;
        

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="GUID"> GUID de l'auteur</param>
        /// <param name="name">Nom de l'auteur</param>
        /// <param name="firstname">Prénom</param>
        /// <param name="lastname">Nom</param>
        public Author(string GUID, string name, string firstname, string lastname)
        {
            this._GUID = GUID;
            this._name = name;
            this._firstname = firstname;
            this._lastname = lastname;
        }

        /// <summary>
        /// Constructeur par defaut necessaire pour la serialisation du service web
        /// </summary>
        public Author()
        { 
        }

        /// <summary>
        /// surcharge de la methode ToString de la classe Object
        /// </summary>
        /// <returns> Prénom et nom de l'auteur</returns>
        public override string ToString()
        {

            return (_firstname + " " + _lastname);

        }

       
        //proprietes
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public string Adress
        {
            get { return _adress; }
            set { _adress = value; }
        }

        public string PhoneNumber
        {
            get { return _phonenumber; }
            set { _phonenumber = value; }
        }

        public string FirstName
        {
            get { return _firstname; }
            set { _firstname = value; }
        }

        public string LastName
        {
            get { return _lastname; }
            set { _lastname = value; }
        }

        public string GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }

    }
}
