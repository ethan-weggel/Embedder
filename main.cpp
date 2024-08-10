#include "vector.h"
#include <vector>
#include <iostream>

int main() {
    Vector vec = Vector();

    std::vector<std::string> vecString = {"indexing", "test", "<EOS>"};
    std::vector<double> vecDouble = {12.0, 13.8, -32.07};

    vec.setStringVector(vecString);
    vec.setDoubleVector(vecDouble);

    vec.printString();
    vec.printDouble();

    return 0;
}