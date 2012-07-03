/**
 * 
 */
package com.isima.library.model;

import java.util.ArrayList;
import java.util.Date;
import java.util.UUID;



/**
 * @author escourbi
 *
 */
public class Person {
	
	private UUID id;
	private String firstName;
	private String lastName;
	private Library library;
	private ArrayList empruntliste;
	

	/**
	 * constructeur de la classe Person 
	 */
	public Person(String firstName,String lastName)
	{
		this.id = UUID.randomUUID();
		this.firstName = firstName;
		this.lastName = lastName;
	}
	
	/**
	 * @param subscribtion library a souscrire 
	 * @throws InvalidAttributesException 
	 */
	public boolean subscribes(Library subscribtion)
	{
		boolean insert = true;
		if(subscribtion == null)
			throw new NullPointerException();
		else
		{
			if(empruntliste.size()==0)
				library = subscribtion;
			else insert = false;;	
		}
		return insert;
	}
	
	/**
	 * 
	 * @param emprunt
	 */
	public boolean borrows(Book emprunt)
	{
		boolean emprunter = false;
		Book livre;
		Borrowing fiche;
		//on verifie l'appartenance du livre a la library souscrite
		if(library != null)
		{
			livre = library.hasBook(emprunt);
			if(livre != null)
			{
				//on regarde si le livre est disponible
				if(livre.isAvailable())
				{
					//on instancie un nouveau Borrowing
					fiche = new Borrowing(new Date(), livre, this);
					empruntliste.add(fiche);
					livre.addBorrow(fiche);
					emprunter = true;
				}
			}
		}
		return emprunter;
	}
	
	
	/**
	 * @param retour
	 */
	public void returns(Book retour)
	{
		int i = 0;
		boolean fin = false;
		Borrowing courant = null;
		
		//on recherche le livre dans la liste des emprunts
		
		while(fin == false)
	    {
			if(i < empruntliste.size())
			{
				courant = (Borrowing) empruntliste.get(i);
				if( courant.getBook().getId() == retour.getId())
				{
				   fin = true;	
				}
			}
			else
			{
				fin = true;
			}
	    }
		
	    if(i < empruntliste.size()) //livre trouve
	    {
	    	//on verifie si le livre a pas ete deja rendu
	    	if(!courant.isCompleted())
	    	{
	    		//on doit setter la date de retour
	    		courant.setActualReturnDate(new Date());
	    	}
		}	
	}
	
	public String toString()
	{
		return ( "Person:" + "FirstName: " + firstName + " LastName " + lastName);
	}
	
	/**
	 * @return the id
	 */
	public UUID getId() {
		return id;
	}
	/**
	 * @return the firstName
	 */
	public String getFirstName() {
		return firstName;
	}
	/**
	 * @param firstName the firstName to set
	 */
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}
	/**
	 * @return the lastName
	 */
	public String getLastName() {
		return lastName;
	}
	/**
	 * @param lastName the lastName to set
	 */
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}
	/**
	 * @return the empruntliste
	 */
	public ArrayList getEmpruntliste() {
		return empruntliste;
	}
	/**
	 * @return the libliste
	 */
	public Library getLibrary() {
		return library;
	}
}
