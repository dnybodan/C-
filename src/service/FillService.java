package service;

import dao.*;
import model.Event;
import model.Person;
import result.FillResult;
import service.data.Data;
import service.data.Location;

import java.io.IOException;
import java.sql.Connection;
import java.util.ArrayList;
import java.util.List;

/**
 * The Fill Service
 */
public class FillService {
    private static List<Location> locations = new ArrayList<>();
    private static List<String> fnames = new ArrayList<>();
    private static List<String> mnames = new ArrayList<>();
    private static List<String> snames = new ArrayList<>();
    private static int numPersons = 1;
    private static int numEvents;



    /**
     * Populates the server's database with generated data for the specified user name.
     * The required "username" parameter must be a user already registered with the server.
     * If there is any data in the database already associated with the given user name,
     * it is deleted.
     * The optional 'generations' parameter lets the caller specify
     * the number of generations of ancestors to be generated,
     * and must be a non-negative integer (the default is 4,
     * which results in 31 new persons each with associated events).
     * @param userName the users name
     * @param numGenerations the number of generations to fill
     * @return the result of the fill request
     */
    public static FillResult fill(String userName, int numGenerations) {
        //TODO: GET THIS DONE
        String message;
        Database db = new Database();
        try {
            Connection conn = db.getConnection();
            FillResult fResult = getFillResponse(userName, numGenerations, conn);
            db.closeConnection(true);
            return fResult;

        } catch (DataAccessException | IOException e) {
            message = e.getMessage();
            e.printStackTrace();
            try {
                db.closeConnection(false);
            } catch (DataAccessException ex) {
                ex.printStackTrace();
                message = ex.getMessage();
            }
            return new FillResult(message, false);
        }
    }

    public static FillResult getFillResponse(String userName, int numGenerations, Connection conn) throws IOException{
        try {
            UserDao uDao = new UserDao(conn);
            if(uDao.getUser(userName) == null) {
                throw new IOException("Error no user with that name");
            }
            Data.getData(fnames,mnames,snames,locations);
            PersonDao pDao = new PersonDao(conn);

            EventDao eDao = new EventDao(conn);
            eDao.clearEvents(userName);
            Person personToKeep = pDao.getPerson(uDao.getUser(userName).getPersonID());
            pDao.clearPersons(userName);
            pDao.insertPerson(personToKeep);
            numEvents = 0;
            numPersons = 1;
            generatePerson(userName, numGenerations, conn);
            return new FillResult("Successfully added " + numPersons + " persons and " + numEvents +
                    " events to the database.", true);
        } catch (DataAccessException | IOException e) {
            e.printStackTrace();
            return new FillResult(e.getMessage(), false);
        }
    }

    private static void generatePerson(String userName, int numGenerations, Connection conn) throws DataAccessException {

        UserDao uDao = new UserDao(conn);
        EventDao eDao = new EventDao(conn);
        Location birthLocation = locations.get((int)(Math.random()*1000) % locations.size());
        Event birth = new Event(Data.generateID(userName), userName, uDao.getUser(userName).getPersonID(),
                birthLocation.getLatitude(), birthLocation.getLongitude(), birthLocation.getCountry(),
                birthLocation.getCity(), "birth" , 2000);
        eDao.insertEvent(birth);
        numEvents += 1;
        int currGeneration = 0;
        if(numGenerations > 0)
            generateGenerations(uDao.getUser(userName).getPersonID(), userName, birth.getYear(), currGeneration, numGenerations, conn);

    }

