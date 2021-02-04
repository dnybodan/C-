package service;

import dao.*;
import model.Event;
import result.EventResult;
import result.PersonResult;
import result.Result;

import java.io.IOException;
import java.sql.Connection;

/**
 * The Event Service
 */
public class EventService {
    /**
     * returns the single event object witht the specified ID
     * @param eventID the event id
     * @return the event corresponding to the event ID
     */
    public static EventResult getEvent(String eventID, String authToken) {
        //TODO: test this
        Database db = new Database();
        String message;

        try {
            Connection conn = db.getConnection();
            EventDao eDao = new EventDao(conn);
            AuthTokenDao aDao = new AuthTokenDao(conn);
            PersonDao pDao = new PersonDao(conn);
            UserDao uDao = new UserDao(conn);
            if(aDao.findAuthToken(authToken) == null) {
                throw new IOException("error Invalid AuthToken");
            }
            if(eDao.getEvent(eventID) == null) {
                throw new IOException("error Invalid EventID");
            }
            if(!eDao.getEvent(eventID).getUsername().equals(pDao.getPerson(aDao.findAuthToken(authToken).getPersonID()).getAssociatedUserName())) {
                throw new IOException("error Request does not belong to this user");
            }
            Event returnEvent = eDao.getEvent(eventID);
            EventResult eResult = new EventResult(returnEvent.getUsername(), returnEvent.getEventID(), returnEvent.getPersonID(),
                    returnEvent.getLatitude(), returnEvent.getLongitude(), returnEvent.getCountry(),
                    returnEvent.getCity(), returnEvent.getEventType(), returnEvent.getYear(), true);
            db.closeConnection(true);
            return eResult;

        }
        catch (DataAccessException | IOException e) {
            message = e.getMessage();
            e.printStackTrace();
            try {
                db.closeConnection(false);
            } catch (DataAccessException ex) {
                ex.printStackTrace();
                message = ex.getMessage();
            }
            return new EventResult(message, false);
        }

    }
}
