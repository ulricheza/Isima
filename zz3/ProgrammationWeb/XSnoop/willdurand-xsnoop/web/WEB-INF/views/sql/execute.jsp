<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>
<%@ taglib uri="/WEB-INF/tlds/functions" prefix="fn" %>

<in:override name="content">
    <h1>Results</h1>
    <div class="row">
        <div class="span12">
            <c:if test="${empty requestScope.results}">
                <br />
                <div class="alert alert-warning alert-block">
                    No results.
                </div>
            </c:if>
            <c:if test="${!empty requestScope.results}">
                <table class="table table-striped">
                    <thead>
                        <c:forEach items="${requestScope.columns}" var="col">
                            <th>${fn:humanize(col.name)}</th>
                        </c:forEach>
                    </thead>
                    <tbody>
                        <c:forEach items="${requestScope.results}" var="row">
                            <tr>
                                <c:forEach items="${requestScope.columns}" var="col">
                                    <c:if test="${col.isPrimaryKey()}">
                                        <td><a href="/xsnoop/pages/sql/deleteRow?database=${requestScope.selected_database_name}&table=${requestScope.selected_table_name}&pk=${col.name}&${col.name}=${row.get(col)}" onclick="return confirm('Do you really want to delete this row?');" title="Delete this row">${row.get(col)}</a></td>
                                    </c:if>
                                    <c:if test="${!col.isPrimaryKey()}">
                                        <td>${row.get(col)}</td>
                                    </c:if>
                                </c:forEach>
                            </tr>
                        </c:forEach>
                    </tbody>
                </table>
            </c:if>
        </div>
    </div>
    <div class="row">
        <div class="span12">
            <form action="/xsnoop/pages/index/selectColumns" method="post">
                <input name="database_name" type="hidden" value="${requestScope.selected_database_name}" />
                <input name="table_name" type="hidden" value="${requestScope.selected_table_name}" />
                <div class="form-actions">
                    <button type="submit" class="btn btn-primary">
                        <i class="icon-share-alt icon-white"></i>
                        Create a new query
                    </button>
                </div>
            </form>
        </div>
    </div>
</in:override>

<%@ include file="../layout.jsp" %>