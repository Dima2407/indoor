package pro.i_it.indoor.masks;

import android.content.res.Resources;
import android.util.Log;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class ResourcesMaskTableFetcher implements MaskTableFetcher {

    private final Resources resources;
    private final int tableResource;
    private int [] maskArray;

    public ResourcesMaskTableFetcher(Resources resources, int tableResource) {
        this.resources = resources;
        this.tableResource = tableResource;
    }

    @Override
    public int[] fetchMaskTable() {
        if(maskArray != null){
            return maskArray;
        }
        List<Integer> maskList = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new InputStreamReader(resources
                .openRawResource(tableResource)))) {
            String str;
            while ((str = br.readLine()) != null) {
                maskList.add(Integer.valueOf(str.trim()));
            }
        } catch (Exception e) {
            Log.e(ResourcesMaskTableFetcher.class.getSimpleName(), "fetchMaskTable: " , e);
        }
        maskArray = new int[maskList.size()];
        for (int i = 0; i < maskArray.length; i++) {
            maskArray[i] = maskList.get(i);
        }
        return maskArray;
    }
}
