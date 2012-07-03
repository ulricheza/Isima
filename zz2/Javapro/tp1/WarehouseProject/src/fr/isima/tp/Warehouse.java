/**
 * 
 */
package fr.isima.tp;

/**
 * @author escourbi
 *
 */
public class Warehouse {
	private String id;
	private String name;
	private Product stores;
	
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
	 * @param stores the name to set
	 */
	public void setStores(Product stores) {
		this.stores = stores;
	}

	/**
	 * @return stores the name to set
	 */
	public Product getStores() {
		return stores;
	}
	
}
