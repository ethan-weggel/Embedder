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

        double output;
        double error;

    public:
        // Default constructor
        Network(std::vector<std::vector<int>> layerDim);
        ~Network();

        // Getter methods
        double getOutput();
        double getError();
        std::vector<Node*>* getInputLayer();
        std::vector<std::vector<Node*>>* getHiddenLayers();
        std::vector<Node*>* getHiddenLayer(int index);
        std::vector<Node*>* getOutputLayer();

        // Additional methods
        std::vector<double> softmax(std::vector<Node*> inputLayer, std::vector<Node*> outputLayer);
        void ReLU(std::vector<Node*> inputNodes, std::vector<Node*> outputNodes);
        std::vector<double> crossEntropy();
        void zipInputs(std::vector<Node*>* nodes, std::vector<double> inputs);
        void zipWeights(std::vector<Node*>* nodes, std::vector<std::vector<double>*> weights);
        void reset();
        void setNetwork(std::vector<Node*>* layer, Vector* vector);
        std::vector<double> forwardPropagate();
        std::vector<double> backwardPropagate();
        void formSynapses();

        // Simple display method
        void print();

};

#endif