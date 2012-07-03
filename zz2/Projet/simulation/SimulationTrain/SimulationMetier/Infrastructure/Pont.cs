using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimulationTrain
{
    public class Pont : RessourceInfra
    {
        private int x1;
        private int x2;
        private int y1;
        private int y2;

        public Pont(int inX1, int inX2, int inY1, int inY2)
        {
            x1 = inX1;
            x2 = inX2;
            y1 = inY1;
            y2 = inY2;
        }

        override public void AfficherInfra(FenetreSimulation fen)
        {
            fen.AffichePont(x1, y1, x2, y2);
        }

        override public void interraction(Train t, int sens)
        {

        }
    }
}
