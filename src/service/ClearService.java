package service;

import dao.DataAccessException;
import dao.Database;
import model.AuthToken;
import result.ClearResult;

import java.sql.Connection;

/**
 * The Clear Service
 */
public class ClearService {
    private static String message;

    /**
     * clears the data base tables
     * @return returns the clear result object
     */
    public static ClearResult clear(){
        Database db = new Database();
        try {
            Connection conn = db.getConnection();
            db.clearTables();
            message = "clear succeeded";
            success = true;
            db.closeConnection(true);
        } catch (DataAccessException e) {
            message = e.getMessage();
            e.printStackTrace();
            try {
                db.closeConnection(false);
            } catch (DataAccessException ex) {
                ex.printStackTrace();
                message = ex.getMessage();
            }
        }
        return new ClearResult(message, success);
    }

    public static String getMessage() {
        return message;
    }

    public static void setMessage(String message) {
        ClearService.message = message;
    }

    public static boolean isSuccess() {
        return success;
    }

    public static void setSuccess(boolean success) {
        ClearService.success = success;
    }

    private static boolean success = false;

}
