<%-- 
    Document   : ajoutTable
    Created on : 31 janv. 2012, 11:44:47
    Author     : JC
--%>


<%@page import="databasemodeling.Attribut"%>
<%@page import="databasemodeling.Table"%>
<%@page import="databasemodeling.Context"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>
        <link rel="stylesheet" href="style.css" type="text/css" />
        <script type="text/javascript">
            function create_champ(i) 
            {
                var i2 = i + 1;
                  
            <%
                Context context = (Context) request.getSession().getAttribute("contexte");
                ArrayList<String> types = context.getBase().getTypesSupportes();
                StringBuffer val = new StringBuffer();
                int index = 0;
                for (String t : types) {
                    val.append("<option value=\"" + t + "\">" + t + "</option>");
                    index++;
                }
            %>
                    var chaine = '<%= new String(val)%>';
                    document.getElementById('champ_'+i).innerHTML = 
                        '<br/><select name="TableChamp_'+i+'" id="TableChamp_'+i+'">'+chaine+'</select>';
                
                
               
                    document.getElementById('champ_'+i).innerHTML += 
                        '<input type="text" name="valeur_'+i+'" id="valeur_'+i+'" />';
               
                    document.getElementById('champ_'+i).innerHTML += '<input name="key_'+i+'"type="checkbox">';
               
                    document.getElementById('champ_'+i).innerHTML += 
                        i+'<span id="champ_'+i2+'">\n\
                   <a href="javascript:del_champ('+i+')">\n\
                    <img src="images/croix_rouge.png" alt="Supprimer" /></a><br/><br/>\n\
                       <a href="javascript:create_champ('+i2+')">Ajouter un champ</a>\n\
                        <input id="nbChamps" name="nbChamps" type="HIDDEN" value="'+i+'"> </span><br/>'
               
                }
               
                function del_champ(i) 
                {
                    var i2 = i - 1 ;
                    if( i2 == 0 )
                    {
                        document.getElementById('champ_'+i).innerHTML = 
                            '<a href="javascript:create_champ('+i+')">Ajouter un champ</a>\n\
                        <input id="nbChamps" name="nbChamps" type="HIDDEN" value="'+i2+'"> </span>';
                    }
                    else
                    {
                        document.getElementById('champ_'+i).innerHTML = 
                            ' <a href="javascript:del_champ('+i2+')">\n\
                    <img src="images/croix_rouge.png" alt="Photo de montagne" /></a><br />\n\
                        <a href="javascript:create_champ('+i+')">Ajouter un champ</a>\n\
                        <input id="nbChamps" name="nbChamps" type="HIDDEN" value="'+i2+'"></span>';
                    }
                    remplir_champs();
                    
                }
        </script>
    </head>
    <body>
        <%@include file="htmlMenu.html" %>
        <br/><br/>


        <form id="makeMeAPrettyForm" name="formulaire" method="post" action="SnoopServerAddTable">
            <h3>Nom de la table</h3>
            <p>
                <br/><br/>
                <input id="nom" name="nom" type="text"> 
                <br/><br/>
            </p>
            <h3>Champs</h3>
            <p>
                <span id="champ_1">
                    <a href="javascript:create_champ(1)">Ajouter un champ</a>
                    <input id="nbChamps" name="nbChamps" type="HIDDEN" value="0"> 
                </span>
                <br/><br/>
                <input type ="submit" value="Ajouter"> <br/>
            </p>
        </form>
    </body>
</html>
