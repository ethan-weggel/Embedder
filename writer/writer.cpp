#include "writer.h"
#include <iostream>
#include <fstream>
#include <vector>

Writer::Writer() {
    this->index = 0;
}

std::string Writer::getPath() {
    return this->relativeFolderPath;
}

std::string Writer::getBaseFileName() {
    return this->baseFileName;
} 

void Writer::setPath(std::string newPath) {
    this->relativeFolderPath = newPath;
}

void Writer::setBaseFileName(std::string newFileName) {
    this->baseFileName = newFileName;
}

void Writer::setIndex(int newIndex) {
    this->index = newIndex;
}

void Writer::incrementIndex() {
    this->index++;
}

void Writer::write(std::string word, Vector* vector) {
    std::string fullFileName = this->relativeFolderPath + this->baseFileName + "-" + std::to_string(this->index) + ".py";


    std::ofstream vectorFile(fullFileName);

    vectorFile << "word = \"" << word << "\"\n";
    
    // Write hot vector
    std::vector<double> hotVector = vector->getHotVector();
    int hotSize = hotVector.size();
    vectorFile << "hotVector = " << "[";
    for (int i = 0; i < hotSize; ++i) {
        vectorFile << hotVector[i];
        if (i < hotSize - 1) {
            vectorFile << ", ";
        }
    }
    vectorFile << "]\n";

    // Write weight vectors
    std::vector<std::vector<double>*> weightVector = vector->getWeightsVector();
    int numWeightVectors = weightVector.size();

    vectorFile << "weightVector = " <<"[";
    for (int i = 0; i < numWeightVectors; ++i) {
        vectorFile << "[";
        int subVectorSize = weightVector[i]->size();
        for (int j = 0; j < subVectorSize; ++j) {
            vectorFile << (*weightVector[i])[j];
            if (j < subVectorSize - 1) {
                vectorFile << ", ";
            }
        }
        vectorFile << "]";
        if (i < numWeightVectors - 1) {
            vectorFile << ",\n";
        }
    }
    vectorFile << "]";

    vectorFile.close();
}