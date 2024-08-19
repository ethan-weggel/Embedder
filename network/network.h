#ifndef NETWORK_H
#define NETWORK_H

#include "../node/node.h"
#include "../vector/vector.h"
#include <vector>
#include <iostream>
#include <tuple>

class Network {
    private:
        // Defining basic layers
        std::vector<Node*> inputLayer;
        std::vector<std::vector<Node*>> hiddenLayers;
        std::vector<Node*> outputLayer; 

        std::vector<double> output;
        std::vector<double> error;
        std::vector<double> target;

    public:
        // Default constructor
        Network(std::vector<std::vector<int>> layerDim);
        ~Network();

        // Getter methods
        std::vector<double> getOutput();
        std::vector<double> getError();
        std::vector<Node*>* getInputLayer();
        std::vector<std::vector<Node*>>* getHiddenLayers();
        std::vector<Node*>* getHiddenLayer(int index);
        std::vector<Node*>* getOutputLayer();
        std::vector<double> getTarget();

        void setTarget(std::vector<double> newTarget);

        // Additional methods
        std::vector<double> softmax(std::vector<Node*> inputLayer, std::vector<Node*> outputLayer);
        void ReLU(std::vector<Node*> inputNodes, std::vector<Node*> outputNodes, int isInputLayer);
        std::vector<double> crossEntropy();
        void zipInputs(std::vector<Node*>* nodes, std::vector<double> inputs);
        void zipWeights(std::vector<Node*>* nodes, std::vector<std::vector<double>*> weights);
        void reset();
        void setNetwork(std::vector<Node*>* layer, Vector* vector);
        std::vector<double> forwardPropagate();
        void backwardPropagate(double learningRate);
        std::vector<double> crossEntropy(std::vector<double> softmaxOutput, std::vector<double> targetDistribution);
        void formSynapses();
        std::vector<double> inference();

        // Simple display method
        void print();

};

#endif