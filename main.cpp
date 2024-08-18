#include "vector/vector.h"
#include "node/node.h"
#include "network/network.h"
#include "reader/reader.h"
#include "writer/writer.h"
#include "utilities/utilities.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <random>

void train(Network* network, std::vector<double>* target, int* epochNum) {
    double learningRate = 0.1;

    for (int i = 0; i < 3; i++) {
        std::vector<double> dist = network->forwardPropagate();
        // printVec(&dist);
        network->backwardPropagate((*target), learningRate);
        network->reset();
    }

    std::cout << "Epoch <" << *epochNum << "> Complete!" << std::endl;
    *epochNum += 1;
}

int main() {

    int hiddenLayerSize = 50;

    Reader reader = Reader();
    reader.setPath("data\\index.txt");

    Writer writer = Writer();
    writer.setPath("./pre-output/");
    writer.setBaseFileName("vector");

    reader.read();

    std::string data = reader.getData();

    std::unordered_map<std::string, Vector> vectors = vectorizeData(data, hiddenLayerSize);

    for (const auto& pair : vectors) {
        std::string key = pair.first;
        Vector value = pair.second;

        writer.write(key, &value);
        writer.incrementIndex();
    }

    // this key will always be prsent after parsing
    // will allow network to be allocated and built
    Vector vector = vectors["index"];
    int layerSize = vector.getHotVector().size();

    Network network = Network({{layerSize},
                               {hiddenLayerSize, hiddenLayerSize}, 
                               {layerSize}});

    std::vector<double> an     = {1, 0, 0, 0, 0, 0, 0};
    std::vector<double> apple  = {0, 1, 0, 0, 0, 0, 0};
    std::vector<double> ate    = {0, 0, 1, 0, 0, 0, 0};
    std::vector<double> index  = {0, 0, 0, 1, 0, 0, 0};
    std::vector<double> man    = {0, 0, 0, 0, 1, 0, 0};
    std::vector<double> pear   = {0, 0, 0, 0, 0, 1, 0};
    std::vector<double> the    = {0, 0, 0, 0, 0, 0, 1};


    int epochNum = 0;

    for (int i = 0; i < 100; i++) {
        network.setNetwork(network.getInputLayer(), &vectors["The"]);
        train(&network, &man, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["man"]);
        train(&network, &ate, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["ate"]);
        train(&network, &an, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["an"]);
        train(&network, &apple, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["The"]);
        train(&network, &man, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["man"]);
        train(&network, &ate, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["ate"]);
        train(&network, &an, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["a"]);
        train(&network, &pear, &epochNum);

    }

    
    for (const auto& pair : vectors) {
        std::string key = pair.first;
        Vector value = pair.second;

        writer.write(key, &value);
        writer.incrementIndex();
    }

    return 0;
}