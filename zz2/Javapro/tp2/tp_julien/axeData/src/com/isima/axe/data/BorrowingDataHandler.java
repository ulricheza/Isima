/**
 * 
 */
package com.isima.axe.data;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

import com.isima.axe.model.Book;
import com.isima.axe.model.Borrowing;
import com.isima.axe.model.Library;
import com.isima.axe.model.Person;

/**
 * Permet de serializer et deserializer la classe borrowing
 * @author julien
 *
 */
public class BorrowingDataHandler implements CSVserialisable {
	
	
	/**
	 * L'instance de la classe
	 */
	private static BorrowingDataHandler ldh;
	
	/**
	 * Permet d'obtenir une instance de la classe
	 * @return l'instance de la classe
	 */
	public static BorrowingDataHandler getInstance()
	{
		if (ldh==null)
			ldh= new BorrowingDataHandler();
		return ldh;
	}
	
	private BorrowingDataHandler()
	{	
	}
	
	
	public Map load(String file,Map books,Map persons) 
		throws IOException
	{
		Map listBorro = new HashMap();
		
		BufferedReader buf= new BufferedReader(new FileReader(file));
		String ligne;
		while ( (ligne=buf.readLine())!=null)
		{
			String val[] = ligne.split(CSV_SEPARTOR);
			if (val.length==5)
			{
				int i=0;
				Borrowing borr = new Borrowing();
				borr.setBorrowingDate(new Date(Long.parseLong(val[i++])));
				borr.setExpectedReturnDate(new Date(Long.parseLong(val[i++])));
				//récupartion de la date de retour actuel
				if (val[i].equals(""))
				{
					borr.setActualReturnDate(null);
					i++;
				}
				else
				{
					borr.setActualReturnDate(new Date(Long.parseLong(val[i++])));
				}
				// recupertion du livre
				Book b =(Book)books.get(val[i++]);
				if (b!=null)
				{
					borr.setBorrowing(b);
					b.getBorrowers().add(borr);
				}
				// recupartion de la personne
				Person p = (Person)persons.get(val[i++]);
				if (p!=null)
				{
					borr.setBorrower(p);
					p.getBorrowings().add(borr);
				}
				listBorro.put(""+borr.hashCode(), borr);
			}
		}
		
		return listBorro;
	}
	
	/**
	 * Permet de serializer la classe borrowing
	 * @param borrowings les borrowings à ajouter
	 * @param file le fichier de sortie
	 * @param append true on ajoute ou fichier et false on ecrase
	 * @throws IOException
	 */
	public void serialize(ArrayList borrowings,String file,boolean append) 
		throws IOException
	{	
		BufferedWriter bw = new BufferedWriter(new FileWriter(file,append));
		for (int i= 0;i<borrowings.size();i++)
		{
			if (borrowings.get(i) instanceof Borrowing)
			{
				Borrowing Borr = (Borrowing) borrowings.get(i);
				bw.append(Borr.toString());
				bw.newLine();
			}
		}
		bw.close();
	}
	

}
