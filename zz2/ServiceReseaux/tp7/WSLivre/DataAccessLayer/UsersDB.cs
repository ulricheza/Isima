using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer
{
    public class UsersDB
    {
                /// <summary>
        /// Nom d'utilisateur
        /// </summary>
        private String _username;
        /// <summary>
        /// Adresse
        /// </summary>
        private String _adress;
        /// <summary>
        /// Code postal
        /// </summary>
        private String _zipcode;
        /// <summary>
        /// Ville
        /// </summary>
        private String _city;

        /// <summary>
        /// Mot de passe
        /// </summary>
        private int _password;



        /// <summary>
        /// Nom d'utilisateur
        /// </summary>
        /// <param name="username">nom d'utilisateur</param>
        /// <param name="adress">Adresse</param>
        /// <param name="zipcode">Code postal</param>
        /// <param name="city">Ville</param>
        public UsersDB(String username, String adress, String zipcode, String city, int password)
        {
            _username = username;
            _adress = adress;
            _zipcode = zipcode;
            _city = city;
            _password = password;
        }

        /// <summary>
        /// Nom d'utilisateur
        /// </summary>
        public String Username
        {
            get { return _username; }
            set { _username = value; }
        }

        /// <summary>
        /// Adresse
        /// </summary>
        public String Adress
        {
            get { return _adress; }
            set { _adress = value; }
        }

        /// <summary>
        /// Code postal
        /// </summary>
        public String Zipcode
        {
            get { return _zipcode; }
            set { _zipcode = value; }
        }

        /// <summary>
        /// Ville
        /// </summary>
        public String City
        {
            get { return _city; }
            set { _city = value; }
        }

        public int Password
        {
            get { return _password; }
            set { _password = value; }
        }
    }
}
