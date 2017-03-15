package khpi.com.demo.net;

import khpi.com.demo.model.Building;
import khpi.com.demo.model.Inpoint;
import khpi.com.demo.net.model.BuildingList;
import khpi.com.demo.net.model.InpointList;
import khpi.com.demo.net.model.LoginModel;
import khpi.com.demo.net.model.RegistrationModel;

import java.util.List;
import java.util.Map;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.HeaderMap;
import retrofit2.http.Headers;
import retrofit2.http.POST;
import retrofit2.http.Path;
import retrofit2.http.Query;

interface API {

    @POST("mobile/register")
    @Headers({
            "Content-Type:application/json",
            "Cache-Control:no-cache"
    })
    Call<Object> addNewUser(@Body RegistrationModel user);


    @Headers({
            "Content-Type:application/json",
            "Cache-Control:no-cache"
    })
    @POST("mobile/login")
    Call<LoginModel> loginUser(@Body RegistrationModel user);


    @Headers({
            "Content-Type:application/json",
            "Cache-Control:no-cache"
    })
    @GET("mob/inpoint")
    Call<List<Inpoint>> getAllInpoints(@HeaderMap Map<String, String> map);


    @Headers({
            "Content-Type:application/json",
            "Cache-Control:no-cache"
    })
    @GET("/mob/{buildingId}/map_inpoint")
    Call<InpointList> getAllInpointsByBuildingId(@HeaderMap Map<String, String> map, @Path("buildingId") long buildingId);


    @Headers({
            "Content-Type:application/json",
            "Cache-Control:no-cache"
    })
    @GET("/mob/building/{buildingId}")
    Call<Building> getBuildingById(@HeaderMap Map<String, String> map, @Path("buildingId") long buildingId);


    @Headers({
            "Content-Type:application/json",
            "Cache-Control:no-cache"
    })
    @GET("/mob/building")
    Call<BuildingList> getAllBuildings(@HeaderMap Map<String, String> map);


    @Headers({
            "Content-Type:application/json",
            "Cache-Control:no-cache"
    })
    @GET("/mob/{poiId}/building")
    Call<List<Building>> getAllBuildingsByPoiId(@HeaderMap Map<String, String> map, @Path("poiId") long poiId);


    @GET("/api/v1/inpoints?gps_lon=0&gps_lat=0&radius=5")
    Call<List<Inpoint>> getInpointsGeoPosition(@Query("gps_lon") double lon,
                                               @Query("gps_lat") double lat,
                                               @Query("radius") int radius);

}
