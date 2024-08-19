#ifndef DISBATCHER_H
#define DISBATCHER_H

#include <vector>
#include <string>
#include "../network/network.h"
#include <unordered_map>
#include "../vector/vector.h"

class Disbatcher {
    private:
        std::string delimiter;
        std::string data;
        std::vector<std::string> batches;
        std::vector<std::vector<std::string>> substrings;
        std::unordered_map<std::string, Vector> vectors;


    public:
        // Default Constructor
        Disbatcher();

        // Getters
        std::string getData();
        std::vector<std::string> getBatches();
        std::vector<std::vector<std::string>> getSubStrings();
        std::vector<std::string> getSubstring(int index);
        std::unordered_map<std::string, Vector> getVectors();

        // Setters
        void setData(std::string newData);
        void setBatches(std::vector<std::string> newBatches);
        void setBatch(int index, std::string batch);
        void setSubstrings(std::vector<std::vector<std::string>> newSubstrings);
        void setSubstring(int index, std::vector<std::string> substring);
        void setVectors(std::unordered_map<std::string, Vector> vectors);

        // Additional Methods

        // will parse through data string, split on set delimiter, default if not set
        // resultant splits will become batches
        void parseData(std::string delimiter = ". ");

        // will parse through each batch, split on set delimiter, default if not set
        // result splits are put into substring vector and saved
        void parseBatches(std::string delimiter = " ");

        // zips up the network with batch words for training
        void disbatch(Network* network, std::vector<std::string> substringBatch);

};

#endif