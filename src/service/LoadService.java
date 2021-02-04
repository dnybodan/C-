package service;

import dao.*;
import model.Event;
import model.Person;
import model.User;
import request.LoadRequest;
import result.ClearResult;
import result.LoadResult;
import result.PersonResult;

import javax.xml.crypto.Data;
import java.io.IOException;
import java.sql.Connection;

/**
 * The Load Service
 */
public class LoadService {

    /**
     * clears all data from database and then loads the posted user, person, and event data into the database
     * @param request the request
     * @return the result of the load request
     */
    public static LoadResult load(LoadRequest request) {
        String message;

        Database db = new Database();
        try {
            if(request.getEvents() == null || request.getPersons() == null || request.getUsers() == null) {
                throw new IOException("null input");
            }
            ClearResult cResult = ClearService.clear();
            Connection conn = db.getConnection();
            UserDao uDao = new UserDao(conn);
            PersonDao pDao = new PersonDao(conn);
            EventDao eDao = new EventDao(conn);
            int x = 0;
            int y = 0;
            int z = 0;
            for(User u: request.getUsers()) {
                uDao.insertUser(u);
                x++;
            }
            for(Person p: request.getPersons()) {
                pDao.insertPerson(p);
                y++;
            }
            for(Event e: request.getEvents()) {
                eDao.insertEvent(e);
                z++;
            }
            message = "Successfully added " + x + " users, " + y + " persons, and " + z + " events to the database.";

            db.closeConnection(true);
            return new LoadResult(message, true);
        } catch (DataAccessException | IOException e) {
            message = e.getMessage();
            e.printStackTrace();
            try {
                db.closeConnection(false);
            } catch (DataAccessException ex) {
                ex.printStackTrace();
                message = ex.getMessage();
            }
            return new LoadResult(message, false);
        }

    }

}
