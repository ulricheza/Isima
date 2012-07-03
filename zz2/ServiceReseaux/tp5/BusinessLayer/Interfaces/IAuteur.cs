using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BusinessLayer.Interfaces
{
    /// <summary>
    /// Interface de la classe auteur
    /// </summary>
    public interface IAuteur
    {
        string GUID
        {
            get;
            set;
        }
        string FirstName
        {
            get;
            set;
        }
        string LastName
        {
            get;
            set;
        }
        string PhoneNumber
        {
            get;
            set;
        }
        string Adress
        {
            get;
            set;
        }
    }
}
