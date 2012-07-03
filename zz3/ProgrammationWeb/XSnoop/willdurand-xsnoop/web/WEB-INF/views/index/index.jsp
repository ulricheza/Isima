<%@taglib uri="/WEB-INF/tlds/inheritance" prefix="in" %>

<in:override name="content">
    <div class="row">
        <div class="span12">
            <form id="xsnoop-form" action="<in:block name="form-action">/xsnoop/pages/index/selectTable</in:block>" method="post">
                <fieldset>
                    <legend>Select a database name</legend>
                    <div class="control-group">
                         <label class="control-label" for="database_name">&nbsp;</label>
                        <div class="controls">
                            <input class="input-xlarge" name="database_name" size="30" type="text" value="${requestScope.selected_database_name}" />
                            <p class="help-block"><strong>Help:</strong> Using MySQL, you should enter something like: <code>jdbc:mysql://127.0.0.1:3306/database-name</code></p>
                        </div>
                    </div>
                </fieldset>

                <in:block name="form-content"></in:block>

                <div class="form-actions">
                    <in:block name="form-actions"></in:block>

                    <button type="submit" class="btn btn-primary">
                        <in:block name="submit_button_name">Submit &rarr;</in:block>
                    </button>
                </div>
            </form>
        </div>
    </div>
    <div class="row">
        <div class="span12">
            <in:block name="content-2"></in:block>
        </div>
    </div>
</in:override>

<%@ include file="../layout.jsp" %>