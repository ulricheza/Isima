using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;

namespace BusinessLayer.Metier
{
    public class Auteur:IAuteur
    {
        int _GUID;

        string _nom;

        string _firstName;

        string _lastName;

        string _phoneNumber;

        string _adress;
        
        // -------------------------------------
        // Constructeur
        // -------------------------------------
        public Auteur(String name)
        {
            this._nom = name;
        }

        // -------------------------------------
        //  Propriétés
        // -------------------------------------
        public string Name
        {
            get { return _nom; }
            set { _nom = value; }
        }

        public string Adress
        {
            get { return _adress; }
            set { _adress = value; }
        }

        public string PhoneNumber
        {
            get { return _phoneNumber; }
            set { _phoneNumber = value; }
        }

        public string FirstName
        {
            get { return _firstName; }
            set { _firstName = value; }
        }

        public string LastName
        {
            get { return _lastName; }
            set { _lastName = value; }
        }

        public int GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }

    }
}
