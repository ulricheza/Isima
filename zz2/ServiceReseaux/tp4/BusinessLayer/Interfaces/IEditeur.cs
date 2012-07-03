using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BusinessLayer.Interfaces
{
    public interface IEditeur
    {
        int GUID
        {
            get;
            set;
        }

        string Name
        {
            get;
            set;
        }

        string Address
        {
            get;
            set;
        }

    }
}
