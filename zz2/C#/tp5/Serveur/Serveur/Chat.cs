using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Serialization;
using System.IO;

namespace Serveur
{
    /// <summary>
    /// Classe modelisant le service complet de messagerie
    /// </summary>
    public class Chat
    {
        private IList<Message> messages;
        private IList<User> users;

        /// <summary>
        /// Constructeur par defaut
        /// </summary>
        public Chat()
        {
            messages = new List<Message>();
            users = new List<User>();
        }

        /// <summary>
        /// Methode qui ajoute un message au chat
        /// </summary>
        /// <param name="inAdd">
        /// message a ajouter
        /// </param>
        public void AddMessage(Message inAdd)
        {
            messages.Add(inAdd);
        }

        /// <summary>
        /// Methode qui ajoute un utilisateur au chat
        /// </summary>
        /// <param name="inAdd">
        /// Utilisateur a ajouter
        /// </param>
        public void AddUser(User inAdd)
        {
            users.Add(inAdd);
        }

        /// <summary>
        /// Enleve un utilisateur du chat
        /// </summary>
        /// <param name="toRemove">
        /// Utilisateur a enlever (la comparaison entre utilisateur se fait par le nick)
        /// </param>
        public void RemoveUser(User toRemove)
        {
            users.Remove(toRemove);
        }

        /// <summary>
        /// Serialise une instance de chat
        /// </summary>
        public void Serialiser()
        {
            //on serialise en 2 fichiers separes pour des questions de maintenance
            //serialisation des messages
            TextWriter writer = new StreamWriter("Message_serialization.xml");
            XmlSerializer serializerMessage = new XmlSerializer(typeof(Message[]));
            Message[] toSerializeMessages = messages.ToArray();
            serializerMessage.Serialize(writer, toSerializeMessages);
           
            writer.Close();
            
            //serialisation des users
            writer = new StreamWriter("User_serialization.xml");
            XmlSerializer serializerUsers = new XmlSerializer(typeof(UserSave[]));
            //le passage a usersave permet de serialiser en effet User contient une List<Message>
            //or ce type de variable ne peut pas etre serialiser donc on passe par une nouvelle classe.
            List<UserSave> listToSave = new List<UserSave>();
            foreach(User a in users)
            {
                listToSave.Add(a.ConvertToUserSave());
            }
            UserSave[] toSerializeUsers = listToSave.ToArray();
            serializerUsers.Serialize(writer, toSerializeUsers);
            writer.Close();
        }

        /// <summary>
        /// Deserialise une instance de chat
        /// Permet de contourner la difficulte, le type stateless du webservice
        /// </summary>
        public void Deserialiser()
        {
            try
            {
                FileStream fs = new FileStream("Message_serialization.xml", FileMode.Open);
                TextReader reader = new StreamReader(fs);
                //deserialiser les messages
                XmlSerializer serializerMessage = new XmlSerializer(typeof(Message[]));
                Message[] toDeserializeMessages = (Message[])serializerMessage.Deserialize(reader);
                this.messages = toDeserializeMessages.ToList<Message>();
                reader.Close();

                //deserialiser les users
                fs = new FileStream("User_serialization.xml", FileMode.Open);
                reader = new StreamReader(fs);
                XmlSerializer serializerUser = new XmlSerializer(typeof(UserSave[]));
                //comme pour la serialisation on est oblige de passer une classe temporaire
                UserSave[] toDeserializeUserSave = (UserSave[])serializerUser.Deserialize(reader);
                foreach (UserSave a in toDeserializeUserSave)
                {
                    this.users.Add(a.ConvertToUser());
                }
                reader.Close();
            }
            catch (FileNotFoundException)
            {
            }
        }

        /// <summary>
        /// Recherche un utilisateur parmi la liste des utilisateurs inscrits
        /// </summary>
        /// <param name="nick">
        /// utilisateur a rechercher
        /// </param>
        /// <returns>
        /// l'utilisateur si il est trouve, null sinon
        /// </returns>
        public User SearchNick(string nick)
        {
            User user = null;
            List<User> LinqResult = new List<User>();
            LinqResult = (from u in users
                          where u.Login == nick
                          select u).ToList<User>();

            //cette partie du code est plus facile a ecrire comme ceci 
            //que redefinir la valeur par default d'User et d'utiliser
            //la methode firstordefault.
            if (LinqResult.Count != 0)
            {
                user = LinqResult.First<User>();
            }   
            return user;
        }

        //proprietes
        public IList<Message> Messages
        {
            get { return messages; }
            set { messages = value; }
        }

        public IList<User> Users
        {
            get { return users; }
            set { users = value; }
        }
    }
}