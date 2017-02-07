/** Faker
 *  Created by  Oleksiy Grechnyev on 2/3/2017.
 *  Create fake measurement data for tester
 *
*/

#include "FakeEngine.h"

int main(){
    using namespace std;
    using namespace tester;
    using namespace faker;


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
