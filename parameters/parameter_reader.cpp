#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <any>
#include "parameter_reader.h"
#include "../reader/reader.h"
#include "../disbatcher/disbatcher.h"

ParameterParser::ParameterParser() {
    this->reader = Reader();
    this->disbatcher = Disbatcher();
    this->data = "";
    parameters["node-layers"] = std::vector<int>{};
    parameters["learning-alpha"] = 0.0f;
    parameters["epochs"] = 0;
    parameters["iterations"] = 0;
    parameters["file-name"] = "";
    this->path = "";
    this->delimiter = "";
}

std::string ParameterParser::getData() {
    return this->data;
}

std::map<std::string, std::any> ParameterParser::getParameters() {
    return this->parameters;
}

std::string ParameterParser::getPath() {
    return this->path;
}

std::string ParameterParser::getDelimiter() {
    return this->delimiter;
}

void ParameterParser::setPath(std::string value) {
    this->path = value;
}

void ParameterParser::setDelimiter(std::string value) {
    this->delimiter = value;
}

void ParameterParser::readParameters() {
    this->reader.setPath(this->path);
    this->reader.read();
    this->data = this->reader.getData();
}

void ParameterParser::parseParameters(const std::string& rawData) {
    std::map<std::string, std::any> parameters;
    std::istringstream stream(rawData);
    std::string line;

    while (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        std::string key;
        char bracket;

        lineStream >> key >> bracket;

        if (key == "node-layers") {
            std::vector<int> values;
            int num;
            while (lineStream >> num) {
                values.push_back(num);
            }
            parameters["node-layers"] = values;
        }
        else if (key == "learning-alpha") {
            float value;
            lineStream >> value;
            parameters["learning-alpha"] = value;
        } else if (key == "epochs") {
            int epochs;
            lineStream >> epochs;
            parameters["epochs"] = epochs;
        } else if (key == "iterations") {
            int iterations;
            lineStream >> iterations;
            parameters["iterations"] = iterations;
        } else if (key == "file-name") {
            std::string fileName;
            lineStream >> fileName;
            parameters["file-name"] = fileName;
        }
    }
    this->parameters = parameters;
}

void ParameterParser::print() {
    for (const auto& [key, value] : this->parameters) {
        std::cout << key << ": ";
        
        // Check if the value is a float
        if (value.type() == typeid(float)) {
            std::cout << std::any_cast<float>(value);
        }
        // Check if the value is a vector of int
        else if (value.type() == typeid(std::vector<int>)) {
            auto vec = std::any_cast<std::vector<int>>(value);
            std::cout << "{ ";
            for (const int& num : vec) {
                std::cout << num << " ";
            }
            std::cout << "}";
        }
        else {
            std::cout << "Unknown type";
        }
        std::cout << '\n';
    }
}