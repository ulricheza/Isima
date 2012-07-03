<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Panier.aspx.cs" Inherits="WebBook.Panier" %>
<asp:Content ID="Content1" ContentPlaceHolderID="HeadContent" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
           <asp:Repeater id="RepeaterPanier" runat="server">
          <HeaderTemplate>
             <table border=1>
                <tr>
                   <td><b>Titre du livre</b></td>
                   <td><b>Nombre d'exemplaire</b></td>
                </tr>
          </HeaderTemplate>
             
          <ItemTemplate>
             <tr>
             <td> 
                <%# DataBinder.Eval(Container.DataItem, "NameBook") %> </td>
                <td> <%# DataBinder.Eval(Container.DataItem, "Nb") %> </td>
                <td><asp:LinkButton ID="ButtonDelete" runat="server" Text="Delete" 
                CommandArgument='<%# DataBinder.Eval(Container.DataItem, "GUID")%>'
                OnClick="ButtonDelete_Click"
                 /></td>

             </tr>
          </ItemTemplate>
             
          <FooterTemplate>
             </table>
          </FooterTemplate>
</asp:Repeater>
           <asp:Button ID="Button1" runat="server" onclick="Button1_Click" 
               Text="Accepter la commande" />
</asp:Content>
