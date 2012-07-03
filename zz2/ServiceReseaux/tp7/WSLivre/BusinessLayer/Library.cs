using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DataAccessLayer.SQLDatabase;
using DataAccessLayer;

namespace BusinessLayer
{
    /// <summary>
    /// Classe de la couche Metier representant la Biliotheque
    /// </summary>
    public class Library
    {
        //attributs
        private List<Book> _cart = new List<Book>();
        private List<Book>  _stock = new List<Book>();
        private List<Author> _authors = new List<Author>();
        private List<Editor> _editors = new List<Editor>();
        private List<Kind> _types = new List<Kind>();
        private List<Users> _users = new List<Users>();
        private DataBaseConnect dataBase;

        /// <summary>
        /// Constructeur par defaut necessaire pour la serialisation du service web
        /// </summary>
        public Library()
        {
            dataBase = new DataBaseConnect();
        }

        /// <summary>
        /// Permet de trouver un Author selon son GUID
        /// </summary>
        /// <param name="GUID"> GUID de l'Author</param>
        /// <returns> Author recherché</returns>
        public Author FindAuthorByGUID(string GUID)
        {
            return ((from aut in _authors
                               where aut.GUID == GUID
                               select aut).FirstOrDefault<Author>());
        }

        /// <summary>
        /// Recherche les livres d'un auteur
        /// </summary>
        /// <param name="name">Nom de famille de l'auteur</param>
        /// <returns>l'auteur si il a ete trouve sinon retourne la valeur pr defaut</returns>
        public Book[] FindBooksByAuthor(string name)
        {
            return ((from book in _stock
                     where book.Writer.LastName == name
                     select book).ToArray<Book>());
        }

        /// <summary>
        /// Recherche les livres par titres (l'utilisateur n'est pas oblige de rentrer le titre exact)
        /// </summary>
        /// <param name="title"></param>
        /// <returns></returns>
        public Book[] FindBooksByName(string title)
        {
            return ((from book in _stock
                     where book.Title.ToLower().Contains(title.ToLower())
                     select book).ToArray<Book>());
        }

        /// <summary>
        /// Permet de trouver un editeur selon son GUID
        /// </summary>
        /// <param name="GUID">GUID de l'editeur</param>
        /// <returns> Editeur recherché</returns>
        public Editor FindEditeurByGUID(string GUID)
        {
            return ((from ed in _editors
                     where ed.GUID == GUID
                     select ed).FirstOrDefault<Editor>());
        }

        /// <summary>
        /// Permet de trouver un livre selon son GUID
        /// </summary>
        /// <param name="GUID">GUID du livre</param>
        /// <returns> Livre recherché</returns>
        public Book FindBookByGUID(string GUID)
        {
            return ((from book in _stock
                     where book.GUID == GUID
                     select book).FirstOrDefault<Book>());
        }

        /// <summary>
        /// Permet de retourner un type selon son GUID
        /// </summary>
        /// <param name="GUID">GUID du type</param>
        /// <returns>Type recherché</returns>
        public Kind FindTypeByGUID(string GUID)
        {
            return ((from typ in _types
                     where typ.GUID == GUID
                     select typ).FirstOrDefault<Kind>());
        }

        /// <summary>
        /// Permet de transformer une liste d'éditeurs "Base de donnée" en 
        /// éditeurs utilisables dans la couche métier
        /// </summary>
        /// <param name="db"> Liste BDD d'éditeur</param>
        public void EditorAdaptor(List<EditorDB> db)
        {
            Editor edit;
            foreach (EditorDB edDB in db)
            {
                edit = new Editor(edDB.GUID, edDB.Name);
                _editors.Add(edit);
            }
        }

        /// <summary>
        /// Permet de transformer une liste d'Authors "Base de donnée" en 
        /// Authors utilisables dans la couche métier
        /// </summary>
        /// <param name="db"> Liste BDD d'Authors</param>
        public void AuthorAdaptor(List<AuthorDB> db)
        {
            Author Author;
            foreach (AuthorDB autDB in db)
            {
                Author = new Author(autDB.GUID, autDB.Name, autDB.FirstName, autDB.LastName);
                _authors.Add(Author);
            }
        }

        /// <summary>
        /// Permet de transformer une liste de livre "Base de donnée" en 
        /// livres utilisables dans la couche métier
        /// </summary>
        /// <param name="db"> Liste BDD de livre </param>
        public void BookAdaptor(List<BookDB> db)
        {
            Book book;
            foreach (BookDB bookdb in db)
            {
                Author Author = FindAuthorByGUID(bookdb.GuidAuthor);
                Editor ed = FindEditeurByGUID(bookdb.Editor);
                Kind g = FindTypeByGUID(bookdb.Kind);
                book = new Book(bookdb.GUID,bookdb.Title,bookdb.ReleaseDate,Author,ed,bookdb.Price,g,bookdb.Description);
                _stock.Add(book);
            }
        }

        /// <summary>
        /// Permet de transformer une listes de type "Base de donnée" en 
        /// types utilisables dans la couche métier
        /// </summary>
        /// <param name="db"> Liste BDD de types</param>
        public void KindAdaptor(List<KindDB> db)
        {
            Kind type;
            foreach (KindDB kinddb in db)
            {
                type = new Kind(kinddb.Guid, kinddb.Name);
                _types.Add(type);
            }
        }

        public void UserAdaptator(List<UsersDB> db)
        {
            Users user;
            foreach (UsersDB usdb in db)
            {
                user = new Users(usdb.Username, usdb.Adress, usdb.Zipcode, usdb.City, usdb.Password);
                _users.Add(user);
            }
        }

