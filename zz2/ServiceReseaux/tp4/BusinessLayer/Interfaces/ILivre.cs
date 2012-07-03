using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Metier;

namespace BusinessLayer.Interfaces
{
    public interface ILivre
    {
        int GUID
        {
            get;
            set;
        }

        string Description
        {
            get;
            set;
        }

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

        IAuteur Ecrivain
        {
            get;
            set;
        }

        IEditeur Editeur
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
