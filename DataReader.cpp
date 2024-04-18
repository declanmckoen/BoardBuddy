
#include "DataReader.h"
#include "ChessGame.h"

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
        game->moves = parseMove(game->data[ChessGame::MOVES]);
    }

}

vector<ChessGame *> DataReader::getAllData() {
    return games;
}

void DataReader::assignAllSimilarityScores(ChessGame *userGame) {
    for(auto game : games){
        game->assignScore(userGame);
    }
}

vector<string> DataReader::parseMove(const string& moveString) {
    vector<string> moveList;

    //Regex pattern from https://stackoverflow.com/questions/40007937/regex-help-for-chess-moves-san
    regex pattern("[BRQNK][a-h][1-8]|[BRQNK][a-h]x[a-h][1-8]|[BRQNK][a-h][1-8]x[a-h][1-8]|[BRQNK][a-h][1-8][a-h][1-8]|[BRQNK][a-h][a-h][1-8]|[BRQNK]x[a-h][1-8]|[a-h]x[a-h][1-8]=(B+R+Q+N)|[a-h]x[a-h][1-8]|[a-h][1-8]x[a-h][1-8]=(B+R+Q+N)|[a-h][1-8]x[a-h][1-8]|[a-h][1-8][a-h][1-8]=(B+R+Q+N)|[a-h][1-8][a-h][1-8]|[a-h][1-8]=(B+R+Q+N)|[a-h][1-8]|[BRQNK][1-8]x[a-h][1-8]|[BRQNK][1-8][a-h][1-8]");

    //Regex Iterator
    //Iterates through String, adds stuff that fits pattern
    sregex_iterator it(moveString.begin(), moveString.end(), pattern);
    sregex_iterator end;

    for (it; it != end; ++it) {
        moveList.push_back(it->str()); // Extract and convert digits to integer, then add to vector
    }

    return moveList;
}


