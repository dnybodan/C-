package handler;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import encode_decode.Encoder;
import result.ClearResult;
import result.FillResult;
import service.ClearService;
import service.FillService;

import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;

public class FillHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        boolean success = false;

        try {
            // Determine the HTTP request type (GET, POST, etc.).
            // Only allow POST requests for this operation.
            // This operation requires a POST request, because the
            // client is "posting" information to the server for processing.
            if (exchange.getRequestMethod().toLowerCase().equals("post")) {
                String url = exchange.getRequestURI().toString();
                String userName = getUserName(url);
                int numGenerations = getNumGenerations(url);
                FillResult fResult = FillService.fill(userName, numGenerations);
                if(fResult.isSuccess()) {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                    OutputStream respBody = Encoder.toJsonEncoded(fResult, exchange.getResponseBody());

                    respBody.close();
                    success = true;
                }
                else {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);

                    OutputStream respBody = Encoder.toJsonEncoded(fResult, exchange.getResponseBody());

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
    private String getUserName(String url) {
        //takes the /fill/ off of the string
        String s = url.substring(6);
        int slashIndex = 0;
        int endIndex = s.length();
        int i = 0;
        for(char c: s.toCharArray()) {
            if(c == '/') {
                endIndex = i;
            }
            i++;
        }
        return s.substring(0, endIndex);
    }
    private int getNumGenerations(String url) {
        String s = url.substring(6);
        int firstSlash = 0;
        int i = 0;
        for(char c: s.toCharArray()) {
            if(c=='/') {
                firstSlash = i;
            }
            i++;
        }
        String num = s.substring((firstSlash + 1));
        if(num.matches("[0-9]+"))
            return (Integer.parseInt(num));
        else
            return 4;
    }
}
