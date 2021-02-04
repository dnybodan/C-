package handler;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import encode_decode.Decoder;
import encode_decode.Encoder;
import request.LoginRequest;
import result.LoginResult;
import service.LoginService;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.nio.file.Files;

public class FileHandler implements HttpHandler {

    @Override
    public void handle(HttpExchange exchange) throws IOException {
        boolean success = false;

        try {
            if (exchange.getRequestMethod().toLowerCase().equals("get")) {
                String url = exchange.getRequestURI().toString();
                if(url == null || url.equals("/"))
                    url = "/index.html";
                String filePath = "web" + url;
                File file = new File(filePath);
                if(!file.exists()) {

                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_NOT_FOUND, 0);
                    String errorPath = "web\\HTML\\404.html";
                    File errorFile = new File(errorPath);
                    OutputStream respBody = exchange.getResponseBody();
                    Files.copy(errorFile.toPath(), respBody);
                    respBody.close();

                }
                exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
                OutputStream respBody = exchange.getResponseBody();
                Files.copy(file.toPath(), respBody);
                respBody.close();
                success = true;
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
