//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//

#ifndef TESTTOOL_GLOBAL_H
#define TESTTOOL_GLOBAL_H

namespace unit {
    /// I know globals are evil, but I couldn't pass parameters to the test otherwise
    namespace global {
        extern int value;
    }
}

#endif //TESTTOOL_GLOBAL_H
