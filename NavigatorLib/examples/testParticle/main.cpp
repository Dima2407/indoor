//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

#include <iostream>
#include <cmath>
#include <cstdio>

#include "Navigator.h"

int main(){
    using namespace std;
    using namespace Navigator::Particles;
    using namespace Navigator::Math;

    cout << "Goblins WON !" << endl;

    Position2D p1;
    p1 = {2,3};
    Position2D p2;
    p2 = {4,5};
    p1 += p2;
    printf("x = %lf , y = %lf \n", p1.x, p1.y);

    return 0;
}