package fr.isima.xsnoop;

import fr.isima.xsnoop.controller.FrontControllerTest;
import fr.isima.xsnoop.routing.RouterTest;
import fr.isima.xsnoop.serializer.JsonSerializerTest;
import fr.isima.xsnoop.service.QueryBuilderTest;
import fr.isima.xsnoop.view.utils.InflectorCapitalizeTest;
import fr.isima.xsnoop.view.utils.InflectorHumanizeTest;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
@RunWith(Suite.class)
@Suite.SuiteClasses({
    FrontControllerTest.class,
    RouterTest.class,
    JsonSerializerTest.class,
    QueryBuilderTest.class,
    InflectorCapitalizeTest.class,
    InflectorHumanizeTest.class
})
public class XSnoopTestSuite {
}
