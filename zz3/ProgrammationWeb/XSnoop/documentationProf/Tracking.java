import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Tracking extends HttpServlet {

        public void doPost(HttpServletRequest query, HttpServletResponse answer) throws IOException, ServletException {
                answer.setContentType("text/html");
                PrintWriter pw = answer.getWriter();
                String id = null;
                Cookie[] cookies = query.getCookies();
                Cookie cookie = null;
                if (cookies != null) {
                        for (int i = 0; i < cookies.length; i++) {
                                if (cookies[i].getName().equals("TrackMaster")) {
                                        cookie = cookies[i];
                                        id = cookie.getValue();
                                        break;
                                }
                        }
                }
                if (id == null) id = new String("*");
                else id = id + "*";
                answer.addCookie(new Cookie("TrackMaster", id));
                pw.print("<html>");
                pw.print("<body bgcolor='white'>");
                pw.print("<h1>This is your visit #</h1>");
                pw.print("<h2>" + id.length() + "</h2>");
                pw.print("</body>");
                pw.print("</html>");
        }

        public void doGet(HttpServletRequest query, HttpServletResponse answer) throws IOException, ServletException {
                doPost(query, answer);
        }

}