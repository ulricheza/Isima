package com.isima.axe.model;

import java.util.ArrayList;
import java.util.Date;
import java.util.UUID;

/**
 * Classe contenant les infos d'une personne
 * @author millau - Gentil
 *
 */
public class Person {
	/**
	 * Identifiant de la classe
	 */
	private UUID id;
	/**
	 * Le nom de la personne
	 */
	private String firstName;
	/**
	 * Le prenom de la personne
	 */
	private String lastName;
	/**
	 * La librairie de la personne
	 */
	private Library library;
	/**
	 * La liste des emprunts
	 */
	private ArrayList borrowings;


	/**
	 * Contructeur de la classe personne
	 */
	public Person()
	{
		borrowings = new ArrayList();
		id = UUID.randomUUID();
	}
	
	
	/**
	 * Methode permettant de s'inscrire à une librairie
	 * @param l :  la librairie
	 * @return : true si l'inscription est réussi, false si l'inscription est impossible
	 */
	public boolean subscribes(Library l)
	{
		boolean ret = false;
		
		if(l!=null)
		{
			// suppression de la personne de son ancienne librairie
			if (library!=null)
				library.getSubscribers().remove(id);
			// ajout dans la nouvelle
			library=l;
			l.getSubscribers().put(id, this);
			ret=true;
		}
		
		return ret;
		
	}
	
	/**
	 * Methode permettant d'emprunter un livre
	 * @param b : le livre
	 * @return : true si l'emprunt à réussit, false sinon
	 */
	public boolean borrows(Book b)
	{
		boolean ret = false;
		// si le livre n'est pas null 
		if(b!=null)
		{
			boolean emprunt = false;
			// permet de verifier que le livre posséde un emprunt
			if(!b.getBorrowers().isEmpty())
			{
				Borrowing bo = (Borrowing) b.getBorrowers().get(b.getBorrowers().size()-1);
				// verification que le livre n'est pas emprunté
				if (bo.isInProgress())
				{
					emprunt = true;
				}
			}
			// si il n'est pas emprunté 
			if (!emprunt)
			{
				Borrowing bor = new Borrowing();
				bor.setBorrowing(b);
				bor.setBorrower(this);
				this.getBorrowings().add(bor);
				b.getBorrowers().add(bor);
				ret=true;
			}
			
		}
		return ret;
	}
	
	
	/**
	 * Permet de retourner un livre
	 * @param b le livre à retourner
	 */
	public void returnb(Book b)
	{
		if (b!=null)
		{
			if (!b.getBorrowers().isEmpty())
			{
				Borrowing bor = (Borrowing) b.getBorrowers().get(b.getBorrowers().size()-1);
				if (bor.getBorrower()==this)
				{
					bor.setActualReturnDate(new Date());
				}
			}
		}
	}
	
	
	/**
	 * Permet d'obtenir le borrowings
	 * @return the borrowings qui est un ArrayList
	 */
	public ArrayList getBorrowings() {
		return borrowings;
	}

	/**
	 * Permet de modifier le borrowings avec celui passé
	 * en paramètre
	 * @param borrowings le borrowings à modifier
	 */
	public void setBorrowings(ArrayList borrowings) {
		this.borrowings = borrowings;
	}
	
	
	public UUID getId() {
		return id;
	}
	public String getFirstName() {
		return firstName;
	}
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}
	public String getLastName() {
		return lastName;
	}
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}
	public Library getLibrary() {
		return library;
	}
	
	/**
	 * Permet de modifier le id avec celui passé
	 * en paramètre
	 * @param id le id à modifier
	 */
	public void setId(UUID id) {
		this.id = id;
	}


	public String toString() {
		StringBuffer buffer = new StringBuffer();
		buffer.append(id);
		buffer.append(";");
		buffer.append(firstName);
		buffer.append(";");
		buffer.append(lastName);
		buffer.append(";");
		buffer.append(library.getId().toString());
		buffer.append(";");
		return buffer.toString();
	}
	
	
	
	

}
