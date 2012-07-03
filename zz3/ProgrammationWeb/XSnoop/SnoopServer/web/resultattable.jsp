<%-- 
    Document   : resultattable
    Created on : 25 janv. 2012, 11:45:57
    Author     : Maxime
--%>

<%@page import="java.util.ArrayList"%>
<%@page import="databasemodeling.Resultats"%>
<%@page import="databasemodeling.Context"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
         <link rel="stylesheet" href="style.css" type="text/css" />
    </head>
    <body>
        <%@include file="htmlMenu.html" %>
        <h3>Résultat:</h3>
        <form name="formulaire" method="post" action="SnoopServerDropRow">
        <%
            Context context = (Context) request.getSession().getAttribute("contexte");
            Resultats res = context.getResultats();
            
            ArrayList<String> col;
            
            col = res.getColumnName();
            
            out.println("<table><caption>Résultat</caption>");
            out.println("<tr>");
            for (int j = 0; j < col.size(); ++j)
            {
                    out.println("<th>");
                    out.println(col.get(j));
                    out.println("</th>");
            }
            out.println("<th>");
            out.println("</th>");
            out.println("</tr>");
            for (int i = 1; i<=res.nbResult(); ++i)
            {
                col = res.getRow(i);
                out.println("<tr>");
                for (int j = 0; j < col.size(); ++j)
                {
                    out.println("<td>");
                    out.println(col.get(j));
                    out.println("</td>");
                }
                out.println("<td>");

                out.println("<input name=\"sup_"+i+"\" type=\"checkbox\">");
                
                out.println("</td>");
                out.println("</tr>");
            }
            out.println("</table>");
            
         %>
         <input type ="submit" value="Supprimer">
        </form>

    </body>
</html>
