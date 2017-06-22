//
// Created by Igor Maschikevich on 6/22/2017.
//

#include "Acceltester.h"

namespace acceltester {

Document strimJson(string inFile)
{
    ifstream in(inFile);
    IStreamWrapper isw(in);
    Document document;
    document.ParseStream(isw);
    in.close();
    return document;
}


}
