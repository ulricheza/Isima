using System;
using System.Collections.Generic;
using System.Data;
using DataAccessLayer;

namespace DataAccessLayer.SQLDatabase
{
    /// <summary>
    /// Permet d'accéder à la base de donnée
    /// </summary>
    public class DataBaseConnect
    {
         private static DataBaseConnect instance;
         private ManagerSQL Base;

        /// <summary>
        /// Permet de se connecter à la base de donnée
        /// </summary>
         public DataBaseConnect() 
         {
             Base = new ManagerSQL(); 
             Base.Connexion();
         }

        /// <summary>
        /// Permet de retourner la liste des éditeurs
        /// </summary>
        /// <returns> la liste des éditeurs </returns>
         public List<EditorDB> getEditeur()
         {
             EditorDB auteur;

             List<EditorDB> EditorsCollection = new List<EditorDB>();
             DataTable t = Base.Select("SELECT * FROM Publishers");

             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 auteur = new EditorDB(row["GUID"].ToString(), row["NAME"].ToString(), row["ADDRESS"].ToString(), row["ZIPCODE"].ToString(), row["CITY"].ToString(),
                                        row["STATE"].ToString(), row["COUNTRY"].ToString());
                 EditorsCollection.Add(auteur);
             }

             return EditorsCollection;
         }

         /// <summary>
         /// Permet de retourner la liste des users
         /// </summary>
         /// <returns> la liste des users </returns>
         public List<UsersDB> getUser()
         {
             UsersDB users;

             List<UsersDB> UsersCollection = new List<UsersDB>();
             DataTable t = Base.Select("SELECT * FROM USERS");
             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 users = new UsersDB(row["username"].ToString(), row["adress"].ToString(), row["zipcode"].ToString(), row["city"].ToString(), Int32.Parse(row["password"].ToString()));
                 UsersCollection.Add(users);
             }

