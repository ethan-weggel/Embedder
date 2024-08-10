#include "vector.h"
#include "node.h"
#include <vector>
#include <iostream>

int main() {
    // Vector vec = Vector();

    // std::vector<std::string> vecString = {"indexing", "test", "<EOS>"};
    // std::vector<double> vecDouble = {12.0, 13.8, -32.07};

    // vec.setStringVector(vecString);
    // vec.setDoubleVector(vecDouble);

    // vec.printString();
    // vec.printDouble();

    std::vector<Node*> nodes;

    for (int i = 0; i < 10; i++) {
        nodes.push_back(new Node());
    }

    for (Node* node : nodes) {
        node->print();
    }

    return 0;
}