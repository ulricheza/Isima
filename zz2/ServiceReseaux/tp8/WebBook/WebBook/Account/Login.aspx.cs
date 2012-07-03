using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.Security;
using WebBook.ServiceIsimaServ;

namespace WebBook.Account
{
    public partial class Login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            RegisterHyperLink.NavigateUrl = "Register.aspx?ReturnUrl=" + HttpUtility.UrlEncode(Request.QueryString["ReturnUrl"]);
        }


        protected void LoginUser_Authenticate(object sender, AuthenticateEventArgs e)
        {
            bool authenticated = AuthenticateMe(LoginUser.UserName, LoginUser.Password, LoginUser.RememberMeSet);

            if (authenticated)
            {
                Session["login"] = LoginUser.UserName;
                FormsAuthentication.RedirectFromLoginPage(LoginUser.UserName, LoginUser.RememberMeSet);

            }
        }

        /// <summary>

        /// Authenticate user

        /// </summary>

        /// <param name="userName"></param>

        /// <param name="password"></param>

        /// <param name="rememberUserName"></param>

        /// <returns></returns>

        private bool AuthenticateMe(string userName, string password, bool rememberUserName)
        {
            ServiceIsimaBookSoapClient serv = new ServiceIsimaBookSoapClient();
            return serv.VerifyUser(userName, password);
        }

    }
}
