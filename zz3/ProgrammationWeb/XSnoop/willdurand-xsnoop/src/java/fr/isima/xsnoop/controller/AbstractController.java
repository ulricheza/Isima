package fr.isima.xsnoop.controller;

import java.util.logging.Logger;
import javax.servlet.http.HttpServlet;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public abstract class AbstractController extends HttpServlet implements ControllerInterface {

    /**
     * Logger
     */
    final static protected Logger LOGGER = Logger.getLogger(AbstractController.class.getName());

    /**
     * View template name to use instead the default one
     */
    private String view = null;

    /**
     * Where to redirect
     */
    private String redirectLocation = null;

    /**
     * Should we redirect?
     */
    private boolean hasToRedirect = false;

    /**
     * @param String view   A view template name
     */
    public void setView(String view) {
        this.view = view;
    }

    @Override
    public String getView() {
        return view;
    }

    @Override
    public String getRedirectLocation() {
        return redirectLocation;
    }

    @Override
    public boolean hasToRedirect() {
        return hasToRedirect;
    }

    public void redirectTo(String redirect) {
        redirectLocation = redirect;
        hasToRedirect = true;
    }
}