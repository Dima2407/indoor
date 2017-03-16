package khpi.com.demo.ui.opengl;

import android.content.Context;

final class IndoorRenderer extends OutdoorRenderer {

    public IndoorRenderer(final Context context) {
        super(context);

        setUseDynamicScaling(true);
        setUseMeshing(false);
        setUseConverting(false);
    }
}