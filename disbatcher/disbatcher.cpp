#include "disbatcher.h"
#include "../network/network.h"
#include "../utilities/utilities.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

Disbatcher::Disbatcher() {
    this->delimiter = "";
    this->data = "";
}


std::string Disbatcher::getData() {
    return this->data;
}

std::vector<std::string> Disbatcher::getBatches() {
    return this->batches;
}

std::vector<std::vector<std::string>> Disbatcher::getSubStrings() {
    return this->substrings;
}

std::vector<std::string> Disbatcher::getSubstring(int index) {
    return this->substrings[index];
}

std::unordered_map<std::string, Vector>* Disbatcher::getVectors() {
    return this->vectors;
}

void Disbatcher::setData(std::string newData) {
    this->data = newData;
}

void Disbatcher::setBatches(std::vector<std::string> newBatches) {
    this->batches = newBatches;
}

void Disbatcher::setBatch(int index, std::string batch) {
    this->batches[index] = batch;
}

void Disbatcher::setSubstrings(std::vector<std::vector<std::string>> newSubstrings) {
    this->substrings = newSubstrings;
}

void Disbatcher::setSubstring(int index, std::vector<std::string> substring) {
    this->substrings[index] = substring;
}

void Disbatcher::setVectors(std::unordered_map<std::string, Vector>* vectors) {
    this->vectors = vectors;
}

void Disbatcher::parseData(std::string delimiter) {
    if (this->delimiter.empty()) {
        this->delimiter = delimiter;
    }

    size_t start = 0;
    size_t end = this->data.find(this->delimiter);

    while (end != std::string::npos) {
        // Include the period in the substring
        this->batches.push_back(this->data.substr(start, end - start + 1));

        // Move start to the character after the ". "
        start = end + this->delimiter.length();
        end = this->data.find(this->delimiter, start);
    }

    // Add the last token, if any
    if (start < this->data.length()) {
        this->batches.push_back(this->data.substr(start));
    }
}

void Disbatcher::parseBatches(std::string delimiter) {

    this->delimiter = " ";

    for (std::string batch : this->batches) {
        std::vector<std::string> substringBatch = {};

        size_t start = 0;
        size_t end = batch.find(this->delimiter);

        while (end != std::string::npos) {
            substringBatch.push_back(batch.substr(start, end - start));
            start = end + this->delimiter.length();
            end = batch.find(this->delimiter, start);
        }

        // Add the last token
        substringBatch.push_back(batch.substr(start));

        this->substrings.push_back(substringBatch);
    }

}

// void Disbatcher::disbatch(Network* network, std::vector<std::string> substringBatch, double learningRate, int epoch) {
//     int substringBatchSize = substringBatch.size();
//     int wordIndex = 0;

//     while (wordIndex < substringBatchSize-1) {
//         std::cout << "INPUT WORD [" << substringBatch[wordIndex] << "]" << std::endl;
//         std::cout << "OUTPUT WORD [" << substringBatch[wordIndex+1] << "]" << std::endl;
//         network->setNetwork(network->getInputLayer(), &(*this->vectors)[substringBatch[wordIndex]]);
//         network->setTarget((*this->vectors)[substringBatch[wordIndex+1]].getHotVector());
//         (*this->vectors)[substringBatch[wordIndex+1]].printHot();
//         std::vector<double> dist = network->forwardPropagate();
//         // std::cout << "1" << std::endl;
//         network->backwardPropagate(learningRate);
//         // std::cout << "2" << std::endl;
//         network->reset();
//         wordIndex++;
//     }  

// }

void Disbatcher::disbatch(Network* network, std::vector<std::string> substringBatch, double learningRate, int epoch) {
    int substringBatchSize = substringBatch.size();
    int wordIndex = 0;

    while (wordIndex < substringBatchSize-1) {
        std::string inputWord = substringBatch[wordIndex];
        std::string outputWord = substringBatch[wordIndex+1];
        // std::cout << "INPUT WORD [" << inputWord << "]" << std::endl;
        // std::cout << "OUTPUT WORD [" << outputWord << "]" << std::endl;

        if (this->vectors->find(inputWord) == this->vectors->end()) {
            std::cerr << "Key not found in vectors: " << inputWord << std::endl;
            return;
        }
        if (this->vectors->find(outputWord) == this->vectors->end()) {
            std::cerr << "Key not found in vectors: " << outputWord << std::endl;
            return;
        }

        network->setNetwork(network->getInputLayer(), &(*this->vectors)[inputWord]);
        network->setTarget((*this->vectors)[outputWord].getHotVector());
        // (*this->vectors)[outputWord].printHot();

        std::vector<double> dist = network->forwardPropagate();
        network->backwardPropagate(learningRate);
        network->reset();
        wordIndex++;
    }  
}
