<%-- 
    Document   : index
    Created on : 18 janv. 2012, 13:45:50
    Author     : JC
--%>


<%@page import="databasemodeling.Attribut"%>
<%@page import="databasemodeling.Table"%>
<%@page import="databasemodeling.Table"%>
<%@page import="databasemodeling.Context"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Requête automatique sur les tables</title>
        <link rel="stylesheet" href="style.css" type="text/css" />
        <script type="text/javascript">
                
            function create_contrainte(i) 
            {
                var i2 = i + 1;
                if ( i == 1)
                {
                    document.getElementById('contrainte_'+i).innerHTML = 
                        '<h3>Contrainte: </h3>';
                    document.getElementById('contrainte_'+i).innerHTML = 
                        "Where ";
                }
                else
                {
                    document.getElementById('contrainte_'+i).innerHTML = "<br/>And ";     
                }
                 
                document.getElementById('contrainte_'+i).innerHTML += 
                    '<select name="TableContrainte_'+i+'" id="TableContrainte_'+i+'">';
            <%

                // Ajout des valeurs
            %>
        document.getElementById('contrainte_'+i).innerHTML += "</select>";
                
        //Ajout de la liste des opérations possibles
        document.getElementById('contrainte_'+i).innerHTML += 
            '<select id="TableComp_'+i+'" name="TableComp_'+i+'" id="TableComp_'+i+'">\n\
               <option value="CompSup"> > </option>"\n\
                <option value="CompInf"> < </option>"\n\
                <option value="CompSupEg"> >= </option>"\n\
                <option value="CompInfEg"> <= </option>"\n\
                <option value="CompNEg"> != </option>"\n\
                <option value="CompEg"> = </option>"';
    

        document.getElementById('contrainte_'+i).innerHTML += "</select>";
               
        document.getElementById('contrainte_'+i).innerHTML += 
            '<input type="text" name="valeur_'+i+'" id="valeur_'+i+'" />';
               
        document.getElementById('contrainte_'+i).innerHTML += 
            i+'<span id="contrainte_'+i2+'">\n\
               <a href="javascript:del_contrainte('+i+')">\n\
                <img src="images/croix_rouge.png" alt="Supprimer" /></a><br />\n\
                   <a href="javascript:create_contrainte('+i2+')">Ajouter une contrainte</a>\n\
                    <input id="nbContrainte" name="nbContrainte" type="HIDDEN" value="'+i+'"> </span>'
                        
        remplir_champs();
    }
               
    function del_contrainte(i) 
    {
        var i2 = i - 1 ;
        if( i2 == 0 )
        {
            document.getElementById('contrainte_'+i).innerHTML = 
                '<a href="javascript:create_contrainte('+i+')">Ajouter une contrainte</a>\n\
                    <input id="nbContrainte" name="nbContrainte" type="HIDDEN" value="'+i2+'"> </span>';
        }
        else
        {
            document.getElementById('contrainte_'+i).innerHTML = 
                ' <a href="javascript:del_contrainte('+i2+')">\n\
                <img src="images/croix_rouge.png" alt="Photo de montagne" /></a><br />\n\
                    <a href="javascript:create_contrainte('+i+')">Ajouter une contrainte</a>\n\
                    <input id="nbContrainte" name="nbContrainte" type="HIDDEN" value="'+i2+'"></span>';
        }
        remplir_champs();
                    
    }
                
    function remplir_champs() 
    {
        var x = new Array();
                    
        for (j=1; j <= document.getElementById("nbContrainte").value ; j++)
        {
            while ( 0 < document.getElementById("TableContrainte_"+j).length)
                document.getElementById("TableContrainte_"+j).options[0] = null;
        }
                    
        // Remplir un tableau javascript avec les attributs des différentes tables
            <%
                Context context2 = (Context) request.getSession().getAttribute("contexte");
                ArrayList<Table> tables = context2.getBase().getTables();
                StringBuffer val = new StringBuffer();

                ArrayList< ArrayList<String>> listVal = new ArrayList< ArrayList< String>>();

                int index = 0;
                for (Table t : tables) {
                    // Initialiser le tableau
                    out.println("x[" + index + "] = new Array();");
                    listVal.add(new ArrayList<String>());

                    ArrayList<Attribut> atr = t.getAttributs();

                    int index2 = 0;
                    for (Attribut a : atr) {
                        out.println("x[" + index + "][" + index2 + "] = \"" + a.getName() + "\" ;");
                        listVal.get(index).add(a.getName());
                        index2++;
                    }
                    index++;

                }

            %>
                    var valeur = document.formulaire.Tables.options.selectedIndex;
                                         
                    document.getElementById("Attributs").innerHTML = '<span name="Attributs" id="Attributs">';
                    for (i = 0; i < x[valeur].length ; i++)
                    {
                        document.getElementById("Attributs").innerHTML += '<input name="'+x[valeur][i]+'"type="checkbox"> ' + x[valeur][i];
                        for (j=1; j <= document.getElementById("nbContrainte").value ; j++)
                        {
                            nouvel_element = new Option(x[valeur][i],x[valeur][i],false,true);
                            document.getElementById("TableContrainte_"+j).options[document.getElementById("TableContrainte_"+j).length] = nouvel_element;
                        }
                    }
                     
                    document.getElementById("Attributs").innerHTML += '</span>';
                }
               
        </script>

    </head>
    <body onLoad="javascript:remplir_champs()">

        <%@include file="htmlMenu.html" %>

        Vous pouvez entrer votre requête.

        
            
            <br/><br/>
            <form id="makeMeAPrettyForm" name="formulaire" method="post" action="SnoopServerInterrogation">

            <h3> Tables </h3>
            <p>
            <br/><br/>
            <select name="Tables" id="Tables"  onChange="javascript:remplir_champs()">
            
            <%
                Context context = (Context) request.getSession().getAttribute("contexte");
                ArrayList<Table> tables2 = context.getBase().getTables();

                for (Table t : tables2) 
                {
                    int i = 0;
                    out.println("<option id=\"Table_" + i + "\" name=\"" + t.getName() + "\">" + t.getName() + "</option>");
                }
            %>

    </select> 
    </p>
    <br/><br/>
    <h3>Select: </h3>
    <p>
    <br/><br/>
    <span name="Attributs" id="Attributs">
    </span>

    <br/><br/>
    </p>
    <h3>Contrainte </h3>
    <br/><br/>
     <p>
    <span id="contrainte_1">
        <a href="javascript:create_contrainte(1)">Ajouter une contrainte</a>
        <input id="nbContrainte" name="nbContrainte" type="HIDDEN" value="0"> 
    </span>
    <br/>
    <br/>
    <input type ="submit" value="Affichage">
    </p>
</form>
</body>
</html>
