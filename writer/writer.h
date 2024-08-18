#ifndef WRITER_H
#define WRITER_H

#include <string>
#include "../vector/vector.h"

class Writer {
    private:
        // Defining write paths and attributes
        std::string relativeFolderPath;
        std::string baseFileName;
        int index;

    public: 
        // Default Constructor
        Writer();

        // Getters
        std::string getPath();
        std::string getBaseFileName();

        // Setters
        void setPath(std::string newPath);
        void setBaseFileName(std::string newFileName);

        // Additional Methods
        void incrementIndex();
        void write(std::string word, Vector* vector);

};

#endif