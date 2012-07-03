/**
 * 
 */
package com.isima.library.model;

import java.util.Date;


/**
 * @author escourbi
 *
 */

public class Borrowing {
	private Date borrowingDate;
	private Date expectedReturnDate;
	private Date actualReturnDate;
	private Book book;
	private Person pers;
	
	public boolean isInProgress()
	{ 
		return( actualReturnDate == null); 
	}
	
	public boolean isCompleted()
	{
		return(actualReturnDate != null);
	}
	
	public boolean isLate()
	{
		Date todayDate =new Date();
		return (todayDate.compareTo(expectedReturnDate) > 0);
	}
		
	public String toString() {
		return "Borrowing [borrowingDate= " + borrowingDate.toString()
				+ ", expectedReturnDate= " + expectedReturnDate.toString()
				+ ", actualReturnDate= " + actualReturnDate + ", book=" + book.toString()
				+ ", pers= " + pers.toString() + "]";
	}

	/**
	 * @param borrowingDate
	 * @param book
	 * @param pers
	 */
	
	public Borrowing(Date borrowingDate, Book book, Person pers) {
		this.borrowingDate = borrowingDate;
		this.book = book;
		this.pers = pers;
		borrowingDate.setMonth(borrowingDate.getMonth() + 1);
		this.expectedReturnDate = borrowingDate;
	}
	
	/**
	 * @return the borrowingDate
	 */
	public Date getBorrowingDate() {
		return borrowingDate;
	}
	/**
	 * @param borrowingDate the borrowingDate to set
	 */
	public void setBorrowingDate(Date borrowingDate) {
		this.borrowingDate = borrowingDate;
	}
	/**
	 * @return the expectedReturnDate
	 */
	public Date getExpectedReturnDate() {
		return expectedReturnDate;
	}
	/**
	 * @param expectedReturnDate the expectedReturnDate to set
	 */
	public void setExpectedReturnDate(Date expectedReturnDate) {
		this.expectedReturnDate = expectedReturnDate;
	}
	/**
	 * @return the actualReturnDate
	 */
	public Date getActualReturnDate() {
		return actualReturnDate;
	}
	/**
	 * @param actualReturnDate the actualReturnDate to set
	 */
	public void setActualReturnDate(Date actualReturnDate) {
		this.actualReturnDate = actualReturnDate;
	}
	/**
	 * @return the book
	 */
	public Book getBook() {
		return book;
	}
	/**
	 * @param book the book to set
	 */
	public void setBook(Book book) {
		this.book = book;
	}
	/**
	 * @return the pers
	 */
	public Person getPers() {
		return pers;
	}
	/**
	 * @param pers the pers to set
	 */
	public void setPers(Person pers) {
		this.pers = pers;
	}
	
	
	
	

}
