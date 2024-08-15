#include <vector>
#include <string>

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
        std::vector<std::vector<double>> weightsVector;
        std::vector<double> hotVector;

    public:
        // Default constructor
        Vector();

        // Getter method
        std::vector<double> getHotVector();

        // Set hot-vector method
        void setHotVector(std::vector<double> vector);

        // Set hot-vector index
        void setHotVectorIndex(int index, double value);

        // Getter method
        std::vector<std::vector<double>*> getWeightsVector();

        // Set weight-vector method
        void setWeightsVector(std::vector<std::vector<double>> vector);

        // Set weights sub-vector method
        void setWeightsSubVector(int node, std::vector<double> weights);

        // Set weight-vector index
        void setWeightVectorIndex(int node, int index, double value);

        // Display functions
        void printHot();
        void printWeight();

};

#endif
