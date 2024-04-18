//
// Created by justi on 4/14/2024.
//

#ifndef BOARDBUDDYDATAREADING_DATAREADER_H
#define BOARDBUDDYDATAREADING_DATAREADER_H

#include <string>
#include <regex>
#include "ChessGame.h"

using namespace std;

class DataReader {
    string filepath;
    vector<ChessGame*> games;

public:
    DataReader(string path);

    void read();

    vector<ChessGame*> getAllData();
};


#endif //BOARDBUDDYDATAREADING_DATAREADER_H
