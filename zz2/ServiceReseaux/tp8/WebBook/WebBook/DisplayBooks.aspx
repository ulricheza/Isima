<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="DisplayBooks.aspx.cs" Inherits="WebBook.DisplayBooks" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
     <asp:Label ID="Titre" runat="server" Text="Titre: "></asp:Label>
    <asp:Label ID="LabelTitle" runat="server" Font-Names="Arial" Font-Size="Larger" 
        Text=""></asp:Label>
    <br />
    <br />
    <asp:Label ID="Kind" runat="server" Text="Genre: "></asp:Label>
    <asp:Label ID="LabelKind" runat="server" Text=""></asp:Label>
    <br />
    <br />
    <asp:Label ID="Autor" runat="server" Text="Auteurs: "></asp:Label>
    <asp:Label ID="LabelAutor" runat="server" Text=""></asp:Label>
    <br />
    <asp:Label ID="Editor" runat="server" Text="Editeur: "></asp:Label>
    <asp:Label ID="LabelEditor" runat="server" Text=""></asp:Label>
    <br />
    <br />
    <asp:Label ID="Date" runat="server" Text="Date: "></asp:Label>
    <asp:Label ID="LabelDate" runat="server" Text=""></asp:Label>
    <br />
    <br />
    <asp:Label ID="Price" runat="server" Text="Prix: "></asp:Label>
    <asp:Label ID="LabelPrice" runat="server" Text=""></asp:Label>
        <br />
        <br />
    <br />
        <asp:Label ID="Label1" runat="server" Text="Nombre d'exemplaire"></asp:Label>
    <br />
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<asp:TextBox 
            ID="TextBox1" runat="server" Width="92px"></asp:TextBox>
        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<asp:Button ID="Button1" runat="server" 
            onclick="Button1_Click" Text="Ajouter au panier" Width="106px" />
        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <input type="button" value="Fermer" onClick="javascript:window.close();" /><br />
    </div>
    </form>
</body>
</html>
