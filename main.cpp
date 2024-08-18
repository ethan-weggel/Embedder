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
    double learningRate = 0.001;

    for (int i = 0; i < 300; i++) {
        std::vector<double> dist = network->forwardPropagate();
        // printVec(&dist);
        network->backwardPropagate((*target), learningRate);
        network->reset();
    }

    std::cout << "Epoch <" << *epochNum << "> Complete!" << std::endl;
    *epochNum += 1;
}

int main() {

    int hiddenLayerSize = 3;

    Reader reader = Reader();
    reader.setPath("data\\index.txt");

    Writer writer = Writer();
    writer.setPath("./output/");
    writer.setBaseFileName("vector");

    reader.read();

    std::string data = reader.getData();

    std::unordered_map<std::string, Vector> vectors = vectorizeData(data, hiddenLayerSize);

    // this key will always be prsent after parsing
    // will allow network to be allocated and built
    Vector vector = vectors["index"];
    int layerSize = vector.getHotVector().size();

    Network network = Network({{layerSize},
                               {hiddenLayerSize, hiddenLayerSize}, 
                               {layerSize}});

    std::vector<double> the =   {0, 0, 0, 0, 0, 1};
    std::vector<double> man =   {0, 0, 0, 0, 1, 0};
    std::vector<double> ate =   {0, 0, 1, 0, 0, 0};
    std::vector<double> an =    {1, 0, 0, 0, 0, 0};
    std::vector<double> apple = {0, 1, 0, 0, 0, 0};

    int epochNum = 0;

    for (int i = 0; i < 10; i++) {
        network.setNetwork(network.getInputLayer(), &vectors["The"]);
        train(&network, &man, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["man"]);
        train(&network, &ate, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["ate"]);
        train(&network, &an, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["an"]);
        train(&network, &apple, &epochNum);

        network.setNetwork(network.getInputLayer(), &vectors["man"]);
    }

    std::cout << "Inference: " << std::endl;
    std::vector<double> dist = network.forwardPropagate();

    printVec(&dist);
    
    for (const auto& pair : vectors) {
        std::string key = pair.first;
        Vector value = pair.second;

        writer.write(key, &value);
        writer.incrementIndex();
    }

    return 0;
}