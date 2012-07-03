import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;


public class ClavierReader {
	
	private String Lire()
	{
		//version 1 standard
		//Attention aux exeptions souleve
		String lecture = null;
		try {
			InputStreamReader isr = new InputStreamReader(System.in);
			BufferedReader br = new BufferedReader(isr);
		    System.out.println("ECRIS");
			lecture = br.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return lecture;
	}
	public void LireEtAfficher()
	{
		//version 1 standard
		//Attention aux exeptions souleve
		try {
			String lecture;
			InputStreamReader isr = new InputStreamReader(System.in);
			BufferedReader br = new BufferedReader(isr);
		    System.out.println("ECRIS");
			lecture = br.readLine();
			System.out.println(lecture);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void LireEtEcrireFichier()
	{
		
		String lect = Lire();
		
		try {
			File fic = new File("log.txt");
			FileOutputStream fos = new FileOutputStream(fic);
			PrintStream ps = new PrintStream(fos);
			ps.println(lect);
			ps.close();
			try {
				fos.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
	    }	
	}
}
