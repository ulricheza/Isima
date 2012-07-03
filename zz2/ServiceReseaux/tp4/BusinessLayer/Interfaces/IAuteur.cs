using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BusinessLayer.Interfaces
{
    public interface IAuteur
    {
        int GUID
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
