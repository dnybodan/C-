package service;

import dao.*;
import model.Event;
import model.Person;
import result.EventResult;
import result.PersonResult;

import java.io.IOException;
import java.sql.Connection;

/**
 * The Person Service
 */
public class PersonService {

    /**
     * returns the single person object with the specified ID
     * @param personID the persons ID
     */
    public static PersonResult getPerson(String personID, String authToken){
        //TODO: TEST THIS
        Database db = new Database();

        String message;
        boolean success = false;
        try {
            Connection conn = db.getConnection();
            PersonDao pDao = new PersonDao(conn);
            AuthTokenDao aDao = new AuthTokenDao(conn);
            UserDao uDao = new UserDao(conn);
            if(aDao.findAuthToken(authToken) == null) {
                throw new IOException("error Invalid AuthToken");
            }
            if(pDao.getPerson(personID) == null) {
                throw new IOException("error Invalid PersonID");
            }
            if(!(uDao.getUser(pDao.getPerson(aDao.findAuthToken(authToken).getPersonID()).getAssociatedUserName()).getUserName().equals(pDao.getPerson(personID).getAssociatedUserName()))){
                throw new IOException("error Request does not belong to this user");
            }
            if(!(aDao.findAuthToken(aDao.findAuthToken(authToken).getAuthToken()).getAuthToken().equals(authToken))) {
                throw new IOException("error Request does not belong to this user");
            }

            Person returnPerson = pDao.getPerson(personID);
            PersonResult pResult = new PersonResult(returnPerson.getAssociatedUserName(), returnPerson.getPersonID(),
                    returnPerson.getFirstName(), returnPerson.getLastName(),
                    returnPerson.getGender(),  returnPerson.getFatherID(),
                    returnPerson.getMotherID(), returnPerson.getSpouseID(), true);
            db.closeConnection(true);
            return pResult;
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
            return new PersonResult(message, false);
        }
    }
}
