using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BusinessLayer.Interfaces
{
    /// <summary>
    /// Interface de la classe bibliotheque
    /// </summary>
    interface IBibliotheque
    {
        void UpdateLivreBdd(string GUID, string titre, double prix, IAuteur aut, IEditeur ed, IGenre genre);

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

        List<IEditeur> Editeur
        {
            get;
            set;
        }

        double MoyennePrixGenre(string genre);

        List<IEditeur> RealEditor();
    }
}
