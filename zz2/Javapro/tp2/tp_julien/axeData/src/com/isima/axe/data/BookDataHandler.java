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
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.UUID;

import com.isima.axe.model.Book;
import com.isima.axe.model.Library;
import com.isima.axe.model.Person;

/**
 * @author julien
 *
 */
public class BookDataHandler implements CSVserialisable{
	
	
	
	/**
	 * L'instance de la classe
	 */
	private static BookDataHandler bdh;
	
	/**
	 * Permet d'obtenir une instance de la classe
	 * @return l'instance de la classe
	 */
	public static BookDataHandler getInstance()
	{
		if (bdh==null)
			bdh= new BookDataHandler();
		return bdh;
	}
	
	
	public Map load(String file) 
		throws IOException
	{
		Map listBooks = new HashMap();
		
		BufferedReader buf= new BufferedReader(new FileReader(file));
		
		String ligne;
		while ( (ligne=buf.readLine())!=null)
		{
			String val[] = ligne.split(CSV_SEPARTOR);
			if (val.length==3)
			{
				int i=0;
				Book b = new Book();
				b.setId(UUID.fromString(val[i++]));
				b.setTitle(val[i++]);
				b.setAuthor(val[i++]);
				listBooks.put(b.getId().toString(),b);
			}
		}
		
		return listBooks;
	}
	
	/**
	 * Permet de serializer un livre
	 * @param books la liste des livres à serializer
	 * @param file le fichier de sortie
	 * @param append true on ajoute au fichier et false on écrase le fichier
	 * @throws IOException
	 */
	public void serialize(ArrayList books,String file,boolean append) 
		throws IOException
	{	
		BufferedWriter bw = new BufferedWriter(new FileWriter(file,append));
		for (int i= 0;i<books.size();i++)
		{
			if (books.get(i) instanceof Book)
			{
				Book b = (Book) books.get(i);
				bw.append(b.toString());
				bw.newLine();
			}
		}
		bw.close();
	}
	

	private BookDataHandler()
	{
	}
	
}
