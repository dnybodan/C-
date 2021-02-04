package dao;

import model.AuthToken;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * Authorization Token Data Access Object
 */

public class AuthTokenDao {
    private final Connection conn;

    /**
     * creates a new Authorization token data access object
     * @param conn the data base connection which is provided
     */
    public AuthTokenDao(Connection conn) {this.conn = conn;}

    /**
     * adds an Authorization Token and pairs it with the personID
     * @param authToken the authToken to be added to the database
     * @throws DataAccessException thrown when there is a problem adding auth token to database
     */
    public void insertAuthToken(AuthToken authToken) throws DataAccessException{
        String sql = "INSERT INTO authTokens (personID, authToken) VALUES(?,?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, authToken.getPersonID());
            stmt.setString(2, authToken.getAuthToken());
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("There was an error inserting the " +
                    "AuthToken in the dataBase related to personID: " + authToken.getPersonID());
        }
    }

    /**
     * checks to see if the auth token is in the database and returns true if it is
     * @param personID the person ID
     * @return the authToken if it found or null if not found
     * @throws DataAccessException thrown when there is a problem finding the auth token
     */
    public AuthToken getAuthToken(String personID) throws DataAccessException{
        AuthToken authTok;
        ResultSet rs = null;
        String sql = "SELECT * FROM authTokens WHERE personID = ?";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, personID);
            rs = stmt.executeQuery();
            if(rs.next()) {
                authTok = new AuthToken(rs.getString("personID"), rs.getString("authToken"));
                return authTok;
            }
        } catch (SQLException e){
            e.printStackTrace();
            throw new DataAccessException("Error retrieving auth token from data base related to personID: " + personID);
        } finally {
            if(rs != null) {
                try{
                    rs.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
        return null;
    }

    /**
     * checks to see if the auth token is in the database and returns true if it is
     * @param aToken the person ID
     * @return the authToken if it found or null if not found
     * @throws DataAccessException thrown when there is a problem finding the auth token
     */
    public AuthToken findAuthToken(String aToken) throws DataAccessException {
        AuthToken authTok;
        ResultSet rs = null;
        String sql = "SELECT * FROM authTokens WHERE authToken = ?";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, aToken);
            rs = stmt.executeQuery();
            if(rs.next()) {
                authTok = new AuthToken(rs.getString("personID"), rs.getString("authToken"));
                return authTok;
            }
        } catch (SQLException e){
            e.printStackTrace();
            throw new DataAccessException("Error retrieving auth token from data base related to AuthToken: " + aToken);
        } finally {
            if(rs != null) {
                try{
                    rs.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
        return null;
    }

    /**
     * removes everything in the authToken table
     * @throws DataAccessException thrown when there is a problem clearing the table
     */
    public void clearAllAuthTokens() throws DataAccessException {
        String sql = "DELETE FROM authTokens";
        try(PreparedStatement stmt = conn.prepareStatement(sql)){
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error deleting authTokens table from the data base");
        }
    }

    /**
     * removes an authToken and its paired personID from the dataBase and throws error if unsuccessful
     * @param personID the person ID
     * @throws DataAccessException thrown if there was a problem removing from the data base
     */
    public void removeAuthToken(String personID) throws DataAccessException {
        String sql = "DELETE FROM authTokens WHERE personID";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("There was an error removing the auth token related to personID value: " + personID);
        }
    }
}
