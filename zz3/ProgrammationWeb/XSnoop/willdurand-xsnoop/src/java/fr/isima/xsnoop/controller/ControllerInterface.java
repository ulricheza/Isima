package fr.isima.xsnoop.controller;

import fr.isima.xsnoop.request.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public interface ControllerInterface {

    /**
     * The main action a controller must implement.
     *
     * @param request   A request.
     * @param response  A response.
     * @throws Exception
     */
    void indexAction(HttpServletRequest request, HttpServletResponse response) throws Exception;

    /**
     * Returns the view to use in the response.
     *
     * @return String
     */
    String getView();

    /**
     * Returns true if the controller has to redirect to a new location, false otherwise.
     *
     * @return boolean
     */
    boolean hasToRedirect();

    /**
     * Returns the redirect location if defined, or null.
     *
     * @return String
     */
    String getRedirectLocation();
}
