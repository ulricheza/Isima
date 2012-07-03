package fr.isima.xsnoop.routing;

import java.util.Arrays;
import java.util.Collection;
import static org.junit.Assert.assertEquals;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
@RunWith(Parameterized.class)
public class RouterTest {

    String pathInfo;

    String expectedController;

    String expectedAction;

    String expectedFormat;

    public RouterTest(String pathInfo, String expectedController, String expectedAction, String expectedFormat) {
        this.pathInfo = pathInfo;
        this.expectedController = expectedController;
        this.expectedAction = expectedAction;
        this.expectedFormat = expectedFormat;
    }

    @Test
    public void testParsePathInfo() {
        Router r = new Router();
        r.parsePathInfo(pathInfo);

        assertEquals(expectedController, r.getController());
        assertEquals(expectedAction, r.getAction());
        assertEquals(expectedFormat, r.getFormat());
    }

    @Parameterized.Parameters
    static public Collection<Object[]> generateData() {
        return Arrays.asList(new Object[][] {
            { "/index/index", "index", "index", null },
            { "/index", "index", Router.DEFAULT_ACTION, null },
            { "/", Router.DEFAULT_CONTROLLER, Router.DEFAULT_ACTION, null },
            { "/index/index.json", "index", "index", "json" },
            { "/bar/FOO.html", "bar", "FOO", "html" },
            { "/bar/Foo.html", "bar", "Foo", "html" }
        });
    }
}