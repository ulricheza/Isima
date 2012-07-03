using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimulationTrain
{
    public class Mission
    {
        private Gare gare;

        private int rang;

        public int Rang
        {
            get { return rang; }
            set { rang = value; }
        }

        public Gare Gare
        {
            get { return gare; }
            set { gare = value; }
        }

        private int tempsMission;

        public int TempsMission
        {
            get { return tempsMission; }
            set { tempsMission = value; }
        }


        public Mission(Gare inGare, int inTemps, int inRang)
        {
            gare = inGare;
            tempsMission = inTemps;
            rang = inRang;
        }
    }
}