    private static void generateGenerations(String personID, String associatedUsername, int childBirthYear, int currGeneration, int numGenerations, Connection conn) throws DataAccessException{
        if(currGeneration == numGenerations) {
            return;
        }
        UserDao uDao = new UserDao(conn);
        PersonDao pDao = new PersonDao(conn);
        EventDao eDao = new EventDao(conn);

        String motherID = createMother(associatedUsername, childBirthYear, currGeneration, numGenerations, conn);
        String fatherID = createFather(associatedUsername, childBirthYear, currGeneration, numGenerations, motherID, conn);
        Person upDatedMother= pDao.getPerson(motherID);
        pDao.removePerson(motherID);
        upDatedMother.setSpouseID(fatherID);
        pDao.insertPerson(upDatedMother);

        Location marriageLocation = locations.get((int)(Math.random()*1000) % locations.size());
        Event marriageEventMother = new Event(Data.generateID(associatedUsername), associatedUsername, motherID,
                marriageLocation.getLatitude(), marriageLocation.getLongitude(), marriageLocation.getCountry(),
                marriageLocation.getCity(), "marriage" , childBirthYear-2);
        eDao.insertEvent(marriageEventMother);
        numEvents += 1;
        Event marriageEventFather = new Event(Data.generateID(associatedUsername), associatedUsername, fatherID,
                marriageLocation.getLatitude(), marriageLocation.getLongitude(), marriageLocation.getCountry(),
                marriageLocation.getCity(), "marriage" , childBirthYear-2);
        eDao.insertEvent(marriageEventFather);
        numEvents += 1;

        //setting the childs mother/fatherID
        Person upDatedPerson = pDao.getPerson(personID);
        pDao.removePerson(personID);
        upDatedPerson.setFatherID(fatherID);
        upDatedPerson.setMotherID(motherID);
        pDao.insertPerson(upDatedPerson);

    }

    private static String createMother(String associatedUsername, int childBirthYear, int currGeneration, int numGenerations, Connection conn) throws DataAccessException{
        PersonDao pDao = new PersonDao(conn);
        EventDao eDao = new EventDao(conn);
        Person mother = new Person(Data.generateID(associatedUsername), associatedUsername,
                fnames.get(((int)(Math.random()*1000) % fnames.size())), snames.get(((int)(Math.random()*1000) % snames.size())),
                "f", null, null, null);
            pDao.insertPerson(mother);
            numPersons += 1;

            Location birthLocation = locations.get((int)(Math.random()*1000) % locations.size());
            Event motherBirth = new Event(Data.generateID(associatedUsername), associatedUsername, mother.getPersonID(),
                birthLocation.getLatitude(), birthLocation.getLongitude(), birthLocation.getCountry(),
                birthLocation.getCity(), "birth" , childBirthYear-20);
            eDao.insertEvent(motherBirth);
            numEvents += 1;

            Location deathLocation = locations.get((int)(Math.random()*1000) % locations.size());
            Event death = new Event(Data.generateID(associatedUsername), associatedUsername, mother.getPersonID(),
                deathLocation.getLatitude(), deathLocation.getLongitude(), deathLocation.getCountry(),
                deathLocation.getCity(), "death" , childBirthYear+80);
            eDao.insertEvent(death);
            numEvents += 1;

        generateGenerations(mother.getPersonID(), associatedUsername, motherBirth.getYear(), currGeneration+1, numGenerations, conn);

        return mother.getPersonID();
    }


    private static String createFather(String associatedUsername, int childBirthYear, int currGeneration, int numGenerations,
                                     String spouseID,  Connection conn) throws DataAccessException{

        PersonDao pDao = new PersonDao(conn);
        EventDao eDao = new EventDao(conn);
            Person father = new Person(Data.generateID(associatedUsername), associatedUsername,
                    mnames.get(((int)(Math.random()*1000) % mnames.size())), pDao.getPerson(spouseID).getLastName(),
                    "m", null, null, spouseID);
            pDao.insertPerson(father);
            numPersons += 1;
            Location birthLocation = locations.get((int)(Math.random()*1000) % locations.size());
            Event fatherBirth = new Event(Data.generateID(associatedUsername), associatedUsername, father.getPersonID(),
                    birthLocation.getLatitude(), birthLocation.getLongitude(), birthLocation.getCountry(),
                    birthLocation.getCity(), "birth" , childBirthYear-20);
            eDao.insertEvent(fatherBirth);
            numEvents += 1;
            Location deathLocation = locations.get((int)(Math.random()*1000) % locations.size());
            Event death = new Event(Data.generateID(associatedUsername), associatedUsername, father.getPersonID(),
                    deathLocation.getLatitude(), deathLocation.getLongitude(), deathLocation.getCountry(),
                    deathLocation.getCity(), "death" , childBirthYear+80);
            eDao.insertEvent(death);
            numEvents += 1;
            generateGenerations(father.getPersonID(), associatedUsername, fatherBirth.getYear(), currGeneration+1, numGenerations, conn);

            return father.getPersonID();

    }
}
