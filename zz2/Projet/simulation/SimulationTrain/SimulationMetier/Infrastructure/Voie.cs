using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;

namespace SimulationTrain
{
    class Voie : RessourceInfra
    {
        private int x1;
        private int x2;
        private int y1;
        private int y2;

        public Voie(int inX1, int inX2, int inY1, int inY2)
        {
            x1 = inX1;
            x2 = inX2;
            y1 = inY1;
            y2 = inY2;
        }

        override public void AfficherInfra(FenetreSimulation fen)
        {
            fen.AfficheVoie(x1, y1, x2, y2);
        }

        override public void interraction(Train t, int sens)
        {
           //Calcul du vecteur directeur
            Vector vect;
            if(sens == 1)
                vect = new Vector(x2-x1, y2-y1);
            else vect = new Vector(x1-x2, y1-y2);
            vect.Normalize();

            if(
            vect = vect * t.Vitesse;
            Point p = Vector.Add(vect, new Point(t.X, t.Y));
            t.X = (int)p.X;
            t.Y = (int)p.Y;

        }
    }
}
