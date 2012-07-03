package fr.isima.xsnoop.view.tags;

/**
 * @author badqiu
 * @see http://rapid-framework.googlecode.com/svn/trunk/rapid-framework/src/rapid_framework_common/cn/org/rapid_framework/web/tags/Utils.java
 */
class Utils {

    public static String BLOCK = "__jsp_override__";

    static String getOverrideVariableName(String name) {
        return BLOCK + name;
    }
}