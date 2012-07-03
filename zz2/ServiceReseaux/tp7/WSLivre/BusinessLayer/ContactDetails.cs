using System;

namespace BusinessLayer
{
    /// <summary>
    /// Classe represantant une adresse d'une personne
    /// </summary>
    [Serializable]
    public class ContactDetails
    {
        private string name;
        private string adress;
        private string zipcode;
        private string city;

        public ContactDetails(string name, string adress, string zipcode, string city)
        {
            this.name = name;
            this.adress = adress;
            this.zipcode = zipcode;
            this.city = city;
        }

        /// <summary>
        /// Constructeur par defaut necessaire pour la serialisation du service web
        /// </summary>
        public ContactDetails()
        { 
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string Adress
        {
            get { return adress; }
            set { adress = value; }
        }

        public string Zipcode
        {
            get { return zipcode; }
            set { zipcode = value; }
        }

        public string City
        {
            get { return city; }
            set { city = value; }
        }

    }
}