#include "vector/vector.h"
#include "node/node.h"
#include "network/network.h"
#include "reader/reader.h"
#include "utilities/utilities.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <random>

int main() {

    Reader reader = Reader();
    reader.setPath("data\\index.txt");

    reader.read();

    std::string data = reader.getData();

    std::unordered_map<std::string, Vector> dataLookup = vectorizeData(data, 5);

    // this key will always be prsent after parsing
    // will allow network to be allocated and built
    Vector vector = dataLookup["index"];

    std::vector<std::vector<double>*> weights = vector.getWeightsVector();

    int layerSize = static_cast<int>(vector.getHotVector().size());

    Network network = Network({{layerSize},
                               {5, 5}, 
                               {layerSize}});

    // network.setNetwork(network.getInputLayer(), &vector);
    // network.print();
    // network.forwardPropagate();
    // network.print();

    // network.setNetwork(network.getInputLayer(), &dataLookup["zygote"]);
    // network.print();
    // network.forwardPropagate();
    // network.print();

    // network.setNetwork(network.getInputLayer(), &vector);
    // network.print();

    (*network.getHiddenLayer(1))[0]->print();

    return 0;
}