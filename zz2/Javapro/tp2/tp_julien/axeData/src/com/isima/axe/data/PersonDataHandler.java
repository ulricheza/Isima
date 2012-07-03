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
import java.util.Map;
import java.util.UUID;

import com.isima.axe.model.Book;
import com.isima.axe.model.Library;
import com.isima.axe.model.Person;

/**
 * @author julien
 *
 */
public class PersonDataHandler implements CSVserialisable {
	
	
	/**
	 * L'instance de la classe
	 */
	private static PersonDataHandler ldh;
	
	/**
	 * Permet d'obtenir une instance de la classe
	 * @return l'instance de la classe
	 */
	public static PersonDataHandler getInstance()
	{
		if (ldh==null)
			ldh= new PersonDataHandler();
		return ldh;
	}
	
	private PersonDataHandler()
	{	
	}
	
	
	public Map load(String file,Map librarys) 
		throws IOException
	{
		Map listPerson = new HashMap();
		
		BufferedReader buf= new BufferedReader(new FileReader(file));
		String ligne;
		while ( (ligne=buf.readLine())!=null)
		{
			String val[] = ligne.split(CSV_SEPARTOR);
			if (val.length==4)
			{
				int i=0;
				Person per = new Person();
				per.setId(UUID.fromString(val[i++]));
				per.setFirstName(val[i++]);
				per.setLastName(val[i++]);
				per.subscribes((Library)librarys.get(val[i++]));
				listPerson.put(per.getId().toString(),per);
			}
		}
		
		return listPerson;
	}
	
	/**
	 * Permet de serializer une liste de personne
	 * @param persons les personnes à ajouter
	 * @param file le fichier de sortie
	 * @param append true on ajoute ou fichier et false on ecrase
	 * @throws IOException
	 */
	public void serialize(ArrayList persons,String file,boolean append) 
		throws IOException
	{	
		BufferedWriter bw = new BufferedWriter(new FileWriter(file,append));
		for (int i= 0;i<persons.size();i++)
		{
			if (persons.get(i) instanceof Person)
			{
				Person pers = (Person) persons.get(i);
				bw.append(pers.toString());
				bw.newLine();
			}
		}
		bw.close();
	}

}
