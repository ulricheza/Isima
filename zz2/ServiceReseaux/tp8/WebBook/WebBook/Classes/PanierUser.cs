using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using WebBook.ServiceIsimaServ;
using System.Collections;

namespace WebBook.Classes
{
    //Représente le panier de l'utilisateur
    public class PanierUser
    {
        /// <summary>
        /// Représente les livres du paniers
        /// </summary>
        private Dictionary<Book, int> books;

        /// <summary>
        /// Propriété des livres du paniers
        /// </summary>
        public Dictionary<Book, int> Books
        {
            get { return books; }
            set { books = value; }
        }

        /// <summary>
        /// Constructeur
        /// </summary>
        public PanierUser()
        {
            books = new Dictionary<Book,int>();
        }

        /// <summary>
        /// Permet de savoir si un book est contenu dedans
        /// </summary>
        /// <param name="b">Book</param>
        /// <returns></returns>
        public bool SearchBook(Book book)
        {
            bool ret = false;
            foreach (Book b in books.Keys)
            {
                if (b.GUID == book.GUID)
                {
                    ret = true;
                    break;
                }
                
            }
            return ret;
        }

        public int getInfoBook(Book book)
        {
            int ret = 0;
            foreach (KeyValuePair<Book,int> b in books)
            {
                if (b.Key.GUID == book.GUID)
                {
                    ret = b.Value;
                    break;
                }   
            }
            return ret;
        }

        

        /// <summary>
        /// Supprimer un livre
        /// </summary>
        /// <param name="GUID">GUID</param>
        public void DeleteBook(string GUID)
        {
            foreach (Book b in books.Keys)
            {
                if (b.GUID == GUID)
                {
                    books.Remove(b);
                    break;
                }
            }
            
        }

        /// <summary>
        /// Ajoute au panier
        /// </summary>
        /// <param name="b">livre</param>
        /// <param name="c">nombre de livre</param>
        public void AddBookPanier(Book b, int c)
        {
            books.Add(b,c);
        }
    }
}