using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BussinesLayer.Metier;

namespace BussinesLayer.Interfaces
{
    interface IBibliotheque
    {
        void AddLivre(Livre add);

        List<Livre> Livre
        {
            get;
            set;
        }

        List<Auteur> Ecrivain
        {
            get;
            set;
        }

        void AddAuteur(Auteur add);

        List<Editeur> Editeur
        {
            get;
            set;
        }

        void AddEditeur(Editeur add);

        double MoyennePrixGenre(string genre);

        List<Editeur> RealEditor();
    }
}
