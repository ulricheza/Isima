using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebBook.ServiceIsimaServ;
using System.Collections;

namespace WebBook
{
    public partial class ListBook : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            String choice = Request.QueryString["choice"];
            String search = Request.QueryString["search"];

            
            ServiceIsimaBookSoapClient serv = new ServiceIsimaBookSoapClient();
            Book[] books;

            if (choice == null)
                books = serv.AllBooks();
            else if (choice == "0")
                books = serv.BookByTitle(search);
            else books = serv.BookByWriter(search);
                    


            ArrayList values = new ArrayList();
            foreach (Book b in books)
            {
                values.Add(b);
            }

            RepeaterBook.DataSource = values;
            RepeaterBook.DataBind();
        }

        protected void ButtonDisplay_Click(object sender, EventArgs e)
        {
            String test = ((LinkButton)sender).CommandArgument;

            ViewState["GUID_Book"] = ((LinkButton)sender).CommandArgument;
            String guid = (String)ViewState["GUID_Book"];
            ClientScript.RegisterStartupScript(this.Page.GetType(), "popupOpener", "window.open('DisplayBooks.aspx?GUID_Book=" + test +"');", true);
            
        }
    }
}