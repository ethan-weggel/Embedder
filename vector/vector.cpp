#include "vector.h"
#include <iostream>

// Default constructor
Vector::Vector() {
    // Initialize if needed
}

// Getter method
std::vector<double> Vector::getHotVector() const {
    return hotVector;
}

// Getter method
std::vector<double> Vector::getWeightVector() const {
    return weightVector;
}

// Set hot-vector method
void Vector::setHotVector(const std::vector<double> vector) {
    hotVector = vector;
}

// Set weight-vector method
void Vector::setWeightVector(const std::vector<double> vector) {
    weightVector = vector;
}

// Set hot-vector index
void Vector::setHotVectorIndex(int index, const double value) {
    if (index >= hotVector.size()) {
        hotVector.resize(index + 1);  // Ensure the vector is large enough
    }
    hotVector[index] = value;
}

// Set weight-vector index
void Vector::setWeightVectorIndex(int index, double value) {
    if (index >= weightVector.size()) {
        weightVector.resize(index + 1);  // Ensure the vector is large enough
    }
    weightVector[index] = value;
}

void Vector::printWeight() {
    std::cout << "Current Vector[weight]: ";
    for (const double currentWeight : this->weightVector) {
        std::cout << currentWeight << " ";
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
