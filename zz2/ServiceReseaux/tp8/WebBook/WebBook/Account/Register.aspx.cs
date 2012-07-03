using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using WebBook.ServiceIsimaServ;

namespace WebBook.Account
{
    /// <summary>
    /// Class pour s'enregistrer
    /// </summary>
    public partial class Register : System.Web.UI.Page
    {

        protected void Page_Load(object sender, EventArgs e)
        {
            
        }

        /// <summary>
        /// Permet de s'identifier
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void CreateUserButton_Click(object sender, EventArgs e)
        {
            ServiceIsimaBookSoapClient serv = new ServiceIsimaBookSoapClient();
            serv.AddUser(UserName.Text, Email.Text, ZipCode.Text, Ville.Text, Password.Text);

            FormsAuthentication.RedirectFromLoginPage(UserName.Text, true);
            Response.Redirect("Default.aspx");
        }

    }
}
