using System;
using System.Collections.Generic;
using System.Text;
using SimulationTrain;

namespace SimulationMetier
{
    /// <summary>
    /// Le graphe d'infrastructure
    /// </summary>
    public class GrapheInfra
    {
        List<RessourceInfra> ressourceInfra;

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

        }
    }
}
