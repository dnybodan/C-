package dao;

import model.Event;
import model.Person;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * Event Data Access Object
 */
public class EventDao {
    private final Connection conn;

    /**
     * creates new Event Data Access Object and establishes connection
     * @param conn connection passed to the new object
     */
    public EventDao(Connection conn)
    {
        this.conn = conn;
    }

    /**
     * Inserts a new event to the data base
     * @param event event object to be inserted
     * @throws DataAccessException thrown when there is a problem inserting data
     */
    public void insertEvent(Event event) throws DataAccessException {
        //We can structure our string to be similar to a sql command, but if we insert question
        //marks we can change them later with help from the statement
        String sql = "INSERT INTO events (EventID, AssociatedUsername, PersonID, Latitude, Longitude, " +
                "Country, City, EventType, Year) VALUES(?,?,?,?,?,?,?,?,?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            //Using the statements built-in set(type) functions we can pick the question mark we want
            //to fill in and give it a proper value. The first argument corresponds to the first
            //question mark found in our sql String
            stmt.setString(1, event.getEventID());
            stmt.setString(2, event.getUsername());
            stmt.setString(3, event.getPersonID());
            stmt.setFloat(4, event.getLatitude());
            stmt.setFloat(5, event.getLongitude());
            stmt.setString(6, event.getCountry());
            stmt.setString(7, event.getCity());
            stmt.setString(8, event.getEventType());
            stmt.setInt(9, event.getYear());

            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new DataAccessException("Error encountered while inserting into the database");
        }
    }

    /**
     *
     * @param eventID id of the event you wish to find
     * @return the event with the specified ID
     * @throws DataAccessException thrown when there is a problem finding data
     */
    public Event getEvent(String eventID) throws DataAccessException {
        Event event;
        ResultSet rs = null;
        String sql = "SELECT * FROM events WHERE EventID = ?;";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, eventID);
            rs = stmt.executeQuery();
            if (rs.next()) {
                event = new Event(rs.getString("EventID"), rs.getString("AssociatedUsername"),
                        rs.getString("PersonID"), rs.getFloat("Latitude"), rs.getFloat("Longitude"),
                        rs.getString("Country"), rs.getString("City"), rs.getString("EventType"),
                        rs.getInt("Year"));
                return event;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while finding event");
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
     * deletes an event tied to an event ID
     * @param eventID the events ID
     * @throws DataAccessException thrown when there is an error deleting event
     */
    public void removeEvent(String eventID) throws DataAccessException {
        String sql = "DELETE FROM events WHERE eventID = ?;";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, eventID);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered when clearing events related to eventID: " + eventID);
        }
    }

    /**
     * deletes all events tied to the specific user name
     * @param associatedUserName the associated user name
     * @throws DataAccessException thrown when there is a problem deleting the events in the data base
     */
    public void clearEvents(String associatedUserName) throws DataAccessException {
        String sql = "DELETE FROM events WHERE associatedUserName = ?;";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, associatedUserName);
            stmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered when clearing events related to userName: " + associatedUserName);
        }
    }

    /**
     * clears all events from events table
     * @throws DataAccessException thrown when there is a problem clearing all events
     */
    public void clearAllEvents()throws DataAccessException {
        String sql = "DELETE FROM events";
        try(PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        }catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error deleting events table from the data base");
        }
    }



    /**
     * returns array of events tied to a specific username
     * @param associatedUsername the user name
     * @return events that are associated with user name
     * @throws DataAccessException thrown when there is a problem getting the events
     */
    public List<Event> getEvents(String associatedUsername) throws DataAccessException {
        List<Event> events = new ArrayList<>();
        ResultSet rs = null;
        String sql = "SELECT * FROM events WHERE associatedUsername = ?;";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, associatedUsername);
            rs = stmt.executeQuery();
            while (rs.next()) {
                events.add(new Event(rs.getString("EventID"), rs.getString("AssociatedUsername"),
                        rs.getString("PersonID"), rs.getFloat("Latitude"), rs.getFloat("Longitude"),
                        rs.getString("Country"), rs.getString("City"), rs.getString("EventType"),
                        rs.getInt("Year")));
            }
            if(!events.isEmpty())
                return events;
        } catch (SQLException e) {
            e.printStackTrace();
            throw new DataAccessException("Error encountered while loading array of events");
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
}
