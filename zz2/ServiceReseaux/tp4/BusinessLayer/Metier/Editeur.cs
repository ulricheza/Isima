using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;

namespace BusinessLayer.Metier
{

    public class Editeur : IEditeur
    {
        int _GUID;

        string _nom;

        string _address;

        // -------------------------------------
        // Constructeur
        // -------------------------------------
        public Editeur(String name)
        {
            this._nom = name;
        }

        // -------------------------------------
        // Propriété
        // -------------------------------------
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

        public int GUID
        {
            get { return _GUID; }
            set { _GUID = value; }
        }

    }
}
