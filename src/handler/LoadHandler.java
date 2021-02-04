package handler;

import com.google.gson.Gson;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import encode_decode.Encoder;
import request.LoadRequest;
import request.RegisterRequest;
import result.LoadResult;
import result.RegisterResult;
import service.LoadService;
import service.RegisterService;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;

public class LoadHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange exchange) throws IOException {

        boolean success = false;

        try {

            if (exchange.getRequestMethod().toLowerCase().equals("post")) {
                String str = readString(exchange.getRequestBody());
                Gson gson = new Gson();
                LoadRequest lRequest = gson.fromJson(str, LoadRequest.class);
                LoadResult lResult = LoadService.load(lRequest);
                if(lResult.isSuccess()) {
                    // Start sending the HTTP response to the client, starting with
                    // the status code and any defined headers.
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
                    // Now that the status code and headers have been sent to the client,
                    // next we send the JSON data in the HTTP response body.
                    // Get the response body output stream.
                    OutputStream respBody = Encoder.toJsonEncoded(lResult, exchange.getResponseBody());
                    // Close the output stream.  This is how Java knows we are done
                    // sending data and the response is complete/
                    respBody.close();
                    success = true;
                }
                else {
                    exchange.sendResponseHeaders(HttpURLConnection.HTTP_BAD_REQUEST, 0);
                    // Now that the status code and headers have been sent to the client,
                    // next we send the JSON data in the HTTP response body.
                    // Get the response body output stream.
                    OutputStream respBody = Encoder.toJsonEncoded(lResult, exchange.getResponseBody());
                    // Close the output stream.  This is how Java knows we are done
                    // sending data and the response is complete/
                    respBody.close();
                    success = true;
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
