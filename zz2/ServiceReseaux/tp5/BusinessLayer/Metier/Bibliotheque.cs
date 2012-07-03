using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;
using BusinessLayer.Metier;
using DataAccessLayer;
using DataAccessLayer.Metier;

namespace BusinessLayer.Metier
{
    /// <summary>
    /// Classe de la couche Metier representant la Biliotheque
    /// </summary>
    public class Bibliotheque:IBibliotheque
    {
        //attributs
        private List<ILivre> _panier = new List<ILivre>();
        private List<ILivre>  _stock = new List<ILivre>();
        private List<IAuteur> _auteur = new List<IAuteur>();
        private List<IEditeur> _editeur = new List<IEditeur>();
        private List<IGenre> _type = new List<IGenre>();
        private DataBaseConnect dataBase = DataBaseConnect.Instance;

        /// <summary>
        /// Permet de trouver un auteur selon son GUID
        /// </summary>
        /// <param name="inGuid"> GUID de l'auteur</param>
        /// <returns> Auteur recherché</returns>
        private IAuteur FindAuteur(string inGuid)
        {
            IAuteur aut = null;
            foreach (IAuteur autBdd in _auteur)
            {
                if (autBdd.GUID == inGuid)
                {
                    aut = autBdd;
                    break;
                }
            }
            return aut;
        }

        /// <summary>
        /// Permet de trouver un editeur selon son GUID
        /// </summary>
        /// <param name="inGuid">GUID de l'editeur</param>
        /// <returns> Editeur recherché</returns>
        private IEditeur FindEditeur(string inGuid)
        {
            IEditeur ed = null;
            foreach (IEditeur edBdd in _editeur)
            {
                if (edBdd.GUID == inGuid)
                {
                    ed = edBdd;
                    break;
                }
            }
            return ed;
        }

        /// <summary>
        /// Permet de retourner un type selon son GUID
        /// </summary>
        /// <param name="inGuid">GUID du type</param>
        /// <returns>Type recherché</returns>
        private IGenre FindGenre(string inGuid)
        {
            IGenre g = null;
            foreach (IGenre geBdd in _type)
            {
                if (geBdd.GUID == inGuid)
                {
                    g = geBdd;
                    break;
                }
            }
            return g;
        }

        /// <summary>
        /// Permet de transformer une liste d'éditeurs "Base de donnée" en 
        /// éditeurs utilisables dans la couche métier
        /// </summary>
        /// <param name="bdd"> Liste BDD d'éditeur</param>
        void adaptateurEditeur(List<EditeurBDD> bdd)
        {
            IEditeur edit;
            foreach (EditeurBDD edBdd in bdd)
            {
                edit = new Editeur(edBdd.GUID, edBdd.Name);
                _editeur.Add(edit);
            }
        }

        /// <summary>
        /// Permet de transformer une liste d'auteurs "Base de donnée" en 
        /// auteurs utilisables dans la couche métier
        /// </summary>
        /// <param name="bdd"> Liste BDD d'auteurs</param>
        void adaptateurAuteur(List<AuteurBDD> bdd)
        {
            IAuteur auteur;
            foreach (AuteurBDD autBdd in bdd)
            {
                auteur = new Auteur(autBdd.GUID, autBdd.Nom, autBdd.FirstName, autBdd.LastName);
                _auteur.Add(auteur);
            }
        }

        /// <summary>
        /// Permet de transformer une liste de livre "Base de donnée" en 
        /// livres utilisables dans la couche métier
        /// </summary>
        /// <param name="bdd"> Liste BDD de livre </param>
        void adaptateurBook(List<LivreBDD> bdd)
        {
            ILivre livre;
            foreach (LivreBDD livBdd in bdd)
            {
                IAuteur auteur = FindAuteur(livBdd.GuidAuthor);
                IEditeur ed = FindEditeur(livBdd.Editeur);
                IGenre g = FindGenre(livBdd.Genre);
                livre = new Livre(livBdd.GUID,livBdd.Titre,livBdd.Datesortie,auteur,ed,livBdd.Prix,g,livBdd.Description);
                _stock.Add(livre);
            }
        }

        /// <summary>
        /// Permet de transformer une listes de type "Base de donnée" en 
        /// types utilisables dans la couche métier
        /// </summary>
        /// <param name="bdd"> Liste BDD de types</param>
        void adaptateurGenre(List<TypesBDD> bdd)
        {
            IGenre genre;
            foreach (TypesBDD genreBdd in bdd)
            {
                genre = new Genre(genreBdd.Guid, genreBdd.Name);
                _type.Add(genre);
            }
        }

