using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BussinesLayer.Metier;
using BussinesLayer.Interfaces;

namespace Programme
{
    class Affichage
    {
        public void AfficherAuteur(Bibliotheque bibli)
        {
            string temp = "";
            foreach (Auteur i in bibli.Ecrivain)
            {
                temp += i.Name + " ";
            }
            Console.WriteLine(temp);
        }

        public void AfficherEditeur(Bibliotheque bibli)
        {
            string temp = "";
            foreach (Editeur i in bibli.Editeur)
            {
                temp += i.Name + " ";
            }
            Console.WriteLine(temp);
        }

        public void AfficherLivre(Bibliotheque bibli)
        {
            string temp = "";
            foreach (Livre i in bibli.Livre)
            {
                temp += i.Titre + " ";
            }
            Console.WriteLine(temp);
        }
    }
}
