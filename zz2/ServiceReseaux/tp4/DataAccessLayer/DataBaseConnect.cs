using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer
{


    public class DataBaseConnect
    {
         private static DataBaseConnect instance;
         private IBridge Base;

         private DataBaseConnect() 
         {
             Base = new ManagerSQL();
             Base.Connexion("C:\\Users\\jc\\Documents\\Visual Studio 2010\\Projects\\tp4\\DataAccessLayer\\Database1.sdf", "127.0.0.1", "root", null);

         }

         public static DataBaseConnect Instance
         {
                 get 
                 {
                     if (instance == null)
                     {
                         instance = new DataBaseConnect();
                     }
                     return instance;
                 }
         }



    }



}
