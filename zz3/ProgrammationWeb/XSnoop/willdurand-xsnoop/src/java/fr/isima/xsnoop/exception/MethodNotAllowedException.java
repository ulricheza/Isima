package fr.isima.xsnoop.exception;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class MethodNotAllowedException extends Exception implements ExceptionInterface {

    @Override
    public int getStatusCode() {
        return 405;
    }

    @Override
    public String getMessage() {
        return "Method Not Allowed";
    }
}
