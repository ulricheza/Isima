using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer
{

        

    /// <summary>
    /// Auteur vu de la base de donnée
    /// </summary>
    public class AuthorDB
    {
        private string guid;
        private string name;
        private string firstname;
        private string lastname;
        private string phonenumber;
        private string address;
        private string zipcode;
        private string city;
        private string state;
        private string country;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="inGUID">GUID</param>
        /// <param name="inNom">Distinction</param>
        /// <param name="inFirstName">Prénom</param>
        /// <param name="inLastName">Nom</param>
        /// <param name="inPhoneNumber">Numéro de téléphone</param>
        /// <param name="inAdress">Adresse</param>
        /// <param name="inZipCode">Code postal</param>
        /// <param name="inCity">Ville</param>
        /// <param name="inState">Etats</param>
        /// <param name="inCountry">Pays</param>
        public AuthorDB(string guid, string name, string firstname, string lastname,string phonenumber, string adress,
                         string zipcode, string city,string state, string country)
        {
            this.guid = guid;
            this.name = name;
            this.firstname = firstname;
            this.lastname = lastname;
            this.phonenumber = phonenumber;
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

        public string FirstName
        {
          get { return firstname; }
          set { firstname = value; }
        }
        
        public string LastName
        {
          get { return lastname; }
          set { lastname = value; }
        }
        
        public string PhoneNumber
        {
          get { return phonenumber; }
          set { phonenumber = value; }
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
