package khpi.com.demo.core.bridge;

public interface NetBridge {

    void loadBuildingList();

    void loadInpointsByBuildingId(long i);

    void logIn(String login, String password);
}
