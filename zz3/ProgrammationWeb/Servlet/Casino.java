import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class Casino extends HttpServlet {
	
	// Request and response's content type
	static final private String CONTENT_TYPE = "text/html";
	
	// Main
	public void service(HttpServletRequest query, HttpServletResponse answer) throws ServletException, IOException {
		answer.setContentType(CONTENT_TYPE);
		PrintWriter out = answer.getWriter();
		
		int n = 6, m = 49;
		
		out.println("<html>");
		out.println("<head><title>Casino</title></head>");
		out.println("<body>");
		
		out.println("<h1>Welcome loser !</h1>");
		
		out.println("<p>Today is <b>" + (new Date()).toString() + "</b></p>");
		out.println("<p><b>The wining martingale is:</b></p>");
		Random r =new Random();
		out.println("<table border=1><tr align=center>");
		
		for(int i = 0; i < n; i++) out.print("<th> Draw #" + (i+1) + " </th>");
		out.print("</tr>");
		for (int i = 0; i < n; i++) {
			out.print("<tr align=center>");
			for(int j = 0; j < n; j++) out.print("<td>" + r.nextInt(m) + "</td>");
			out.println("</tr>");
		}
		out.println("</tr></table>");
		out.println("</body></html>");
	}
}
