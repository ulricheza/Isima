<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>
<%@ taglib uri="/WEB-INF/tlds/functions" prefix="fn" %>

<in:override name="form-action">/xsnoop/pages/sql/createQuery</in:override>

<in:override name="form-content-2">
    <div class="clearfix"></div>
    <fieldset>
        <legend>Select columns</legend>
        <div class="clearfix">
            <table class="table table-striped">
                <thead>
                    <tr>
                        <th>
                            Selected?
                            &nbsp;
                            <span class="label" id="check_all">all</span>
                            &nbsp;
                            <span class="label" id="uncheck_all">none</span>
                        </th>
                        <th>Column Name</th>
                        <th>Type</th>
                    </tr>
                </thead>
                <tbody>
                    <c:forEach items="${requestScope.column_names}" var="col">
                        <tr>
                            <td>
                            <c:if test="${fn:contains(requestScope.selected_column_names, col.name)}">
                                <input type="checkbox" name="column_names[]" value="${col.name}" checked="checked" />
                            </c:if>
                            <c:if test="${!fn:contains(requestScope.selected_column_names, col.name)}">
                                <input type="checkbox" name="column_names[]" value="${col.name}" />
                            </c:if>
                            </td>
                            <td>
                                ${col.name}
                                <c:if test="${col.isPrimaryKey()}">
                                    <em>(primary key)</em>
                                </c:if>
                            </td>
                            <td>${col.type}</td>
                        </tr>
                    </c:forEach>
                </tbody>
            </table>
        </div>
    </fieldset>
    <in:block name="form-content-3"></in:block>
</in:override>

<in:override name="javascript">
    <script type="text/javascript">
        $(document).ready(function() {
            $("#selectTables").change(function() {
                $('#xsnoop-form').attr('action', '/xsnoop/pages/index/selectColumns');
                $('#xsnoop-form').submit();
            });

            $('#back_button').click(function() {
                $('#xsnoop-form').attr('action', '/xsnoop/pages/index/selectTable');
                $('#xsnoop-form').submit();
            });

            $('#check_all').click(function() {
		$('.table-striped input[type="checkbox"]').each(function() {
                    $(this).attr('checked', 'checked');
                });
                $(this).addClass('label-info');
                $('#uncheck_all').removeClass('label-info');
            });

            $('#uncheck_all').click(function () {
		$('.table-striped input[type="checkbox"]').each(function() {
                    $(this).removeAttr('checked');
                });
                $(this).addClass('label-info');
                $('#check_all').removeClass('label-info');
            });
        });
    </script>
</in:override>

<%@ include file="selectTable.jsp" %>