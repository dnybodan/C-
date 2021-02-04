package handler;

import com.google.gson.Gson;
import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import encode_decode.Decoder;
import encode_decode.Encoder;
import request.LoginRequest;
import request.RegisterRequest;
import result.LoginResult;
import result.RegisterResult;
import service.LoginService;
import service.RegisterService;

import java.io.*;
import java.net.HttpURLConnection;

public class UserLoginHandler implements HttpHandler {

    @Override
    public void handle(HttpExchange exchange) throws IOException {


        boolean success = false;
        try {
            // Determine the HTTP request type (GET, POST, etc.).
            // Only allow POST requests for this operation.
            // This operation requires a POST request, because the
            // client is "posting" information to the server for processing.
            if (exchange.getRequestMethod().toLowerCase().equals("post")) {
                String str = readString(exchange.getRequestBody());
                Gson gson = new Gson();
                LoginRequest lRequest = gson.fromJson(str, LoginRequest.class);
                LoginResult lResult = LoginService.login(lRequest);
                if(lResult.isSuccess()) {
                    // Start sending the HTTP response to the client, starting with
                    // the status code and any defined headers.

                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
                    // Now that the status code and headers have been sent to the client,
                    // next we send the JSON data in the HTTP response body.

                    OutputStream respBody = Encoder.toJsonEncoded(lResult, exchange.getResponseBody());

                    respBody.close();
                    success = true;
                }
                else {
                    // Start sending the HTTP response to the client, starting with
                    // the status code and any defined headers.

                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                    // Now that the status code and headers have been sent to the client,
                    // next we send the JSON data in the HTTP response body.

                    OutputStream respBody = Encoder.toJsonEncoded(lResult, exchange.getResponseBody());

                    respBody.close();
                    success = true;
                }
            }

            if (!success) {
                // The HTTP request was invalid somehow, so we return a "bad request"
                // status code to the client.
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                // We are not sending a response body, so close the response body
                // output stream, indicating that the response is complete.
                exchange.getResponseBody().close();
            }
        }
        catch (IOException e) {
            // Some kind of internal error has occurred inside the server (not the
            // client's fault), so we return an "internal server error" status code
            // to the client.
            exchange.sendResponseHeaders(HttpURLConnection.HTTP_SERVER_ERROR, 0);
            // We are not sending a response body, so close the response body
            // output stream, indicating that the response is complete.
            exchange.getResponseBody().close();

            // Display/log the stack trace
            e.printStackTrace();
        }
    }

    private String readString(InputStream is) throws IOException {
        StringBuilder sb = new StringBuilder();
        InputStreamReader sr = new InputStreamReader(is);
        char[] buf = new char[1024];
        int len;
        while ((len = sr.read(buf)) > 0) {
            sb.append(buf, 0, len);
        }
        return sb.toString();
    }

}
