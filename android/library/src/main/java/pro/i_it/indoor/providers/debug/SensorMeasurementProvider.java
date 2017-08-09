package pro.i_it.indoor.providers.debug;

import android.content.Context;
import android.os.Handler;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import pro.i_it.indoor.R;
import pro.i_it.indoor.events.MeasurementEvent;
import pro.i_it.indoor.masks.ResourcesMaskTableFetcher;
import pro.i_it.indoor.providers.MeasurementProvider;
import pro.i_it.indoor.providers.MeasurementTransfer;


public class SensorMeasurementProvider extends MeasurementProvider {

    private final Context context;
    private final Handler handler;
    private int currentIndex = 0;

    public SensorMeasurementProvider(Context context, MeasurementTransfer transfer) {
        super(transfer);
        this.context = context;
        this.handler = new Handler();
    }

    @Override
    public void start() {
        final JSONArray accelerometer = loadJsonData(R.raw.accelerometer);
        final JSONArray angles = loadJsonData(R.raw.angles);
        final long start  = System.currentTimeMillis();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                JSONObject acc = accelerometer.optJSONObject(currentIndex);
                JSONObject angle = angles.optJSONObject(currentIndex);
                if (acc != null && angle != null) {
                    float x = (float) acc.optDouble("x");
                    float y = (float) acc.optDouble("y");
                    float z = (float) acc.optDouble("z");
                    float azimuth = (float) angle.optDouble("yaw");
                    float pitch = (float) angle.optDouble("pitch");
                    float roll = (float) angle.optDouble("roll");
                    //if((System.currentTimeMillis() - start) >= 5000) {
                        transfer.deliver(MeasurementEvent.createFromSensor(x, y, z, azimuth, pitch, roll));
                    //}
                    handler.postDelayed(this, 25);
                    currentIndex++;
                }
            }
        }, 25);
    }

    @Override
    public void stop() {

    }

    private JSONArray loadJsonData(int code) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(context.getResources()
                .openRawResource(code)))) {
            StringBuilder data = new StringBuilder();
            String str;
            while ((str = br.readLine()) != null) {
                data.append(str);
            }
            return new JSONArray(data.toString());
        } catch (Exception e) {
            Log.e(ResourcesMaskTableFetcher.class.getSimpleName(), "fetchMaskTable: ", e);
        }
        return null;

    }
}
