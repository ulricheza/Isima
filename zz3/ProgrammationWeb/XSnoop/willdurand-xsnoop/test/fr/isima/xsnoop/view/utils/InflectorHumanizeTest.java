package fr.isima.xsnoop.view.utils;

import java.util.Arrays;
import java.util.Collection;
import static org.junit.Assert.assertEquals;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
@RunWith(Parameterized.class)
public class InflectorHumanizeTest {

    private String value;

    private String expectedValue;

    public InflectorHumanizeTest(String value, String expectedValue) {
        this.value = value;
        this.expectedValue = expectedValue;
    }

    @Test
    public void testHumanize() {
        assertEquals(expectedValue, Inflector.humanize(value));
    }

    @Parameters
    static public Collection<Object[]> generateData() {
        return Arrays.asList(new Object[][] {
            { "foo", "Foo" },
            { "foo bar", "Foo Bar" },
            { "foo_bar", "Foo Bar" },
            { "foo_", "Foo" },
            { "-bar", "Bar" },
            { "BAR", "Bar" },
            { "BaR", "Bar" },
            { "foo-bar", "Foo Bar" }
        });
    }
}