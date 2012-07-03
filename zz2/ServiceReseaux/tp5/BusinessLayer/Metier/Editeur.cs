using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;

namespace BusinessLayer.Metier
{

    /// <summary>
    /// Représente un éditeur
    /// </summary>
    public class Editeur : IEditeur
    {
        string _GUID;

        string _nom;

        // -------------------------------------
        // Constructeur
        // -------------------------------------
        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="guid"> Guid de l'éditeur</param>
        /// <param name="name"> Nom</param>
        public Editeur(string guid, string name)
        {
            _GUID = guid;

            this._nom = name;
        }

        /// <summary>
        /// Permet d'afficher les informations de l'éditeur
        /// </summary>
        /// <returns> Nom de l'éditeur</returns>
        public override string ToString()
        {

            return Name;

        }

        // -------------------------------------
        // Propriété
        // -------------------------------------
        /// <summary>
        /// Nom
        /// </summary>
        public string Name
        {
            get { return _nom; }
            set { _nom = value; }
        }

        /// <summary>
        /// GUID
        /// </summary>
        public string GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }

    }
}
