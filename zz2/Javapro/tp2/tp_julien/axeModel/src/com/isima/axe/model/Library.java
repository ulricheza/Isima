package com.isima.axe.model;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.UUID;

/**
 * Classe permettant de décrire un librairie
 * @author millau -Gentil
 *
 */
public class Library {
	/**
	 * L'identifiant de la librairie
	 */
	private UUID id;
	
	/**
	 * Le nom de la librairie
	 */
	private String name;
	
	/**
	 * L'adresse de la librairie
	 */
	private String address;
	
	/**
	 * la liste des books
	 */
	private Map books;
	
	/**
	 * La liste de personnes
	 */
	private Map subscribers;
		
	/**
	 * Le constructeur par defaut
	 */
	public Library() {
		books= new HashMap();
		subscribers = new HashMap();
		id = UUID.randomUUID();
	}
	
	/**
	 * Permet d'ajouter un livre 
	 * @param b le livre
	 * @return vrai si le livre peux être ajouté et false sinon
	 */
	public boolean addBook(Book b)
	{
		boolean ret = false;
		
		if (b!=null && books.get(b.getId())==null)
		{
			if (b.getLibrary()!=null)
				b.getLibrary().getBooks().remove(b.getId());
			books.put(b.getId(), b);
			b.setLibrary(this);
			ret=true;
		}
		return ret;
	}

	public UUID getId() {
		return id;
	}

	public void setId(UUID id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public Map getBooks() {
		return books;
	}	
	

	public Map getSubscribers() {
		return subscribers;
	}

	/**
	 * méthode toString
	 */
	public String toString() {
		StringBuffer buffer = new StringBuffer();
		buffer.append(id);
		buffer.append(";");
		buffer.append(name);
		buffer.append(";");
		buffer.append(address);
		buffer.append(";");
		Iterator it = books.values().iterator();
		while(it.hasNext())
		{
			Book b = (Book)it.next();
			buffer.append(b.getId().toString()).append(',');
		}
		return buffer.toString();
	}
	
	
	
	

}
