package khpi.com.demo.routing;

import android.graphics.PointF;
import android.os.Parcel;
import android.os.Parcelable;

import java.util.UUID;

public class FloorModel implements Parcelable {

    private double pixelSize;

    private double width;

    private double height;

    private String imgPath;

    private String maskPath;

    private String mapUid;

    private String name;
    private String description;

    private String calibrationFilePath;

    private PointF destination;

    public String getCalibrationFilePath() {
        return calibrationFilePath;
    }

    public void setCalibrationFilePath(String calibrationFilePath) {
        this.calibrationFilePath = calibrationFilePath;
    }

    public double getPixelSize() {
        return pixelSize;
    }

    public void setPixelSize(double pixelSize) {
        this.pixelSize = pixelSize;
    }

    public double getWidth() {
        return width;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public String getImgPath() {
        return imgPath;
    }

    public void setImgPath(String imgPath) {
        this.imgPath = imgPath;
    }

    public String getMapUid() {
        return mapUid;
    }

    public void setMapUid(String mapUid) {
        this.mapUid = mapUid;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public PointF getDestination() {
        return destination;
    }

    public void setDestination(PointF destination) {
        this.destination = destination;

    }

    public String getMaskPath() {
        return maskPath;
    }

    public void setMaskPath(String maskPath) {
        this.maskPath = maskPath;
    }


    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public FloorModel() {
        mapUid = UUID.randomUUID().toString();
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel parcel, int i) {
        parcel.writeDouble(pixelSize);
        parcel.writeDouble(width);
        parcel.writeDouble(height);
        parcel.writeString(imgPath);
        parcel.writeString(mapUid);
        parcel.writeString(name);
        parcel.writeString(description);
        parcel.writeString(maskPath);
    }

    private FloorModel(Parcel parcel) {
        pixelSize = parcel.readDouble();
        width = parcel.readDouble();
        height = parcel.readDouble();
        imgPath = parcel.readString();
        mapUid = parcel.readString();
        name = parcel.readString();
        description = parcel.readString();
        maskPath = parcel.readString();
    }

    public static Creator<FloorModel> CREATOR = new Creator<FloorModel>() {
        @Override
        public FloorModel createFromParcel(Parcel parcel) {
            return new FloorModel(parcel);
        }

        @Override
        public FloorModel[] newArray(int i) {
            return new FloorModel[i];
        }
    };
}
