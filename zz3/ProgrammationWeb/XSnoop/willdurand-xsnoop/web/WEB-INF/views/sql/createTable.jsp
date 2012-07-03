<%@taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<in:override name="content">
    <form action="/xsnoop/pages/sql/addColumns" method="post" class="form">
        <fieldset>
            <legend>Add a new table</legend>
            <div class="control-group">
                <div class="controls">
                    <label for="table_name">&nbsp;</label>
                    <input class="xlarge" name="table_name" size="30" type="text" value="${requestScope.table_name}" />
                    <p class="help-block"><strong>Help:</strong> This is the first step to create your table. Please avoid special characters ;-)</p>
                </div>
            </div>
        </fieldset>

        <c:if test="${!empty requestScope.table_name}">
            <fieldset>
                <legend>Add few columns to this table</legend>
                <div class="control-group">
                    <label for="columns">
                        <table class="table table-striped">
                            <thead>
                                <tr>
                                    <th>Name</th>
                                    <th>Type</th>
                                    <th>Primary Key</th>
                                    <th></th>
                                </tr>
                            </thead>
                            <tbody id="cols">
                                <c:if test="${requestScope.columns_name}">
                                    <c:forEach items="${requestScope.columns_name}" var="colName">
                                    </c:forEach>
                                </c:if>
                            </tbody>
                        </table>
                    </label>
                </div>
            </fieldset>
        </c:if>

        <div class="form-actions">
            <input type="hidden" value="${requestScope.database_name}" name="database_name" />
            <c:if test="${!empty requestScope.table_name}">
                <a class="btn" id="add_button">
                    <i class="icon-plus-sign"></i>
                    New column
                </a>
            </c:if>
            <button type="submit" class="btn btn-primary">Submit &rarr;</button>
        </div>
    </form>
    <script type="text/javascript">
        $(document).ready(function() {
            var numCol = 1;

            $("#new_column").tmpl([ { numCol: "0" } ]).appendTo("#cols");
            $('#add_button').click(function() {
                $("#new_column").tmpl([{"numCol": numCol++}]).insertAfter("#cols tr:last");
            });
            $('#cols a.remove').live("click", function() {
                $(this).parents('tr:first').empty();
            });
        });
    </script>
    <script id="new_column" type="text/x-jquery-tmpl">
        <tr>
            <td>
                <input type="text" name="columns_name[]" />
            </td>
            <td>
                <select name="columns_type[]">
                    <option value="CHAR">CHAR</option>
                    <option value="DECIMAL">DECIMAL</option>
                    <option value="INTEGER">INTEGER</option>
                    <option value="TEXT">TEXT</option>
                    <option value="TIMESTAMP">TIMESTAMP</option>
                    <option value="VARCHAR(255)">VARCHAR</option>
                </select>
            </td>
            <td>
                <input type="checkbox" name="columns_pk[]" value="\${numCol}" />
            </td>
            <td>
                <a class="remove"><i class="icon-minus-sign"></i> remove</a>
            </td>
        </tr>
    </script>
</in:override>

<%@ include file="../layout.jsp" %>