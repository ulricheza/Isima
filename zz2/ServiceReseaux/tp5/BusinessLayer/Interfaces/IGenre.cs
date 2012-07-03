using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BusinessLayer.Interfaces
{
    /// <summary>
    /// Interface de la classe Genre
    /// </summary>
    public interface IGenre
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
        /// Nom
        /// </summary>
        string Name
        {
            get;
            set;
        }
    }
}
