/**
 * 
 */
package com.isima.library.model;

import java.util.ArrayList;
import java.util.UUID;

/**
 * @author escourbi
 *
 */
public class Book {
	
	UUID id;
	String title;
	String author;
	ArrayList emprunt;
	
	public Book(String title, String author)
	{
		this.id = UUID.randomUUID();
		this.author = author;
		this.title = title;
	}
	
	public Object clone()
	{
		Book copie = new Book(this.title,this.author);
		return copie;
	}
	
	public boolean isAvailable()
	{
		boolean ret = false;
		//on regarde le dernier emprunt
		if(!emprunt.isEmpty())
		{
			Borrowing temp = (Borrowing)emprunt.get(emprunt.size()-1);
			ret = temp.isCompleted();
		}
		return ret;
	}
	
	public boolean addBorrow(Borrowing fiche)
	{
		boolean ret = this.isAvailable();
		if(ret) //si le livre est disponible
		{
			emprunt.add(fiche);
		}
		return ret;
		
	}
	
	public String toString()
	{
		return ("Book: " + "Title: " + title + " Author: " + author);
	}
	
	public String getTitle()
	{
		return title;
	}
	
	public String getAuthor()
	{
		return author;
	}
	
	public UUID getId()
	{
		return id;
	}

}
