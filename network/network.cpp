#include "../node/node.h"
#include "network.h"
#include "../vector/vector.h"
#include "../utilities/utilities.h"
#include <vector>
#include <tuple>

Network::Network(std::vector<std::vector<int>> layerDim) {
    int inputSize = layerDim[0][0];
    int outputSize = layerDim.back()[0];

    // allocate space for pointers
    this->inputLayer.resize(inputSize);
    this->outputLayer.resize(outputSize);
    this->hiddenLayers.resize(layerDim[1].size());

    int iterator = 0;
    for (int size : layerDim[1]) {
        this->hiddenLayers[iterator].resize(size);
        iterator++;
    }

    // create and initialize pointers to nodes
    for (int i = 0; i < this->inputLayer.size(); i++) {
        this->inputLayer[i] = new Node("input");
    }

    for (int i = 0; i < this->hiddenLayers.size(); i++) {
        for (int j = 0; j < this->hiddenLayers[i].size(); j++) {
            this->hiddenLayers[i][j] = new Node("hidden");
            if (this->hiddenLayers.size() == 1) {
                this->hiddenLayers[i][j]->setWeightsHidden(initializeNodeWeights(this->outputLayer.size()));
            } else if ((this->hiddenLayers.size() - i) > 1) {
                this->hiddenLayers[i][j]->setWeightsHidden(initializeNodeWeights(this->hiddenLayers[i + 1].size()));
            } else {
                this->hiddenLayers[i][j]->setWeightsHidden(initializeNodeWeights(this->outputLayer.size()));
            }
        }
    }

    for (int i = 0; i < this->outputLayer.size(); i++) {
        this->outputLayer[i] = new Node("output");
    }

    this->output = 0;
    this->error = 0;

}

Network::~Network() {
    for (Node* node : inputLayer) {
        delete node;
    }
    for (auto& layer : hiddenLayers) {
        for (Node* node : layer) {
            delete node;
        }
    }
    for (Node* node : outputLayer) {
        delete node;
    }
}


double Network::getOutput() {
    return this->output;
}

double Network::getError() {
    return this->error;
}

std::vector<Node*>* Network::getInputLayer() {
    return &inputLayer;
}

std::vector<std::vector<Node*>>* Network::getHiddenLayers() {
    return &hiddenLayers;
}

std::vector<Node*>* Network::getHiddenLayer(int index) {
    return &hiddenLayers[index];
}

std::vector<Node*>* Network::getOutputLayer() {
    return &outputLayer;
}

void Network::reset() {
    this->output = 0;
    this->error = 0;

    for (Node* node : this->inputLayer) {
        node->clear();
    }
    
    for (std::vector<Node*> layer : this->hiddenLayers) {
        for (Node* node : layer) {
            node->clear();
        }
    }

    for (Node* node : this->outputLayer) {
        node->clear();
    }

}

void Network::zipInputs(std::vector<Node*>* nodes, std::vector<double> inputs) {
    int iterLen = nodes->size();
    int iter = 0;

    while (iter < iterLen) {
        (*nodes)[iter]->setInput(inputs[iter]);
        iter++;  
    } 
}

void Network::zipWeights(std::vector<Node*>* nodes, std::vector<std::vector<double>*> weights) {
    int iterLen = nodes->size();
    int iter = 0;

    while (iter < iterLen) {
        (*nodes)[iter]->setWeights(weights[iter]);
        iter++;
    }
}

void Network::setNetwork(std::vector<Node*>* layer, Vector* vector) {
       
    zipInputs(layer, vector->getHotVector());
    zipWeights(layer, vector->getWeightsVector());
    this->inputLayer = *layer;

}

std::vector<double> Network::forwardPropagate() {
    // TODO, just added fixed weight to prove pointer manipulation
    this->inputLayer[0]->setWeight(0, 2.7813);
    return {2.1};
}

// std::vector<double> softmax(std::vector<double> outputPreActivation);
// std::vector<double> ReLU(std::vector<double> inputs);
// std::vector<double> crossEntropy();
// std::vector<double> backwardPropagate();

void Network::print() {
    
    std::cout << "Input Layer Size: " << this->inputLayer.size() << std::endl;
    for (int i = 0; i < this->hiddenLayers.size(); i++) {
        std::cout << "Hidden Layer [" << i+1 << "] Size: " << this->hiddenLayers[i].size() << std::endl;
    }
    std::cout << "Output Layer Size: " << this->outputLayer.size() << std::endl;

    std::cout << "Embedding Layout: " << std::endl;
    std::cout << "Input | Node | Weights" << std::endl;
    for (Node* node : this->inputLayer) {
        std::cout << node->getInput() << " -> " << node->getId() << " -> { ";
        for (double weight : (*node->getWeights())) {
            std::cout << weight << " ";
        }
        std::cout << "}" << std::endl;
    }
}