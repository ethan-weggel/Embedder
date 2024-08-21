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

    // Replace all newline characters with ". "
    size_t pos = 0;
    while ((pos = this->data.find('\n', pos)) != std::string::npos) {
        this->data.replace(pos, 1, ". ");
        pos += 2;  // Move past the ". "
    }

    // Remove double quotes and single quotes
    pos = 0;
    while ((pos = this->data.find_first_of("\"'", pos)) != std::string::npos) {
        this->data.erase(pos, 1);  // Remove the quote character
    }

    size_t start = 0;
    size_t end = this->data.find(this->delimiter);

    while (end != std::string::npos) {
        this->batches.push_back(this->data.substr(start, end - start));
        start = end + this->delimiter.length();
        end = this->data.find(this->delimiter, start);
    }

    // Add the last token
    this->batches.push_back(this->data.substr(start));
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

void Disbatcher::disbatch(Network* network, std::vector<std::string> substringBatch, double learningRate) {
    int substringBatchSize = substringBatch.size();
    int wordIndex = 0;

    while (wordIndex < substringBatchSize-2) {
        network->setNetwork(network->getInputLayer(), &(*this->vectors)[substringBatch[wordIndex]]);
        network->setTarget((*this->vectors)[substringBatch[wordIndex+1]].getHotVector());
        // network->print();
        std::vector<double> dist = network->forwardPropagate();
        // printVec(&dist);
        network->backwardPropagate(learningRate);
        network->reset();
        wordIndex++;
    }  

}