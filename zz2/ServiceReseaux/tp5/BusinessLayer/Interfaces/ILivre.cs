using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BusinessLayer.Interfaces
{
    /// <summary>
    /// Interface de la classe Livre
    /// </summary>
    public interface ILivre
    {
        /// <summary>
        /// GUID
        /// </summary>
        string GUID
        {
            get;
            set;
        }

        /// <summary>
        /// Description
        /// </summary>
        string Description
        {
            get;
            set;
        }

        /// <summary>
        /// Titre
        /// </summary>
        string Titre
        {
            get;
            set;
        }
        /// <summary>
        /// Date de sortie
        /// </summary>
        string Datesortie
        {
            get;
            set;
        }
        /// <summary>
        /// Ecrivain
        /// </summary>
        IAuteur Ecrivain
        {
            get;
            set;
        }
        /// <summary>
        /// Editeur
        /// </summary>
        IEditeur Editeur
        {
            get;
            set;
        }
        /// <summary>
        /// Genre
        /// </summary>
        IGenre Genre
        {
            get;
            set;
        }
        /// <summary>
        /// Prix
        /// </summary>
        double Prix
        {
            get;
            set;
        }

    }
}
