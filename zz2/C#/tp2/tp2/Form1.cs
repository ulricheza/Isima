using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace tp2
{
    public partial class Form1 : Form
    {
        private Simulateur Sim;
        private Graphics G;
        

        public Form1()
        {
            InitializeComponent();
        }

        public void DisplayRed(int X, int Y)
        {
            Rectangle rec = new Rectangle();
            Brush brosse = new SolidBrush(Color.Red);
            rec.Height = 2;
            rec.Width = 2;
            rec.X = X;
            rec.Y = Y;
            G.FillRectangle(brosse, rec);
        }

        public void DisplayBlack(int X, int Y)
        {
            
            Rectangle rec = new Rectangle();
            Brush brosse = new SolidBrush(Color.Black);
            rec.Height = 2;
            rec.Width = 2;
            rec.X = X;
            rec.Y = Y;
            G.FillRectangle(brosse, rec);
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {

            Rectangle rec = new Rectangle();
            Brush brosse = new SolidBrush(Color.Black);
            rec.Height = 2;
            rec.Width = 2;
            Agent ajout = new Agent();
            ajout.X = e.X;
            ajout.Y = e.Y;
            Sim.AjoutAgent(ajout);
            DisplayBlack(e.X, e.Y);
            G.FillRectangle(brosse, rec);

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            G = CreateGraphics();
            Sim = new Simulateur(this);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Sim.TickDeplacement();
        }

    }
}
