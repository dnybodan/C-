package dao;

import model.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
/**
 * User Data Access Object
 */
public class UserDao {
    private final Connection conn;

    /**
     * creates a user data access object with the specified connection
     * @param conn the connection linked to the database
     */
    public UserDao(Connection conn) {this.conn = conn;}

    /**
     * add user will create a new instance of the User model and adds it to the data base
     * @param  user the user to be added to database
     * @throws DataAccessException throws when there is a problem manipulating the database
     */
    public void insertUser(User user) throws DataAccessException {
        String sql = "INSERT INTO users (userName, password, email, firstName, lastName, gender, personID) VALUES(?,?,?,?,?,?,?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, user.getUserName());
            stmt.setString(2, user.getPassword());
            stmt.setString(3, user.getEmail());
            stmt.setString(4, user.getFirstName());
            stmt.setString(5, user.getLastName());
            stmt.setString(6, user.getGender());
            stmt.setString(7, user.getPersonID());

            stmt.executeUpdate();
        } catch(SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while inserting new user into the data base");
        }
    }

    /**
     * checks to see if a user is in the database
     * @param userName the name to find
     * @return the user tied to the userName or null if not found
     * @throws DataAccessException throws when there is a problem manipulating the database
     */
    public User getUser(String userName) throws DataAccessException {
        User user;
        ResultSet rs = null;
        String sql = "SELECT * FROM users WHERE userName = ?;";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, userName);
            rs = stmt.executeQuery();
            if(rs.next()) {
                user = new User(rs.getString("userName"), rs.getString("password"),
                                rs.getString("email"), rs.getString("firstName"),
                                rs.getString("lastName"), rs.getString("gender"),
                                rs.getString("personID"));
                return user;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered when finding user");
        } finally {
            if(rs != null) {
                try{
                    rs.close();
                }
                catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
        return null;
    }

    /**
     * removes a user from the database if there is one that matches the given userName otherwise throws error
     * @param userName the user name to remove
     * @throws DataAccessException thrown if there was a problem removing from the data base
     */
    public void removeUser(String userName) throws DataAccessException {
        String sql = "DELETE FROM users WHERE userName = ?;";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, userName);
            stmt.executeUpdate();
        }catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error deleting users table from the data base related to userName: " + userName);
        }
    }

    /**
     * clears the User table in the data base
     * @throws DataAccessException thrown when there is a problem clearing the table
     */
    public void clearAllUsers() throws DataAccessException {
        String sql = "DELETE FROM users";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        }catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error deleting users table from the data base");
        }
    }



}
