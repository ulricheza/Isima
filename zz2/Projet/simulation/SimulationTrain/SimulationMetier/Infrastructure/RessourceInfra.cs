using System;
using System.Collections.Generic;
using System.Text;


namespace SimulationTrain
{
    public abstract class RessourceInfra
    {
        /// <summary>
        /// Permet d'afficher la gare
        /// </summary>
        /// <param name="f"></param>
        public abstract void AfficherInfra(FenetreSimulation f);

        public abstract void interraction(Train t, int sens);

        public double Distance(double x1, double y1, double x2, double y2)
        {
            return Math.Sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
        }
        
    }
}
