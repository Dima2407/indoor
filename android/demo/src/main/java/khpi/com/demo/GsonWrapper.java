package khpi.com.demo;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

/**
 * Created by kit on 9/28/16.
 */

public class GsonWrapper {

    private static final String DATE_TIME_PATTERN = "yyyy-MM-dd'T'HH:mm:ss.SSS";
    private static Gson gson;


    public static Gson getGson(){
        if(gson==null){
            gson = new GsonBuilder()
                    .setDateFormat(DATE_TIME_PATTERN)
                    .excludeFieldsWithoutExposeAnnotation()
                    .create();
        }
        return gson;
    }
}
