using System;
using System.Collections.Generic;
using System.Text;


namespace SimulationTrain
{
    /// <summary>
    /// Classe qui correspond à une gare
    /// </summary>
    public class Gare : RessourceInfra
    {
        /// <summary>
        /// Coordonnée x
        /// </summary>
        int x;
        /// <summary>
        /// Coordonnée y
        /// </summary>
        int y;

        /// <summary>
        /// Constructeur de la gare
        /// </summary>
        /// <param name="inX"> Coordonnée X de la gare</param>
        /// <param name="inY"> Coordonnée Y de la gare</param>
        public Gare(int inX,int inY)
        {
            x = inX;
            y = inY;
        }

        /// <summary>
        /// Permet d'afficher la gare dans la fenêtre 
        /// </summary>
        /// <param name="fen"> Fenêtre fen </param>
        override public void AfficherInfra(FenetreSimulation fen)
        {
            fen.AfficheGare(x, y);
        }

        override public void interraction(Train t, int sens)
        {
            if (t.Sillon.Miss[t.IndexMission].Rang == t.Sillon.Parcours[t.IndexRessource].Rang)
            {
                if (t.Attente < t.Sillon.Miss[t.IndexMission].TempsMission)
                {
                    t.Attente++;
                }
                else
                {
                    t.IndexMission++;
                    t.IndexRessource++;
                }
            }
        }

    }
}
