<%@ page contentType="text/html" pageEncoding="UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <!-- Le HTML5 shim, for IE6-8 support of HTML elements -->
        <!--[if lt IE 9]>
            <script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
        <![endif]-->

        <link rel="stylesheet" href="http://twitter.github.com/bootstrap/assets/css/bootstrap.css">
        <link rel="stylesheet" href="http://twitter.github.com/bootstrap/assets/css/bootstrap-responsive.css">
        <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>

        <style type="text/css">
        body { padding-top: 20px; }
        </style>

        <in:block name="head">
            <title>XSnoop</title>
        </in:block>
    </head>
    <body>
        <div class="navbar navbar-fixed-top">
            <div class="navbar-inner">
                <div class="container">
                    <a class="brand" href="/xsnoop/pages/">XSnoop</a>
                    <c:if test="${!empty sessionScope.user.username}">
                        <ul class="nav pull-right">
                            <li class="dropdown" data-dropdown="dropdown">
                                <a href="#" class="dropdown-toggle" data-toggle="dropdown">
                                    Connected as <strong>${sessionScope.user.username}</strong>
                                    <b class="caret"></b>
                                </a>
                                <ul class="dropdown-menu">
                                    <c:if test="${!empty requestScope.selected_database_name}">
                                        <li>
                                            <a href="/xsnoop/pages/sql/createTable?database_name=${requestScope.selected_database_name}">Add a new table</a>
                                        </li>
                                        <li>
                                            <a href="/xsnoop/pages/sql/manageTables?database_name=${requestScope.selected_database_name}">Manage tables</a>
                                        </li>
                                        <li>
                                            <a href="/xsnoop/pages/sql/rawSql?database_name=${requestScope.selected_database_name}">Execute raw SQL</a>
                                        </li>
                                    </c:if>
                                    <c:if test="${empty requestScope.selected_database_name}">
                                        <li><a>Enter a database name</a></li>
                                        <li><a>to get more features.</a></li>
                                    </c:if>
                                    <li class="divider"></li>
                                    <li><a href="/xsnoop/pages/admin/logout">Logout</a></li>
                                </ul>
                            </li>
                        </ul>
                    </c:if>
                    <c:if test="${empty sessionScope.user.username}">
                        <form action="/xsnoop/pages/admin/login" meth="post" class="navbar-form pull-right">
                            <input class="input-small" type="text" placeholder="Username" name="username" />
                            <input class="input-small" type="password" placeholder="Password" name="password" />
                            <button class="btn btn-success" type="submit">Log in</button>
                        </form>
                    </c:if>
                </div>
            </div>
        </div>
        <div class="container">
            <div class="content">
                <div class="page-header">
                    <in:block name="page-header"></in:block>
                </div>
                <div id="notifications">
                    <c:forEach items="${sessionScope.errors}" var="error">
                        <div class="alert alert-block alert-error fade in">
                            <a class="close" data-dismiss="alert" href="#">&times;</a>
                            ${error}
                        </div>
                    </c:forEach>
                    <c:remove var="errors" scope="session"></c:remove>
                    <c:forEach items="${sessionScope.infos}" var="info">
                        <div class="alert alert-block alert-info fade in">
                            <a class="close" data-dismiss="alert" href="#">&times;</a>
                            ${info}
                        </div>
                    </c:forEach>
                    <c:remove var="infos" scope="session"></c:remove>
                </div>
                <in:block name="content"></in:block>
            </div>
            <footer>
                <script type="text/javascript" src="http://ajax.aspnetcdn.com/ajax/jquery.templates/beta1/jquery.tmpl.min.js"></script>
                <script type="text/javascript" src="http://twitter.github.com/bootstrap/assets/js/bootstrap-modal.js"></script>
                <script type="text/javascript" src="http://twitter.github.com/bootstrap/assets/js/bootstrap-dropdown.js"></script>
                <script type="text/javascript" src="http://twitter.github.com/bootstrap/assets/js/bootstrap-alert.js"></script>
                <script type="text/javascript" src="http://twitter.github.com/bootstrap/assets/js/bootstrap-transition.js"></script>
                <in:block name="javascript"></in:block>
                <script type="text/javascript">
                    $().dropdown();
                    $(".alert-message").alert();
                </script>
                <p align="center">Guillaume Bernard, William Durand &copy; 2012</p>
            </footer>
        </div>
    </body>
</html>