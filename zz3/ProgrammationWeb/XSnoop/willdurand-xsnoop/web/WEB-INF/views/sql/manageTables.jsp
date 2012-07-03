<%@taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<in:override name="content">
    <div class="row">
        <div class="span12">
            <table class="table table-striped">
                <thead>
                    <tr>
                        <th>Name</th>
                        <th>Actions</th>
                    </tr>
                </thead>
                <tbody>
                    <c:if test="${!empty requestScope.tables}">
                        <c:forEach items="${requestScope.tables}" var="table">
                            <tr>
                                <td>${table.name}</td>
                                <td>
                                    <a href="/xsnoop/pages/sql/insertRow?database_name=${requestScope.database_name}&table_name=${table.name}">
                                        <i class="icon-plus-sign"></i>
                                        insert a new row
                                    </a>
                                    &nbsp;&nbsp;&nbsp;
                                    <a href="/xsnoop/pages/sql/deleteTable?database_name=${requestScope.database_name}&table_name=${table.name}" onclick="return confirm('Do you really want to delete the table \'${table.name}\' ?');">
                                        <i class="icon-minus-sign"></i>
                                        delete the table
                                    </a>
                                    &nbsp;&nbsp;&nbsp;
                                    <a href="/xsnoop/pages/sql/truncateTable?database_name=${requestScope.database_name}&table_name=${table.name}" onclick="return confirm('Do you really want to truncate the table \'${table.name}\' ?');">
                                        <i class="icon-trash"></i>
                                        truncate the table
                                    </a>
                                </td>
                            </tr>
                        </c:forEach>
                    </c:if>
                </tbody>
            </table>
        </div>
    </div>
</in:override>

<%@ include file="../layout.jsp" %>