             return UsersCollection;
         }

        /// <summary>
        /// Permet de retourner une liste d'auteur
        /// </summary>
         /// <returns>une liste d'auteur</returns>
         public List<AuthorDB> getAuthors()
         {
             AuthorDB auteur;

             List<AuthorDB> AuthorsCollection = new List<AuthorDB>();
             DataTable t = Base.Select("SELECT * FROM Authors");

             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 auteur = new AuthorDB(row["GUID"].ToString(), row["CIVILITE"].ToString(), row["FIRST_NAME"].ToString(), row["LAST_NAME"].ToString(),
                                       row["PHONE_NUMBER"].ToString(), row["ADDRESS"].ToString(), row["ZIPCODE"].ToString(), row["CITY"].ToString(),
                                       row["STATE"].ToString(), row["COUNTRY"].ToString());
                 
                 AuthorsCollection.Add(auteur);
             }

             return AuthorsCollection; 
         }

        /// <summary>
        /// Permet de retourner la liste des bouquins
        /// </summary>
         /// <returns>la liste des bouquins</returns>
         public List<BookDB> getBooks()
         {
             BookDB book;

             List<BookDB> BookCollection = new List<BookDB>();
             DataTable t = Base.Select("SELECT * FROM BOOKS");

             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 book = new BookDB(row["GUID"].ToString(), row["TITLE"].ToString(), row["PUBLICATION_DATE"].ToString(), row["ISBN_10"].ToString(),
                                        row["ISBN_13"].ToString(), row["PUBLISHER_GUID"].ToString(), row["PRICE"].ToString(), row["TYPE_GUID"].ToString(),
                                        row["DESCRIPTION"].ToString());
                 // Recherche de l'auteur
                 DataTable aut = Base.Select("SELECT * FROM BOOK_AUTHOR WHERE BOOK_GUID IN ('" + row["GUID"].ToString() + "')");
                 DataView vAut = new DataView(aut);
                 DataRow rowAut = vAut[0].Row;
                 book.GuidAuthor = rowAut["AUTHOR_GUID"].ToString();

                 BookCollection.Add(book);
             }

             return BookCollection;

         }

        /// <summary>
        /// Permet de retourner la liste des types de livres
        /// </summary>
         /// <returns>la liste des types de livres</returns>
         public List<KindDB> getTypes()
         {
             KindDB ty;

             List<KindDB> TypesCollection = new List<KindDB>();
             DataTable t = Base.Select("SELECT * FROM TYPES");

             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 ty = new KindDB(row["GUID"].ToString(), row["TYPE"].ToString());
                 TypesCollection.Add(ty);
             }

             return TypesCollection;
         }

        /// <summary>
        /// Permet de supprimer un livre
        /// </summary>
        /// <param name="GUID"> GUID du livre à supprimer</param>
         public void DeleteBook(String GUID)
         {
             DataTable dt;
             DataRow[] deleteRow;

             //supprime d'abord les correspondance avec les auteurs
             dt = Base.Select("Select * from BOOK_AUTHOR");
             deleteRow = dt.Select("book_guid ='" + GUID + "'");
             foreach (DataRow row in deleteRow)
             {
                 row.Delete();
             }

             Base.Update("Select * from BOOK_AUTHOR", dt);

             //supprime le livre
             dt = Base.Select("Select * from BOOKS");
             deleteRow = dt.Select("guid ='" + GUID + "'");
             foreach (DataRow row in deleteRow)
             {
                 row.Delete();
             }

             Base.Update("Select * from BOOKS", dt);
         }

        /// <summary>
        /// Update d'un livre
        /// </summary>
        /// <param name="GUID"> GUID du livre</param>
        /// <param name="titre"> titre du livre</param>
        /// <param name="prix"> prix du livre</param>
        /// <param name="guidAut"> GUID de l'auteur</param>
        /// <param name="guidEd"> GUID de l'éditeur</param>
        /// <param name="guidGenre"> GUID du type de livre</param>
         public void UpdateBook(string GUID, string titre, double prix, string guidAut, string guidEd, string guidGenre)
         {
             DeleteBook(GUID);
             AddBook(GUID, titre, prix, guidAut, guidEd, guidGenre);
         }

        /// <summary>
        /// Permet d'ajouter un livre à la base de donnée
        /// </summary>
         /// <param name="GUID"> GUID du livre</param>
         /// <param name="titre"> titre du livre</param>
         /// <param name="prix"> prix du livre</param>
         /// <param name="guidAut"> GUID de l'auteur</param>
         /// <param name="guidEd"> GUID de l'éditeur</param>
         /// <param name="guidGenre"> GUID du type de livre</param>
         public bool AddBook(string GUID, string titre, double prix, string guidAut, string guidEd, string guidGenre)
         {
             try
             {
                 DataTable dt;

                 dt = Base.Select("Select * from BOOKS");
                 DataRow nRow = dt.NewRow();

                 nRow["guid"] = GUID;
                 nRow["title"] = titre;
                 nRow["publisher_guid"] = guidEd;
                 nRow["type_guid"] = guidGenre;
                 nRow["price"] = prix;

                 dt.Rows.Add(nRow);

                 Base.Update("Select * from BOOKS", dt);

                 //insertion pour enregistrer les auteurs du livre
                 dt = Base.Select("Select * from BOOK_AUTHOR");
                 DataRow newRow = dt.NewRow();
                 newRow["book_guid"] = GUID;
                 newRow["author_guid"] = guidAut;
                 dt.Rows.Add(newRow);

                 Base.Update("Select * from BOOK_AUTHOR", dt);
                 return true;
             }
             catch (Exception)
             {
                 return false;
             }
         }

         /// <summary>
         /// Permet d'ajouter un livre dans la base de donnée
         /// </summary>
         /// <param name="username">Utilisateur</param>
         /// <param name="adress">Adress</param>
         /// <param name="zipcode">Code postal</param>
         /// <param name="city">Ville</param>
         public bool AddUser(string username, string adress, string zipcode, string city, string password)
         {
             try
             {

                 DataTable dt;

                 dt = Base.Select("Select * from USERS");
                 DataRow nRow = dt.NewRow();

                 nRow["username"] = username;
                 nRow["adress"] = adress;
                 nRow["zipcode"] = zipcode;
                 nRow["city"] = city;
                 nRow["password"] = (password + "salage").GetHashCode();

                 dt.Rows.Add(nRow);

                 Base.Update("Select * from USERS", dt);
                 return true;
             }
             catch
             {
                 return false;
             }

         }

        /// <summary>
        /// Ajoute une commande a la base de donnee
        /// </summary>
        /// <param name="usernumber">numero d'utilisateur</param>
        /// <param name="ordernumber">numero de commande</param>
        /// <param name="creditcard">numero carte de credit utilise</param>
        /// <param name="shipping">adresse de livraison </param>
        /// <param name="invoicing">adresse de facturation</param>
        /// <param name="books">tableau de livre command</param>
         public void AddOrder(string usernumber, string ordernumber, string creditcard, string shipping, string invoicing, BookDB[] books)
         {
             DataTable dt;

             //modification de la classe ORDERS_BOOK
             dt = Base.Select("Select * from ORDER_BOOK");
             DataRow nRow = dt.NewRow();
             nRow["ordernum"] = ordernumber;
             foreach (BookDB i in books)
             {
                 nRow["booknum"] = i.GUID;
                 dt.Rows.Add(nRow);
             }

             //Modification de la table ORDERS
             dt = Base.Select("Select * from ORDER");
             DataRow mRow = dt.NewRow();
             mRow["username"] = usernumber;
             mRow["ordernum"] = ordernumber;
             mRow["shipping"] = shipping;
             mRow["invoicing"] = invoicing;
             mRow["creditcard"] = creditcard;
             dt.Rows.Add(mRow);
             Base.Update("Select * from ORDER", dt);
         }

        /// <summary>
        /// Retourne les commandes d'un utilisateur donnee
        /// </summary>
        /// <param name="usernumber">numero d'utilisateur</param>
        /// <returns>La liste des commandes faites par cet utilisateur</returns>
        public List<OrderDB> GetOrdersByUser(string usernumber)
        {
            OrderDB ty;

            List<OrderDB> TypesCollection = new List<OrderDB>();
            DataTable t = Base.Select("SELECT * FROM ORDERS where username=" + usernumber );

            DataView v = new DataView(t);
            for(int i = 0; i < v.Count; i++)
            {
                DataRow rowA = v[i].Row;
                string ordernum = rowA["ordernum"].ToString();
                //on recreer le tableau de livre
                DataTable s = Base.Select("SELECT * FROM ORDER_BOOKS where ordernum=" + ordernum);
                DataView w = new DataView(t);
                BookDB[] books = new BookDB[w.Count];
                for (int j = 0; i < w.Count; ++j)
                {
                    DataRow rowB = w[i].Row;
                    string booknum = rowB["booknum"].ToString();
                    DataTable r = Base.Select("SELECT * FROM BOOKS where GUID=" + booknum);
                    DataView x = new DataView(r);
                    DataRow row = x[0].Row;
                    books[j] = new BookDB(row["GUID"].ToString(), row["TITLE"].ToString(), row["PUBLICATION_DATE"].ToString(), row["ISBN_10"].ToString(),
                                        row["ISBN_13"].ToString(), row["PUBLISHER_GUID"].ToString(), row["PRICE"].ToString(), row["TYPE_GUID"].ToString(),
                                        row["DESCRIPTION"].ToString());
                }
                ty = new OrderDB(rowA["ordernum"].ToString(), rowA["creditcard"].ToString(), rowA["shipping"].ToString(), rowA["invoicing"].ToString(), books);
                TypesCollection.Add(ty);
            }
            return TypesCollection;
        }

        /// <summary>
        /// Permet de retourner un instance de DataBaseConnect
        /// </summary>
         public static DataBaseConnect Instance
         {
            get 
            {
                if (instance == null)
                {
                    instance = new DataBaseConnect();
                }
                return instance;
            }
         }

    }
}
