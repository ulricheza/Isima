<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="SearchBook.aspx.cs" Inherits="WebBook.SearchBook" %>
<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
    <p>
        Recherche avancée</p>
    <asp:TextBox ID="TextBoxSearch" runat="server"></asp:TextBox>
    <br />
    <p>
    <asp:RadioButton ID="RadioButtonTitle" runat="server"/> Par titre
    <asp:RadioButton ID="RadioButtonWriter" runat="server"/> Par auteur

    </p>
<p>
    <asp:Button ID="ButtonSearch" runat="server" onclick="ButtonSearch_Click" 
        Text="Rechercher" Width="99px" />

    </p>
</asp:Content>
