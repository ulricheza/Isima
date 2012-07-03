using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Data;

namespace DataAccessLayer.SQLDatabase
{
    class ManagerSQL
    {
        private SqlConnection sqlConnect;

        //C:\Users\Maxime\Documents\Visual Studio 2010\Projects\DataBase\EASY_BOOKING_Data.MDF

        /// <summary>
        /// Permet de se connecter
        /// </summary>
        public bool Connexion()
        {
            string chaineConnexion = string.Format("Data Source=.\\SQLEXPRESS;AttachDbFilename=\"C:\\Users\\Maxime\\Documents\\Visual Studio 2010\\Projects\\DataBase\\EASY_BOOKING_Data.MDF\";Integrated Security=True;Connect Timeout=30;User Instance=True");
            sqlConnect = new SqlConnection(chaineConnexion);
            try
            {
                sqlConnect.Open();
                return true;
            }
            catch (InvalidOperationException) //Pour des erreurs de connections la BDD
            {
                return(false);
            }
            catch (SqlException) //Exemple d'erreur: Identification errone
            {
                return(false);
            }
        }

        /// <summary>
        /// Permet de faire une requète de type select
        /// </summary>
        /// <param name="strRequete">Requète utilisée</param>
        /// <returns></returns>
        public System.Data.DataTable Select(string strRequete)
        {
            if (sqlConnect != null)
            {
                DataTable dt = new DataTable();
                SqlTransaction myTrans = sqlConnect.BeginTransaction();
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

        /// <summary>
        /// Permet de faire une requète de type UPDATE ou INSERT INTO
        /// </summary>
        /// <param name="rqt"> Requète</param>
        /// <param name="dt"> Database à modifier</param>
        /// <returns></returns>
        public int Update(string strRequete, System.Data.DataTable dttable)
        {
            if (sqlConnect != null)
            {
                SqlTransaction trans = sqlConnect.BeginTransaction();
                SqlCommand sqlCmd = new SqlCommand(strRequete, sqlConnect, trans);
                SqlDataAdapter sqlDA = new SqlDataAdapter(sqlCmd);
                SqlCommandBuilder build = new SqlCommandBuilder(sqlDA);
                sqlDA.UpdateCommand = build.GetUpdateCommand();
                sqlDA.InsertCommand = build.GetInsertCommand();
                sqlDA.DeleteCommand = build.GetDeleteCommand();

                sqlDA.MissingSchemaAction = MissingSchemaAction.AddWithKey;

                try
                {
                    int res = sqlDA.Update(dttable);
                    trans.Commit();
                    return res;
                }
                catch (DBConcurrencyException)
                {
                    trans.Rollback();
                }
            }
            return 0;
        }
    }
}
