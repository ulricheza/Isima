package com.isima.axe.model;

import java.util.ArrayList;
import java.util.UUID;

/**
 * Permet de décrire un livre
 * @author millau - Gentil
 *
 */
public class Book {
	
	/**
	 * L'identifiant du livre
	 */
	private UUID id;
	
	/**
	 * Le titre du livre
	 */
	private String title;
	/**
	 * l'auteur du livre
	 */
	private String author;
	/**
	 * La librairie du livre
	 */
	private Library library;
	
	/**
	 * La liste des emprunteurs
	 */
	private ArrayList borrowers; 
	
	/**
	 * 
	 */
	public Book() {
		borrowers= new ArrayList();
		id = UUID.randomUUID();
	}
	
	
	/**
	 * Permet d'obtenir le borrowers
	 * @return the borrowers qui est un ArrayList
	 */
	public ArrayList getBorrowers() {
		return borrowers;
	}
	
	public UUID getId() {
		return id;
	}
	public void setId(UUID id) {
		this.id = id;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public String getAuthor() {
		return author;
	}
	public void setAuthor(String author) {
		this.author = author;
	}
	public Library getLibrary() {
		return library;
	}
	public void setLibrary(Library library) {
		this.library = library;
	}
	
	public String toString() {
		StringBuffer buffer = new StringBuffer();
		buffer.append(id);
		buffer.append(";");
		buffer.append(title);
		buffer.append(";");
		buffer.append(author);
		buffer.append(";");
		return buffer.toString();
	}

}
