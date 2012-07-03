using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BusinessLayer.Interfaces;
using DataAccessLayer;


namespace BusinessLayer.Metier
{
    /// <summary>
    /// Classe de gestion de la bibliotheque
    /// </summary>
    public class Bibliotheque:IBibliotheque
    {
        //attributs
        private List<ILivre>  _stock = new List<ILivre>();
        private List<IAuteur> _auteur = new List<IAuteur>();
        private List<IEditeur> _editeur = new List<IEditeur>();
        private DataBaseConnect dataBase = DataBaseConnect.Instance;

        //methodes

        public void UpdateBdd()
        {
           
            
           



        }

        public void AddLivre(ILivre add)
        {
            _stock.Add(add);
        }

        public void AddAuteur(IAuteur add)
        {
            _auteur.Add(add);
        }

        public void AddAuteur(String Auteur)
        {
            IAuteur add = new Auteur(Auteur);
            _auteur.Add(add);
        }

        public void AddEditeur(IEditeur add)
        {
            _editeur.Add(add);
        }

        /// <summary>
        /// Retourne le prix moyen d'un genre donne en parametre
        /// </summary>
        /// <param name="genre"></param>
        /// <returns></returns>
        public double MoyennePrixGenre(string genre)
        {
            double prix = 0;
            IEnumerable<Livre> livre = new List<Livre>();
            prix = (from liv in _stock
                    where liv.Genre == genre
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

        public List<ILivre> Livre
        {
            get { return _stock; }
            set { _stock = value; }
        }

        public List<IAuteur> Ecrivain
        {
            get { return _auteur; }
            set { _auteur = value; }
        }



        public List<IEditeur> Editeur
        {
            get { return _editeur; }
            set { _editeur = value; }
        }



    }
}
