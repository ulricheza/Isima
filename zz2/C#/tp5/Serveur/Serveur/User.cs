using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;

namespace Serveur
{
    /// <summary>
    /// Classe modelisant un utilisateur du chat
    /// Implemente l'interface qui permet de comparer deux utilisateurs
    /// </summary>
    public class User : IEqualityComparer<User>
    {
        private string login;
        private int password;
        private DSAParameters publickey;
        private List<Message> privatemessage;
        private DateTime lastread;

        /// <summary>
        /// Constructeur par defaut
        /// </summary>
        public User()
        {
            this.privatemessage = new List<Message>();
            lastread = DateTime.MinValue;
        }

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="login">login de l'utilisateur</param>
        /// <param name="password">password de l'utilisateur</param>
        public User(string login, string password)
        {
            this.login = login;
            this.password = password.GetHashCode();
            this.privatemessage = new List<Message>();
            lastread = DateTime.MinValue;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="login">login de l'utilisateur</param>
        /// <param name="password">password de l'utilisateur</param>
        /// <param name="publickey">Key publique de l'utilisateur</param>
        public User(string login, string password, DSAParameters publickey)
        {
            this.login = login;
            this.password = password.GetHashCode();
            this.publickey = publickey;
            this.privatemessage = new List<Message>();
            lastread = DateTime.MinValue;
        }

        /// <summary>
        /// Methode de test de mot de passe valide
        /// </summary>
        /// <param name="InCheck">mot de passe a tester</param>
        /// <returns>true si le mot de passe est correct, false sinon</returns>
        public bool CheckPassword(string InCheck)
        {
            return (password == InCheck.GetHashCode());
        }

        /// <summary>
        /// Methode d'ajout d'un message prive pour l'utilisateur
        /// </summary>
        /// <param name="toAdd">message a ajouter</param>
        public void AddPrivateMessage(Message toAdd)
        {
            privatemessage.Add(toAdd);
        }

        /// <summary>
        /// Convertisseur de User en UserSave afin de serialiser un utilisateur
        /// </summary>
        /// <returns>une instance de UserSave representant l'utilisateur en cours</returns>
        public UserSave ConvertToUserSave()
        {
            UserSave convert = new UserSave();
            convert.Login = login;
            convert.Password = password;
            convert.Publickey = publickey;
            convert.PrivateMessage = privatemessage.ToArray<Message>();
            convert.LastRead = lastread;
            return convert;
        }

        /// <summary>
        /// Methode de comparaison de 2 utilisateurs
        /// </summary>
        /// <param name="x">User 1</param>
        /// <param name="y">User 2</param>
        /// <returns>true si les logins sont identiques, false sinon</returns>
        public bool Equals(User x, User y)
        {
            return (x.Login == y.Login);
        }

        /// <summary>
        /// Methode faisant partie de l'implementationd e l'interface de IEqualityComparer
        /// Cependant...Elle semble inutile dans notre webservice
        /// </summary>
        /// <param name="obj">instance de User</param>
        /// <returns>Hashcode du login</returns>
        /// 
        public int GetHashCode(User obj)
        {
            return (Login.GetHashCode());
        }

        //Proprietes de la classe
        public int Password
        {
            get { return password; }
            set { password = value; }
        }

        public string Login
        {
            get { return login; }
            set { login = value; }
        }

        public DSAParameters Publickey
        {
            get { return publickey; }
            set { publickey = value; }
        }

        public List<Message> PrivateMessage
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