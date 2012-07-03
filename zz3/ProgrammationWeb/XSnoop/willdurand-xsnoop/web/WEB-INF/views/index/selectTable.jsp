<%@taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<in:override name="form-action">/xsnoop/pages/index/selectColumns</in:override>

<in:override name="form-actions">
    <button class="btn" id="back_button">
        &larr; Previous step
    </button>
</in:override>

<in:override name="form-content">
    <fieldset>
        <legend>Select a table</legend>
        <div class="control-group">
            <label class="control-label" for="table_name">&nbsp;</label>
            <div class="controls">
                <select name="table_name" id="selectTables">
                    <option value="">Select a table</option>
                    <c:forEach items="${requestScope.table_names}" var="table">
                        <c:if test="${requestScope.selected_table_name.equals(table.name)}">
                            <option value="${table.name}" selected="selected">${table.name}</option>
                        </c:if>
                        <c:if test="${!requestScope.selected_table_name.equals(table.name)}">
                            <option value="${table.name}">${table.name}</option>
                        </c:if>
                    </c:forEach>
                </select>
                <c:if test="${!empty sessionScope.user}">
                    <a href="/xsnoop/pages/sql/createTable?database_name=${requestScope.selected_database_name}"><i class="icon-plus-sign"></i>Add a new table</a>
                </c:if>
            </div>
        </div>
    </fieldset>
    <in:block name="form-content-2"></in:block>
</in:override>

<in:override name="javascript">
    <script type="text/javascript">
        $(document).ready(function() {
            $("#selectTables").change(function() {
                $('#xsnoop-form').attr('action', '/xsnoop/pages/index/selectColumns');
                $('#xsnoop-form').submit();
            });

            $('#back_button').click(function() {
                $('#xsnoop-form').attr('action', '/xsnoop/pages/index');
                $('#xsnoop-form').submit();
            });
        });
    </script>
</in:override>

<%@ include file="index.jsp" %>
