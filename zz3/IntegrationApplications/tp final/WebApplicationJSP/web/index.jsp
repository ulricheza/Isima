<%-- 
    Document   : index
    Created on : 12 déc. 2011, 22:46:24
    Author     : JC
--%>

<%@page import="rendezvous_service2.Clients"%>
<%@page import="java.util.List"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JSP Page</title>

                <script type="text/javascript">
            function getClients() {
                <%
                beanJsp.IndexClient ind = new beanJsp.IndexClient();
                StringBuffer val = new StringBuffer();

                for ( rendezvous_service2.Clients c : ind.getClients()) {
                    val.append(c.getNom() + "<br />");
                }
                %>
                var chaine = "<%= new String(val) %>";
                document.getElementById("clients").innerHTML = chaine;
            }

             function getMedecins() {
              <%
               beanJsp.IndexClient ind2 = new beanJsp.IndexClient();
               StringBuffer val2 = new StringBuffer();

                for ( rendezvous_service2.Medecins m : ind2.getMedecins()) {
                    val2.append(m.getNom() + "<br />");
                }
                %>
                var chaine2 = "<%= new String(val2) %>";
                document.getElementById("medecins").innerHTML = chaine2;
            }
            
            function getMedecinsClient() { 
            <% 
               beanJsp.IndexClient ind3 = new beanJsp.IndexClient();
               StringBuffer val3 = new StringBuffer();
               
               for (rendezvous_service2.Clients c : ind3.getClients()) {
                   val3.append(c.getNom()).append("  <br/>Médecins:");
                   for (rendezvous_service2.Medecins m : ind3.getMedecinByIdClient(c.getId())) { 
                       val3.append(m.getNom()).append(" ");
                   }
                   val3.append(" <br/> "); 
                   val3.append(" <br/> "); 
               } 
               %>
               var chaine3 = "<%= new String(val3) %>"; 
               document.getElementById("medecinsClients").innerHTML = chaine3; 
            }

                  

        </script>
        
        
    </head>
    <body>
        
         La date courante est : <%= new java.util.Date() %>
        
        <%
        String [] languages = { "Java", "C++", "Smalltalk", "Simula 67" };
        out.println("<h3>Principaux langages orientés objets : </h3>");
        for (int i = 0; i < languages.length; i++) {
            out.println("<p>" + languages[i] + "</p>");
        }
        %>
        
        <button onclick="getClients();">afficher clients</button>
        <div id="clients"></div>
       
        <button onclick="getMedecins();">afficher medecins</button>
        <div id="medecins"></div>
        
        <button onclick="getMedecinsClient();">afficher les medecins par clients</button>
        <div id="medecinsClients"></div>


    </body>
</html>

