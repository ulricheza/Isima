using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Security.Cryptography;
using System.Text;
using System.IO;

namespace Serveur
{
    /// <summary>
    /// Classe principale du webservice
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]

    public class ServeurChat : System.Web.Services.WebService
    {

        /// <summary>
        /// Methode permettant a un utilisateur de se connecter
        /// </summary>
        /// <param name="nick"> login de l'utilisateur</param>
        /// <param name="password"> password de l'utilisateur</param>
        /// <param name="nickhashed">login signe</param>
        /// <returns>true si il y a eu connection false sinon</returns>
        [WebMethod]
        public bool LogIn(string nick, string password,byte[] nickhashed, int counter, byte[] G, byte[] J, byte[] P, byte[] Q, byte[] Seed, byte[] X, byte[] Y)
        {
            bool result = false;
            Chat instance = new Chat();
            instance.Deserialiser();
            User user = instance.SearchNick(nick);
            if (user != null) //si l'utilisateur existe
            {
                if (user.CheckPassword(password)) //si le mot de passe de l'utilisateur est bon
                {
                    DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
                    DSAParameters key = Security.RecreateKey(counter, G, J, P, Q, Seed, X, Y);
                    mycrypto.ImportParameters(key);
                    ASCIIEncoding encoding = new ASCIIEncoding();
                    if (mycrypto.VerifyData(encoding.GetBytes(nick), nickhashed)) //verification de la cle publique recue
                    {
                        result = true;
                        instance.RemoveUser(user);
                        user.Publickey = key; //on stocke la cle publique pour la reception prochaine de message
                        instance.AddUser(user);
                        instance.Serialiser();
                    }
                }
            }
            return result;
        }

        /// <summary>
        /// Methode permettant d'enregister un nouvel utilisateur sur le serveur
        /// </summary>
        /// <param name="nick">login de l'utilisateur</param>
        /// <param name="password">mot de passe de l'utilisateur</param>
        /// <param name="nickhashed">login signe</param>
        /// <returns>true si l'enregistrement a eu lieu false sinon</returns>
        [WebMethod]
        public bool Register(string nick, string password,byte[] nickhashed, int counter, byte[] G, byte[] J, byte[] P, byte[] Q, byte[] Seed, byte[] X, byte[] Y)
        {
            bool result = false;
            Chat instance = new Chat();
            instance.Deserialiser();
            User user = instance.SearchNick(nick);
            if (user == null) //si l'utilisateur n'existe deja pas
            {
                DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
                DSAParameters key = Security.RecreateKey(counter, G, J, P, Q, Seed, X, Y);
                mycrypto.ImportParameters(key); 
                ASCIIEncoding encoding = new ASCIIEncoding();
                if (mycrypto.VerifyData(encoding.GetBytes(nick), nickhashed)) //verifie la cle publique recue
                {
                    User newcommer = new User(nick, password, key);
                    instance.AddUser(newcommer);
                    instance.Serialiser();
                    result = true;
                }
            }
            return result;
        }

        /// <summary>
        /// Reception d'un message public
        /// </summary>
        /// <param name="nick">Auteur du message</param>
        /// <param name="message">texte du message</param>
        /// <param name="messagehashed">message signe</param>
        /// <returns></returns>
        [WebMethod]
        public bool SendMessage(string nick, string message, byte[] messagehashed)
        {
            bool result = false;
            Chat instance = new Chat();
            instance.Deserialiser();
            User user = instance.SearchNick(nick); //verification de l'utilisateur
            if (user != null)
            {
                ASCIIEncoding encoding = new ASCIIEncoding();
                DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
                mycrypto.ImportParameters(user.Publickey);
                if(mycrypto.VerifyData(encoding.GetBytes(message), messagehashed)) //on verifie que le message provient bien de l'utilisateur
                {
                    Message news = new Message(nick, message);
                    instance.AddMessage(news);
                    instance.Serialiser();
                    result = true;
                }
            }
            return result;
        }

        /// <summary>
        /// Reception d'un message prive
        /// </summary>
        /// <param name="nick"> Auteur du message</param>
        /// <param name="recipient">Destinataire du message</param>
        /// <param name="message">texte du message</param>
        /// <param name="messagehashed">message signe</param>
        /// <returns></returns>
        [WebMethod]
        public bool SendPrivateMessage(string nick, string recipient, string message, byte[] messagehashed)
        {
            bool result = false;
            Chat instance = new Chat();
            instance.Deserialiser();
            User user = instance.SearchNick(nick); //on verifie que l'auteur existe
            if (user != null)
            {
                ASCIIEncoding encoding = new ASCIIEncoding();
                DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
                mycrypto.ImportParameters(user.Publickey);
                if (mycrypto.VerifyData(encoding.GetBytes(message), messagehashed)) //on verifie la provenance du message
                {
                    Message news = new Message(nick, message);
                    User todeliver = instance.SearchNick(recipient); //on verifie la presence du destinataire
                    if (todeliver != null)
                    {
                        Message privatemessage = new Message(nick, message);
                        instance.RemoveUser(todeliver);
                        todeliver.AddPrivateMessage(privatemessage);
                        instance.AddUser(todeliver);
                        instance.Serialiser();
                        result = true;
                    }
                }
            }
            return result;
        }

        /// <summary>
        /// Envoi de tous les messages publics
        /// </summary>
        /// <param name="nick">login du demandeur</param>
        /// <param name="nickhashed">login signe</param>
        /// <returns>la tableau de tous les messages public, null si il y en a aucun</returns>
        [WebMethod]
        public Message[] ReceiveAllMessage(string nick, byte[] nickhashed)
        {
            Chat instance = new Chat();
            instance.Deserialiser();
            Message[] message = null;
            User user = instance.SearchNick(nick);
            if (user != null) //on verifie si le demandeur existe
            {
                ASCIIEncoding encoding = new ASCIIEncoding();
                DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
                mycrypto.ImportParameters(user.Publickey);
                if (mycrypto.VerifyData(encoding.GetBytes(nick), nickhashed)) //on verifie la provenance de la demande
                {
                    message = instance.Messages.ToArray<Message>();
                }
            }
            return message;
        }

        /// <summary>
        /// Envoi de tous les messages non-lus par l'utilisateur demandeur
        /// </summary>
        /// <param name="nick">login du demandeur</param>
        /// <param name="nickhashed">login signe</param>
        /// <returns>Le tableau des messages non-lus, null si il n'y en a pas</returns>
        [WebMethod]
        public Message[] ReceiveMessageNonRead(string nick, byte[] nickhashed)
        {

            Chat instance = new Chat();
            instance.Deserialiser();
            User user = instance.SearchNick(nick);
            Message[] unread = null;
            if (user != null) //on verifie si l'utilisateur existe
            {
                ASCIIEncoding encoding = new ASCIIEncoding();
                DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
                mycrypto.ImportParameters(user.Publickey);
                if (mycrypto.VerifyData(encoding.GetBytes(nick), nickhashed)) //on verifie la provenance de la demande
                {
                    //requete LINQ pour recuperer les messages a lire
                    unread = (from Message m in instance.Messages
                              where m.Creation > user.LastRead
                              select m).ToArray<Message>();

                    instance.RemoveUser(user);
                    user.LastRead = DateTime.Now; //on modifie la date de derniere lecture
                    instance.AddUser(user);
                    instance.Serialiser();
                }
            }
            return unread;
        }

        /// <summary>
        /// Envoie les messages prives de l'utilisateur
        /// </summary>
        /// <param name="nick">login de l'utilisateur</param>
        /// <param name="nickhashed">login signe</param>
        /// <returns>le tableau des messages prives, null si il n'y en a pas</returns>
        [WebMethod]
        public Message[] ReceivePrivateMessage(string nick, byte[] nickhashed)
        {
            Chat instance = new Chat();
            instance.Deserialiser();
            User user = instance.SearchNick(nick);
            Message[] privatemessage = null;
            if (user != null) //si l'utilisateur existe
            {
                ASCIIEncoding encoding = new ASCIIEncoding();
                DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
                mycrypto.ImportParameters(user.Publickey);
                if (mycrypto.VerifyData(encoding.GetBytes(nick), nickhashed)) //verification de la provenance du message
                {
                    privatemessage = user.PrivateMessage.ToArray<Message>();
                }
            }
            return privatemessage;
        }


        /// <summary>
        /// Methode de changement de login
        /// </summary>
        /// <param name="oldnick"></param>
        /// <param name="newnick"></param>
        /// <param name="newnickhashed"></param>
        /// <returns></returns>
        [WebMethod]
        public bool ChangeNick(string oldnick, string newnick, byte[] newnickhashed)
        {
            bool result = false;
            Chat instance = new Chat();
            instance.Deserialiser();
            User user = instance.SearchNick(oldnick);
            if (user != null) //si l'utilisateur actuel existe
            {
                if (instance.SearchNick(newnick) == null) //si le nouveau login choisi est bon
                {
                    ASCIIEncoding encoding = new ASCIIEncoding();
                    DSACryptoServiceProvider mycrypto = new DSACryptoServiceProvider();
                    mycrypto.ImportParameters(user.Publickey);
                    if (mycrypto.VerifyData(encoding.GetBytes(newnick), newnickhashed)) //verification de la provenance du message
                    {
                        instance.RemoveUser(user);
                        user.Login = newnick;
                        instance.AddUser(user);
                        instance.Serialiser();
                        result = true;
                    }
                }
            }
            return result;
        }
    
    
    }
}