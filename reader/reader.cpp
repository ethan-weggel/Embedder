#include "reader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Reader::Reader() {
    this->path = "";
}

std::string Reader::getData() {
    return this->data;
}

std::string Reader::getPath() {
    return this->path;
}

void Reader::setPath(std::string value) {
    this->path = value;
}

void Reader::read() {
    if (this->path == "") {
        std::cout << "File cannot be found because path was not set." << std::endl;
        return;
    }

    std::ifstream file(this->path);

    if (!file) {
        std::cerr << "Error opening file: " << this->path << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    this->data = buffer.str();
}

void Reader::print() {
    std::cout << this->data << std::endl;
}