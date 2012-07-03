package fr.isima.xsnoop.exception;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class UnauthorizedException extends Exception implements ExceptionInterface {

   @Override
    public int getStatusCode() {
        return 401;
    }

    @Override
    public String getMessage() {
        return "Unauthorized";
    }
}