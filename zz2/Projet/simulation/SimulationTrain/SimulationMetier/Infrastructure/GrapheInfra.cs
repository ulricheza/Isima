using System;
using System.Collections.Generic;
using System.Text;

namespace SimulationTrain
{
    /// <summary>
    /// Le graphe d'infrastructure
    /// </summary>
    public class GrapheInfra
    {
        private List<RessourceInfra> ressourceInfra;

        public List<RessourceInfra> RessourceInfra
        {
            get { return ressourceInfra; }
            set { ressourceInfra = value; }
        }

        /// <summary>
        /// Constructeur du graphe d'infrastructure
        /// </summary>
        public GrapheInfra()
        {
            ressourceInfra = new List<RessourceInfra>();
        }

        /// <summary>
        /// Permet d'afficher le graphe des infrastructures dans la fenêtre
        /// </summary>
        /// <param name="fen">Fenêtre dans laquelle sera affiché le train</param>
        public void AfficherGraphe(FenetreSimulation fen)
        {
            foreach ( RessourceInfra r in ressourceInfra)
            {
                r.AfficherInfra(fen);

            }
        }
    }
}
