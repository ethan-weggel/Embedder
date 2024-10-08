#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <iostream>

class Node {

private:
    // Private info fields
    static int instCnt;
    int id;
    std::string type;
    std::vector<double> inputs;
    double output;
    double gradient;
    double error;
    std::vector<double>* weights;
    std::vector<double> weightsValues;
    double bias;
    std::vector<Node*> forwardNodes;
    std::vector<Node*> previousNodes;

public:
    // Default constructor
    Node();

    // typed and indexed constructor
    Node(std::string type);

    // destructor
    ~Node();

    // Getter methods
    int getId();
    std::string getType();
    std::vector<double> getInputs();
    double getOutput();
    double getGradient();
    double getError();
    double getBias();
    std::vector<double>* getWeights();
    std::vector<double> getWeightsHidden();
    double getWeight(int index);
    double getWeightHidden(int index);
    std::vector<Node*> getForwardNodes();
    std::vector<Node*> getPreviousNodes();

    // Setter methods
    void setId(int id);
    void setType(const std::string& type);
    void setInput(int index, double input);
    void setInputs(std::vector<double> inputs);
    void setOutput(double output);
    void setGradient(double gradient);
    void setError(double error);
    void setBias(double bias);
    void setForwardNodes(std::vector<Node*> nodes);
    void setPreviousNodes(std::vector<Node*> nodes);
    void setWeights(std::vector<double>* newWeights);
    void setWeightsHidden(std::vector<double> newWeights);
    void setWeight(int index, double newWeight);
    void setWeightHidden(int index, double newWeight);

    // Additional methods
    void addForwardNode(Node* node);
    void addPreviousNode(Node* node);

    // Clears node of input, output, error and gradient
    void clear();

    // Reset synapses [clears all prev and forward ptr connections]
    void clearSynapses();

    // Simple display function to see current node internals
    void print();
};

#endif 
