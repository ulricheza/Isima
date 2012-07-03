<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<c:if test="${empty requestScope.error}">
{
    "query": "${requestScope.query}",
    "columns": ${requestScope.humanized_columns},
    "results": ${requestScope.results}
}
</c:if>

<c:if test="${!empty requestScope.error}">
{
    "error": "${requestScope.error}"
}
</c:if>