using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer
{
    /// <summary>
    /// Editeur vu de la base de donnée
    /// </summary>
    public class EditorDB
    {
        private string guid;
        private string name;
        private string address;
        private string zipcode;
        private string city;
        private string state;
        private string country;


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
        public EditorDB(string guid, string name, string adress, string zipcode, string city, string state, string country)
        {
            this.guid = guid;
            this.name = name;
            this.address = adress;
            this.zipcode = zipcode;
            this.city = city;
            this.state = state;
            this.country = country;
        }

        //proprietes
        public string GUID
        {
            get { return guid; }
            set { guid = value; }
        }

        
        public string Name
        {
          get { return name; }
          set { name = value; }
        }
        
        public string Address
        {
          get { return address; }
          set { address = value; }
        }
        
        public string Zipcode
        {
          get { return zipcode; }
          set { zipcode = value; }
        }
        
        public string City
        {
          get { return city; }
          set { city = value; }
        }
        
        public string State
        {
          get { return state; }
          set { state = value; }
        }

        public string Country
        {
          get { return country; }
          set { country = value; }
        }

    }
}
