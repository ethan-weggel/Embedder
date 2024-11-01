#ifndef PARAMETER_READER_H
#define PARAMETER_READER_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <any>
#include "../reader/reader.h"
#include "../disbatcher/disbatcher.h"

class ParameterParser {
    private:
        Reader reader;
        Disbatcher disbatcher;
        std::string data;
        std::map<std::string, std::any> parameters;
        std::string path;
        std::string delimiter;

    public:
        // default constructor
        ParameterParser();

        // getter methods
        std::string getData();
        std::map<std::string, std::any> getParameters();
        std::string getPath();
        std::string getDelimiter();


        // setter methods
        void setPath(std::string value);
        void setDelimiter(std::string value);

        // additional methods
        void readParameters();
        void parseParameters(const std::string& rawData);
        void print();


};

#endif