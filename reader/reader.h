#ifndef READER_H
#define NODE_H

#include <vector>
#include <string>

class Reader {
    private:
        std::string data;
        std::string path;

    public:
        // Default constructor
        Reader();

        // Getter methods
        std::string getPath();
        std::string getData();

        // Setter methods
        void setPath(std::string value);

        // Additional methods
        void read();

        // Simple display
        void print();
};

#endif