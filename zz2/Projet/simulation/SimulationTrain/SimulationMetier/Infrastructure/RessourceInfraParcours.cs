using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimulationTrain
{
    public class RessourceInfraParcours
    {
        private RessourceInfra infra;

        public RessourceInfra Infra
        {
            get { return infra; }
            set { infra = value; }
        }

        private int sens;

        public int Sens
        {
            get { return sens; }
            set { sens = value; }
        }
        private int rang;

        public int Rang
        {
            get { return rang; }
            set { rang = value; }
        }

        public void interraction(Train t)
        {
            infra.interraction(t, sens);
        }

        public RessourceInfraParcours(RessourceInfra inInfra, int inSens, int inRang)
        {
            infra = inInfra; ;
            sens = inSens;
            rang = inRang;
        }
    }
}
