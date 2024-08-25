#include "utilities.h"
#include "../vector/vector.h"
#include "../node/node.h"
#include "../network/network.h"
#include "../reader/reader.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <random>

std::vector<std::vector<double>> initializeLayerWeights(int firstLayerSize, int secondLayerSize, double mean, double stddev) {
    std::vector<std::vector<double>> weights(firstLayerSize, std::vector<double>(secondLayerSize));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(mean, stddev);
    
    for (auto& nodeWeights : weights) {
        for (auto& weight : nodeWeights) {
            weight = dis(gen);
        }
    }

    return weights;
}

double initializeBias() {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator

    // Define the range for the random number
    std::uniform_real_distribution<> distr(-10.0, 10.0); // Range between -10.0 and 10.0

    // Generate a random value
    double randomValue = distr(eng);

    // Generate a random sign (+ or -)
    std::uniform_int_distribution<> signDistr(0, 1); // 0 or 1
    int sign = signDistr(eng) == 0 ? -1 : 1;
    double result = sign * randomValue;
    return result;
}

std::vector<double> initializeNodeWeights(int size, double mean, double stddev) {
    std::vector<double> weights(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(mean, stddev);
    

    for (auto& weight : weights) {
        weight = dis(gen);
    }


    return weights;
}

std::vector<double> initializeOneHotVectors(std::vector<std::string> uniqueWords, std::string word) {

        std::vector<double> hotVector(uniqueWords.size(), 0.0);

        auto it = std::find(uniqueWords.begin(), uniqueWords.end(), word);
        int index = std::distance(uniqueWords.begin(), it);
        hotVector[index] = 1.0;

        return hotVector;
}

std::unordered_map<std::string, Vector> vectorizeData(std::string input, int secondLayerSize) {

    // Split the string into words
    std::istringstream iss(input);
    std::set<std::string> wordSet;
    std::string word;
    
    // Add words to set
    while (iss >> word) {
        wordSet.insert(word);
    }

    // Copy the unique words into a vector
    std::vector<std::string> uniqueWords(wordSet.begin(), wordSet.end());

    // Sort the vector alphabetically
    std::sort(uniqueWords.begin(), uniqueWords.end());

    std::unordered_map<std::string, Vector> dictionary;


    // going through, finding index of each word,
    // making a hot encoded vector,
    // making a random weight vector using normal dist.
    // adding both sub vectors to custom Vector class
    // adding to dictionary word: Vector
    for (const std::string word : uniqueWords) {

        Vector vector = Vector();

        std::vector<double> hotVector = initializeOneHotVectors(uniqueWords, word);

        // add hot vector to custom Vector class, then create weight vector
        vector.setHotVector(hotVector);

        std::vector<std::vector<double>> weights = initializeLayerWeights(uniqueWords.size(), secondLayerSize);
        vector.setWeightsVector(weights);

        dictionary[word] = vector;
    }

    return dictionary;
}

double doubleSum(std::vector<double> inputs) {
    double sum = 0;

    for (double input : inputs) {
        sum += input;
    }

    return sum;
}

double oneDimDotProduct(std::vector<double> arr1, std::vector<double> arr2) {
    double sum = 0;
    int index = 0;

    while (index < arr1.size()) {
        sum += (arr1[index] * arr2[index]);
        index++;
    }

    return sum;
    
}