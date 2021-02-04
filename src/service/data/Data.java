package service.data;

import com.google.gson.Gson;

import java.io.*;
import java.util.List;

public class Data {

    public static void getData(List<String> fnames, List<String> mnames, List<String> snames, List<Location> locations) throws IOException {
        try {
            Gson gson = new Gson();
            File file = new File("json//fnames.json");
            FileReader reader = new FileReader(file);
            FemaleNames femaleNames = gson.fromJson(reader, FemaleNames.class);

            file = new File("json//mnames.json");
            reader = new FileReader(file);
            MaleNames maleNames = gson.fromJson(reader, MaleNames.class);
            file = new File("json//snames.json");
            reader = new FileReader(file);
            SurNames surNames = gson.fromJson(reader, SurNames.class);
            file = new File("json//locations.json");
            reader = new FileReader(file);
            Locations locations1 = gson.fromJson(reader, Locations.class);
            fnames.addAll(femaleNames.getData());
            snames.addAll(surNames.getData());
            mnames.addAll(maleNames.getData());
            locations.addAll(locations1.getData());


        } catch(FileNotFoundException e) {
            e.printStackTrace();
            System.out.println("Problem reading in json files");
            throw new IOException("there was an error getting fake family information");
        }
    }

    public static String generateID(String randString) {
        StringBuilder ID = new StringBuilder();
        String charString = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                + "0123456789"
                + "abcdefghijklmnopqrstuvxyz";

        for (int i = 0; i < 20; i++) {

            int index = (int)(charString.length()
                    * Math.random() * (int)randString.charAt(randString.length() - 1) % charString.length() - 1);

            ID.append(charString.charAt(index));
        }
        return ID.toString();
    }
}



