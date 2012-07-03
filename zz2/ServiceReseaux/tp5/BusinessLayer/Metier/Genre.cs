using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;

namespace DataAccessLayer.Metier
{
    /// <summary>
    /// Reprsente le genre d'un livre
    /// </summary>
    public class Genre : IGenre
    {
        private string _guid;
        private string _type;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="inGuid"> GUID du genre</param>
        /// <param name="inType"> Type</param>
        public Genre (string inGuid, string inType)
        {
            _guid = inGuid;
            _type = inType;
        }

        /// <summary>
        /// Permet d'afficher les informations d'un genre
        /// </summary>
        /// <returns> Nom du genre</returns>
        public override string ToString()
        {

            return Name;

        }

        /// <summary>
        /// Nome
        /// </summary>
        public string Name
        {
            get { return _type; }
            set { _type = value; }
        }

        /// <summary>
        /// Guid
        /// </summary>
        public string GUID
        {
            get { return _guid; }
            set { _guid = value; }
        }
    }
}
