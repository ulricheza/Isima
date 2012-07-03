using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer.Metier
{
    /// <summary>
    /// Editeur dans la base de donnée
    /// </summary>
    public class EditeurBDD
    {
        /// <summary>
        /// Constructeur d'editeur
        /// </summary>
        /// <param name="inGUID">GUID</param>
        /// <param name="inNom">Nom</param>
        /// <param name="inAdress">Adresse</param>
        /// <param name="inZipCode">Code postal</param>
        /// <param name="inCity">Ville</param>
        /// <param name="inState">Etat</param>
        /// <param name="inCountry">Pays</param>
         public EditeurBDD(string inGUID, string inNom, string inAdress, string inZipCode, string inCity,
                            string inState, string inCountry)
        {
            GUID = inGUID;
            Name = inNom;
            Address = inAdress;
            Zipcode = inZipCode;
            City = inCity;
            State = inState;
            Country = inCountry;
            
        }


        // ------------------------
        // Attribut
        // ------------------------
        string _GUID;

        string _nom;

        string _address;

        string _zipcode;

        string _city;

        string _state;

        string _country;

        // ------------------------
        // Propiétés
        // ------------------------
        public string GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }

        
        public string Name
        {
          get { return _nom; }
          set { _nom = value; }
        }
        
        public string Address
        {
          get { return _address; }
          set { _address = value; }
        }
        
        public string Zipcode
        {
          get { return _zipcode; }
          set { _zipcode = value; }
        }
        
        public string City
        {
          get { return _city; }
          set { _city = value; }
        }
        
        public string State
        {
          get { return _state; }
          set { _state = value; }
        }

        public string Country
        {
          get { return _country; }
          set { _country = value; }
        }

    }
}
