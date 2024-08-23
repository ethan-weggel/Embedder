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

int main() {
    int hiddenLayerSize = 50;

    Reader reader = Reader();
    reader.setPath("data\\test.txt");

    Writer writer = Writer();
    writer.setPath("./pre_output/");
    writer.setBaseFileName("vector");

    reader.read();

    std::string data = reader.getData();

    Disbatcher disbatcher = Disbatcher();
    disbatcher.setData(data);
    disbatcher.parseData();
    disbatcher.parseBatches();

    std::unordered_map<std::string, Vector> vectors = vectorizeData(data, 50);
    disbatcher.setVectors(&vectors);

    for (const auto& pair : vectors) {
        std::string key = pair.first;
        Vector value = pair.second;

        writer.write(key, &value);
        writer.incrementIndex();
    }

    // this key will always be prsent after parsing
    // will allow network to be allocated and built
    Vector vector = vectors["man"];
    int layerSize = vector.getHotVector().size();

    Network network = Network({{layerSize},
                               {50}, 
                               {layerSize}});


    int epochNum = 0;
    int totalEpochs = 100;

    for (int i = 0; i < totalEpochs; i++) {

        for (const auto& substringBatch : disbatcher.getSubStrings()) {
            // std::cout << substringBatch.size() << std::endl;
            disbatcher.disbatch(&network, substringBatch, 0.001, epochNum);
        }
        epochNum++;

        std::cout << "Epoch <" << i << "> Complete!" << std::endl;
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