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

    // std::cout << disbatcher.getBatches().size() << std::endl;
    // for (std::vector<std::string> strings : disbatcher.getSubStrings()) {
    //     for (std::string subStr : strings) {
    //         std::cout << subStr << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    std::unordered_map<std::string, Vector> vectors = vectorizeData(data, 16);
    disbatcher.setVectors(&vectors);

    for (const auto& pair : vectors) {
        std::string key = pair.first;
        Vector value = pair.second;

        writer.write(key, &value);
        writer.incrementIndex();
    }

    // this key needs to exist for a word tha is in corpus of data
    // in order for network to be allocated and constructed
    Vector vector = vectors["man."];
    int layerSize = vector.getHotVector().size();

    Network network = Network({{layerSize},
                               {16, 16, 16, 16}, 
                               {layerSize}});


    int epochNum = 0;
    int totalEpochs = 50;

    for (int i = 0; i < totalEpochs; i++) {

        for (const auto& substringBatch : disbatcher.getSubStrings()) {
            disbatcher.disbatch(&network, substringBatch, 0.1, epochNum);
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