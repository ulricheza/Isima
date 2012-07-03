using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using DataAccessLayer.Metier;

namespace DataAccessLayer
{
    /// <summary>
    /// Permet d'accéder à la base de donnée
    /// </summary>
    public class DataBaseConnect
    {
         private static DataBaseConnect instance;
         private IBridge Base;

        /// <summary>
        /// Permet de se connecter à la base de donnée
        /// </summary>
         private DataBaseConnect() 
         {
             Base = new ManagerSQL(); 
             Base.Connexion();
             this.getAuthors();
             this.getBooks();
         }

        /// <summary>
        /// Permet de retourner la liste des éditeurs
        /// </summary>
        /// <returns> la liste des éditeurs </returns>
         public List<EditeurBDD> getEditeur()
         {
             EditeurBDD auteur;

             List<EditeurBDD> EditorsCollection = new List<EditeurBDD>();
             Base.Connexion();
             DataTable t = Base.Select("SELECT * FROM Publishers");

             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 auteur = new EditeurBDD(row["GUID"].ToString(), row["NAME"].ToString(), row["ADDRESS"].ToString(), row["ZIPCODE"].ToString(), row["CITY"].ToString(),
                                        row["STATE"].ToString(), row["COUNTRY"].ToString());
                 EditorsCollection.Add(auteur);
             }

             return EditorsCollection;
         }

        /// <summary>
        /// Permet de retourner une liste d'auteur
        /// </summary>
         /// <returns>une liste d'auteur</returns>
         public List<AuteurBDD> getAuthors()
         {
             AuteurBDD auteur;

             List<AuteurBDD> AuthorsCollection = new List<AuteurBDD>();
             Base.Connexion();
             DataTable t = Base.Select("SELECT * FROM Authors");

             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 auteur = new AuteurBDD(row["GUID"].ToString(), row["CIVILITE"].ToString(), row["FIRST_NAME"].ToString(), row["LAST_NAME"].ToString(),
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
         public List<LivreBDD> getBooks()
         {
             LivreBDD book;

             List<LivreBDD> BookCollection = new List<LivreBDD>();
             Base.Connexion();
             DataTable t = Base.Select("SELECT * FROM BOOKS");

             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 book = new LivreBDD(row["GUID"].ToString(), row["TITLE"].ToString(), row["PUBLICATION_DATE"].ToString(), row["ISBN_10"].ToString(),
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
         public List<TypesBDD> getTypes()
         {
             TypesBDD ty;

             List<TypesBDD> TypesCollection = new List<TypesBDD>();
             Base.Connexion();
             DataTable t = Base.Select("SELECT * FROM TYPES");

             DataView v = new DataView(t);
             for (int i = 0; i < v.Count; i++)
             {
                 DataRow row = v[i].Row;
                 ty = new TypesBDD(row["GUID"].ToString(), row["TYPE"].ToString());
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
         public void AddBook(string GUID, string titre, double prix, string guidAut, string guidEd, string guidGenre)
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

             }
             catch (Exception)
             {
                 Console.Write("Identifiant existant");
             }
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
