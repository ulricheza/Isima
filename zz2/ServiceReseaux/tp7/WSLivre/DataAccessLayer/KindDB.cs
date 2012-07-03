using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer
{
    /// <summary>
    /// Type dans la base de donnée
    /// </summary>
    public class KindDB
    {
        private string guid;
        private string type;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="inGuid">Guid</param>
        /// <param name="inType">Type</param>
        public KindDB(string guid, string type)
        {
            this.guid = guid;
            this.type = type;
        }

        //proprietes
        public string Name
        {
            get { return type; }
            set { type = value; }
        }

        public string Guid
        {
            get { return guid; }
            set { guid = value; }
        }
    }
}
