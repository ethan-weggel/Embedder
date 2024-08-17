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

    this->output = {};
    this->error = {};

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

std::vector<double> Network::getOutput() {
    return this->output;
}

std::vector<double> Network::getError() {
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
    this->output = {};
    this->error = {};

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
    ReLU(this->inputLayer, this->hiddenLayers[0], 1);
    int numHiddenLayers = this->hiddenLayers.size();
    int layerIndex = 0;
    std::vector<double> outputDistribution = {};

    if (numHiddenLayers == 1) {
        outputDistribution = softmax(this->hiddenLayers[0], this->outputLayer);
    } else {
        for (std::vector<Node*> layer : this->hiddenLayers) {
            if (layerIndex < numHiddenLayers-1) {
                ReLU(this->hiddenLayers[layerIndex], this->hiddenLayers[layerIndex+1], 0);
            } else {
                outputDistribution = softmax(this->hiddenLayers[layerIndex], this->outputLayer);
            }
            layerIndex++;
        }
    }

    this->output = outputDistribution;
   
    return outputDistribution;
}

void Network::ReLU(std::vector<Node*> inputLayer, std::vector<Node*> outputLayer, int isInputLayer) {
    int iterator = 0;
    int tempOutput = 0;

    if (isInputLayer) {
        // if ReLU is being performed on input nodes in the network,
        // we must get weight values through dereferenced pointers to
        // change vector values stored outside the network
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
    } else {
        // if ReLU is being performed on not an input layer, we cannot
        // access weights through dereferenced pointers, we need to 
        // access hard values
        for (Node* inputNode : inputLayer) {
            // setting inputs as weighted inputs
            for (Node* node : inputNode->getForwardNodes()) {
                node->setInput(-1, (inputNode->getOutput() * inputNode->getWeightHidden(iterator)));
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
    }
}

double softmaxHelper(std::vector<double> inputs) {
    double sum = 0;

    for (double input : inputs) {
        sum += exp(input);
    }

    return sum;
}

std::vector<double> Network::softmax(std::vector<Node*> inputLayer, std::vector<Node*> outputLayer) {
    int outputNodeIndex = 0;

    for (Node* inputNode : inputLayer) {
        for (Node* outputNode : outputLayer) {
            outputNode->setInput(-1, (inputNode->getOutput() * inputNode->getWeightsHidden()[outputNodeIndex]));
            outputNodeIndex++;
        }
        outputNodeIndex = 0;
    }


    for (Node* node : outputLayer) {
        node->setOutput(doubleSum(node->getInputs()));
    }


    std::vector<double> outputProbabilities = {};
    std::vector<double> preSoftmaxOutputs = {};
    for (Node* node : outputLayer) {
        preSoftmaxOutputs.push_back(node->getOutput());
    }

    int featureIndex = 0;

    while (featureIndex < outputLayer.size()){
        double denominator = softmaxHelper(preSoftmaxOutputs);
        double numerator = exp(preSoftmaxOutputs[featureIndex]);
        
        if (denominator != 0) {
            outputProbabilities.push_back(numerator / denominator);
        } else {
            outputProbabilities.push_back(0.0);
        } 

        featureIndex++;
    }

    return outputProbabilities;
}

std::vector<double> Network::crossEntropy(std::vector<double> softmaxOutput, std::vector<double> targetDistribution) {
    std::vector<double> errors = {};
    int index = 0;

    while (index < softmaxOutput.size()) {
        errors.push_back(softmaxOutput[index] - targetDistribution[index]);
        index++;
    }

    this->error = errors;
    return errors;
} 

std::vector<double> Network::backwardPropagate(std::vector<double> targetDistribution) {
    // assume there will always be a hidden layer and an output layer
    // this section is to correct weights between last layer and output layer

    for (Node* node : this->hiddenLayers[this->hiddenLayers.size()-1]) {
        std::vector<double> errors = crossEntropy(this->output,  targetDistribution);
        double dLoss_dActivation = 0;
        for (double weight : node->getWeightsHidden()) {
            dLoss_dActivation += weight * error[0];
        }

    }
}

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