        /// <summary>
        /// Permet de mettre à l'instance de library selon la base de donnee
        /// </summary>
        public void UpdateDB()
        {
            _authors.Clear();
            _editors.Clear();
            _stock.Clear();
            _types.Clear();
            List<AuthorDB> autBdd = dataBase.getAuthors();
            AuthorAdaptor(autBdd);
            List<EditorDB> edBdd = dataBase.getEditeur();
            EditorAdaptor(edBdd);
            List<KindDB> genreBdd = dataBase.getTypes();
            KindAdaptor(genreBdd);
            List<BookDB> livBdd = dataBase.getBooks();
            BookAdaptor(livBdd);
            List<UsersDB> userBdd = dataBase.getUser();
            UserAdaptator(userBdd);
        }

        /// <summary>
        /// Permet d'ajouter un livre au panier
        /// </summary>
        /// <param name="book"></param>
        public void AddBookToCart(Book book)
        {
            _cart.Add(book);
        }

        /// <summary>
        /// Permet de supprimer un livre du panier
        /// </summary>
        /// <param name="book"></param>
        public void RemoveBookFromCart(Book book)
        {
            _cart.Remove(book);
        }

        /// <summary>
        /// Permet de supprimer un livre de la base de donnée
        /// </summary>
        /// <param name="GUID">Guid du livre à supprimer</param>
        public void DeleteBookDB(string GUID)
        {
            dataBase.DeleteBook(GUID);
        }

        /// <summary>
        /// Permet d'ajouter un livre dans la base de donnée
        /// </summary>
        /// <param name="GUID">GUID</param>
        /// <param name="titre">Titre</param>
        /// <param name="prix">Prix</param>
        /// <param name="aut">Author</param>
        /// <param name="ed">Editeur</param>
        /// <param name="genre">Genre</param>
        public void AddBookDB(string GUID, string titre, double prix, Author aut, Editor ed, Kind genre)
        {
            dataBase.AddBook(GUID, titre, prix, aut.GUID, ed.GUID, genre.GUID);
        }

        /// <summary>
        /// Permet d'ajouter un livre dans la base de donnée
        /// </summary>
        /// <param name="username">Utilisateur</param>
        /// <param name="adress">Adress</param>
        /// <param name="zipcode">Code postal</param>
        /// <param name="city">Ville</param>
        public bool AddUserDB(string username, string adress, string zipcode, string city, string password)
        {
            return dataBase.AddUser(username, adress, zipcode, city, password);
        }

        /// <summary>
        /// Permet de modifier un livre dans la base de donnée
        /// </summary>
        /// <param name="GUID">GUID</param>
        /// <param name="titre">Titre</param>
        /// <param name="prix">Prix</param>
        /// <param name="aut">Author</param>
        /// <param name="ed">Editeur</param>
        /// <param name="genre">Genre</param>
        public void UpdateBookDB(string GUID, string titre, double prix, Author aut, Editor ed, Kind genre)
        {
            dataBase.UpdateBook(GUID, titre, prix, aut.GUID, ed.GUID, genre.GUID);
        }

        /// <summary>
        /// Retourne le prix moyen d'un genre donne en parametre
        /// </summary>
        /// <param name="type">Genre</param>
        /// <returns>Prix moyen</returns>
        public double AveragePriceByKind(string type)
        {
            double price = 0;
            price = (from liv in _stock
                     where liv.Type.Name == type
                    select liv.Price).Average();
            return (price);
        }

        /// <summary>
        /// Retourne la liste des editeurs qui possedes des livres dans la biliotheque
        /// </summary>
        /// <returns></returns>
        public List<Editor> RealEditor()
        {
            return ((from ed in _stock
                    select ed.Publisher).Distinct<Editor>().ToList<Editor>());
        }

        /// <summary>
        /// Verifie si le livre est contenue dans la base de données
        /// </summary>
        /// <param name="book">livre a verifier</param>
        /// <returns>true si le livre est contenue</returns>
        public bool Contains(Book book)
        {
            bool result = false;
            int i = 0;
            Book[] nameappear = FindBooksByName(book.Title);

            while (i < nameappear.Length && result == false)
            {
                result = nameappear[i++].Equals(book);
            }
            return result;
        }

        /// <summary>
        /// Liste des livres
        /// </summary>
        public List<Book> Books
        {
            get { return _stock; }
            set { _stock = value; }
        }

        /// <summary>
        /// Liste des Authors
        /// </summary>
        public List<Author> Writers
        {
            get { return _authors; }
            set { _authors = value; }
        }

        /// <summary>
        /// Liste des éditeurs
        /// </summary>
        public List<Editor> Editors
        {
            get { return _editors; }
            set { _editors = value; }
        }

        /// <summary>
        /// Liste des genres
        /// </summary>
        public List<Kind> Types
        {
            get { return _types; }
            set { _types = value; }
        }

        /// <summary>
        /// Panier
        /// </summary>
        public List<Book> Cart
        {
            get { return _cart; }
            set { _cart = value; }
        }


        /// <summary>
        /// Permet de vérifier si un utilisateur est valide
        /// </summary>
        /// <param name="username">Nom d'utilisateur</param>
        /// <param name="password">Mot de passe</param>
        /// <returns></returns>
        public bool VerifyUser(string username, string password)
        {
                     Users user =  (from us in _users
                     where us.Username == username && us.Password == (password + "salage").GetHashCode()
                     select us).FirstOrDefault<Users>();

            return (user != null );
        }
    }
}