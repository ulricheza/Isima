using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SimulationTrain
{
    public partial class FenetreSimulation : Form
    {
        private GrapheInfra grInfra;

        private Simulateur sim;

        public FenetreSimulation(GrapheInfra inGraphe, Simulateur inSimu)
        {
            InitializeComponent();
            grInfra = inGraphe;
            grInfra.AfficherGraphe(this);
            sim = inSimu;
            TimerStart();
        }

        private void OnTimerEvent(object sender, EventArgs e)
        {
            Refresh();
            sim.nextMinute(this);
            
        }

        public void TimerStart()
        {
            Timer t = new Timer();
            t.Interval = 1000;
            t.Tick += new System.EventHandler(OnTimerEvent);
            t.Enabled = true;


        }

        /// <summary>
        /// Permet d'afficher une gare à un point particulier
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public void AfficheGare(int x, int y)
        {
            Graphics g = this.CreateGraphics();
            //
            Bitmap MyBitmap = new Bitmap("C:\\Users\\jc\\Documents\\Visual Studio 2010\\Projects\\SimulationTrain\\SimulationMetier\\gare_longuyon_medium.jpg");
            g.DrawImage(MyBitmap, new RectangleF(x - 15, y - 15,
                         30, 30));
        }

        public void AfficheVoie(int x1, int y1, int x2, int y2)
        {
            Graphics g = this.CreateGraphics();
            g.DrawLine(new Pen(Color.Black, 1), new Point(x1, y1), new Point(x2, y2));
        }

        public void AffichePont(int x1, int y1, int x2, int y2)
        {
            Graphics g = this.CreateGraphics();
            g.DrawLine(new Pen(Color.Red, 1), new Point(x1, y1), new Point(x2, y2));
            
        }

        public void AfficheTrain(Train train)
        {
            Graphics g = this.CreateGraphics();
            //
            Bitmap MyBitmap1 = new Bitmap("C:\\Users\\jc\\Documents\\Visual Studio 2010\\Projects\\SimulationTrain\\SimulationMetier\\train.jpg");
            g.DrawImage(MyBitmap1, new RectangleF(train.X - 8, train.Y - 8,
                         16, 16));
        }

        public void SetMinute(int temps)
        {
            labelMinute.Text = temps.ToString();
        }

        private void FenetreSimulation_Paint(object sender, PaintEventArgs e)
        {
            //AfficheGare(5, 10);
            //AfficheVoie(100, 10, 20, 20);
            //AfficheDoubleVoie(10, 10, 100, 10);
            grInfra.AfficherGraphe(this);
        }

    }
}
