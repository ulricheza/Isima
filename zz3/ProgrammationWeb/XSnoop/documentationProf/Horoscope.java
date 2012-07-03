import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class Horoscope extends HttpServlet {

  static final private String CONTENT_TYPE = "text/html";

  public void doPost(HttpServletRequest query, HttpServletResponse answer) throws ServletException, IOException {
    answer.setContentType(CONTENT_TYPE);
    PrintWriter out = answer.getWriter();
    String sign = "unknown";
    int jj = Integer.parseInt(query.getParameter("BirthDay"));
    String mm = query.getParameter("BirthMonth");
    if ( ((mm.compareTo("Mar") == 0) && (jj>=20)) || ((mm.compareTo("Apr") == 0) && (jj<=20))) sign = "Aries";
    if ( ((mm.compareTo("Apr") == 0) && (jj>=21)) || ((mm.compareTo("May") == 0) && (jj<=21))) sign = "Taurus";
    if ( ((mm.compareTo("May") == 0) && (jj>=22)) || ((mm.compareTo("Jun") == 0) && (jj<=21))) sign = "Gemini";
    if ( ((mm.compareTo("Jun") == 0) && (jj>=22)) || ((mm.compareTo("Jul") == 0) && (jj<=22))) sign = "Cancer";
    if ( ((mm.compareTo("Jul") == 0) && (jj>=23)) || ((mm.compareTo("Au") == 0) && (jj<=22))) sign = "Leo";
    if ( ((mm.compareTo("Au") == 0) && (jj>=23)) || ((mm.compareTo("Sep") == 0) && (jj<=22))) sign = "Virgo";
    if ( ((mm.compareTo("Sep") == 0) && (jj>=23)) || ((mm.compareTo("Oct") == 0) && (jj<=22))) sign = "Libra";
    if ( ((mm.compareTo("Oct") == 0) && (jj>=23)) || ((mm.compareTo("Nov") == 0) && (jj<=22))) sign = "Scorpio";
    if ( ((mm.compareTo("Nov") == 0) && (jj>=23)) || ((mm.compareTo("Dec") == 0) && (jj<=21))) sign = "Sagittarius";
    if ( ((mm.compareTo("Dec") == 0) && (jj>=22)) || ((mm.compareTo("Jan") == 0) && (jj<=20))) sign = "Capricorn";
    if ( ((mm.compareTo("Jan") == 0) && (jj>=21)) || ((mm.compareTo("Feb") == 0) && (jj<=19))) sign = "Aquarius";
    if ( ((mm.compareTo("Feb") == 0) && (jj>=20)) || ((mm.compareTo("Mar") == 0) && (jj<=19))) sign = "Pisces";
    out.println("<html>");
    out.println("<head><title>Horoscope</title></head>");
    out.println("<body>");
    out.println("<h2>" + query.getParameter("FirstName") + "</h2>");
    out.println("<p>You're " + "<h1>" + sign + "</h1></b></p>");
    out.println("</body></html>");
  }

  public void doGet(HttpServletRequest query, HttpServletResponse answer) throws ServletException, IOException {
    doPost(query, answer);
  }
}