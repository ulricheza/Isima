package fr.isima.xsnoop.controller.impl;

import fr.isima.xsnoop.controller.AbstractController;
import fr.isima.xsnoop.controller.ControllerInterface;
import fr.isima.xsnoop.exception.PageNotFoundException;
import fr.isima.xsnoop.request.HttpServletRequest;
import fr.isima.xsnoop.user.User;
import java.text.MessageFormat;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import org.apache.commons.lang3.StringUtils;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class AdminController extends AbstractController implements ControllerInterface {

    @Override
    public void indexAction(HttpServletRequest request, HttpServletResponse response) throws Exception {
        throw new PageNotFoundException();
    }

    /**
     * @param request   The request.
     * @param response  The response.
     * @throws Exception
     */
    public void loginAction(HttpServletRequest request, HttpServletResponse response)
    throws Exception {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        HttpSession session = request.getSession(true);

        if (StringUtils.isBlank(username)) {
            request.addError("The username cannot be left blank.");
        } else if (StringUtils.isBlank(password)) {
            request.addError("The password cannot be left blank.");
        } else {
            session.setAttribute("user", new User(username, password));

            request.addInfo(MessageFormat.format("Welcome home Mister <strong>{0}</strong> !", username));
        }

        redirectTo("/xsnoop/pages/index/index");
    }

    /**
     *
     * @param request
     * @param response
     * @throws Exception
     */
    public void logoutAction(HttpServletRequest request, HttpServletResponse response)
    throws Exception {
        HttpSession session = request.getSession(false);

        if (session != null) {
            session.removeAttribute("user");

            request.addInfo("Disconnected, bye!");
        }

        redirectTo("/xsnoop/pages/index/index");
    }
}