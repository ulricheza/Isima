import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Post extends HttpServlet {

        public void doGet(HttpServletRequest query, HttpServletResponse answer) throws IOException, ServletException {
                answer.setContentType("text/html");
                PrintWriter pw = answer.getWriter();
                pw.println("<html>");
                pw.println("<head>");
                pw.println("<title>Some HttpServletRequest methods</title>");
                pw.println("</head>");
                pw.println("<body>");
                pw.println("<h3>HttpServletRequest methods</h3>");
                pw.println("<table>");
                pw.println("<tr><td colspan='2' align='center' bgcolor='lightgreen'>");
                pw.println("<b>Information about the request</b></td></tr>");
                pw.println("<tr>");
                pw.println("<td><b>Action:</b></td>");
                pw.println("<td>" + query.getMethod() + "</td>");
                pw.println("</tr><tr>");
                pw.println("<td><b>URI:</b></td>");
                pw.println("<td>" + query.getRequestURI() + "</td>");
                pw.println("</tr><tr>");
                pw.println("<td><b>Protocol:</b></td>");
                pw.println("<td>" + query.getProtocol() + "</td>");
                pw.println("</tr><tr>");
                pw.println("<td><b>Path:</b></td>");
                pw.println("<td valign='bottom'>" + query.getPathInfo() + "</td>");
                pw.println("</tr><tr>");
                pw.println("<td><b>Client's IP:</b></td>");
                pw.println("<td>" + query.getRemoteAddr() + "</td>");
                pw.println("</tr>");
                pw.println("<tr><td colspan='2' align='center' bgcolor='lightgreen'>");
                pw.println("<b>En-têtes</b></td></tr>");
                Enumeration e = query.getHeaderNames();
                while (e.hasMoreElements()) {
                        String nm = (String)e.nextElement();
                        String val = query.getHeader(nm);
                        pw.println("<tr><td valign='top'><b>" + nm + "</b></td>");
                        pw.println("<td>" + val + "</td></tr>");
                }
                pw.println("</table>");
                pw.println("</body>");
                pw.println("</html>");
        }

        public void doPost(HttpServletRequest query,HttpServletResponse answer) throws IOException, ServletException {
                doGet(query, answer);
        }
}