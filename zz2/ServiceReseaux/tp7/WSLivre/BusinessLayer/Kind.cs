using System;

namespace BusinessLayer
{
    /// <summary>
    /// Reprsente le genre d'un livre
    /// </summary>
    [Serializable]
    public class Kind
    {
        private string _guid;
        private string _type;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="GUID"> GUID du genre</param>
        /// <param name="type"> Type</param>
        public Kind (string GUID, string type)
        {
            this._guid = GUID;
            this._type = type;
        }

        /// <summary>
        /// Constructeur par defaut necessaire pour la serialisation du service web
        /// </summary>
        public Kind()
        {
        }

        /// <summary>
        /// Surcharge de la methode ToString de la classe Object
        /// </summary>
        /// <returns> Nom du genre</returns>
        public override string ToString()
        {
            return Name;
        }

        //propriete
        public string Name
        {
            get { return _type; }
            set { _type = value; }
        }

        public string GUID
        {
            get { return _guid; }
            set { _guid = value; }
        }
    }
}
