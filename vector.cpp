#include "vector.h"
#include <iostream>

// Default constructor
Vector::Vector() {
    // Initialize if needed
}

// Getter method
std::vector<std::string> Vector::getStringVector() const {
    return stringVector;
}

// Getter method
std::vector<double> Vector::getDoubleVector() const {
    return doubleVector;
}

// Set string-vector method
void Vector::setStringVector(const std::vector<std::string>& vector) {
    stringVector = vector;
}

// Set double-vector method
void Vector::setDoubleVector(const std::vector<double>& vector) {
    doubleVector = vector;
}

// Set string-vector index
void Vector::setStringVectorIndex(int index, const std::string& value) {
    if (index >= stringVector.size()) {
        stringVector.resize(index + 1);  // Ensure the vector is large enough
    }
    stringVector[index] = value;
}

// Set double-vector index
void Vector::setDoubleVectorIndex(int index, double value) {
    if (index >= doubleVector.size()) {
        doubleVector.resize(index + 1);  // Ensure the vector is large enough
    }
    doubleVector[index] = value;
}

void Vector::printString() {
    std::cout << "Current Vector[string]: ";
    for (const std::string currentString : this->stringVector) {
        std::cout << currentString << " ";
    }
    std::cout << std::endl;
}

void Vector::printDouble() {
    std::cout << "Current Vector[double]: ";
    for (const double currentDouble : this->doubleVector) {
        std::cout << currentDouble << " ";
    }
    std::cout << std::endl;
}
