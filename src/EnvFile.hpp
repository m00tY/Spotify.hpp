#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class EnvFile {
    private:
    ifstream file;
    
    string filePath;
    map<string, string> envContents;

    map<string, string> envToMap(string filePath) {
        file.open(filePath);
        if (!file) {
            throw "Could not open file.";
        }

        string line;
        map<string, string> fileContents;
        while (file) {
            getline(file, line);
            auto linePair = breakAtEquals(line);
            fileContents[linePair.first] = linePair.second;
        }
        return fileContents;
    }
    
    //input should only be one line, while loop is jank but works
    pair<string, string> breakAtEquals(string text) {
        string key;
        string value;
        
        string delimiter = "=";
        int pos = 0;
        while ((pos = text.find(delimiter)) != string::npos) {
            key = text.substr(0, pos);
            value = text.substr(pos+1, text.length());
        }
        return make_pair(key, value);
    }
    
    public:
    EnvFile(string filePath) {
        this->filePath = filePath;
        envContents = envToMap(filePath); 
    }

    map<string, string> getMap() {
        return envContents;
    }
    
};