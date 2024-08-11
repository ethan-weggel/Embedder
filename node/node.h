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
    double input;
    double output;
    double gradient;
    double error;
    std::vector<Node*> forwardNodes;
    std::vector<Node*> previousNodes;

public:
    // Default constructor
    Node();

    // typed and indexed constructor
    Node(std::string type, int id);

    // destructor
    ~Node();

    // Getter methods
    int getId() const;
    std::string getType() const;
    double getInput() const;
    double getOutput() const;
    double getGradient() const;
    double getError() const;
    std::vector<Node*> getForwardNodes() const;
    std::vector<Node*> getPreviousNodes() const;

    // Setter methods
    void setId(int id);
    void setType(const std::string& type);
    void setInput(double input);
    void setOutput(double output);
    void setGradient(double gradient);
    void setError(double error);
    void setForwardNodes(const std::vector<Node*>& nodes);
    void setPreviousNodes(const std::vector<Node*>& nodes);

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
