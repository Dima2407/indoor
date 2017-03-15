package khpi.com.demo.net.model;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class LoginModel {

    public static LoginModel loginModel;

    public static LoginModel getLoginModel(){
        if (loginModel == null)
            loginModel = new LoginModel();
        return loginModel;
    }

    @SerializedName("data")
    @Expose
    private String token;

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }
}
