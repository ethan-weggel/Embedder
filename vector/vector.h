#include <vector>
#include <string>

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
        std::vector<double> weightVector;
        std::vector<double> hotVector;

    public:
        // Default constructor
        Vector();

        // Getter method
        std::vector<double> getHotVector() const;
        // Getter method
        std::vector<double> getWeightVector() const;

        // Set hot-vector method
        void setHotVector(const std::vector<double> vector);

        // Set weight-vector method
        void setWeightVector(const std::vector<double> vector);

        // Set hot-vector index
        void setHotVectorIndex(int index, const double value);

        // Set weight-vector index
        void setWeightVectorIndex(int index, double value);

        // Display functions
        void printHot();
        void printWeight();

};

#endif
