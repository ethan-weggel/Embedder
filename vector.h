#include <vector>
#include <string>

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
        std::vector<std::string> stringVector;
        std::vector<double> doubleVector;

    public:
        // Default constructor
        Vector();

        // Getter method
        std::vector<std::string> getStringVector() const;
        // Getter method
        std::vector<double> getDoubleVector() const;

        // Set string-vector method
        void setStringVector(const std::vector<std::string>& vector);

        // Set double-vector method
        void setDoubleVector(const std::vector<double>& vector);

        // Set string-vector index
        void setStringVectorIndex(int index, const std::string& value);

        // Set double-vector index
        void setDoubleVectorIndex(int index, double value);

        // Display functions
        void printString();
        void printDouble();
};

#endif
