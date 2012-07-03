using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;

namespace BusinessLayer.Metier
{
    class Auteur:IAuteur
    {
        string _nom;

        public Auteur(String name)
        {
            this._nom = name;
        }

        public string Name
        {
            get { return _nom; }
            set { _nom = value; }
        }
    }
}
