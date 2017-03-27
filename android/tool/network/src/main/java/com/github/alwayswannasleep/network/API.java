package com.github.alwayswannasleep.network;

import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.FloorModel;
import com.github.alwayswannasleep.models.IndoorMap;
import com.github.alwayswannasleep.models.IndoorPoint;
import com.github.alwayswannasleep.models.Poi;
import com.github.alwayswannasleep.network.model.Credentials;
import com.github.alwayswannasleep.network.model.DeleteIndoorMapRequest;
import com.github.alwayswannasleep.network.model.DeletePoiRequest;
import com.github.alwayswannasleep.network.model.GenericResponse;
import com.github.alwayswannasleep.network.model.LoginRequest;

import java.util.List;

import okhttp3.MultipartBody;
import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.DELETE;
import retrofit2.http.GET;
import retrofit2.http.Multipart;
import retrofit2.http.POST;
import retrofit2.http.PUT;
import retrofit2.http.Part;
import retrofit2.http.Path;

interface API {

    @POST("mobile/login")
    Call<GenericResponse<String>> login(@Body LoginRequest loginRequest);

    @POST("mobile/register")
    Call<GenericResponse<Credentials>> register(@Body Credentials credentials);

    @GET("mob/poi/{id}")
    Call<GenericResponse<Poi>> getPoi(@Path("id") long id);

    @GET("mob/poi")
    Call<GenericResponse<List<Poi>>> getPois();

    @PUT("mob/poi")
    Call<GenericResponse<Poi>> updatePoi(@Body Poi poi);

    @DELETE("mob/poi")
    Call<GenericResponse<Boolean>> deletePoi(@Body DeletePoiRequest request);

    @GET("mob/inpoint/{id}")
    Call<GenericResponse<IndoorPoint>> getInpoint(@Path("id") long id);

    @GET("mob/{mapId}/inpoints")
    Call<GenericResponse<List<IndoorPoint>>> getIndoorPointsByMapId(@Path("mapId") long id);

    @PUT("mob/inpoint")
    Call<GenericResponse<IndoorPoint>> updateIndoorPoint(@Body IndoorPoint point);

    @DELETE("mob/inpoint")
    Call<GenericResponse<Boolean>> deleteInpoint(@Body IndoorPoint point);

    @GET("mob/building/{id}")
    Call<GenericResponse<IndoorMap>> getMap(@Path("id") long id);

    @GET("mob/building")
    Call<GenericResponse<List<IndoorMap>>> getMaps();

    @GET("mob/{poiId}/buildings")
    Call<GenericResponse<List<IndoorMap>>> getMaps(@Path("poiId") long poiId);

    @Multipart
    @POST("mob/building/{id}")
    Call<GenericResponse<IndoorMap>> updateIndoorMap(@Path("id") long id, @Part MultipartBody.Part configFile, @Part MultipartBody.Part dataFile, @Part("floor") int floor);

    @DELETE("mob/building")
    Call<GenericResponse<Boolean>> deleteIndoorMap(@Body DeleteIndoorMapRequest request);

    @GET("mob{filePath}")
    Call<ResponseBody> loadFile(@Path(value = "filePath", encoded = true) String filePath);

    @PUT("mob/{floorId}/beacon")
    Call<GenericResponse<Object>> updateBeaconByFloor(@Path("floorId") Long id, @Body List<BeaconModel> beaconModels);

    @Multipart
    @POST("mob/floor/{floorId}")
    Call<GenericResponse<Object>> uploadFloor(@Path("floorId") Long id,
                                              @Part MultipartBody.Part configFile);

    @GET("mob/{mapId}/floor")
    Call<GenericResponse<List<FloorModel>>> loadFloorsByMapId(@Path("mapId") long mapId);
}
