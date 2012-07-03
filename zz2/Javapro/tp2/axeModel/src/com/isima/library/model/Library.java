/**
 * 
 */
package com.isima.library.model;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

/**
 * @author escourbi
 *
 */
public class Library {
	
	private static int cpt = 0;
	
	private UUID id;
	private String name;
	private String address;
	private ArrayList books;
	

	public Library(String name, String address) {
		this.id = UUID.randomUUID();
		cpt++;
		this.name = name;
		this.address = address;
	}
	
	public void addBook( Book bookAdd )
	{
		//on teste si le bouquin existe deja
		int i = 0;
		Book copie = null;
		while(i < books.size() && ((Library) books.get(i)).getId() != bookAdd.getId())
		{
			++i;
		}
		if(i < books.size())
		{
			copie = (Book) bookAdd.clone();
			books.add(copie);
		}
	}
	
	//On retourne la reference du livre recherche dans la library si livre pas trouve on renvoie null
	public Book hasBook(Book inTest)
	{
		int i = 0;
		Book ret = null;
		while(i < books.size() && ((Library) books.get(i)).getId() != inTest.getId())
		{
			++i;
		}
		if(i < books.size())
		{
			ret = (Book) books.get(i);
		}
		return ret;
	}
	
	public String toString()
	{
		return ("Lybrary: Name: " + name + " Adress : " + address );
	}
	
	/**
	 * @return the id
	 */
	public UUID getId() {
		return id;
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}
	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}
	/**
	 * @return the address
	 */
	public String getAddress() {
		return address;
	}
	/**
	 * @param address the address to set
	 */
	public void setAddress(String address) {
		this.address = address;
	}
	
	/**
	 * @return the books
	 */
	public List getBooks() {
		return books;
	}
}
