#include "vector/vector.h"
#include "node/node.h"
#include "reader/reader.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <random>

std::vector<double> initializeWeights(int size, double mean = 0.0f, double stddev = 0.01f) {
    std::vector<double> weights(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(mean, stddev);
    
    for (auto& weight : weights) {
        weight = dis(gen);
    }
    return weights;
}

std::unordered_map<std::string, Vector> oneHotEncodeData(std::string input) {

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

        std::vector<int> hotVector(uniqueWords.size(), 0);

        auto it = std::find(uniqueWords.begin(), uniqueWords.end(), word);
        int index = std::distance(uniqueWords.begin(), it);
        hotVector[index] = 1;

        // add hot vector to custom Vector class, then create weight vector
        vector.setHotVector(hotVector);

        std::vector<double> weights = initializeWeights(uniqueWords.size());
        vector.setWeightVector(weights);

        dictionary[word] = vector;
    }

    return dictionary;
}

int main() {

    Reader reader = Reader();
    reader.setPath("C:\\Users\\ewegg\\OneDrive\\Documents\\C++_Scripts\\Embedder\\data\\index.txt");
    reader.read();

    // Reading in text file as a string
    std::string dataString = reader.getData();

    // Passing data into vectorizing encoder
    std::unordered_map<std::string, Vector> oneHotVectors = oneHotEncodeData(dataString);

    std::cout << oneHotVectors["\"by"].getHotVector()[0] << std::endl;

    return 0;
}