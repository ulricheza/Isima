<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>

<in:override name="content">
    <div class="row">
        <div class="span12">
            <h2>Execute RAW SQL</h2>
            <br />
            <form action="" method="post">
                <div class="control-group">
                    <label for="sql">&nbsp;</label>
                    <div class="controls">
                        <input type="hidden" value="${database_name}" name="database_name" />
                        <textarea name="sql" class="span8" rows="8">${requestScope.sql}</textarea>
                        <p class="help-block"><strong>Help:</strong> Enter all SQL statements you want separated by semi-colons.</p>
                    </div>
                </div>
                <div class="form-actions">
                    <button class="btn btn-primary" type="submit">Execute</button>
                </div>
            </form>
        </div>
    </div>
</in:override>

<%@ include file="../layout.jsp" %>