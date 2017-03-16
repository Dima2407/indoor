package khpi.com.demo.net;

import khpi.com.demo.core.bridge.DbBridge;
import khpi.com.demo.core.bridge.NetBridge;

public final class NetFacade implements NetBridge {

    private final PointsManager pointsManager;

    public NetFacade(DbBridge dbBridge, String url) {
        API api = new RetrofitHelper(url).getApi();

        pointsManager = new PointsManager(api, dbBridge);
    }

    @Override
    public void loadBuildingList() {
        pointsManager.loadBuildings();
    }

    @Override
    public void loadInpointsByBuildingId(long id) {
        pointsManager.loadInpointsByBuildingId(id);
    }

    @Override
    public void logIn(String login, String password) {
        pointsManager.logIn(login, password);
    }
}
