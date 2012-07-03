using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebBook
{
    public partial class SearchBook : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void ButtonSearch_Click(object sender, EventArgs e)
        {
            int choice = 0;
            if (RadioButtonTitle.Checked)
                choice = 0;
            else if (RadioButtonWriter.Checked)
                choice = 1;

            String text = TextBoxSearch.Text;
            Response.Redirect("ListBook.aspx?choice="+ choice + "&search=" + text, true);
        }


    }
}