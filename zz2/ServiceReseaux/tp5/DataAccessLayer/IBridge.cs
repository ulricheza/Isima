using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace DataAccessLayer
{
    /// <summary>
    /// Interface qui représente un Bridge vers la base de donnée
    /// </summary>
    public interface IBridge
    {
        void Connexion();
        DataTable Select(string strRequete);
        int Update(string strRequete, DataTable dttable);
    }
}
