package fr.isima.xsnoop.user;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public class User {

    private String username;

    private String password;

    public User(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }
}
