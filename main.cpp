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

    int hiddenLayerSize = 5;

    Reader reader = Reader();
    reader.setPath("data\\index.txt");

    reader.read();

    std::string data = reader.getData();

    std::unordered_map<std::string, Vector> vectors = vectorizeData(data, hiddenLayerSize);

    // this key will always be prsent after parsing
    // will allow network to be allocated and built
    Vector vector = vectors["index"];

    std::vector<std::vector<double>*> weights = vector.getWeightsVector();

    int layerSize = vector.getHotVector().size();

    Network network = Network({{layerSize},
                               {hiddenLayerSize}, 
                               {layerSize}});

    network.setNetwork(network.getInputLayer(), &vector);
    network.print();

    std::vector<double> dist = network.forwardPropagate();
    
    printVec(&dist);



    return 0;
}