package fr.isima.xsnoop.exception;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public interface ExceptionInterface {

    /**
     * Returns the status code to use in the HTTP response.
     */
    int getStatusCode();
}