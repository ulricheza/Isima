<%@ Page Title="Se connecter" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
    CodeBehind="Login.aspx.cs" Inherits="WebBook.Account.Login" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">
    <h2>
        Se connecter
    </h2>
    <p>
        Entrez un nom d'utilisateur et un mot de passe.
        <asp:HyperLink ID="RegisterHyperLink" runat="server" EnableViewState="false">S'inscrire</asp:HyperLink> si vous n'avez pas de compte.
    </p>
    <asp:Login ID="LoginUser" runat="server" EnableViewState="false" 
        RenderOuterTable="false" onauthenticate="LoginUser_Authenticate">
    </asp:Login>
</asp:Content>
