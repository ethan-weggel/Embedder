#include "../node/node.h"
#include "network.h"
#include "../vector/vector.h"
#include "../utilities/utilities.h"
#include <vector>
#include <tuple>
#include <cmath>

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

    formSynapses();

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

void Network::formSynapses() {

    int numHiddenLayers = this->hiddenLayers.size();
    int currentHiddenLayer = 0;

    for (Node* node : this->inputLayer) {
        for (Node* hiddenNode : this->hiddenLayers[currentHiddenLayer]) {
            node->addForwardNode(hiddenNode);
            hiddenNode->addPreviousNode(node);
        }
    }
    currentHiddenLayer++;

    while (currentHiddenLayer < numHiddenLayers) {
        int prevLayer = currentHiddenLayer - 1;
        for (Node* node : this->hiddenLayers[prevLayer]) {
            for (Node* nextNode : this->hiddenLayers[currentHiddenLayer]) {
                node->addForwardNode(nextNode);
                nextNode->addPreviousNode(node);
            }
        }
        currentHiddenLayer++;
    }

    for (Node* hiddenNode : this->hiddenLayers[this->hiddenLayers.size()-1]) {
        for (Node* outputNode : this->outputLayer) {
            hiddenNode->addForwardNode(outputNode);
            outputNode->addPreviousNode(hiddenNode);
        }
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
        (*nodes)[iter]->setInput(-1, inputs[iter]);
        if ((*nodes)[iter]->getType() == "input") {
            (*nodes)[iter]->setOutput(inputs[iter]);
        }
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
    ReLU(this->inputLayer, this->hiddenLayers[0]);
    int numHiddenLayers = this->hiddenLayers.size();

    if (numHiddenLayers == 1) {

    } else {
        
    }
   
    return {2.1};
}

void Network::ReLU(std::vector<Node*> inputLayer, std::vector<Node*> outputLayer) {
    int iterator = 0;
    int tempOutput = 0;

    for (Node* inputNode : inputLayer) {
        // setting inputs as weighted inputs
        for (Node* node : inputNode->getForwardNodes()) {
            node->setInput(-1, (inputNode->getOutput() * inputNode->getWeight(iterator)));
        }
    }

    for (Node* outputNode : outputLayer) {
        // summing weighted inputs, hard start after y = 0
        double weightedSum = doubleSum(outputNode->getInputs());
        if (weightedSum <= 0) {
            outputNode->setOutput(0.0);
        } else {
            outputNode->setOutput(doubleSum(outputNode->getInputs()));
        }
    }

    for (Node* node : outputLayer) {
        node->print();
    }
}

double softmaxHelper(int featureIndex, std::vector<double> features) {
    int sum = 0;
    int index = 0;

    for (double feature : features) {
        if (index != featureIndex) {
            sum += feature;
        }
        index++;
    }

    return sum;
}

std::vector<double> Network::softmax(std::vector<Node*> inputLayer, std::vector<Node*> outputLayer) {
    std::vector<double> softmaxProbabilities = {};
    int outputNodeIndex = 0;

    for (Node* inputNode : inputLayer) {
        for (Node* outputNode : outputLayer) {
            outputNode->setInput(-1, (inputNode->getOutput() * inputNode->getWeights()[outputNodeIndex]));
        }
    }

    std::vector<double> presoftmaxTransform = {};
    for (Node* node : outputLayer) {
        presoftmaxTransform.push_back(node->get);
    }


    // std::vector<double> outputProbabilities = {};
    // int featureIndex = 0;

    // while (featureIndex < inputs.size()){
    //     double denominator = softmaxHelper(featureIndex, inputs);
    //     double numerator = inputs[featureIndex];
    //     outputProbabilities.push_back(numerator / denominator);
    //     featureIndex++;
    // }

    // return outputProbabilities;
}

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
        std::cout << "{ ";
        for (double input : node->getInputs()) {
            std::cout << input << " ";
        }
        std::cout << "}";
        std::cout << " -> " << node->getId() << " -> { ";
        for (double weight : (*node->getWeights())) {
            std::cout << weight << " ";
        }
        std::cout << "}" << std::endl;
    }
}