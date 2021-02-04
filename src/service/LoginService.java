package service;

import dao.AuthTokenDao;
import dao.DataAccessException;
import dao.Database;
import dao.UserDao;
import model.AuthToken;
import model.User;
import request.LoginRequest;
import result.LoginResult;

import java.io.IOException;
import java.sql.Connection;

/**
 * The Login Service
 */
public class LoginService {


    public static LoginResult getLoginResponse(LoginRequest r, Connection conn_1) {
        //TODO: TEST THIS
        String message;
        try {
            UserDao uDao = new UserDao(conn_1);
            errorCheck(r, uDao);
            String userName = r.getUserName();
            String password = r.getPassword();
            AuthTokenDao aDao = new AuthTokenDao(conn_1);
            String newAuthToken = generateAuthToken(r.getUserName());
            AuthToken newAuthTokenObj = new AuthToken(uDao.getUser(userName).getPersonID(), newAuthToken);
            aDao.insertAuthToken(newAuthTokenObj);
            return new LoginResult(newAuthTokenObj.getAuthToken(), userName,
                    uDao.getUser(userName).getPersonID(), true);
        }
        catch (DataAccessException | IOException e) {
            e.printStackTrace();
            message = e.getMessage();
        }
        return new LoginResult(message, false);
    }

    /**
     * Logs in the user and returns an auth token.
     * @param r the login request
     * @return the login result, whether it was a success or if there was an error
     */
    public static LoginResult login(LoginRequest r)  {
        String message;
        Database db = new Database();
        try {
            Connection conn = db.getConnection();
            LoginResult lResult = getLoginResponse(r, conn);
            db.closeConnection(true);
            return lResult;

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
        return new LoginResult(message, false);
    }

    private static String generateAuthToken(String randString) {
        StringBuilder authToken = new StringBuilder();
        String charString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                + "0123456789"
                + "abcdefghijklmnopqrstuvxyz";

        for (int i = 0; i < 10; i++) {

            int index = (int)(charString.length() * Math.random()
                    * (int)randString.charAt(randString.length() - 1) % charString.length() - 1);
            authToken.append(charString.charAt(index));
        }
        return authToken.toString();
    }

    private static void errorCheck(LoginRequest request, UserDao uDao) throws IOException, DataAccessException {
        if(request.getUserName() == null || request.getPassword() == null)
            throw new IOException("Input Error");
        else if (uDao.getUser(request.getUserName()) == null)
            throw new IOException("Input error");
        else if (!uDao.getUser(request.getUserName()).getPassword().equals(request.getPassword()))
            throw new IOException("Input error");
    }
}
