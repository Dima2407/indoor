package khpi.com.demo.ui.opengl;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.drawable.Drawable;
import android.opengl.GLUtils;
import android.support.annotation.DrawableRes;
import android.support.v4.content.ContextCompat;

import khpi.com.demo.R;
import khpi.com.demo.model.Point;

import java.lang.ref.WeakReference;
import java.util.HashMap;
import java.util.Map;

import static android.opengl.GLES20.GL_NEAREST;
import static android.opengl.GLES20.GL_TEXTURE_2D;
import static android.opengl.GLES20.GL_TEXTURE_MAG_FILTER;
import static android.opengl.GLES20.GL_TEXTURE_MIN_FILTER;
import static android.opengl.GLES20.glBindTexture;
import static android.opengl.GLES20.glGenTextures;
import static android.opengl.GLES20.glTexParameteri;

public final class TextureManager {

    private final WeakReference<Context> context;
    private final Map<String, Integer> texturesMap;

    public TextureManager(final Context context) {
        this.context = new WeakReference<>(context);
        texturesMap = new HashMap<>();
    }

    public int loadTexture(@DrawableRes int texture, String name) {
        if (texturesMap.containsKey(name)) {
            return texturesMap.get(name);
        }

        final BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;

        final Bitmap bitmap = BitmapFactory.decodeResource(context.get().getResources(), texture, options);

        int value = bindTexture(bitmap);
        texturesMap.put(name, value);

        return value;
    }

    public int generatePoiTexture(final Point point, final float distance) {
        Bitmap bitmap = Bitmap.createBitmap(400, 200, Bitmap.Config.ARGB_4444);
        Canvas canvas = new Canvas(bitmap);
        bitmap.eraseColor(0);

        Drawable background = ContextCompat.getDrawable(context.get(), R.drawable.table_1_bg);
        background.setBounds(0, 0, bitmap.getWidth(), bitmap.getHeight());
        background.draw(canvas);

        Bitmap icon = BitmapFactory.decodeResource(context.get().getResources(), R.drawable.map_point_icn);

        RectF rectF = new RectF(40, 10, 100, 80);
        canvas.drawBitmap(icon, null, rectF, null);

        Paint paint = new Paint(Paint.ANTI_ALIAS_FLAG);
        paint.setTextSize(24);
        paint.setColor(Color.DKGRAY);

        canvas.drawText(point.getTitle(), 140, 50, paint);
        canvas.drawText("Distance: " + (int) distance + " m", 40, 130, paint);

        return bindTexture(bitmap);
    }

    private int bindTexture(Bitmap bitmap) {
        final int[] textureHandle = new int[1];
        glGenTextures(1, textureHandle, 0);

        int texturePointer = textureHandle[0];
        if (texturePointer == 0) {
            throw new RuntimeException("Error loading texture.");
        }

        glBindTexture(GL_TEXTURE_2D, texturePointer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        GLUtils.texImage2D(GL_TEXTURE_2D, 0, bitmap, 0);

        bitmap.recycle();

        return texturePointer;
    }

    public int generateRoadTexture(final float distance) {
        Bitmap bitmap = Bitmap.createBitmap(500, 500, Bitmap.Config.ARGB_4444);
        Canvas canvas = new Canvas(bitmap);
        bitmap.eraseColor(0);

        Bitmap road = BitmapFactory.decodeResource(context.get().getResources(), R.drawable.table);
        canvas.drawBitmap(road, null, new Rect(240, 0, 260, 500), null);

        return bindTexture(bitmap);
    }
}
