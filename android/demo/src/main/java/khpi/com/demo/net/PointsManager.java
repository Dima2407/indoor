package khpi.com.demo.net;

import android.util.Log;

import khpi.com.demo.core.bridge.DbBridge;
import khpi.com.demo.net.model.BuildingList;
import khpi.com.demo.net.model.InpointList;
import khpi.com.demo.net.model.LoginModel;
import khpi.com.demo.net.model.RegistrationModel;

import java.util.HashMap;
import java.util.Map;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

final class PointsManager {
    private static final String TAG = PointsManager.class.getSimpleName();

    private final API api;
    private final DbBridge dbBridge;
    private LoginModel loginModel = LoginModel.getLoginModel();

    PointsManager(API api, DbBridge dbBridge) {
        this.api = api;
        this.dbBridge = dbBridge;
    }

    void registerUser(String login, String password){
        Log.d(TAG, "registerUser: ");
        RegistrationModel user = new RegistrationModel(login, password);
        api.addNewUser(user).enqueue(new Callback<Object>() {
            @Override
            public void onResponse(Call<Object> call, Response<Object> response) {
                if (!response.isSuccessful()) {
                    Log.e(TAG, response.message() + " " + response.code());
                    return;
                }
                Log.d(TAG, "register success");
            }

            @Override
            public void onFailure(Call<Object> call, Throwable t) {
                Log.d(TAG, "onFailure: error");
            }
        });
    }

    void logIn(final String login, String password){
        Log.d(TAG, "logIn: ");

        api.loginUser(new RegistrationModel(login, password)).enqueue(new Callback<LoginModel>() {
            @Override
            public void onResponse(Call<LoginModel> call, Response<LoginModel> response) {
                if (!response.isSuccessful()) {
                    Log.e(TAG, response.message() + " " + response.code());
                    return;
                }
                loginModel.getLoginModel().setToken(response.body().getToken());
                loadBuildings();
                Log.d(TAG, " login success with token " + loginModel.getToken());
            }

            @Override
            public void onFailure(Call<LoginModel> call, Throwable t) {
                Log.d(TAG, "onFailure: error");
            }
        });
    }


    void loadBuildings(){
        Log.d(TAG, "load maps");
        Map<String, String> map = new HashMap<>();
        String s = loginModel.getToken();
        map.put("Authorization", loginModel.getToken());
        api.getAllBuildings(map).enqueue(new Callback<BuildingList>() {
            @Override
            public void onResponse(Call<BuildingList> call, Response<BuildingList> response) {
                Log.d(TAG, "onResponse");
                if (!response.isSuccessful()) {
                    Log.e(TAG, response.message() + " " + response.code());
                    return;
                }
                dbBridge.saveBuildings(response.body().getData());
            }

            @Override
            public void onFailure(Call<BuildingList> call, Throwable t) {
                Log.e(TAG, t.getMessage(), t);
            }

        });
        return ;
    }

    public void loadInpointsByBuildingId(long id) {
        Map<String, String> map = new HashMap<>();
        map.put("Authorization", loginModel.getToken());
        api.getAllInpointsByBuildingId(map, id).enqueue(new Callback<InpointList>() {
            @Override
            public void onResponse(Call<InpointList> call, Response<InpointList> response) {
                if (!response.isSuccessful()) {
                    Log.e(TAG, response.message() + " " + response.code());
                    return;
                }
                dbBridge.saveInpoinrs(response.body().getData());
            }

            @Override
            public void onFailure(Call<InpointList> call, Throwable t) {
                Log.e(TAG, t.getMessage(), t);
            }
        });
    }
}
