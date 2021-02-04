package handler;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import encode_decode.Decoder;
import encode_decode.Encoder;
import request.LoginRequest;
import result.ClearResult;
import result.LoginResult;
import service.ClearService;
import service.LoginService;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;

public class ClearHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {
        boolean success = false;

        try {
            // Determine the HTTP request type (GET, POST, etc.).
            // Only allow POST requests for this operation.
            // This operation requires a POST request, because the
            // client is "posting" information to the server for processing.
            if (exchange.getRequestMethod().toLowerCase().equals("post")) {
                ClearResult cResult = ClearService.clear();
                if(cResult.isSuccess()) {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);

                    OutputStream respBody = Encoder.toJsonEncoded(cResult, exchange.getResponseBody());

                    respBody.close();
                    success = true;
                }
                else {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);

                    OutputStream respBody = Encoder.toJsonEncoded(cResult, exchange.getResponseBody());

                    respBody.close();
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
}
