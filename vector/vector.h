#include <vector>
#include <string>

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
        std::vector<double> weightVector;
        std::vector<int> hotVector;

    public:
        // Default constructor
        Vector();

        // Getter method
        std::vector<int> getHotVector() const;
        // Getter method
        std::vector<double> getWeightVector() const;

        // Set hot-vector method
        void setHotVector(const std::vector<int>& vector);

        // Set weight-vector method
        void setWeightVector(const std::vector<double>& vector);

        // Set hot-vector index
        void setHotVectorIndex(int index, const int& value);

        // Set weight-vector index
        void setWeightVectorIndex(int index, double value);

        // Display functions
        void printHot();
        void printWeight();

};

#endif
