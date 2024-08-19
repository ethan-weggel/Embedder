#include "vector/vector.h"
#include "node/node.h"
#include "network/network.h"
#include "reader/reader.h"
#include "writer/writer.h"
#include "utilities/utilities.h"
#include "disbatcher/disbatcher.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <random>

void train(Network* network, int* epochNum) {
    double learningRate = 0.1;

    for (int i = 0; i < 100; i++) {
        std::vector<double> dist = network->forwardPropagate();
        // printVec(&dist);
        network->backwardPropagate(learningRate);
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

    Disbatcher disbatcher = Disbatcher();
    disbatcher.setData(data);
    disbatcher.parseData();
    disbatcher.parseBatches();

    std::unordered_map<std::string, Vector> vectors = vectorizeData(data, hiddenLayerSize);
    disbatcher.setVectors(&vectors);

    for (const auto& pair : vectors) {
        std::string key = pair.first;
        Vector value = pair.second;

        writer.write(key, &value);
        writer.incrementIndex();
    }

    // this key will always be prsent after parsing
    // will allow network to be allocated and built
    Vector vector = vectors["index\nThe"];
    int layerSize = vector.getHotVector().size();

    Network network = Network({{layerSize},
                               {hiddenLayerSize, hiddenLayerSize}, 
                               {layerSize}});

    int epochNum = 0;

    // disbating each sentence, training
    for (int i = 0; i < 3; i++) {
        for (std::vector<std::string> substringBatch : disbatcher.getSubStrings()) {
            disbatcher.disbatch(&network, substringBatch);
            train(&network, &epochNum);
        }
    } 

    writer.setPath("./output/");
    writer.setBaseFileName("vector");
    writer.setIndex(0);
    for (const auto& pair : vectors) {
        std::string key = pair.first;
        Vector value = pair.second;

        writer.write(key, &value);
        writer.incrementIndex();
    }

    return 0;
}