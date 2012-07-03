/**
 * 
 */
package fr.isima.tp;

/**
 * @author escourbi
 *
 */
public class Location {
	private String id;
	private String name;
	private String zipCode;
	private Warehouse[] ware;
	/**
	 * @return the id
	 */
	public String getId() {
		return id;
	}
	/**
	 * @param id the id to set
	 */
	public void setId(String id) {
		this.id = id;
	}
	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}
	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}
	/**
	 * @return the zipCode
	 */
	public String getZipCode() {
		return zipCode;
	}
	/**
	 * @param zipCode the zipCode to set
	 */
	public void setZipCode(String zipCode) {
		this.zipCode = zipCode;
	}
	/**
	 * @return the ware
	 */
	public Warehouse[] getWare() {
		return ware;
	}
	/**
	 * @param ware the ware to set
	 */
	public void setWare(Warehouse[] ware) {
		this.ware = ware;
	}
}
