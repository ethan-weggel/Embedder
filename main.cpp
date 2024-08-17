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

void train(Network* network, std::vector<double>* target) {
    double learningRate = 0.00000005;

    for (int i = 0; i < 5; i++) {
        std::vector<double> dist = network->forwardPropagate();
        // printVec(&dist);
        network->backwardPropagate((*target), learningRate);
        network->reset();
    }
}

int main() {

    int hiddenLayerSize = 5000;

    Reader reader = Reader();
    reader.setPath("data\\index.txt");

    reader.read();

    std::string data = reader.getData();

    std::unordered_map<std::string, Vector> vectors = vectorizeData(data, hiddenLayerSize);

    // this key will always be prsent after parsing
    // will allow network to be allocated and built
    Vector vector = vectors["index"];
    int layerSize = vector.getHotVector().size();

    Network network = Network({{layerSize},
                               {hiddenLayerSize}, 
                               {layerSize}});

    std::vector<double> the = {0, 0, 0, 0, 0, 1};
    std::vector<double> man = {0, 0, 0, 0, 1, 0};
    std::vector<double> ate = {0, 0, 1, 0, 0, 0};
    std::vector<double> an = {1, 0, 0, 0, 0, 0};
    std::vector<double> apple = {0, 1, 0, 0, 0, 0};

    for (int i = 0; i < 10; i++) {
    network.setNetwork(network.getInputLayer(), &vectors["The"]);
    train(&network, &man);

    network.setNetwork(network.getInputLayer(), &vectors["man"]);
    train(&network, &ate);

    network.setNetwork(network.getInputLayer(), &vectors["ate"]);
    train(&network, &an);

    network.setNetwork(network.getInputLayer(), &vectors["an"]);
    train(&network, &apple);

    network.setNetwork(network.getInputLayer(), &vectors["man"]);
    }

    std::cout << "Inference: " << std::endl;
    std::vector<double> dist = network.forwardPropagate();

    printVec(&dist);


    return 0;
}