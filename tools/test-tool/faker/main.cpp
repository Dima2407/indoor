/** Faker
 *  Created by  Oleksiy Grechnyev on 2/3/2017.
 *  Create fake measurement data for tester
 *
*/

#include "FakeEngine.h"
#include "PolyTrajectory.h"
#include <iostream>
#include <fstream>

/*void trajFun(){
    using namespace std;
    using namespace tester;

    PolyTrajectory traj;

    traj.readAuto("in_txyz_route.dat");

    double t1 = -1, t2 = 4;
    int nt = 101;

    ofstream out("temp.dat");

    for (int i=0; i<nt; i++){
        double t = t1 + (t2-t1) * i /(nt-1);

        out << t << " " << traj.trajectory(t) << endl;
    }

    out.close();

}*/


int main(){
    using namespace std;
    using namespace tester;
    using namespace faker;

    // Test the polyliine trajectory
    // trajFun();

    // Create a new fake engine
    FakeEngine engine;

    // Read config, beacons & beacon times
    engine.readData();

    // Run the actual calculation (create events)
    engine.run();

    // Write the results
    engine.writeResults();

    return 0;
}
