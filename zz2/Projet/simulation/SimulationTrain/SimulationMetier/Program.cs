using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace SimulationTrain
{
    static class Program
    {
        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Simulateur sim = new Simulateur();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new FenetreSimulation(sim.graphe, sim));
            
        }
    }
}
