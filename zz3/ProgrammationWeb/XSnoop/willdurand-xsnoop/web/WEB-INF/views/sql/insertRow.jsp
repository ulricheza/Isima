<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>
<%@ taglib uri="/WEB-INF/tlds/functions" prefix="fn" %>

<in:override name="content">
    <div class="row">
        <div class="span12">
            <h2>Creating a new ${table_name}</h2>
            <br />
            <form action="" method="post">
                <c:forEach items="${requestScope.columns}" var="col">
                    <div class="control-group">
                        <label for="${col.name}">${fn:humanize(col.name)}</label>
                        <div class="controls">
                            <c:if test="${col.isNumeric()}">
                                <input type="text" name="${col.name}" value="" />
                            </c:if>
                            <c:if test="${col.isVarchar()}">
                                <input type="text" name="${col.name}" value="" />
                            </c:if>
                            <c:if test="${col.isText()}">
                                <textarea name="${col.name}"></textarea>
                            </c:if>
                            <c:if test="${col.isDateTime()}">
                                <input type="text" name="${col.name}" value="" />
                            </c:if>
                            <p class="help-inline"><strong>Help:</strong> You have to fill in a <code>${fn:lowercase(col.type)}</code> value.</p>
                        </div>
                    </div>
                </c:forEach>
                <div class="form-actions">
                    <button class="btn btn-primary" type="submit">Create</button>
                </div>
            </form>
        </div>
    </div>
</in:override>

<%@ include file="../layout.jsp" %>