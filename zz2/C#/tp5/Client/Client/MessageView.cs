using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Client
{
    /// <summary>
    /// View pour l'affichage de message
    /// </summary>
    public partial class MessageView : UserControl
    {
        /// <summary>
        /// Constructeur
        /// </summary>
        public MessageView()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Re-initialise les valeurs de la vue
        /// </summary>
        public void ClearView()
        {
            this.textBoxAuthor.Text = "";
            this.textBoxMessage.Text = "";
            this.Date.Text = "";
        }

        /// <summary>
        /// Affiche un message dans la view
        /// </summary>
        /// <param name="inload">Message à afficher</param>
        public void DisplayMessage(ServeurChat.Message inload)
        {
            this.textBoxAuthor.Text = inload.Auteur;
            this.textBoxMessage.Text = inload.Text;
            this.Date.Text = inload.Creation.ToString();
        }
    }
}
