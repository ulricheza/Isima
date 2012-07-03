<%@taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<c:if test="${!empty requestScope.query}">

    <in:override name="form-action">/xsnoop/pages/sql/execute</in:override>

    <in:override name="submit_button_name">
        <i class="icon-play icon-white"></i>
        Execute
    </in:override>

    <in:override name="form-actions">
        <button class="btn" id="back_button">
        &larr; Previous step
        </button>
        <button id="preview-button" class="btn btn-info" data-toggle="modal" href="#modal-from-dom">
            <i class="icon-search icon-white"></i>
            Preview
        </button>
    </in:override>

    <in:override name="content-2">
        <div id="modal-from-dom" class="modal hide fade">
            <div class="modal-header">
                <a class="close" data-dismiss="modal">&times;</a>
                <h3>Preview</h3>
            </div>
            <div class="modal-body">
                <p><code id="executed_query"></code></p>
                <table id="results" class="table table-striped table-condensed">
                    <thead>
                    <tbody>
                    </tbody>
                </table>
            </div>
            <div class="modal-footer">
                <a id="doExecute" class="btn btn-danger">Execute</a>
            </div>
        </div>
    </in:override>

    <in:override name="form-content-3">
        <fieldset>
            <legend>Generated Query</legend>
            <div class="well">
                <code>${requestScope.query}</code>
            </div>
        </fieldset>
    </in:override>

    <in:override name="javascript">
        <script type="text/javascript">
            $(document).ready(function() {
                $("#selectTables").change(function() {
                    $('#xsnoop-form').attr('action', '/xsnoop/pages/index/selectColumns');
                    $('#xsnoop-form').submit();
                });

                $('#back_button').click(function() {
                    $('#xsnoop-form').attr('action', '/xsnoop/pages/index/selectColumns');
                    $('#xsnoop-form').submit();
                });

                $('#preview-button').click(function() {
                    $.post(
                        '/xsnoop/pages/sql/preview.json',
                        $('#xsnoop-form').serialize(),
                        function (data) {
                            $('#results thead').empty();
                            $('#results tbody').empty();
                            $('#executed_query').empty();

                            var json = $.parseJSON(data);

                            if (json.error !== undefined) {
                                $('#executed_query').append(json.error);

                                return;
                            }

                            $('#executed_query').append(json.query);

                            var cols = "<tr>";
                            $.each(json.columns, function (index, value) {
                                cols += "<th>" + value + "</th>";
                            });

                            $('#results thead').append(cols + "</tr>");

                            $.each(json.results, function(key, items) {
                                var row = '<tr>';
                                $.each(items, function (k, v) {
                                    row += '<td>' + v + '</td>';
                                });
                                row += '</tr>';

                                $('#results tbody').append(row);
                            });
                        }
                    );
                });

                $('#doExecute').click(function() {
                    $('#xsnoop-form').attr('action', '/xsnoop/pages/sql/execute');
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
</c:if>

<%@ include file="../index/selectColumns.jsp" %>
