package fr.isima.xsnoop.view.tags;

import javax.servlet.jsp.JspException;
import javax.servlet.jsp.tagext.BodyContent;
import javax.servlet.jsp.tagext.BodyTagSupport;

/**
 * @author badqiu
 * @see http://rapid-framework.googlecode.com/svn/trunk/rapid-framework/src/rapid_framework_common/cn/org/rapid_framework/web/tags/OverrideTag.java
 */
public class OverrideTag extends BodyTagSupport {

    private String name;

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public int doStartTag() throws JspException {
        return isOverrided() ? SKIP_BODY : EVAL_BODY_BUFFERED;
    }

    @Override
    public int doEndTag() throws JspException {
        if (isOverrided()) {
            return EVAL_PAGE;
        }
        
        BodyContent b = getBodyContent();
        String varName = Utils.getOverrideVariableName(name);

        pageContext.getRequest().setAttribute(varName, b.getString());

        return EVAL_PAGE;
    }

    private boolean isOverrided() {
        String varName = Utils.getOverrideVariableName(name);
    
        return pageContext.getRequest().getAttribute(varName) != null;
    }
}