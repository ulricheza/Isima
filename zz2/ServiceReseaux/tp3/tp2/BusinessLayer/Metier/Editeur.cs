using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BussinesLayer.Interfaces;

namespace BussinesLayer.Metier
{

    public class Editeur : IEditeur
    {
        string _nom;

        public string Name
        {
            get { return _nom; }
            set { _nom = value; }
        }
    }
}
