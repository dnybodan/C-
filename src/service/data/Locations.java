package service.data;

import java.util.ArrayList;
import java.util.List;

public class Locations {
    private List<Location> data;

    public Locations(){
        data = new ArrayList<>();
    }

    public java.util.List<Location> getData() {
        return data;
    }

    @Override
    public String toString() {
        return "Locations{" +
                "data=" + data +
                '}';
    }
}
