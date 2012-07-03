using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Metier;

namespace BusinessLayer.Interfaces
{
    interface IBibliotheque
    {
        void AddLivre(ILivre add);

        List<ILivre> Livre
        {
            get;
            set;
        }

        List<IAuteur> Ecrivain
        {
            get;
            set;
        }

        void AddAuteur(IAuteur add);

        List<IEditeur> Editeur
        {
            get;
            set;
        }

        void AddEditeur(IEditeur add);

        double MoyennePrixGenre(string genre);

        List<IEditeur> RealEditor();
    }
}
