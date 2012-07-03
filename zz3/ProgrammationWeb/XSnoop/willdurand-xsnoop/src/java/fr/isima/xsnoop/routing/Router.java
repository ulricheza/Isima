package fr.isima.xsnoop.routing;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class Router {

    /**
     * Defaults
     */
    final static public String DEFAULT_CONTROLLER   = "index";
    final static public String DEFAULT_ACTION       = "index";

    /**
     * Route Patterns
     */
    final static private String ROUTE_PATTERN_FORMAT            = "^/([a-zA-Z0-9\\/]+)\\.([a-z]+)";
    final static private String ROUTE_PATTERN_CONTROLLER_ACTION = "^/([a-z]+)/([a-zA-Z0-9]+)";
    final static private String ROUTE_PATTERN_CONTROLLER_ONLY   = "^/([a-z]+)";

    private String shortController;

    private String shortAction;

    private String format;

    public void parsePathInfo(String pathInfo) {
        // reset attributes, just in case..
        shortController = null;
        shortAction = null;
        format = null;

        if (pathInfo.equals("/") || pathInfo.length() == 0) {
            shortController = DEFAULT_CONTROLLER;
            shortAction = DEFAULT_ACTION;
        } else {
            Pattern p = Pattern.compile(ROUTE_PATTERN_FORMAT);
            Matcher m = p.matcher(pathInfo);

            // Format present?
            if (m.find()) {
                format = m.group(2).trim();
                // remove the format
                pathInfo = pathInfo.split(format)[0];
            }

            p = Pattern.compile(ROUTE_PATTERN_CONTROLLER_ACTION);
            m = p.matcher(pathInfo);

            if (m.find()) {
                shortController = m.group(1).trim();
                shortAction = m.group(2).trim();
            } else {
                p = Pattern.compile(ROUTE_PATTERN_CONTROLLER_ONLY);
                m = p.matcher(pathInfo);

                if (m.find()) {
                    shortController = m.group(1).trim();
                    shortAction = DEFAULT_ACTION;
                }
            }
        }
    }

    public String getController() {
        return shortController;
    }

    public String getAction() {
        return shortAction;
    }

    public String getFormat() {
        return format;
    }
}
