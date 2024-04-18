//
// Created by justi on 4/14/2024.
//

#include "DataReader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

DataReader::DataReader(string path) {
    filepath = path;
}

void DataReader::read() {
    ifstream file(filepath);

    if(!file.is_open()){
        cout << "error: file did not open properly!";
    }

    string line;
    while(getline(file, line)){
        stringstream ss(line);

        ChessGame* game = new ChessGame;

        string columnVal;
        while(getline(ss, columnVal, ',')){
            if(columnVal.empty()){
                columnVal = "";
            }
            game->data.push_back(columnVal);
        }

        games.push_back(game);
    }

    //Okay, now read data[MOVES] into moves

    for(auto game : games){
        //Regex pattern from https://stackoverflow.com/questions/40007937/regex-help-for-chess-moves-san
        regex pattern("[BRQNK][a-h][1-8]|[BRQNK][a-h]x[a-h][1-8]|[BRQNK][a-h][1-8]x[a-h][1-8]|[BRQNK][a-h][1-8][a-h][1-8]|[BRQNK][a-h][a-h][1-8]|[BRQNK]x[a-h][1-8]|[a-h]x[a-h][1-8]=(B+R+Q+N)|[a-h]x[a-h][1-8]|[a-h][1-8]x[a-h][1-8]=(B+R+Q+N)|[a-h][1-8]x[a-h][1-8]|[a-h][1-8][a-h][1-8]=(B+R+Q+N)|[a-h][1-8][a-h][1-8]|[a-h][1-8]=(B+R+Q+N)|[a-h][1-8]|[BRQNK][1-8]x[a-h][1-8]|[BRQNK][1-8][a-h][1-8]");

        //Regex Iterator
        //Iterates through String, adds stuff that fits pattern
        sregex_iterator it(game->data[ChessGame::MOVES].begin(), game->data[ChessGame::MOVES].end(), pattern);
        sregex_iterator end;

        for (it; it != end; ++it) {
            game->moves.push_back(it->str()); // Extract and convert digits to integer, then add to vector
        }
    }

}

vector<ChessGame *> DataReader::getAllData() {
    return games;
}


