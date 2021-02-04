package dao;

import model.Person;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * Person Data Access Object
 */
public class PersonDao {
    private final Connection conn;

    /**
     * creates new person data access object and establishes and links to the passed connection
     * @param conn the connection which the person data access object should link up with
     */
    public PersonDao(Connection conn) {this.conn = conn;}

    /**
     * adds a new person to the database
     * @param person the person to be added to the data base
     * @throws DataAccessException thrown when there is a problem adding a person
     */
    public void insertPerson(Person person) throws DataAccessException {
        //We can structure our string to be similar to a sql command, but if we insert question
        //marks we can change them later with help from the statement
        String sql = "INSERT INTO persons (personID, associatedUserName, firstName, lastName, gender, " +
                "fatherID, motherID, spouseID) VALUES(?,?,?,?,?,?,?,?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            //Using the statements built-in set(type) functions we can pick the question mark we want
            //to fill in and give it a proper value. The first argument corresponds to the first
            //question mark found in our sql String
            stmt.setString(1, person.getPersonID());
            stmt.setString(2, person.getAssociatedUserName());
            stmt.setString(3, person.getFirstName());
            stmt.setString(4, person.getLastName());
            stmt.setString(5, person.getGender());
            stmt.setString(6, person.getFatherID());
            stmt.setString(7, person.getMotherID());
            stmt.setString(8, person.getSpouseID());

            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while inserting a person into the database");
        }
    }


    /**
     * checks to see if person is in data base and returns the result
     * @param personID the person ID to look for
     * @return the person matchin the personID or NULL if not found
     * @throws DataAccessException thrown when there is a problem finding a person
     */
    public Person getPerson(String personID) throws DataAccessException{
        Person person;
        ResultSet rs = null;
        String sql = "SELECT * FROM persons WHERE personID = ?;";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, personID);
            rs = stmt.executeQuery();
            if (rs.next()) {
                person = new Person(rs.getString("personID"), rs.getString("associatedUserName"),
                                    rs.getString("firstName"), rs.getString("lastName"),
                                    rs.getString("gender"), rs.getString("fatherID"),
                                    rs.getString("motherID"), rs.getString("spouseID"));
                return person;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while finding person");
        } finally {
            if(rs != null) {
                try {
                    rs.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }

        }
        return null;
    }

    public List<Person> getPersons(String associatedUsername) throws DataAccessException {
        List<Person> data = new ArrayList<>();
        ResultSet rs = null;
        String sql = "SELECT * FROM persons WHERE associatedUsername = ?;";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, associatedUsername);
            rs = stmt.executeQuery();
            int i = 0;

            while (rs.next()) {
                data.add(new Person(rs.getString("personID"), rs.getString("associatedUserName"),
                        rs.getString("firstName"), rs.getString("lastName"),
                        rs.getString("gender"), rs.getString("fatherID"),
                        rs.getString("motherID"), rs.getString("spouseID")));
                i++;
            }
            if(!data.isEmpty())
                return data;

        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while loading array of persons");
        } finally {
            if(rs != null) {
                try {
                    rs.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }

        }
        return null;

    }
    /**
     * deletes person from the database
     * @param personID person ID of the person to delete
     * @throws DataAccessException thrown when there is a problem deleting person
     */
    public void removePerson(String personID) throws DataAccessException {
        String sql = "DELETE FROM persons WHERE personID = ?;";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, personID);
            stmt.executeUpdate();
        }catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error deleting person table from the data base related to personID: " + personID);
        }
    }

    /**
     * deletes all persons related to given username
     * @param associatedUserName the associated user name
     * @throws DataAccessException thrown when there is a problem deleting the persons in the database
     */
    public void clearPersons(String associatedUserName) throws DataAccessException{
        String sql = "DELETE FROM persons WHERE associatedUserName = ?;";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, associatedUserName);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered when clearing persons related to userName: " + associatedUserName);
        }
    }

    /**
     * delete the persons tied to this username
     //* @param associatedUserName the associated username //fixme this could be a parameter in another function
     * @throws DataAccessException thrown when there is a problem deleting persons
     */
    public void clearAllPersons() throws DataAccessException {
        String sql = "DELETE FROM persons";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        }catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error deleting persons table from the data base");
        }
    }
}
