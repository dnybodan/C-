package encode_decode;

import com.google.gson.Gson;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class Encoder {

    public static OutputStream toJsonEncoded(Object o, OutputStream os) throws IOException {
        Gson gson = new Gson();
        writeString(gson.toJson(o), os);
        return os;
    }

    /*
        The writeString method shows how to write a String to an OutputStream.
    */
    public static void writeString(String str, OutputStream os) throws IOException {
        OutputStreamWriter sw = new OutputStreamWriter(os);
        sw.write(str);
        sw.flush();
    }
}
