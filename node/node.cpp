#include <iostream>
#include <string>
#include "Node.h"

int Node::instCnt = 0;

Node::Node() {
    // Default Constructor
    // initalizing as emtpy so it can be resized
    this->forwardNodes = {};
    this->previousNodes = {};

    this->input = 0.0;
    this->output = 0.0;
    this->error = 0.0;
    this->gradient = 0.0;

    this->id = instCnt;
    instCnt++;
}

// Typed constructor
Node::Node(std::string type, int id) {
    this->type = type;
    this->id = id;

    // initalizing as emtpy so it can be resized
    this->forwardNodes = {};
    this->previousNodes = {};

    this->input = 0.0;
    this->output = 0.0;
    this->error = 0.0;
    this->gradient = 0.0;
    
    this->id = instCnt;
    instCnt++;
}

Node::~Node() {
    id--;
}

// Getter methods
int Node::getId() const {
    return this->id;
}

std::string Node::getType() const {
    return this->type;
}

double Node::getInput() const {
    return this->input;
}

double Node::getOutput() const {
    return this->output;  
}

double Node::getGradient() const {
    return this->gradient;
}

double Node::getError() const {
    return this->error;
}

std::vector<Node*> Node::getForwardNodes() const {
    return this->forwardNodes;
}

std::vector<Node*> Node::getPreviousNodes() const {
    return this->previousNodes;
}

// Setter methods
void Node::setId(int id) {
    this->id = id;
}

void Node::setType(const std::string& type) {
    this->type = type;
}

void Node::setInput(double input) {
    this->input = input;
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

void Node::setForwardNodes(const std::vector<Node*>& nodes) {
    this->forwardNodes = nodes;
}

void Node::setPreviousNodes(const std::vector<Node*>& nodes) {
    this->previousNodes = nodes;
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
    this->input = 0.0;
    this->output = 0.0;
    this->error = 0.0;
    this->gradient = 0.0;
}

void Node::clearSynapses() {
    this->forwardNodes = {};
    this->previousNodes = {};
}

void Node::print() {
    std::cout << "\nNode [" << this->id << "]:" << std::endl;
    std::cout << "\tInput    -> " << this->input << std::endl;
    std::cout << "\tOutput   -> " << this->output << std::endl;
    std::cout << "\tError    -> " << this->error << std::endl;
    std::cout << "\tGradient -> " << this->gradient << std::endl;
}