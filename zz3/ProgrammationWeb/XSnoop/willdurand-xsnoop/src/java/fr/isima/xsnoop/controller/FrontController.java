package fr.isima.xsnoop.controller;

import fr.isima.xsnoop.exception.ExceptionInterface;
import fr.isima.xsnoop.routing.Router;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.lang3.StringUtils;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class FrontController extends HttpServlet {

    /**
     * Where to find controller classes.
     */
    final static private String CONTROLLERS_PACKAGE = "fr.isima.xsnoop.controller.impl";

    /**
     * Base path for all JSPs.
     */
    final static protected String JSP_PATH = "/WEB-INF/views";

    /**
     * Logger
     */
    final static private Logger LOGGER = Logger.getLogger(FrontController.class.getName());

    /**
     * The Router object
     */
    private Router router = new Router();

    @Override
    public  void doGet(HttpServletRequest request, HttpServletResponse  response)
        throws IOException, ServletException {
        doProcessRequest(request, response);
    }

    @Override
    public  void doPost(HttpServletRequest request, HttpServletResponse  response)
        throws IOException, ServletException {
        doProcessRequest(request, response);
    }

    protected void doProcessRequest(HttpServletRequest request, HttpServletResponse response)
        throws IOException, ServletException {
        dispatch(new fr.isima.xsnoop.request.HttpServletRequest(request), response);
    }

    /**
     * Returns a Class which represents a controller identified by its short name.
     *
     * @param String controllerName A short controller name.
     * @return Class
     */
    protected Class getControllerClass(String controllerName) {
        Class cl = null;
        StringBuilder clazz = new StringBuilder();

        clazz.append(CONTROLLERS_PACKAGE);
        clazz.append(".");
        clazz.append(StringUtils.capitalize(controllerName));
        clazz.append("Controller");

        try {
            cl = Class.forName(clazz.toString());
        } catch (Exception ex) {
            LOGGER.log(Level.WARNING, "Exception catched: {0}", ex);
            cl = null;
        }

        return cl;
    }

    /**
     * Returns an instance of a controller
     *
     * @param String controllerName
     * @return ControllerInterface
     */
    protected ControllerInterface getController(String controllerName) {
        ControllerInterface ctrl = null;
        Class cl = getControllerClass(controllerName);

        if (cl != null) {
            try {
                ctrl = (ControllerInterface) cl.newInstance();
            } catch (Exception ex) {
                LOGGER.log(Level.WARNING, "Exception catched: {0}", ex.getMessage());
                ctrl = null;
            }
        }

        return ctrl;
    }

    /**
     * Returns the view's path for the current controller.
     *
     * @param String controller A controller name.
     * @param String action An action name.
     * @return String
     */
    protected String getView(String controller, String action, String format)
    {
        StringBuilder sb = new StringBuilder();
        sb.append(JSP_PATH);
        sb.append("/");

        if (action.split("/").length == 2) {
            String [] s = action.split("/");
            sb.append(s[0]);
            sb.append("/");
            sb.append(s[1]);
        } else {
            sb.append(controller);
            sb.append("/");
            sb.append(action);
        }

        if (!format.equals(fr.isima.xsnoop.request.HttpServletRequest.DEFAULT_FORMAT)) {
            sb.append(".");
            sb.append(format);
        }

        sb.append(".jsp");

        LOGGER.log(Level.INFO, "View: {0}", sb.toString());

        return sb.toString();
    }

    /**
     * Here is the magic to dispatch an incoming request.
     * First we try to find a controller short name, and an action short name.
     * Then, we try to load them... Fallback is "index".
     *
     * @param HttpServletRequest request The request.
     * @param HttpServletResponse response The response.
     * @throws IOException
     * @throws ServletException
     */
    private void dispatch(fr.isima.xsnoop.request.HttpServletRequest request, HttpServletResponse response)
        throws IOException, ServletException {

        String pathInfo = request.getPathInfo();
        LOGGER.log(Level.INFO, "PathInfo: {0}", pathInfo);

        // Parse the URL to retrieve controller/action names
        router.parsePathInfo(pathInfo);

        String shortController = router.getController();
        String shortAction     = router.getAction();
        String format          = fr.isima.xsnoop.request.HttpServletRequest.DEFAULT_FORMAT;

        // Handle format
        if (StringUtils.isNotBlank(router.getFormat())) {
            format = router.getFormat();
        }
        request.setFormat(format);

        LOGGER.log(Level.INFO, "Controller: {0}", shortController);
        LOGGER.log(Level.INFO, "Action: {0}", shortAction);
        LOGGER.log(Level.INFO, "Format: {0}", format);

        // Get the controller object
        ControllerInterface controller = getController(shortController);

        if (controller == null) {
            raiseErrorControllerNotFound(request, response, shortController);
        } else {

            try {
                // Let's do the work
                getControllerClass(shortController)
                    .getMethod(
                        shortAction + "Action",
                        new Class[] {
                            fr.isima.xsnoop.request.HttpServletRequest.class,
                            HttpServletResponse.class
                        }
                    )
                    .invoke(controller, new Object[] { request, response });
            } catch (InvocationTargetException ex) {
                LOGGER.log(Level.WARNING, "Exception catched: {0}", ex);

                if (ex.getCause() instanceof ExceptionInterface) {
                    response.setStatus(((ExceptionInterface)ex.getCause()).getStatusCode());
                    request.setAttribute("error", ex.getCause().getMessage());

                    getServletContext().getRequestDispatcher(JSP_PATH + "/error.jsp").forward(request.getRequest(), response);
                    return;
                } else {
                    raiseErrorActionNotFound(request, response, shortController, shortAction);
                    return;
               }
            } catch (Exception ex1) {
                LOGGER.log(Level.WARNING, "Exception catched: {0}", ex1);
                request.setAttribute("error", "Exception catched: " + ex1.toString());

                getServletContext().getRequestDispatcher(JSP_PATH + "/error.jsp").forward(request.getRequest(), response);
                return;
            }

            // Redirection?
            if (controller.hasToRedirect()) {
                response.sendRedirect(controller.getRedirectLocation());
            } else {
                // Determine which view to use
                String view;
                if (controller.getView() != null) {
                    view = getView(shortController, controller.getView(), format);
                } else {
                    view = getView(shortController, shortAction, format);
                }

                getServletContext().getRequestDispatcher(view).forward(request.getRequest(), response);
            }
        }
    }

    private void raiseErrorControllerNotFound(fr.isima.xsnoop.request.HttpServletRequest request, HttpServletResponse response, String controllerName)
    throws IOException, ServletException {
        StringBuilder sb = new StringBuilder();
        sb.append("Controller \"");
        sb.append(controllerName);
        sb.append("Controller\" not found.");

        request.setAttribute("error", sb.toString());
        request.setAttribute("exception", "");

        getServletContext().getRequestDispatcher(JSP_PATH + "/error.jsp").forward(request.getRequest(), response);
    }

    private void raiseErrorActionNotFound(fr.isima.xsnoop.request.HttpServletRequest request, HttpServletResponse response, String controllerName, String actionName)
    throws IOException, ServletException {
        StringBuilder sb = new StringBuilder();
        sb.append("Action \"");
        sb.append(actionName);
        sb.append("Action\"");
        sb.append(" not found in controller \"");
        sb.append(controllerName);
        sb.append("Controller\"");
        sb.append(".");

        request.setAttribute("error", sb.toString());

        getServletContext().getRequestDispatcher(JSP_PATH + "/error.jsp").forward(request.getRequest(), response);
    }
}