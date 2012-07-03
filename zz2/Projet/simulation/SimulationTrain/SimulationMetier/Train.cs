using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimulationTrain
{
    /// <summary>
    /// Claase représentant un train
    /// </summary>
    public class Train
    {

        /// <summary>
        /// Permet au train d'effectuer une action, correspondant à une minute de simulation
        /// </summary>
        /// <param name="temps"> Temps de la simulation </param>
        public void Action(int temps)
        {
            // Si le train peut partir
            if (sillon.Depart < temps)
            {
                sillon.Parcours[indexRessource].interraction(this);



            }
        }

        /// <summary>
        /// Constructeur du train
        /// </summary>
        /// <param name="inX">Coordonnée x</param>
        /// <param name="inY">Coordonnée y</param>
        /// <param name="inSillon">Sillon correspondant au train</param>
        public Train(int inX, int inY, SillonType inSillon)
        {
            x = inX;
            y = inY;
            sillon = inSillon;
            attente = 0;
            indexMission = 0;
            indexRessource = 0;

            vitesse = 10;
        }

        // --------------------------------------------------   //
        // Attributs                                           //
        // --------------------------------------------------   //

        /// <summary>
        /// Coordonnée x du train
        /// </summary>
        private int x;

        /// <summary>
        /// Coordonnée y du train
        /// </summary>
        private int y;

        /// <summary>
        /// Temps d'attente d'un train, utilisé pour savoir combien de temps 
        /// un train a attendu en gare
        /// </summary>
        private int attente;

        /// <summary>
        /// Index sur le tableau de ressource pour savoir ou est le train
        /// </summary>
        private int indexRessource;

        /// <summary>
        /// Index sur le tableau de Mission pour savoir quelle est la prochaine mission
        /// à effectuer
        /// </summary>
        private int indexMission;


        /// <summary>
        /// Sillon que le train doit parcourir
        /// </summary>
        SillonType sillon;

        /// <summary>
        /// Vitesse du train
        /// </summary>
        double vitesse;

        // --------------------------------------------------   //
        // Propriété                                            //
        // --------------------------------------------------   //

        /// <summary>
        /// Propriété sur la Coordonnée y du train
        /// </summary>
        public int Y
        {
            get { return y; }
            set { y = value; }
        }

        /// <summary>
        /// Propriété sur la Coordonnée x du train
        /// </summary>
        public int X
        {
            get { return x; }
            set { x = value; }
        }

        /// <summary>
        /// Propriété correspondant au temps d'attente d'un train, utilisé pour savoir combien de temps 
        /// un train a attendu en gare
        /// </summary>
        public int Attente
        {
            get { return attente; }
            set { attente = value; }
        }

        /// <summary>
        /// Propriété correspondant au Sillon que le train doit parcourir
        /// </summary>
        public SillonType Sillon
        {
            get { return sillon; }
            set { sillon = value; }
        }

        /// <summary>
        /// Propriété correspondant à l'index sur le tableau de ressource 
        /// pour savoir ou est le train
        /// </summary>
        public double IndexRessource
        {
            get { return indexRessource; }
            set { indexRessource = value; }
        }

        /// <summary>
        /// Propriété correspondant à l'Index sur le tableau de Mission pour savoir quelle est la prochaine mission
        /// à effectuer
        /// </summary>
        public int IndexMission
        {
            get { return indexMission; }
            set { indexMission = value; }
        }

        /// <summary>
        /// Propriété sur la vitesse du train
        /// </summary>
        public double Vitesse
        {
            get { return vitesse; }
            set { vitesse = value; }
        }

    }
}
