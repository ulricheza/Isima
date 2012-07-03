<%@ Page Title="" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="ListBook.aspx.cs" Inherits="WebBook.ListBook" %>
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
                <td> <%# DataBinder.Eval(Container.DataItem, "Title") %> </td>
                <td> <%# DataBinder.Eval(Container.DataItem, "NameWriter") %> </td>
                <td align="center">
                <asp:LinkButton ID="ButtonDisplay" runat="server" Text="Details" 
                CommandArgument='<%# DataBinder.Eval(Container.DataItem, "GUID")%>'
                OnClick="ButtonDisplay_Click"
                 />
            </td>
             </tr>
          </ItemTemplate>
             
          <FooterTemplate>
             </table>
          </FooterTemplate>
             
       </asp:Repeater>
</asp:Content>
