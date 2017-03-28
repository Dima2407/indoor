package khpi.com.demo.ui.launcher;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;

import khpi.com.demo.R;
import khpi.com.demo.model.Floor;
import khpi.com.demo.ui.fragment.FloorsFragment;
import khpi.com.demo.ui.fragment.IndoorCameraFragment;
import khpi.com.demo.ui.fragment.IndoorMap2DFragment;
import khpi.com.demo.ui.fragment.BuildingsFragment;

public final class Launcher {

    private final FragmentManager fragmentManager;
    private final int fragmentContainer;

    public Launcher(FragmentManager fragmentManager) {
        this.fragmentManager = fragmentManager;
        this.fragmentContainer = R.id.fragment_container;
    }

    private void launch(Fragment fragment) {
        launch(fragment, fragmentManager);
    }

    private void launch(Fragment fragment, FragmentManager fragmentManager) {
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        fragmentTransaction.replace(fragmentContainer, fragment);
        fragmentTransaction.commitAllowingStateLoss();
    }

    public void launchIndoorMapsFragment() {
        launch(new BuildingsFragment());
    }

    public void launchFloorFragment(){
        launch(new FloorsFragment());
    }

    public void launchIndoorMapFragment(Floor floor) {
        launch(IndoorMap2DFragment.makeInstance(floor));
    }

    public void launchIndoorCameraFragment(Floor map) {
        launch(IndoorCameraFragment.makeInstance(map));
    }
}
