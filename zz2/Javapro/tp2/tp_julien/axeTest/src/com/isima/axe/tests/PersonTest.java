package com.isima.axe.tests;

import com.isima.axe.model.Book;
import com.isima.axe.model.Library;
import com.isima.axe.model.Person;

import junit.framework.TestCase;

public class PersonTest extends TestCase {
	
	/**
	 * Permet de tester l'inscription d'une personne
	 */
	public static void testSubscribes()
	{
		Library l = new Library();
		Library l2 = new Library();
		Person p = new Person();
		
		
		assertTrue("subcribes methode false",p.subscribes(l));
		assertTrue("la librairie ne possede pas bien la personne",l.getSubscribers().containsKey(p.getId()));
		assertFalse("subscribes methode with null true", p.subscribes(null));
		assertTrue("La personne ne contient pas la librairie",p.getLibrary()==l);
		p.subscribes(l);
		assertTrue("la meme personne est abonnée 2 fois",l.getSubscribers().size()==1);
	}
	
	/**
	 * Permet de tester la méthode borrows
	 */
	public static void testBorrows()
	{
		Book b = new Book();
		Person p = new Person();
		Person p2 = new Person();
		
		try{
			p.returnb(b);
		}catch(Exception e)
		{
			fail("Le livre n'a jamais été emprunté");
		}
		assertTrue("borrows method false",p.borrows(b));
		assertTrue("List borrowing de Person ne contient pas le borrowing", p.getBorrowings().size()==1);
		assertTrue("Le livre ne contient pas le borrowing", !b.getBorrowers().isEmpty());
		
		assertFalse("impossible d'emprunter le livre deux fois",p2.borrows(b));				
	}

}
