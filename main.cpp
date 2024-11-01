#include "vector/vector.h"
#include "node/node.h"
#include "network/network.h"
#include "reader/reader.h"
#include "writer/writer.h"
#include "utilities/utilities.h"
#include "disbatcher/disbatcher.h"
#include "parameters/parameter_reader.h"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <random>

int main() {
    ParameterParser parameterParser = ParameterParser();
    parameterParser.setPath("parameters.txt");
    parameterParser.setDelimiter(" ");
    parameterParser.readParameters();
    std::string parameterData = parameterParser.getData();
    parameterParser.parseParameters(parameterData);
    std::map<std::string, std::any> parameters = parameterParser.getParameters();

    // parameterParser.print();

    Reader reader = Reader();
    reader.setPath("data\\pointblank.txt");

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
    int secondNodeLayer = std::any_cast<std::vector<int>>(parameters["node-layers"])[0];
    std::unordered_map<std::string, Vector> vectors = vectorizeData(data, secondNodeLayer);
    disbatcher.setVectors(&vectors);

    std::string setUpKey = "";

    for (const auto& pair : vectors) {
        std::string key = pair.first;
        setUpKey = key;
        Vector value = pair.second;

        writer.write(key, &value);
        writer.incrementIndex();
    }

    // this key needs to exist for a word that is in corpus of data
    // in order for network to be allocated and constructed
    Vector vector = vectors[setUpKey];
    int layerSize = vector.getHotVector().size();
    const std::vector<int>& nodeLayers = std::any_cast<std::vector<int>>(parameters["node-layers"]);
    float learningAlpha = std::any_cast<float>(parameters["learning-alpha"]);
    int epochs = std::any_cast<int>(parameters["epochs"]);
    int iterations = std::any_cast<int>(parameters["iterations"]);
    Network network = Network({{layerSize},
                               nodeLayers, 
                               {layerSize}});


    int epochNum = 0;
    int totalEpochs = epochs;

    for (int i = 0; i < totalEpochs; i++) {

        for (const auto& substringBatch : disbatcher.getSubStrings()) {
            disbatcher.disbatch(&network, substringBatch, learningAlpha, epochNum, iterations);
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