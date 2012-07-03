package model.tests;

import com.isima.library.model.*;

import junit.framework.TestCase;

public class BorrowingTest extends TestCase{
	
	public void isInProgressTest()
	{
		Person pers = new Person("JC","septier");
		Book booktest = new Book("LOTR","Trucmuche");
		Library libtest = new Library("BU","DTC");
		Book bookFalse = new Book("Harry Crotteur","Moi");
		
		libtest.addBook(booktest);
		libtest.addBook(bookFalse);
		pers.subscribes(libtest);
		pers.borrows(booktest);
		Borrowing fiche = (Borrowing) pers.getEmpruntliste().get(0);
		//test livre emprunte
		assertEquals(true, fiche.isInProgress());
		
		//test livre rendu
		pers.returns(booktest);
		assertEquals(false, fiche.isInProgress());
	}
	
	public void isCompletedTest()
	{
		Person pers = new Person("JC","septier");
		Book booktest = new Book("LOTR","Trucmuche");
		Library libtest = new Library("BU","DTC");
		Book bookFalse = new Book("Harry Crotteur","Moi");
		
		libtest.addBook(booktest);
		libtest.addBook(bookFalse);
		pers.subscribes(libtest);
		pers.borrows(booktest);
		Borrowing fiche = (Borrowing) pers.getEmpruntliste().get(0);
		//test livre emprunte
		assertEquals(false, fiche.isInProgress());
		
		//test livre rendu
		pers.returns(booktest);
		assertEquals(true, fiche.isInProgress());
	}
	
	public void isLate()
	{
		//TODO: Comment tester par rapport la date d'aujourd'hui
		Person pers = new Person("JC","septier");
		Book booktest = new Book("LOTR","Trucmuche");
		Library libtest = new Library("BU","DTC");
		Book bookFalse = new Book("Harry Crotteur","Moi");
		
		libtest.addBook(booktest);
		libtest.addBook(bookFalse);
		pers.subscribes(libtest);
		pers.borrows(booktest);
		Borrowing fiche = (Borrowing) pers.getEmpruntliste().get(0);
		
		//test livre correct
		assertEquals(true, fiche.isLate());
	}
}
