<%-- 
    Document   : index
    Created on : 18 janv. 2012, 13:50:53
    Author     : Maxime
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
        <title>Connexion à l'application</title>
        <link rel="stylesheet" href="styleConnexion.css" type="text/css" />

    </head>
    <header>
        <div class="container_title">
            <h1 class="fontface" id="title">Maxime Escourbiac's website</h1>
        </div>
    </header>
    <body>
        <div id="content">
            <form name="session" method="POST" action="SnoopServerConnection" /> 
            <table>
                <tr>
                    <td>SGBD : </td>
                    <td>
                        <select name="type" size="1">
                            <option>OBDC</option>
                            <option>MySQL</option>
                        </select>
                    </td>
                </tr>
                <tr>
                    <td>Adresse de la base : </td>
                    <td><input type="text" name="adress" /> </td>
                </tr>
                <tr>
                    <td>Nom de la base : </td>
                    <td>
                        <input type="text" name="name" />
                    </td>
                </tr>

                <tr>
                    <td>Login : </td>
                    <td><input type="text" name="login" /> </td>
                </tr>
                <tr>
                    <td>Mot de passe : </td>
                    <td><input type="password" name="password" /> </td>
                </tr>
                <tr>
                    <td colspan="2" style="text-align:center"><input type="submit" name="valider" /></td>
                </tr>
            </table>
        </form>
    </div>
</body>
</html>
