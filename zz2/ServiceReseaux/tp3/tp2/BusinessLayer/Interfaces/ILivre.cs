using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BussinesLayer.Metier;

namespace BussinesLayer.Interfaces
{
    interface ILivre
    {
        string Titre
        {
            get;
            set;
        }

        DateTime Datesortie
        {
            get;
            set;
        }

        Auteur Ecrivain
        {
            get;
            set;
        }

        Editeur Editeur
        {
            get;
            set;
        }

        string Genre
        {
            get;
            set;
        }

        double Prix
        {
            get;
            set;
        }

        void afficher();

    }
}
