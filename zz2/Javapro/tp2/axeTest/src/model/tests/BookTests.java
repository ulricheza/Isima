package model.tests;

import java.util.Date;

import com.isima.library.model.*;

import junit.framework.TestCase;

public class BookTests extends TestCase {
	
	public void isAvailableTest()
	{
		Person pers = new Person("JC","septier");
		Book booktest = new Book("LOTR","Trucmuche");
		Library libtest = new Library("BU","DTC");
		Book bookFalse = new Book("Harry Crotteur","Moi");
		
		libtest.addBook(booktest);
		libtest.addBook(bookFalse);
		
		//test livre non disponible
		
		pers.subscribes(libtest);
		pers.borrows(bookFalse);
		Book test = libtest.hasBook(bookFalse);
		assertEquals(false, test.isAvailable());
		
		
		//test livre disponible
		test = libtest.hasBook(booktest);
		assertEquals(true, test.isAvailable());
	}
	
	public void assBorrowTest()
	{
		Person pers = new Person("JC","septier");
		Book booktest = new Book("LOTR","Trucmuche");
		Library libtest = new Library("BU","DTC");
		Book bookFalse = new Book("Harry Crotteur","Moi");
		
		libtest.addBook(booktest);
		libtest.addBook(bookFalse);
		Borrowing fichetest = new Borrowing(new Date(), null, null); //on se preocuppe pas de la fiche
		
		//test livre non disponible
		
		pers.subscribes(libtest);
		pers.borrows(bookFalse);
		Book test = libtest.hasBook(bookFalse);
		assertEquals(false, test.addBorrow(fichetest));
		
		
		//test livre disponible
		test = libtest.hasBook(booktest);
		assertEquals(true, test.addBorrow(fichetest));
	}


}
