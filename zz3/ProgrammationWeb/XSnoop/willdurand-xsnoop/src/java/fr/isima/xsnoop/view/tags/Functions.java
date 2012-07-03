package fr.isima.xsnoop.view.tags;

import fr.isima.xsnoop.view.utils.Inflector;
import java.util.List;

/**
 * A set of EL functions.
 *
 * @author William Durand <william.durand1@gmail.com>
 */
public class Functions {
   static public boolean contains(List list, Object o) {
      return list.contains(o);
   }

   static public Object humanize(Object o) {
       return Inflector.humanize((String) o);
   }

   static public Object lowercase(Object o) {
       return Inflector.lowercase((String) o);
   }
}
