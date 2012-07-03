<%-- 
    Document   : supressionTable
    Created on : 31 janv. 2012, 11:29:34
    Author     : JC
--%>

<%@page import="databasemodeling.Table"%>
<%@page import="java.util.ArrayList"%>
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
        <br/><br/>
        <form id="makeMeAPrettyForm" name="formulaire_sup" method="POST" action="SnoopServerDropTable">
            <h3> Tables à supprimer </h3>
            <p><br/>
            <select name="Tables" id="Tables">
                
                <%
                    Context context = (Context) request.getSession().getAttribute("contexte");
                    ArrayList<Table> tables2 = context.getBase().getTables();
                    for (Table t : tables2) {
                        out.println("<option>" + t.getName() + "</option>");
                    }
                %>
            </select>
            <br/><br/>
            

            <input type ="submit" value="Supprimer">
            </p>
        </form>

    </body>
</html>
