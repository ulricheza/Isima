package fr.isima.xsnoop.exception;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class UnsupportedFormatException extends Exception implements ExceptionInterface {

    private String format = null;

    public UnsupportedFormatException() {
        super();
    }

    public UnsupportedFormatException(String format) {
        super();
        this.format = format;
    }

    @Override
    public int getStatusCode() {
        return 400;
    }

    @Override
    public String getMessage() {
        if (format != null && !format.isEmpty()) {
            StringBuilder sb = new StringBuilder("The format '");
            sb.append(format);
            sb.append("' is not supported.");

            return sb.toString();
        }

        return "Format not supported.";
    }
}