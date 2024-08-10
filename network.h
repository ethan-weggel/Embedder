#include "node.h"
#include <vector>
#include <iostream>

class Network {
    private:
        // Defining basic layers
        std::vector<Node*> inputLayer;
        std::vector<std::vector<Node*>> hiddenLayers;
        std::vector<Node*> outputLayer; 

        // Weights
        std::vector<std::vector<double>> weights;

        double output;
        double error;

    public:
        // Default constructor
        Network(int inputSize, int hiddenLayers, std::vector<int> hiddenSizes, int outputSize);

        // Getter methods
        double getOutput();
        double getError();
        std::vector<Node*> getInputLayer();
        std::vector<std::vector<Node*>> getHiddenLayers();
        std::vector<Node*> getOutputLayer();
        double getWeight(int layer, int index);

        // Setter methods
        void setWeight(int layer, int index, double value);

        // Additional methods
        std::vector<double> forwardPropagate();
        std::vector<double> softmax();
        double crossEntropy();
        std::vector<double> backwardPropagate();

};