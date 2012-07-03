using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DataAccessLayer
{
    public class OrderDB
    {
        private string ordernumber;
        private string creditcard;
        private string shipping;
        private string invoicing;       
        private BookDB[] books;

        /// <summary>
        /// Constructeur de la classe OrderDB
        /// </summary>
        /// <param name="ordernumber">numero de commande</param>
        /// <param name="creditcard">numero de carte de credit</param>
        /// <param name="shipping">adresse d'envoi</param>
        /// <param name="invoicing">adresse de facturation</param>
        /// <param name="books">livres commande</param>
        public OrderDB(string ordernumber, string creditcard, string shipping, string invoicing, BookDB[] books)
        {
            this.ordernumber = ordernumber;
            this.creditcard = creditcard;
            this.shipping = shipping;
            this.invoicing = invoicing;
            this.books = books;
        }

        //Proprietes

        public string Ordernumber
        {
            get { return ordernumber; }
            set { ordernumber = value; }
        }

        public string Creditcard
        {
            get { return creditcard; }
            set { creditcard = value; }
        }

        public string Shipping
        {
            get { return shipping; }
            set { shipping = value; }
        }

        public string Invoicing
        {
            get { return invoicing; }
            set { invoicing = value; }
        }

        public BookDB[] Books
        {
            get { return books; }
            set { books = value; }
        }
    }
}
