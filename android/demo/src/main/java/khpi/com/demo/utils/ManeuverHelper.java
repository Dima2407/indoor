package khpi.com.demo.utils;

import khpi.com.demo.R;
import khpi.com.demo.model.Step;

public final class ManeuverHelper {

    public static int getManeuverIcon(String maneuver) {
        int icon;

        switch (maneuver) {
            case Step.MANEUVER_STRAIGHT:
                icon = R.drawable.straight_icn;
                break;
            case Step.MANEUVER_TURN_LEFT:
                icon = R.drawable.turn_left_icn;
                break;
            case Step.MANEUVER_TURN_RIGHT:
                icon = R.drawable.turn_right_icn;
                break;
            case Step.MANEUVER_FERRY_TRAIN:
                icon = R.drawable.ferry_train_icn_;
                break;
            case Step.MANEUVER_FORK_LEFT:
                icon = R.drawable.fork_left_icn_;
                break;
            case Step.MANEUVER_FORK_RIGHT:
                icon = R.drawable.fork_right_icn;
                break;
            case Step.MANEUVER_MERGE:
                icon = R.drawable.merge_icn_;
                break;
            case Step.MANEUVER_ROUNDABOUT_LEFT:
                icon = R.drawable.roundbout_left_icn_;
                break;
            case Step.MANEUVER_ROUNDABOUT_RIGHT:
                icon = R.drawable.roundbout_right_icn_;
                break;
            case Step.MANEUVER_TURN_SHARP_LEFT:
                icon = R.drawable.turn_sharp_left_icn;
                break;
            case Step.MANEUVER_TURN_SHARP_RIGHT:
                icon = R.drawable.turn_sharp_right_icn;
                break;
            case Step.MANEUVER_TURN_SLIGHT_LEFT:
                icon = R.drawable.turn_slight_left_icn;
                break;
            case Step.MANEUVER_TURN_SLIGHT_RIGHT:
                icon = R.drawable.turn_slight_right_icn;
                break;
            case Step.MANEUVER_UTURN_LEFT:
                icon = R.drawable.uturn_left_icn;
                break;
            case Step.MANEUVER_UTURN_RIGHT:
                icon = R.drawable.uturn_right_icn;
                break;
            default:
                icon = R.drawable.straight_icn;
                break;
        }

        return icon;
    }
}
