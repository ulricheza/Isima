/*
 * SnooperModifApp.java
 */

package snoopermodif;

import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdesktop.application.Application;
import org.jdesktop.application.SingleFrameApplication;

/**
 * The main class of the application.
 */
public class SnooperModifApp extends SingleFrameApplication {

    /**
     * At startup create and show the main frame of the application.
     */
    @Override protected void startup() {
        try {
            show(new SnooperModifView(this));
        } catch (SQLException ex) {
            Logger.getLogger(SnooperModifApp.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     * This method is to initialize the specified window by injecting resources.
     * Windows shown in our application come fully initialized from the GUI
     * builder, so this additional configuration is not needed.
     */
    @Override protected void configureWindow(java.awt.Window root) {
    }

    /**
     * A convenient static getter for the application instance.
     * @return the instance of SnooperModifApp
     */
    public static SnooperModifApp getApplication() {
        return Application.getInstance(SnooperModifApp.class);
    }

    /**
     * Main method launching the application.
     */
    public static void main(String[] args) {
        launch(SnooperModifApp.class, args);
    }
}
