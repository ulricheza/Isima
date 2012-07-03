package com.isima.axe.data;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

import com.isima.axe.model.Book;
import com.isima.axe.model.Library;


/**
 * Cette classe permet de charger les données d'une librairie
 * @author julien
 *
 */
public class LibraryDataHandler implements CSVserialisable{
	
	/**
	 * L'instance de la classe
	 */
	private static LibraryDataHandler ldh;
	
	/**
	 * Permet d'obtenir une instance de la classe
	 * @return l'instance de la classe
	 */
	public static LibraryDataHandler getInstance()
	{
		if (ldh==null)
			ldh= new LibraryDataHandler();
		return ldh;
	}
	
	
	public Map load(String file,Map books) 
		throws IOException
	{
		Map listLibrary = new HashMap();
		
		BufferedReader buf= new BufferedReader(new FileReader(file));
		String ligne;
		while ( (ligne=buf.readLine())!=null)
		{
			String val[] = ligne.split(CSV_SEPARTOR);
			if (val.length>=3)
			{
				int i=0;
				Library lib = new Library();
				lib.setId(UUID.fromString(val[i++]));
				lib.setName(val[i++]);
				lib.setAddress(val[i++]);
				// Récupertaion des ID des livres
				String listId[] = val[i++].split(",");
				for (int j =0;j<listId.length ;j++)
				{
					String id= listId[j];
					Book b = (Book) books.get(id);
					lib.addBook(b);
				}
				listLibrary.put(lib.getId().toString(),lib);
			}
		}
		
		return listLibrary;
	}
	
	/**
	 * Permet de serializer une librairie
	 * @param lib la librairie à ajouter
	 * @param file le fichier de sortie
	 * @param append true on ajoute ou fichier et false on ecrase
	 * @throws IOException
	 */
	public void serialize(ArrayList libs,String file,boolean append) 
		throws IOException
	{	
		BufferedWriter bw = new BufferedWriter(new FileWriter(file,append));
		for (int i= 0;i<libs.size();i++)
		{
			if (libs.get(i) instanceof Library)
			{
				Library lib = (Library) libs.get(i);
				bw.append(lib.toString());
				bw.newLine();
			}
		}
		bw.close();
	}
	
	private LibraryDataHandler()
	{
	}
	

}
