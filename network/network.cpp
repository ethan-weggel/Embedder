#include "../node/node.h"
#include "network.h"
#include "../vector/vector.h"
#include <vector>
#include <tuple>

Network::Network(std::vector<std::vector<int>> layerDim) {
    int inputSize = layerDim[0][0];
    int outputSize = layerDim[layerDim.size()-1][0];

    std::vector<Node> inputLayer = {std::vector<Node>(inputSize)};
    std::vector<Node> outputLayer = {std::vector<Node>(outputSize)};

    for (const int hiddenLayerSize : layerDim[1]) {
        std::vector<Node> hiddenLayer = {std::vector<Node>(hiddenLayerSize)};
        this->hiddenLayers.push_back(hiddenLayer);
    }

    this->inputLayer = inputLayer;
    this->outputLayer = outputLayer;
}

double Network::getOutput() {
    return this->output;
}

double Network::getError() {
    return this->error;
}

std::vector<Node> Network::getInputLayer() {
    return this->inputLayer;
}

std::vector<std::vector<Node>> Network::getHiddenLayer() {
    return this->hiddenLayers;
}

std::vector<Node> Network::getHiddenLayer(int index) {
    return this->hiddenLayers[index];
}

std::vector<Node> Network::getOutputLayer() {
    return this->outputLayer;
}

std::vector<double> Network::getWeights(int layer) {
    return this->weights[layer];
}

double Network::getWeight(int layer, int index) {
    return this->weights[layer][index];
}

void Network::setWeights(int layer, std::vector<double> value) {
    this->weights[layer] = value;
}

void Network::setWeight(int layer, int index, double value) {
    this->weights[layer][index] = value;
}

void Network::reset() {
    this->output = 0;
    this->error = 0;
    this->weights[0] = {};

    for (Node node : this->inputLayer) {
        node.clear();
    }
    
    for (std::vector<Node> layer : this->hiddenLayers) {
        for (Node node : layer) {
            node.clear();
        }
    }

    for (Node node : this->outputLayer) {
        node.clear();
    }

}

void Network::zip(std::vector<Node> nodes, std::vector<double> inputs) {
    int iterLen = nodes.size();
    int iter = 0;

    while (iter < iterLen) {
        nodes[iter].setInput(inputs[iter]);
        iter++;  
    } 

    this->inputLayer = nodes;
}

void Network::set(std::vector<Node> layer, Vector vector) {

    zip(layer, vector.getHotVector());
    // this->weights[0] = vector.getWeightVector();

}

// std::vector<double> softmax(std::vector<double> outputPreActivation);
// std::vector<double> ReLU(std::vector<double> inputs);
// std::vector<double> crossEntropy();
// std::vector<double> forwardPropagate();
// std::vector<double> backwardPropagate();

void Network::print() {
    std::cout << "Input Layer Size: " << this->inputLayer.size() << std::endl;
    for (int i = 0; i < this->hiddenLayers.size(); i++) {
        std::cout << "Hidden Layer [" << i+1 << "] Size: " << this->hiddenLayers[i].size() << std::endl;
    }
    std::cout << "Output Layer Size: " << this->outputLayer.size() << std::endl;

    std::cout << "Zipped Nodes: " << std::endl;
    for (Node node : this->inputLayer) {
        std::cout << node.getId() << " -> Input: " << node.getInput() << std::endl;
    }
}