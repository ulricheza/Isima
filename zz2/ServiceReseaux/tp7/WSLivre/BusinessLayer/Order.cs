using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.IO;
using System.Runtime.Serialization.Formatters.Soap;
using DataAccessLayer.SQLDatabase;
using DataAccessLayer;

namespace BusinessLayer
{
    /// <summary>
    /// Classe represantant un enregistrement de commande
    /// </summary>
    [Serializable]
    public class Order
    {
        private string ordernumber;
        private string creditcard;
        private ContactDetails shipping;
        private ContactDetails invoicing;
        private Book[] books;
        private DataBaseConnect database;

       
        /// <summary>
        /// instancie une commande afin de la serialiser par la suite pour les services de traitement.
        /// </summary>
        /// <param name="shipping"></param>
        /// <param name="facturation"></param>
        /// <param name="creditcard"></param>
        /// <param name="books"></param>
        public Order(ContactDetails shipping, ContactDetails invoicing, string creditcard, Book[] books)
        {
            this.shipping = shipping;
            this.invoicing = invoicing;
            this.creditcard = creditcard;
            this.books = books;
            this.ordernumber = Guid.NewGuid().ToString();
            database = new DataBaseConnect();
        }

        /// <summary>
        /// Constructeur par defaut necessaire pour la serialisation du service web et celle pour le soap
        /// </summary>
        public Order()
        {
            database = new DataBaseConnect();
        }

        /// <summary>
        /// Serialise une commande pour la traiter par un autre service
        /// </summary>
        public void OrderSerializer()
        {
            string filename = ordernumber + ".xml" ;
            SoapFormatter saveorder = new SoapFormatter();
            FileStream file = new FileStream( filename , FileMode.Create);
            saveorder.Serialize(file, this);
            file.Close();
        }

        /// <summary>
        /// Verifie la validite d'une carte de credit
        /// Cette methode implemente l'algorithme de luhn
        /// </summary>
        /// <param name="creditcard">Numero de la carte a verifier</param>
        /// <returns></returns>
        public static bool VerifyCreditCard(string creditcard)
        {
            int number;
            int card = 0;
            int counter = creditcard.Length;
            bool retour = false;

            try
            {
                foreach(char i in creditcard)
                {
                    number = int.Parse(i.ToString());
                    if ( counter-- % 2 == 0)
                    {
                        number = number * 2;
                        if (number > 9)
                        {
                            number = number % 10 + 1;
                        }
                    }
                    card += number;
                }

                if (card % 10 == 0)
                {
                    retour = true;
                }

                return retour;
            }
            catch (FormatException)
            {
                return false;
            }
        }

        /// <summary>
        /// Stocke la commande dans la base de donnees 
        /// </summary>
        public void OrderStorage(string usernumber)
        {
            string invoicing = this.invoicing.Name + " " + this.invoicing.Adress + " " + this.invoicing.Zipcode + " " + this.invoicing.City;
            string shipping = this.shipping.Name + " " + this.shipping.Adress + " " + this.shipping.Zipcode + " " + this.shipping.City;
            BookDB[] booksDB = new BookDB[books.Length];
            for(int i = 0; i < books.Length ; ++i)
            {
                booksDB[i] = new BookDB(books[i].GUID,books[i].Title,books[i].ReleaseDate,null,null,books[i].Publisher.Name,
                                        books[i].Price.ToString(),books[i].Type.Name,books[i].Description);
            }
            database.AddOrder(usernumber, ordernumber, creditcard, shipping, invoicing, booksDB);
        }



        //proprietes
        public string Ordernumber
        {
            get { return ordernumber; }
            set { ordernumber = value; }
        }

        public string CreditCard
        {
            get { return creditcard; }
            set { creditcard = value; }
        }

        public ContactDetails Shipping
        {
            get { return shipping; }
            set { shipping = value; }
        }

        public ContactDetails Invoicing
        {
            get { return invoicing; }
            set { invoicing = value; }
        }

        public Book[] Books
        {
            get { return books; }
            set { books = value; }
        }
    }
}