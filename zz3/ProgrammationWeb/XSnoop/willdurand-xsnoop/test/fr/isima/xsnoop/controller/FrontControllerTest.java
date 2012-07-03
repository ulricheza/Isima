package fr.isima.xsnoop.controller;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import org.junit.Before;
import org.junit.Test;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class FrontControllerTest {

    private TestableFrontController controller;

    @Before
    public void setUp() {
        controller = new TestableFrontController();
    }

    @Test
    public void testGetView() {
        String expected = "/WEB-INF/views/foo/bar.format.jsp";

        assertEquals(expected, controller.getView("foo", "bar", "format"));
    }

    @Test
    public void testGetViewWithDefaultFormat() {
        String expected = "/WEB-INF/views/foo/bar.jsp";

        assertEquals(expected, controller.getView("foo", "bar", fr.isima.xsnoop.request.HttpServletRequest.DEFAULT_FORMAT));
    }

    @Test
    public void testGetControllerReturnsNullIfNotFound() {
        assertNull(controller.getController("my.Controller"));
    }
}

class TestableFrontController extends FrontController {

    @Override
    public String getView(String controller, String action, String format) {
        return super.getView(controller, action, format);
    }

    @Override
    public ControllerInterface getController(String controllerName) {
        return super.getController(controllerName);
    }
}
