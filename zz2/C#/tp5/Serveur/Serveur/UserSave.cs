using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Security.Cryptography;

namespace Serveur
{
    /// <summary>
    /// Classe representant un utilisateur afin de le serialiser
    /// </summary>
    public class UserSave
    {
        private string login;
        private int password;
        private DSAParameters publickey;
        private Message[] privatemessage;
        private DateTime lastread;

        
        /// <summary>
        /// Constructeur par defaut
        /// </summary>
        public UserSave()
        {
        }

        /// <summary>
        /// Methode qui convertit un UserSave en User afin de l'utiliser dans le serviceweb
        /// </summary>
        /// <returns> Une instance de User representant l'UserSave en cours</returns>
        public User ConvertToUser()
        {
            User convert = new User();
            convert.Login = login;
            convert.Password = password;
            convert.Publickey = publickey;
            convert.PrivateMessage = privatemessage.ToList<Message>();
            convert.LastRead = lastread;
            return convert;
        }

        //proprietes de la classe
        public string Login
        {
            get { return login; }
            set { login = value; }
        }

        public int Password
        {
            get { return password; }
            set { password = value; }
        }

        public DSAParameters Publickey
        {
            get { return publickey; }
            set { publickey = value; }
        }

        public Message[] PrivateMessage
        {
            get { return privatemessage; }
            set { privatemessage = value; }
        }

        public DateTime LastRead
        {
            get { return lastread; }
            set { lastread = value; }
        }
    }
}