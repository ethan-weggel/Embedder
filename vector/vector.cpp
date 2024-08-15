#include "vector.h"
#include <iostream>

// Default constructor
Vector::Vector() {
    // Initialize if needed
}

// Getter method
std::vector<double> Vector::getHotVector() {
    return hotVector;
}

// Set hot-vector method
void Vector::setHotVector(const std::vector<double> vector) {
    hotVector = vector;
}

// Set hot-vector index
void Vector::setHotVectorIndex(int index, double value) {
    if (index >= hotVector.size()) {
        hotVector.resize(index + 1);  // Ensure the vector is large enough
    }
    hotVector[index] = value;
}

// Getter method
std::vector<std::vector<double>*> Vector::getWeightsVector() {
    std::vector<std::vector<double>*> addresses;

    for (int i = 0; i < this->weightsVector.size(); i++) {
        addresses.push_back(&weightsVector[i]);
    }

    return addresses;
}

// Set weight-vector method
void Vector::setWeightsVector(std::vector<std::vector<double>> vector) {
    this->weightsVector = vector;
}

// Set weight sub-vector method
void Vector::setWeightsSubVector(int node, std::vector<double> weights) {
    this->weightsVector[node] = weights;
}

// Set weight sub-vector index method
void Vector::setWeightVectorIndex(int node, int index, double value) {
    this->weightsVector[node][index] = value;
}

void Vector::printWeight() {
    std::cout << "Current Vector[weight]: ";
    for (const std::vector<double> currentWeightVector : this->weightsVector) {
        for (const double weight : currentWeightVector) {
            std::cout << weight << " " << std::endl;
        }
    }
    std::cout << std::endl;
}

void Vector::printHot() {
    std::cout << "Current Vector[hot]: ";
    for (const int currentInteger : this->hotVector) {
        std::cout << currentInteger << " ";
    }
    std::cout << std::endl;
}
