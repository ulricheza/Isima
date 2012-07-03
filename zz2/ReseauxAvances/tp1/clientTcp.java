
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.Reader;
import java.net.Socket;


public class clientTcp {

    static final int portJava = 6998;
    static final int portC = 61569;

    /**
     * Methode effectuant le corps de metier du serveur Java
     * @param adresse adresse du serveur Java
     * @throws Exception
     */
    public static void serveurJava(String adresse) throws Exception {
        PrintStream sortie = null;
        String line;

        Socket socket = new Socket(adresse, portJava);

        // Ecriture de la phrase
        Reader reader = new InputStreamReader(System.in);
        BufferedReader keyboard = new BufferedReader(reader);
        sortie = new PrintStream(socket.getOutputStream());

        System.out.println("Entrer une ligne de texte: ");
        line = keyboard.readLine();
        sortie.println(line);

        // Lecture de la r?ponse
        reader = new InputStreamReader(socket.getInputStream());
        keyboard = new BufferedReader(reader);

        line = keyboard.readLine();
        System.out.println("Taille de la phrase: " + line);

        socket.close();
    }

    /**
     * demande et verifie un nombre donne par l'utilisateur
     * @return le string correspondant a la saisie de l'utilisateur
     * @throws IOException
     */
    public static String demandeNombre() throws IOException {
        Boolean termin = false;
        // Lecture de la r?ponse
        Reader reader = new InputStreamReader(System.in);
        BufferedReader keyboard = new BufferedReader(reader);
        String line;

        do {
            System.out.println("Entrer votre nombre ( entre -99 999 et 99 999 ) "
                    + "ou end pour terminer la session ");
            line = keyboard.readLine();

            if (line.equals("end")) {
                termin = true;
            } else {
                try {
                    Integer.parseInt(line.toString());
                    termin = true;
                } catch (NumberFormatException e) {
                    System.out.println("Attention, ce n'est pas un nombre");
                }
            }
        } while (termin == false);
        return line;
    }

    /**
     * corps de metier du serveur C
     * @param adresse adresse du serveur C
     * @throws Exception
     */
    public static void serveurC(String adresse) throws Exception {
        PrintStream sortie = null;
        String line;
        Socket socket = new Socket(adresse, portC);
        Reader reader = new InputStreamReader(socket.getInputStream());
        BufferedReader keyboard = new BufferedReader(reader);

        // Ecriture de la phrase
        sortie = new PrintStream(socket.getOutputStream());

        Boolean termin = false;

        do {
            line = demandeNombre();
            StringBuffer l = new StringBuffer(line);
            l.append('\0');
            sortie.print(l);
            if (line.equals("end")) {
                termin = true;
                line = keyboard.readLine();
            }
        } while (termin == false);

        System.out.println("Moyenne: " + line);
        socket.close();
    }


    public static void main(String[] args) throws Exception {

        if (args.length != 1) {
            System.out.println("Attention, pas d'argument");
            System.exit(0);
        }
        String adresse = args[0];

        System.out.println("Menu :");
        System.out.println("____________________________");
        System.out.println("1     : Serveur C ");
        System.out.println("2     : Serveur Java ");
        System.out.println("Autre : Quitter ");

        Reader reader = new InputStreamReader(System.in);
        BufferedReader keyboard = new BufferedReader(reader);

        try {
            int val = Integer.parseInt(keyboard.readLine());
            switch (val) {
                case 1:
                    serveurC(adresse);
                    break;
                case 2:
                    serveurJava(adresse);
                    break;
                default:
                    break;
            }
        } catch (NumberFormatException e) {
            System.out.println("Attention, ce n'est pas un choix ");
        }
    }
}
