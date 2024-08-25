
#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <vector>

class Optimizer {

    private:
        // basic fields
        std::vector<double> originalWeights;
        std::vector<double> rollOverWeights;
        
        std::vector<double> originalOutputDistribution;
        std::vector<double> rollOverDistribution;

    public:
        // default constructor
        Optimizer();

};

#endif 