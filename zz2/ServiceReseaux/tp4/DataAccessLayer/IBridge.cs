using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace DataAccessLayer
{
    public interface IBridge
    {
    void Connexion(string bdd, string server, string user, string pass);
        DataTable Select(string strRequete); 
    }
}
