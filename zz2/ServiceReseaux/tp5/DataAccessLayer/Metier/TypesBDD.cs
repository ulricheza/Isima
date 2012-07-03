using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer.Metier
{
    /// <summary>
    /// Type dans la base de donnée
    /// </summary>
    public class TypesBDD
    {
        private string _guid;
        private string _type;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="inGuid">Guid</param>
        /// <param name="inType">Type</param>
        public TypesBDD(string inGuid, string inType)
        {
            _guid = inGuid;
            _type = inType;
        }

        // ----------------------
        // Propriété
        // ----------------------
        public string Name
        {
            get { return _type; }
            set { _type = value; }
        }

        public string Guid
        {
            get { return _guid; }
            set { _guid = value; }
        }

    }
}
