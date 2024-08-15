
#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <unordered_map>
#include <string>
#include "../vector/vector.h"

std::vector<std::vector<double>> initializeLayerWeights(int firstLayerSize, int secondLayerSize, double mean = 0.0f, double stddev = 0.01f);
std::vector<double> initializeNodeWeights(int size, double mean = 0.0f, double stddev = 0.01f);
std::vector<double> initializeOneHotVectors(std::vector<std::string> uniqueWords, std::string word);
std::unordered_map<std::string, Vector> vectorizeData(std::string input, int secondLayerSize);

#endif