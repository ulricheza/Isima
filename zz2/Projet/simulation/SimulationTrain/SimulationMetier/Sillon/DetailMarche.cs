using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimulationTrain
{
    public class DetailMarche
    {
        RessourceInfra referenceInfra;

        public RessourceInfra ReferenceInfra
        {
            get { return referenceInfra; }
            set { referenceInfra = value; }
        }

        int rang;

        public int Rang
        {
            get { return rang; }
            set { rang = value; }
        }
        int tempsParcours;

        public DetailMarche(RessourceInfra inRessourceInfra)
        {
            referenceInfra = inRessourceInfra;
        }


    }
}
