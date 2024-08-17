
#include <iostream>
#include <string>
#include "Node.h"
#include "../utilities/utilities.h"

int Node::instCnt = 0;

Node::Node() {
    // Default Constructor
    // initalizing as emtpy so it can be resized
    this->forwardNodes = {};
    this->previousNodes = {};

    this->inputs = {};
    this->output = 0.0;
    this->error = 0.0;
    this->gradient = 0.0;
    this->weights = NULL;
    this->weightsValues = {};

    this->id = instCnt;
    instCnt++;
}

// Typed constructor
Node::Node(std::string type) {
    this->type = type;

    // initalizing as emtpy so it can be resized
    this->forwardNodes = {};
    this->previousNodes = {};

    this->inputs = {};
    this->output = 0.0;
    this->error = 0.0;
    this->gradient = 0.0;
    this->weights = NULL;
    this->weightsValues = {};
    
    this->id = instCnt;
    instCnt++;
}

Node::~Node() {
    id--;
}

// Getter methods
int Node::getId() {
    return this->id;
}

std::string Node::getType() {
    return this->type;
}

std::vector<double> Node::getInputs() {
    return this->inputs;
}

double Node::getOutput() {
    return this->output;  
}

double Node::getGradient() {
    return this->gradient;
}

double Node::getError() {
    return this->error;
}

std::vector<double>* Node::getWeights() {
    return this->weights;
}

std::vector<double> Node::getWeightsHidden() {
    if (this->type == "hidden") {
        return this->weightsValues;
    } else {
        return {-1.0};
    }
}

double Node::getWeight(int index) {
    return (*this->weights)[index];
}

double Node::getWeightHidden(int index) {
    if (this->type == "hidden") {
        return this->weightsValues[index];
    } else {
        return -1.0;
    }
}

std::vector<Node*> Node::getForwardNodes() {
    return this->forwardNodes;
}

std::vector<Node*> Node::getPreviousNodes() {
    return this->previousNodes;
}

// Setter methods
void Node::setId(int id) {
    this->id = id;
}

void Node::setType(const std::string& type) {
    this->type = type;
}

void Node::setInput(int index, double input) {
    if (index == -1) {
        this->inputs.push_back(input);
    } else {
        this->inputs[index] = input;
    }
}

void Node::setOutput(double output) {
    this->output = output;
}

void Node::setGradient(double gradient) {
    this->gradient = gradient;
}

void Node::setError(double error) {
    this->error = error;
}  

void Node::setForwardNodes(std::vector<Node*> nodes) {
    this->forwardNodes = nodes;
}

void Node::setPreviousNodes(std::vector<Node*> nodes) {
    this->previousNodes = nodes;
}

void Node::setWeights(std::vector<double>* newWeights) {
    this->weights = newWeights;
}

void Node::setWeightsHidden(std::vector<double> newWeights) {
    if (this->weightsValues.size() < newWeights.size()) {
        this->weightsValues.resize(newWeights.size());
    }

    if (this->type == "hidden") {
        this->weightsValues = newWeights;
    } else {
        return;
    }
}

void Node::setWeight(int index, double newWeight) {
    (*this->weights)[index] = newWeight;
}

void Node::setWeightHidden(int index, double newWeight) {
    if (this->type == "hidden") {
        this->weightsValues[index] = newWeight;
    } else {
        return;
    }
}

// Additional methods
void Node::addForwardNode(Node* node) {
    int index = this->forwardNodes.size();
    if (index >= this->forwardNodes.size()) {
        this->forwardNodes.resize(index + 1);  // Ensure the vector is large enough
    }
    this->forwardNodes[index] = node;
}

void Node::addPreviousNode(Node* node) {
    int index = this->previousNodes.size();
    if (index >= this->previousNodes.size()) {
        this->previousNodes.resize(index + 1);  // Ensure the vector is large enough
    }
    this->previousNodes[index] = node;
}

void Node::clear() {
    this->inputs = {};
    this->output = 0.0;
    this->error = 0.0;
    this->gradient = 0.0;
    this->weights = NULL;
}

void Node::clearSynapses() {
    this->forwardNodes = {};
    this->previousNodes = {};
}

void Node::print() {
    if (this->type == "input") {
        std::cout << "\nNode [" << this->id << "]:" << std::endl;
        std::cout << "\tInput    -> { ";
        for (double input : this->getInputs()) {
            std::cout << input << " ";
        }
        std::cout << "}" << std::endl;
        std::cout << "\tOutput   -> " << this->output << std::endl;
        std::cout << "\tError    -> " << this->error << std::endl;
        std::cout << "\tGradient -> " << this->gradient << std::endl;
        std::cout << "\tWeights  -> { ";
        for (double weight : (*this->weights)) {
            std::cout << weight << " ";
        }
        std::cout << "}" << std::endl;
    } else if (this->type == "hidden") {
        std::cout << "\nNode [" << this->id << "]:" << std::endl;
        std::cout << "\tInput    -> { ";
        for (double input : this->getInputs()) {
            std::cout << input << " ";
        }
        std::cout << "}" << std::endl;
        std::cout << "\tOutput   -> " << this->output << std::endl;
        std::cout << "\tError    -> " << this->error << std::endl;
        std::cout << "\tGradient -> " << this->gradient << std::endl;
        std::cout << "\tWeights  -> { ";
        for (double weight : this->weightsValues) {
            std::cout << weight << " ";
        }
        std::cout << "}" << std::endl;
    } else {
        std::cout << "Print method for node type has not been implemented." << std::endl;
    }
}