using System;


namespace Serveur
{
    /// <summary>
    /// Cette classe modelise un message sur le serveur
    /// </summary>
    public class Message
    {
        private string text;
        private string auteur;
        private DateTime creation;

        /// <summary>
        /// Constructeur
        /// </summary>
        /// <param name="auteur">
        /// login de l'auteur du message
        /// </param>
        /// <param name="text">
        /// contenue du message
        /// </param>
        public Message(string auteur, string text)
        {
            this.auteur = auteur;
            this.text = text;
            creation = DateTime.Now;
        }

        /// <summary>
        /// Constructeur par defaut (necessaire pour la serialisation)
        /// </summary>
        public Message()
        {
            creation = DateTime.Now;
        }

        //proprietes
        public string Text
        {
            get { return text; }
            set { text = value; }
        }

        public string Auteur
        {
            get { return auteur; }
            set { auteur = value; }
        }

        public DateTime Creation
        {
            get { return creation; }
            set { creation = value; }
        }
    }
}