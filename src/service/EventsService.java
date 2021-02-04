package service;

import dao.*;
import model.Event;
import model.Person;
import result.EventResult;
import result.EventsResult;
import result.PersonResult;
import result.PersonsResult;

import java.io.IOException;
import java.sql.Connection;
import java.util.List;

/**
 * The Events Service
 */
public class EventsService {
    /**
     * returns all the events for all the family members of the current user(determined by auth token)
     * @param authToken the users authorization token
     * @return the events of all the family members tied to this user
     */
    public static EventsResult getEvents(String authToken) {
        //TODO: test this
        Database db = new Database();
        String message;
        try {

            Connection conn = db.getConnection();
            AuthTokenDao aDao = new AuthTokenDao(conn);
            UserDao uDao = new UserDao(conn);
            PersonDao pDao = new PersonDao(conn);
            EventDao eDao = new EventDao(conn);
            if(aDao.findAuthToken(authToken) == null) {
                throw new IOException("error bad auth");
            }
            String personID = aDao.findAuthToken(authToken).getPersonID();
            String associatedUsername = pDao.getPerson(personID).getAssociatedUserName();
            List<Event> data = eDao.getEvents(associatedUsername);
            EventsResult eResult = new EventsResult(data, true);
            db.closeConnection(true);
            return eResult;
        } catch (DataAccessException | IOException e) {
            message = e.getMessage();
            e.printStackTrace();
            try {
                db.closeConnection(false);
            } catch (DataAccessException ex) {
                ex.printStackTrace();
                message = ex.getMessage();
            }
            return new EventsResult(message, false);
        }

    }
}
