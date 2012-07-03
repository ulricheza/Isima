using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebBook.Classes;
using System.Collections;
using WebBook.ServiceIsimaServ;

namespace WebBook
{

    /// <summary>
    /// Contient les livres
    /// </summary>
    public struct InterBook
    {

        private   Book _book;
        private   int _nb;

        public int Nb
        {
            get { return _nb; }
            set { _nb = value; }
        }

        public String NameBook
        {
            get { return _book.Title; }
            set { }
        }

        public String GUID
        {
            get { return _book.GUID; }
            set { }
        }

        public    InterBook(Book book,int p)
        {
             // TODO: Complete member initialization
            this._book = book;
            this._nb = p;
        } 
    }

    /// <summary>
    /// Affiche
    /// </summary>
    public partial class Panier : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["panier"] == null)
            {
                Session["panier"] = new PanierUser();
            }
            PanierUser p = (PanierUser)Session["panier"];

            ArrayList values = new ArrayList();
            foreach (KeyValuePair<Book,int> k in p.Books)
            {
                values.Add(new InterBook(k.Key,k.Value));
            }

            RepeaterPanier.DataSource = values;
            RepeaterPanier.DataBind();
        }

        protected void ButtonDelete_Click(object sender, EventArgs e)
        {
            if (Session["panier"] == null)
            {
                Session["panier"] = new PanierUser();
            }
            PanierUser p = (PanierUser)Session["panier"];
            p.DeleteBook(((LinkButton)sender).CommandArgument);
            Response.Redirect("~/Panier.aspx"); 
            

        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/CreateCommande.aspx"); 
        }

        }
    }