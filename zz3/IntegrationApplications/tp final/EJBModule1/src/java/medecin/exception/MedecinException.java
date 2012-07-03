/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package medecin.exception;

import javax.ejb.ApplicationException;
/**
 *
 * @author JC
 */
public class MedecinException extends RuntimeException
{
    private int code = 0;
    
    public int getCode()
    {
        return code;
    }
    
    public void setCode(int code)
    {
        this.code = code;
    }
    
    public MedecinException()
    {
        super();
    }
    
    public MedecinException(String message)
    {
        super(message);
    }
    
    public MedecinException(String message, Throwable cause)
    {
        super(message,cause);
    }
    
    public MedecinException(Throwable cause)
    {
        super(cause);
    }
    
    public MedecinException(String message, int code)
    {
        super(message);
        setCode(code);
    }
    
    public MedecinException(Throwable cause, int code)
    {    
        super(cause);
        setCode(code);
    }
    
    public MedecinException(String message, Throwable cause, int code)
    {
        super(message, cause);
        setCode(code);
    }
    

}
