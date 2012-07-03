using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Data;

namespace DataAccessLayer
{
   
    public class ManagerSQL:IBridge
    {
        private SqlConnection sqlConnect;

        public void Connexion(string bdd, string server, string user, string pass)
        {
            string chaineConnexion = string.Format("Data Source=|DataDirectory|\\DBBook.sdf");
            sqlConnect = new SqlConnection(chaineConnexion);
            sqlConnect.Open();
        }
       
        public DataTable Select(string strRequete)
        {
            if (sqlConnect != null)
            {
                DataTable dt = new DataTable();
                SqlTransaction myTrans =
                sqlConnect.BeginTransaction();
                SqlCommand sqlCommande = new
                SqlCommand(strRequete, sqlConnect, myTrans);
                SqlDataAdapter sqlAdapte = new
                SqlDataAdapter(sqlCommande);
                try
                {
                    sqlAdapte.Fill(dt);
                    myTrans.Commit();
                    return dt;
                }
                catch
                {
                    myTrans.Rollback();
                    return null;
                }
            }
            return null;
        }


    }
}

