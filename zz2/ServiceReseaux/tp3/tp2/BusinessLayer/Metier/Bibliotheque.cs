using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BussinesLayer.Interfaces;


namespace BussinesLayer.Metier
{
    /// <summary>
    /// Classe de gestion de la bibliotheque
    /// </summary>
    public class Bibliotheque:IBibliotheque
    {
        //attributs
        private List<Livre>  _stock = new List<Livre>();
        private List<Auteur> _auteur = new List<Auteur>();
        private List<Editeur> _editeur = new List<Editeur>();

        //methodes
        public void AddLivre(Livre add)
        {
            _stock.Add(add);
        }

        public void AddAuteur(Auteur add)
        {
            _auteur.Add(add);
        }

        public void AddAuteur(String Auteur)
        {
            Auteur add = new Auteur();
            add.Name = Auteur;
            _auteur.Add(add);
        }

        public void AddEditeur(Editeur add)
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
        public List<Editeur> RealEditor()
        {
            List<Editeur> l = new List<Editeur>();
            l = (from ed in _stock
                 select ed.Editeur).Distinct<Editeur>().ToList<Editeur>();
            return l;
        }

        public List<Livre> Livre
        {
            get { return _stock; }
            set { _stock = value; }
        }

        public List<Auteur> Ecrivain
        {
            get { return _auteur; }
            set { _auteur = value; }
        }



        public List<Editeur> Editeur
        {
            get { return _editeur; }
            set { _editeur = value; }
        }



    }
}
