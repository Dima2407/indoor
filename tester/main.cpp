#include <iostream>

#include <bmath.h>

int main() {
    using namespace std;

    cout << "Goblins WON !" << endl;

    cout << "dist = " << BMath::get_distance(1, 3, 0.1) << endl;

    return 0;
}