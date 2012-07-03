using System;

namespace BusinessLayer
{

    /// <summary>
    /// Représente un éditeur
    /// </summary>
    [Serializable]
    public class Editor
    {
        private string _GUID;
        private string _name;


        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="GUID"> Guid de l'éditeur</param>
        /// <param name="name"> Nom</param>
        public Editor(string GUID, string name)
        {
            this._GUID = GUID;
            this._name = name;
        }

        /// <summary>
        /// Constructeur par defaut necessaire pour la serialisation du service web
        /// </summary>
        public Editor()
        {
        }

        /// <summary>
        /// Surcharge de le methode ToString de la clase Object
        /// </summary>
        public override string ToString()
        {
            return _name;
        }

        //Proprietes
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public string GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }

    }
}
