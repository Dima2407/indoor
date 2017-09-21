//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include <iostream>
#include <vector>

// This includes everything you need
#include "Navigator.h"

// There are a few namespaces in the librrary
using namespace std;
using namespace Navigator::Accel::AngleFilt;
using namespace Navigator::Math::Filter;


struct YPR{
    double y, p, r;
};


int main()
{
    cout << "Maria Traydor !!!" << endl;

    AngleCorrect ac(0.0, 1);

    vector<YPR> in{
            {-201.0, -202.0, -203.0},
    };

    for (YPR t : in) {
        ac.correct(t.y, t.p, t.r);
        cout << "Y = " << t.y << " , P = " << t.p << " , R = " << t.r << endl;
    }

    return 0;
}