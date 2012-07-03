<%@ Page Title="Page d'accueil" Language="C#" MasterPageFile="~/Site.master" AutoEventWireup="true"
    CodeBehind="Default.aspx.cs" Inherits="WebBook._Default" %>

<asp:Content ID="HeaderContent" runat="server" ContentPlaceHolderID="HeadContent">
</asp:Content>
<asp:Content ID="BodyContent" runat="server" ContentPlaceHolderID="MainContent">      
       <asp:Repeater id="RepeaterBook" runat="server">
          <HeaderTemplate>
             <table border=1>
                <tr>
                   <td><b>Titre</b></td>
                   <td><b>Auteur</b></td>
                </tr>
          </HeaderTemplate>
             
          <ItemTemplate>
             <tr>
                <td> <%# DataBinder.Eval(Container.DataItem, "GUID") %> </td>
                <td> <%# DataBinder.Eval(Container.DataItem, "NameWriter") %> </td>
             </tr>
          </ItemTemplate>
             
          <FooterTemplate>
             </table>
          </FooterTemplate>
             
       </asp:Repeater>
</asp:Content>
