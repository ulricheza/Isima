import java.io.*;
import java.net.*;

/**
 * Classe principale du serveur TCP
 * @author Septier-Escourbiac
 * @version 1.0
 */
public class serveurTcp {

    static final int port = 6998;

    public static void main(String[] args) throws Exception {
        Reader reader;
        String line;
        Socket soc;
        int ret;

        PrintStream sortie = null;


        ServerSocket s = new ServerSocket(port);
        System.out.println("La socket est cree");
        while (true) {
            soc = s.accept(); //attente d'un client

            reader = new InputStreamReader(soc.getInputStream());
            BufferedReader keyboard = new BufferedReader(reader);

            line = keyboard.readLine();
            System.out.println("Line: " + line);
            ret = getWeight(line);
            System.out.println(ret);

            sortie = new PrintStream(soc.getOutputStream());
            sortie.println(ret);
        }
    }

    /**
     * Fonction qui calcule le poids de la chaine, c'est à dire la somme des codes
     * ASCII de la chaine
     * @param l chaine a calculer
     * @return weight la valeur du poids de la phrase
     */
    public static int getWeight(String l) {
        int weight = 0;
        for (char c : l.toCharArray()) {
            weight += c;
        }
        return weight;
    }
}
