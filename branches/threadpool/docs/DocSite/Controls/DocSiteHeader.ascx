<%@ Control Language="C#" AutoEventWireup="true" Codebehind="DocSiteHeader.ascx.cs"
    Inherits="SlimDXDocs.Controls.DocSiteHeader" %>
<div id="docsite_header_links">
    <asp:HyperLink runat="server" ID="chmHyperLink" meta:resourcekey="chmHyperLinkResource1"
        rel="nofollow">Download Compiled Help</asp:HyperLink>
    |
    <asp:HyperLink runat="server" ID="adminHyperLink" NavigateUrl="~/DocSiteAdmin.aspx"
        meta:resourcekey="adminHyperLinkResource1" rel="nofollow">Admin</asp:HyperLink>
    <asp:LoginView runat="server" ID="loginView">
        <LoggedInTemplate>
            |
            <asp:LoginStatus runat="server" ID="loginStatus" SkinID="LoginStatus" meta:resourcekey="loginStatusResource1" />
            (
            <asp:LoginName runat="server" ID="loginName" SkinID="LoginName" meta:resourcekey="loginNameResource1" />
            )
        </LoggedInTemplate>
    </asp:LoginView>
</div>
<div id="docsite_header_search">
    <asp:TextBox runat="server" ID="searchTextBox" SkinID="SearchTextBox" onfocus="this.select();"
        EnableViewState="False" MaxLength="100" meta:resourcekey="searchTextBoxResource1" />
    <asp:ImageButton runat="server" ID="searchImageButton" OnClick="searchImageButton_Click"
        SkinID="SearchImageButton" CausesValidation="False" ToolTip='<%$ Resources:General,DocSiteSearchButtonToolTip %>'
        meta:resourcekey="searchImageButtonResource1" />
    <asp:ImageButton runat="server" ID="browseImageButton" OnClick="browseImageButton_Click"
        SkinID="BrowseImageButton" CausesValidation="False" ToolTip='<%$ Resources:General,DocSiteBrowseButtonToolTip %>'
        meta:resourcekey="browseImageButtonResource1" />
</div>
<asp:HyperLink runat="server" ID="homepageHyperLink" NavigateUrl="http://slimdx.mdxinfo.com">
    <asp:Image runat="server" ID="logoImage" CssClass="docsite_logo" ImageUrl="~/Images/SdxLogo.png"
        meta:resourcekey="logoImageResource1" />
</asp:HyperLink>
<asp:HyperLink runat="server" ID="docpageHyperLink" NavigateUrl="http://mdxinfo.com/slimdx/ld" style="text-decoration: none">
<div id="docsite_header_title">
    <%= SlimDXDocs.DocSite.ProjectTitle%>
</div>
</asp:HyperLink>
<div id="docsite_header_company">
    <%= SlimDXDocs.DocSite.ProjectCompany%>
</div>
