using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace tp2
{
    class Simulateur
    {
        private List<Agent> maListe;
        Random ran;
        Form1 win;

        public Simulateur(Form1 a)
        {
            win = a;
            ran = new Random();
            maListe = new List<Agent>();
        }

        public void TickDeplacement()
        {
            int depla;
            foreach (Agent i in maListe)
            {
                win.DisplayRed(i.X, i.Y);
                depla = ran.Next(4);
               
                switch (depla)
                {
                    case 0:
                        i.Y = i.Y + 2;
                        break;
                    case 1:
                        i.X =i.X + 2;;
                        break;
                    case 2:
                        i.Y = i.Y - 2;
                        break;
                    case 3:
                        i.X = i.X - 2;
                        break;
                }
                win.DisplayBlack(i.X, i.Y);
            }
        }

        public void AjoutAgent(Agent add)
        {
            maListe.Add(add);
        }
 
    }
}
