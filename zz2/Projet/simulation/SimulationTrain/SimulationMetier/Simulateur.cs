using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SimulationTrain
{
    public class Simulateur
    {
        public GrapheInfra graphe;

        int temps = 0;

        List<Train> trains;

        public Simulateur()
        {
            graphe = new GrapheInfra();
            temps = 0;
            trains = new List<Train>();

            initialisationSimulation();

        }

        public void nextMinute(FenetreSimulation fen)
        {
            temps++;
            fen.SetMinute(temps);
            foreach (Train tr in trains)
            {
                
                tr.Action(temps);
                if(tr.Sillon.Depart<temps)
                    fen.AfficheTrain(tr);

            }
        }

        /// <summary>
        /// Méthode à modifier pour changer les paramètre de la simulation
        /// </summary>
        private void initialisationSimulation()
        {
            // Initialisation des gares
            Gare g1 = new Gare(50, 50);
            Gare g2 = new Gare(150, 300);
            Gare g3 = new Gare( 400, 50);
            Gare g4 = new Gare( 400, 300);
            Gare g5 = new Gare(450, 250);
            Gare g6 = new Gare(200, 200);

            // Initialisation des ponts
            Pont p1 = new Pont(150, 200, 50, 55);
            Pont p2 = new Pont(450, 400, 250, 300);
            Pont p3 = new Pont(200, 250, 350, 350);
            Pont p4 = new Pont(250, 300, 200, 200);

            // Initialisation des voies
            Voie v1 = new Voie(50, 150, 50, 50);
            Voie v2 = new Voie(200,400,55,50);
            Voie v3 = new Voie(50,100,50,150);
            Voie v4 = new Voie(100,200,150,200);
            Voie v5 = new Voie(200,400,200,50);
            Voie v6 = new Voie(400,450,50,250);
            Voie v7 = new Voie(200,250,200,200);
            Voie v8 = new Voie(300,450,200,250);
            Voie v9 = new Voie(250,400,350,300);
            Voie v10 = new Voie(150,200,300,350);
            Voie v11 = new Voie(150,200,300,200);
            Voie v12 = new Voie(100, 150, 150, 300);

            // Ajout dans le graphe
            graphe.RessourceInfra.Add(g1);
            graphe.RessourceInfra.Add(g2);
            graphe.RessourceInfra.Add(g3);
            graphe.RessourceInfra.Add(g4);
            graphe.RessourceInfra.Add(g5);
            graphe.RessourceInfra.Add(g6);

            graphe.RessourceInfra.Add(p1);
            graphe.RessourceInfra.Add(p2);
            graphe.RessourceInfra.Add(p3);
            graphe.RessourceInfra.Add(p4);

            graphe.RessourceInfra.Add(v1);
            graphe.RessourceInfra.Add(v2);
            graphe.RessourceInfra.Add(v3);
            graphe.RessourceInfra.Add(v4);
            graphe.RessourceInfra.Add(v5);
            graphe.RessourceInfra.Add(v6);
            graphe.RessourceInfra.Add(v7);
            graphe.RessourceInfra.Add(v8);
            graphe.RessourceInfra.Add(v9);
            graphe.RessourceInfra.Add(v10);
            graphe.RessourceInfra.Add(v11);
            graphe.RessourceInfra.Add(v12);

            // Creation du parcours
            List<RessourceInfraParcours> list1 = new List<RessourceInfraParcours>();
            list1.Add(new RessourceInfraParcours(g1, 1, 1));
            list1.Add(new RessourceInfraParcours(v3, 1, 2));
            list1.Add(new RessourceInfraParcours(v12, 1, 3));
            list1.Add(new RessourceInfraParcours(g2, 1, 4));
            list1.Add(new RessourceInfraParcours(v11, 1, 5));
            list1.Add(new RessourceInfraParcours(g5, 1, 6));

            List<Mission> listM1 = new List<Mission>();
            listM1.Add(new Mission(g1, 5, 1));
            listM1.Add(new Mission(g2,5,4));
            listM1.Add(new Mission(g5, 5,6));

            SillonType sillon = new SillonType(list1,listM1,5);

            // Création des trains
            Train tr1 = new Train(50, 50, sillon);
            trains.Add(tr1);
            
        }
    }
}