        /// <summary>
        /// Permet de mettre à jour la base de donnée
        /// </summary>
        public void UpdateBdd()
        {
            _auteur.Clear();
            _editeur.Clear();
            _stock.Clear();
            _type.Clear();
            List<AuteurBDD> autBdd = dataBase.getAuthors();
            adaptateurAuteur(autBdd);
            List<EditeurBDD> edBdd = dataBase.getEditeur();
            adaptateurEditeur(edBdd);
            List<TypesBDD> genreBdd = dataBase.getTypes();
            adaptateurGenre(genreBdd);
            List<LivreBDD> livBdd = dataBase.getBooks();
            adaptateurBook(livBdd);

        }

        /// <summary>
        /// Permet d'ajouter un livre au panier
        /// </summary>
        /// <param name="livre"></param>
        public void AddPanier(ILivre livre)
        {
            _panier.Add(livre);
        }

        /// <summary>
        /// Permet de supprimer un livre du panier
        /// </summary>
        /// <param name="livre"></param>
        public void SuppPanier(ILivre livre)
        {
            _panier.Remove(livre);
        }

        /// <summary>
        /// Permet de supprimer un livre de la base de donnée
        /// </summary>
        /// <param name="GUID">Guid du livre à supprimer</param>
        public void DeleteLivreBdd(string GUID)
        {
            dataBase.DeleteBook(GUID);
        }

        /// <summary>
        /// Permet d'ajouter un livre dans la base de donnée
        /// </summary>
        /// <param name="GUID">GUID</param>
        /// <param name="titre">Titre</param>
        /// <param name="prix">Prix</param>
        /// <param name="aut">Auteur</param>
        /// <param name="ed">Editeur</param>
        /// <param name="genre">Genre</param>
        public void AddLivreBdd(string GUID, string titre, double prix, IAuteur aut, IEditeur ed, IGenre genre)
        {
            dataBase.AddBook(GUID, titre, prix, aut.GUID, ed.GUID, genre.GUID);
        }

        /// <summary>
        /// Permet de modifier un livre dans la base de donnée
        /// </summary>
        /// <param name="GUID">GUID</param>
        /// <param name="titre">Titre</param>
        /// <param name="prix">Prix</param>
        /// <param name="aut">Auteur</param>
        /// <param name="ed">Editeur</param>
        /// <param name="genre">Genre</param>
        public void UpdateLivreBdd(string GUID, string titre, double prix, IAuteur aut, IEditeur ed, IGenre genre)
        {
            dataBase.UpdateBook(GUID, titre, prix, aut.GUID, ed.GUID, genre.GUID);
        }

        /// <summary>
        /// Retourne le prix moyen d'un genre donne en parametre
        /// </summary>
        /// <param name="genre">Genre</param>
        /// <returns>Prix moyen</returns>
        public double MoyennePrixGenre(string genre)
        {
            double prix = 0;
            IEnumerable<Livre> livre = new List<Livre>();
            prix = (from liv in _stock
                    where liv.Genre.ToString() == genre
                    select liv.Prix).Average();
            return (prix);
        }

        /// <summary>
        /// Retourne la liste des editeurs qui possedes des livres dans la biliotheque
        /// </summary>
        /// <returns></returns>
        public List<IEditeur> RealEditor()
        {
            List<IEditeur> l = new List<IEditeur>();
            l = (from ed in _stock
                 select ed.Editeur).Distinct<IEditeur>().ToList<IEditeur>();
            return l;
        }

        /// <summary>
        /// Liste des livres
        /// </summary>
        public List<ILivre> Livre
        {
            get { return _stock; }
            set { _stock = value; }
        }

        /// <summary>
        /// Liste des auteurs
        /// </summary>
        public List<IAuteur> Ecrivain
        {
            get { return _auteur; }
            set { _auteur = value; }
        }

        /// <summary>
        /// Liste des éditeurs
        /// </summary>
        public List<IEditeur> Editeur
        {
            get { return _editeur; }
            set { _editeur = value; }
        }

        /// <summary>
        /// Liste des genres
        /// </summary>
        public List<IGenre> Genre
        {
            get { return _type; }
            set { _type = value; }
        }

        /// <summary>
        /// Panier
        /// </summary>
        public List<ILivre> Panier
        {
            get { return _panier; }
            set { _panier = value; }
        }


        
    }
}
