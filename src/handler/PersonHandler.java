package handler;

import com.google.gson.Gson;
import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import encode_decode.Encoder;
import request.LoginRequest;
import result.LoginResult;
import result.PersonResult;
import result.PersonsResult;
import service.LoginService;
import service.PersonService;
import service.PersonsService;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;

public class PersonHandler implements HttpHandler {

    // Handles HTTP requests containing the "/games/list" URL path.
    // The "exchange" parameter is an HttpExchange object, which is
    // defined by Java.
    // In this context, an "exchange" is an HTTP request/response pair
    // (i.e., the client and server exchange a request and response).
    // The HttpExchange object gives the handler access to all of the
    // details of the HTTP request (Request type [GET or POST],
    // request headers, request body, etc.).
    // The HttpExchange object also gives the handler the ability
    // to construct an HTTP response and send it back to the client
    // (Status code, headers, response body, etc.).
    @Override
    public void handle(HttpExchange exchange) throws IOException {

        // This handler returns a list of "Ticket to Ride" games that
        // are (ficticiously) currently running in the server.
        // The game list is returned to the client in JSON format inside
        // the HTTP response body.
        // This implementation is clearly unrealistic, because it
        // always returns the same hard-coded list of games.
        // It is also unrealistic in that it accepts only one specific
        // hard-coded auth token.
        // However, it does demonstrate the following:
        // 1. How to get the HTTP request type (or, "method")
        // 2. How to access HTTP request headers
        // 3. How to return the desired status code (200, 404, etc.)
        //		in an HTTP response
        // 4. How to write JSON data to the HTTP response body
        // 5. How to check an incoming HTTP request for an auth token

        boolean success = false;

        try {
            // Determine the HTTP request type (GET, POST, etc.).
            // Only allow GET requests for this operation.
            // This operation requires a GET request, because the
            // client is "getting" information from the server, and
            // the operation is "read only" (i.e., does not modify the
            // state of the server).
            if (exchange.getRequestMethod().toLowerCase().equals("get")) {

                // Get the HTTP request headers
                Headers reqHeaders = exchange.getRequestHeaders();
                // Check to see if an "Authorization" header is present
                if (reqHeaders.containsKey("Authorization")) {
                    String authToken = reqHeaders.getFirst("Authorization");
                    String url = exchange.getRequestURI().toString();
                    Gson gson = new Gson();
                    if(url.equals("/person")) {
                        PersonsResult pResult = PersonsService.getPeople(authToken);
                        if(pResult.isSuccess()) {
                            exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
                            // Now that the status code and headers have been sent to the client,
                            // next we send the JSON data in the HTTP response body.
                            OutputStream respBody = Encoder.toJsonEncoded(pResult, exchange.getResponseBody());

                            respBody.close();
                            success = true;
                        }
                        else {
                            // Start sending the HTTP response to the client, starting with
                            // the status code and any defined headers.
                            exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                            // Now that the status code and headers have been sent to the client,
                            // next we send the JSON data in the HTTP response body.
                            OutputStream respBody = Encoder.toJsonEncoded(pResult, exchange.getResponseBody());

                            respBody.close();
                            success = true;
                        }
                    }
                    else {
                        String personID = getPersonID(url);

                        PersonResult pResult = PersonService.getPerson(personID, authToken);
                        if(pResult.isSuccess()) {
                            // Start sending the HTTP response to the client, starting with
                            // the status code and any defined headers.
                            exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
                            // Now that the status code and headers have been sent to the client,
                            // next we send the JSON data in the HTTP response body.
                            OutputStream respBody = Encoder.toJsonEncoded(pResult, exchange.getResponseBody());

                            respBody.close();
                            success = true;
                        }
                        else {
                            // Start sending the HTTP response to the client, starting with
                            // the status code and any defined headers.
                            exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                            // Now that the status code and headers have been sent to the client,
                            // next we send the JSON data in the HTTP response body.
                            OutputStream respBody = Encoder.toJsonEncoded(pResult, exchange.getResponseBody());

                            respBody.close();
                            success = true;
                        }
                    }

                }
            }

            if (!success) {
                // The HTTP request was invalid somehow, so we return a "bad request"
                // status code to the client.
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                // Since the client request was invalid, they will not receive the
                // list of games, so we close the response body output stream,
                // indicating that the response is complete.

                exchange.getResponseBody().close();
            }
        }
        catch (IOException e) {
            // Some kind of internal error has occurred inside the server (not the
            // client's fault), so we return an "internal server error" status code
            // to the client.
            exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
            // Since the server is unable to complete the request, the client will
            // not receive the list of games, so we close the response body output stream,
            // indicating that the response is complete.
            exchange.getResponseBody().close();

            // Display/log the stack trace
            e.printStackTrace();
        }
    }

    /*
        The writeString method shows how to write a String to an OutputStream.
    */
    private void writeString(String str, OutputStream os) throws IOException {
        OutputStreamWriter sw = new OutputStreamWriter(os);
        sw.write(str);
        sw.flush();
    }

    private String getPersonID(String url) {
        return url.substring(8);
    }
}
