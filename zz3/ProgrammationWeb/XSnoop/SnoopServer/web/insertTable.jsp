<%-- 
    Document   : insertTable
    Created on : 31 janv. 2012, 11:45:59
    Author     : JC
--%>

<%@page import="databasemodeling.Attribut"%>
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
        <script type="text/javascript">
                // Méthode pour ajouter les champs à remplir
                function remplir_ajout() 
                {
                    // Tableau à deux dimensions contenant les tables et leurs attributs
                    var x = new Array();
                    
                    // Remplir un tableau javascript avec les attributs des différentes tables
                    <%
                        Context context2 = (Context)request.getSession().getAttribute("contexte");
                        ArrayList<Table> tables = context2.getBase().getTables();
                        StringBuffer val = new StringBuffer();
                                                                   
                        int index = 0;
                        for ( Table t : tables)
                        {
                            // Initialiser le tableau
                            out.println("x["+index+"] = new Array();");
                                                         
                            ArrayList<Attribut> atr = t.getAttributs();
                            
                            int index2 = 0;
                            for(Attribut a : atr )
                            {
                                out.println("x["+index+"]["+index2+"] = \""+ a.getName() +"\" ;");
                                index2++;
                            }
                            index++;
                            
                        }
                        
                    %>
                     // Récupère la ligne selectionné
                     var valeur = document.formulaire_aj.Tables.options.selectedIndex;
                     
                     // Ajoute le span à remplacer
                     document.getElementById("ajout").innerHTML = '<span id="ajout"><br/>';
                     for (i = 0; i < x[valeur].length ; i++)
                     {
                        // Créer les champs
                        document.getElementById("ajout").innerHTML += '<input id="'+x[valeur][i]+ '" name="' + x[valeur][i] + '" type="text"> ' + x[valeur][i] + "<br/>";
                     }
                     document.getElementById("ajout").innerHTML += '</span>';
                }
    </script>
    </head>
    <body onLoad="javascript:remplir_ajout()">
        <%@include file="htmlMenu.html" %>
        <br/><br/>
        

            <form id="makeMeAPrettyForm" name="formulaire_aj" method="post" action="SnoopServerAddRow">
                
            <h3> Insertion d'une ligne </h3>
            <br/>  
            <p>
            <select name="Tables" id="Tables" onChange="javascript:remplir_ajout()">
           <%
            Context context = (Context)request.getSession().getAttribute("contexte");
            ArrayList<Table> tables2 = context.getBase().getTables();

            for ( Table t : tables2)
            {
               int i=0;
               out.println("<option>" + t.getName() +"</option>");
            }
        %>
        
        </select> Choix de la table
        <br/>
        </p>
        
        <h3> Valeur à insérer </h3>
        <p>
        <span id="ajout">
        </span>
        
        
        <p>
            <br/>
        <input type ="submit" value="Ajouter">
        </p>
        </form>
        
        
    </body>
</html>
