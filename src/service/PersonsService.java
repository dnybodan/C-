package service;

import dao.*;
import model.Person;
import model.User;
import result.PersonResult;
import result.PersonsResult;

import java.io.IOException;
import java.sql.Connection;
import java.util.List;

/**
 * The Persons Service
 */
public class PersonsService {

    /**
     * returns all family members of the current user. the current user is determined from the provided authorization token
     * @param authToken the auth token for the current user
     * @return the person result
     */
    public static PersonsResult getPeople(String authToken) {
        //TODO: TEST THIS
        String message;
        Database db = new Database();
        try {

            Connection conn = db.getConnection();
            AuthTokenDao aDao = new AuthTokenDao(conn);
            UserDao uDao = new UserDao(conn);
            PersonDao pDao = new PersonDao(conn);
            if(aDao.findAuthToken(authToken) == null) {
                throw new IOException("error bad auth");
            }
            String personID = aDao.findAuthToken(authToken).getPersonID();
            String associatedUsername = pDao.getPerson(personID).getAssociatedUserName();
            List<Person> data = pDao.getPersons(associatedUsername);
            PersonsResult pResult = new PersonsResult(data, true);
            db.closeConnection(true);
            return pResult;
        }
        catch (DataAccessException | IOException exception) {
            message = exception.getMessage();
            exception.printStackTrace();
            try {
                db.closeConnection(false);
            } catch (DataAccessException ex) {
                ex.printStackTrace();
                message = ex.getMessage();
            }
            return new PersonsResult(message, false);
        }
    }
}
