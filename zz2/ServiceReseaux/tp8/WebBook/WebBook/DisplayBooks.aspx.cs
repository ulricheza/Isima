using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebBook.ServiceIsimaServ;
using WebBook.Classes;

namespace WebBook
{
    public partial class DisplayBooks : System.Web.UI.Page
    {
        /// <summary>
        /// Livre correspondant
        /// </summary>
        Book b;

        protected void Page_Load(object sender, EventArgs e)
        {
            String guid = Request.QueryString["GUID_Book"];
            bool display = false;

            if (guid != null && guid != "")
            {
                display = true;
            }

            if (display == true)
            {
                ServiceIsimaBookSoapClient serv = new ServiceIsimaBookSoapClient();
                b = serv.BookByGUID(guid);
                LabelPrice.Text = b.Price.ToString();
                LabelTitle.Text = b.Title;
                LabelDate.Text = b.Writer.ToString();
                LabelDate.Text = b.ReleaseDate.ToString();
                LabelKind.Text = b.Type.ToString();
                LabelEditor.Text = b.Publisher.ToString();


                if (Session["panier"] == null)
                {
                    Session["panier"] = new PanierUser();
                }

                PanierUser p = (PanierUser)Session["panier"];
                if (p.SearchBook(b))
                {
                    TextBox1.Text = p.getInfoBook(b).ToString();
                }


            }
            else
            {
                Response.Write("Problème");
            }

        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            if (Session["panier"] == null)
            {
                Session["panier"] = new PanierUser();
            }
            PanierUser p = (PanierUser)Session["panier"];

            String s = TextBox1.Text;
            int nb;
            if (Int32.TryParse(s, out nb))
            {
                if (p.SearchBook(b))
                {
                    p.DeleteBook(b.GUID);
                }

                p.AddBookPanier(b, nb);
                Response.Write("<body><script>opener=parent;parent.close();</script></body>");
            }
            else
            {
                TextBox1.Text = "Non valide";
            }

        }
    }
}