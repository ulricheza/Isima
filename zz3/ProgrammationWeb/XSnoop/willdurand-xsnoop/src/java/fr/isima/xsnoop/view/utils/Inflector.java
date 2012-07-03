package fr.isima.xsnoop.view.utils;

import java.util.StringTokenizer;
import org.apache.commons.lang3.StringUtils;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class Inflector {

    static public String humanize(String string) {
        string = string.replaceAll("_", " ");
        string = string.replaceAll("-", " ");

        String result = "";
        StringTokenizer st = new StringTokenizer(string, " ");

        while(st.hasMoreTokens()){
            result += " ";
            result += capitalize(st.nextToken());
        }

        return result.trim();
    }

    static public String capitalize(String word) {
        word = StringUtils.lowerCase(word);
        return StringUtils.capitalize(word);
    }

    static public String lowercase(String word) {
        return StringUtils.lowerCase(word);
    }
}
