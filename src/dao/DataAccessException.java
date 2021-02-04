package dao;

/**
 * a data access exception to throw when there are problems accessing the database
 */
public class DataAccessException extends Exception {
    DataAccessException(String message)
    {
        super(message);
    }
    DataAccessException()
    {
        super();
    }
}