package fr.isima.xsnoop.exception;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class PageNotFoundException extends Exception implements ExceptionInterface {

   @Override
    public int getStatusCode() {
        return 404;
    }

    @Override
    public String getMessage() {
        return "Not Found";
    }
}