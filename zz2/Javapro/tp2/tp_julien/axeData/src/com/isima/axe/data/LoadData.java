/**
 * 
 */
package com.isima.axe.data;

import java.io.IOException;
import java.util.Map;

/**
 * @author julien
 *
 */
public class LoadData {
	
	
	public static final String BOOK_PATH = "book.csv";
	public static final String LIBRARY_PATH = "library.csv";
	public static final String PERSON_PATH = "person.csv";
	public static final String BORROWING_PATH = "borrowing.csv";
	
	/**
	 * La liste des livres
	 */
	private Map books;
	/**
	 * la liste des librairies
	 */
	private Map librarys;
	/**
	 * La liste des personnes
	 */
	private Map persons;
	
	/**
	 * La liste des borrowings
	 */
	private Map borrowing;
	
	
	/**
	 * @throws IOException 
	 * 
	 */
	public LoadData(String chemin) throws IOException{
		
			// lecture des livres
			books = BookDataHandler.getInstance().load(chemin+BOOK_PATH);
			// lecture des librarys
			librarys = LibraryDataHandler.getInstance().load(chemin+LIBRARY_PATH, books);
			// lecture des personnes
			persons = PersonDataHandler.getInstance().load(chemin+PERSON_PATH, librarys);
			// lecture des borrowings
			borrowing = BorrowingDataHandler.getInstance().load(chemin+BORROWING_PATH, books, persons);
		
	}


	/**
	 * Permet d'obtenir le books
	 * @return the books qui est un Map
	 */
	public Map getBooks() {
		return books;
	}


	/**
	 * Permet de modifier le books avec celui passé
	 * en paramètre
	 * @param books le books à modifier
	 */
	public void setBooks(Map books) {
		this.books = books;
	}


	/**
	 * Permet d'obtenir le librarys
	 * @return the librarys qui est un Map
	 */
	public Map getLibrarys() {
		return librarys;
	}


	/**
	 * Permet de modifier le librarys avec celui passé
	 * en paramètre
	 * @param librarys le librarys à modifier
	 */
	public void setLibrarys(Map librarys) {
		this.librarys = librarys;
	}


	/**
	 * Permet d'obtenir le persons
	 * @return the persons qui est un Map
	 */
	public Map getPersons() {
		return persons;
	}


	/**
	 * Permet de modifier le persons avec celui passé
	 * en paramètre
	 * @param persons le persons à modifier
	 */
	public void setPersons(Map persons) {
		this.persons = persons;
	}


	/**
	 * Permet d'obtenir le borrowing
	 * @return the borrowing qui est un Map
	 */
	public Map getBorrowing() {
		return borrowing;
	}


	/**
	 * Permet de modifier le borrowing avec celui passé
	 * en paramètre
	 * @param borrowing le borrowing à modifier
	 */
	public void setBorrowing(Map borrowing) {
		this.borrowing = borrowing;
	}
	
	
	
	

}
