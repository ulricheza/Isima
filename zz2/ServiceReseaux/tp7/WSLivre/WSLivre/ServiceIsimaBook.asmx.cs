using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using BusinessLayer;

namespace WSLivre
{
    /// <summary>
    /// Description résumée de Service1
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // Pour autoriser l'appel de ce service Web depuis un script à l'aide d'ASP.NET AJAX, supprimez les marques de commentaire de la ligne suivante. 
    // [System.Web.Script.Services.ScriptService]
    public class ServiceIsimaBook : System.Web.Services.WebService
    {

        /// <summary>
        /// Methode pour le fun =)
        /// </summary>
        /// <returns>Hello World </returns>
        [WebMethod]
        public string HelloWorld()
        {
            return "Hello World";
        }

        /// <summary>
        /// Enregistre une commande
        /// Choses que l'on verifie dan sle service web:
        /// - L'existance de tous les livres demandes
        /// - La validite de la carte de crédit
        /// </summary>
        /// <param name="books">livre a commander</param>
        /// <param name="creditcard">carte de credit utiliser pour la commande</param>
        /// <param name="shipping">Adresse pour la livraison</param>
        /// <param name="invoicing">Adresse pour la facturation </param>
        /// <returns></returns>
        [WebMethod]
        public string RegisterOrder(string username, Book[] books, string creditcard, ContactDetails shipping, ContactDetails invoicing)
        {
            string guid = null;
            if (Order.VerifyCreditCard(creditcard) == true)
            {
                int i = 0;
                bool verifybook = true;
                Library lib = new Library();
                lib.UpdateDB();
                while (i < books.Length && verifybook == true)
                {
                    verifybook = lib.Contains(books[i++]);
                }
                if (verifybook == true)
                {
                    Order toregister = new Order(shipping, invoicing, creditcard, books);
                    toregister.OrderSerializer();
                    toregister.OrderStorage(username);
                    guid = toregister.Ordernumber;
                }
            }
            return guid;
        }

        /// <summary>
        /// Methode de verification de la validite d'une carte de credit
        /// </summary>
        /// <param name="creditcard">Numero de la carte de credit a verifier</param>
        /// <returns>true si la carte est valide</returns>
        [WebMethod]
        public bool VerifyCreditCard(string creditcard)
        {
            return Order.VerifyCreditCard(creditcard);
        }

        /// <summary>
        /// Methode qui permet de retourner tous les livres de la BDD
        /// </summary>
        /// <returns>le tableau des livres de la BDD</returns>
        [WebMethod]
        public Book[] AllBooks()
        {
            Library lib = new Library();
            lib.UpdateDB();
            return lib.Books.ToArray<Book>();
        }

        /// <summary>
        /// Methode de recherche de livre par auteur
        /// </summary>
        /// <param name="writer">nom de l'auteur a retrouver</param>
        /// <returns>le tableau des livres ecrit par cet auteur</returns>
        [WebMethod]
        public Book[] BookByWriter(String writer)
        {
            Library lib = new Library();
            lib.UpdateDB();
            return lib.FindBooksByAuthor(writer);
        }

        /// <summary>
        /// Recherche de livre par titre
        /// </summary>
        /// <param name="title">titre du livre a trouver</param>
        /// <returns>le tableau des livres dont le titre coincide </returns>
        [WebMethod]
        public Book[] BookByTitle(String title)
        {
            Library lib = new Library();
            lib.UpdateDB();
            return lib.FindBooksByName(title);
        }

        /// <summary>
        /// Recherche de livre par GUID
        /// </summary>
        /// <param name="GUID">Guid du livre a chercher</param>
        /// <returns>le livre concerne si il existe sinon null</returns>
        [WebMethod]
        public Book BookByGUID(string GUID)
        {
            Library lib = new Library();
            lib.UpdateDB();
            return lib.FindBookByGUID(GUID);
        }

        /// <summary>
        /// Methode d'ajout d'un auteur dans la base de données
        /// </summary>
        /// <param name="username">pseudo de l'utilisateur</param>
        /// <param name="adress">adresse de l'utilisateur</param>
        /// <param name="zipcode">Code postal</param>
        /// <param name="city">Ville</param>
        /// <param name="password">Mot de passe de l'user</param>
        [WebMethod]
        public bool AddUser(String username, String adress, String zipcode, String city, String password)
        {
            Library lib = new Library();
            lib.UpdateDB();
            return (lib.AddUserDB(username, adress, zipcode, city, password));
        }

        /// <summary>
        /// Permet de verifier l'association nick/password
        /// </summary>
        /// <param name="username">Nom d'utilisateur</param>
        /// <param name="password">Password User</param>
        /// <returns>true si verifier false sinon </returns>
        [WebMethod]
        public bool VerifyUser(String username, String password)
        {
            Library lib = new Library();
            lib.UpdateDB();
            return lib.VerifyUser(username, password);
        }

        /// <summary>
        /// Convertit le prix dans la devise voulue
        /// </summary>
        /// <param name="europrice">Prix en euro</param>
        /// <param name="curr">Devise voulue</param>
        /// <returns>le prix en la devise voulue</returns>
        [WebMethod]
        public double ConvertEuroTo(double europrice,CurrencyConvertor.Currency exchange)
        {
            CurrencyConvertor.CurrencyConvertorSoapClient service = new CurrencyConvertor.CurrencyConvertorSoapClient();
            double rate = service.ConversionRate(CurrencyConvertor.Currency.EUR, exchange);
            return (europrice*rate);
        }
        
    }
}