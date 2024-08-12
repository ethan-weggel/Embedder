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
        std::vector<Node> inputLayer;
        std::vector<std::vector<Node>> hiddenLayers;
        std::vector<Node> outputLayer; 

        // Weights
        std::vector<std::vector<double>> weights;

        double output;
        double error;

    public:
        // Default constructor
        Network(std::vector<std::vector<int>> layerDim);

        // Getter methods
        double getOutput();
        double getError();
        std::vector<Node> getInputLayer();
        std::vector<std::vector<Node>> getHiddenLayer();
        std::vector<Node> getHiddenLayer(int index);
        std::vector<Node> getOutputLayer();
        double getWeight(int layer, int index);
        std::vector<double> getWeights(int layer);

        // Setter methods
        void setWeight(int layer, int index, double value);
        void setWeights(int layer, std::vector<double> value);

        // Additional methods
        std::vector<double> softmax(std::vector<double> outputPreActivation);
        std::vector<double> ReLU(std::vector<double> inputs);
        std::vector<double> crossEntropy();
        void zip(std::vector<Node> nodes, std::vector<double> inputs);
        void reset();
        void set(std::vector<Node> layer, Vector vector);
        std::vector<double> forwardPropagate();
        std::vector<double> backwardPropagate();

        // Simple display method
        void print();

};

#endif