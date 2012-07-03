using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;

namespace BusinessLayer.Metier
{
    /// <summary>
    /// Classe de la couche Metier representant un Auteur
    /// </summary>
    public class Auteur:IAuteur
    {
        string _GUID;

        string _nom;

        string _firstName;

        string _lastName;

        string _phoneNumber;

        string _adress;
        
        // -------------------------------------
        // Constructeur
        // -------------------------------------
        /// <summary>
        /// Auteur
        /// </summary>
        /// <param name="inGUID"> GUID de l'auteur</param>
        /// <param name="inNom">Nom de l'auteur</param>
        /// <param name="inFirstName">Prénom</param>
        /// <param name="inLastName">Nom</param>
        public Auteur(string inGUID, string inNom, string inFirstName, string inLastName)
        {
            GUID = inGUID;
            Name = inNom;
            FirstName = inFirstName;
            LastName = inLastName;
        }

        /// <summary>
        /// Affiche les informations de l'auteur
        /// </summary>
        /// <returns> Prénom et nom de l'auteur</returns>
        public override string ToString()
        {

            return FirstName + " " + LastName;

        }

        // -------------------------------------
        //  Propriétés
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
        /// Adress
        /// </summary>
        public string Adress
        {
            get { return _adress; }
            set { _adress = value; }
        }

        /// <summary>
        /// Numéro
        /// </summary>
        public string PhoneNumber
        {
            get { return _phoneNumber; }
            set { _phoneNumber = value; }
        }

        /// <summary>
        /// Prénom
        /// </summary>
        public string FirstName
        {
            get { return _firstName; }
            set { _firstName = value; }
        }

        /// <summary>
        /// Nom
        /// </summary>
        public string LastName
        {
            get { return _lastName; }
            set { _lastName = value; }
        }

        public string GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }

    }
}
