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

    // Read in_beacons.dat
    FakeEngine::readBeacons();
    // Read in_faker.dat
    FakeEngine::readInput();

    // Run the actual calculation (create Events)
    FakeEngine::run();

    return 0;
}
