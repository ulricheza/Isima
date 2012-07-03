using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimulationTrain
{
    public class SillonType
    {
        List<RessourceInfraParcours> parcours;

        public List<RessourceInfraParcours> Parcours
        {
            get { return parcours; }
            set { parcours = value; }
        }

        List<Mission> miss;

        public List<Mission> Miss
        {
            get { return miss; }
            set { miss = value; }
        }

        int depart;

        public int Depart
        {
            get { return depart; }
            set { depart = value; }
        }

        public SillonType(List<RessourceInfraParcours> inParcours, List<Mission> inMiss, int inDepart)
        {
            parcours = inParcours;
            miss = inMiss;
            depart = inDepart;
        }
    }
}
