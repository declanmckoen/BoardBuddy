
#include "DataReader.h"
#include "ChessGame.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <vector>

DataReader::DataReader() {}

bool DataReader::read(const string& filepath) {
    games.reserve(131000);
    ifstream file(filepath);

    if(!file.is_open()){
        return false;
    }

    int i = 0;
    string line;
    while(getline(file, line)){
        if(i == 0){
            i++;
            continue;
        }

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
        i++;
    }

    return true;
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

    writeMoveListToFile(moveList);

    return moveList;
}

bool DataReader::isValidMove(const string &moveString) {
    regex pattern("[BRQNK][a-h][1-8]|[BRQNK][a-h]x[a-h][1-8]|[BRQNK][a-h][1-8]x[a-h][1-8]|[BRQNK][a-h][1-8][a-h][1-8]|[BRQNK][a-h][a-h][1-8]|[BRQNK]x[a-h][1-8]|[a-h]x[a-h][1-8]=(B+R+Q+N)|[a-h]x[a-h][1-8]|[a-h][1-8]x[a-h][1-8]=(B+R+Q+N)|[a-h][1-8]x[a-h][1-8]|[a-h][1-8][a-h][1-8]=(B+R+Q+N)|[a-h][1-8][a-h][1-8]|[a-h][1-8]=(B+R+Q+N)|[a-h][1-8]|[BRQNK][1-8]x[a-h][1-8]|[BRQNK][1-8][a-h][1-8]");
    return regex_match(moveString, pattern);
}

void DataReader::assignAllRandomSimilarityScores() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 100.0);

    // Loop through the games and set the score to a random double
    for (auto game : games) {
        game->score = dis(gen);
    }
}

void DataReader::parseAllMoves() {
    int i = 0;

    //Okay, now read data[MOVES] into moves
    for(auto game : games){
        i++;

        if(i % 10000 == 0){
            cout << "!";
        }else if(i % 1000 == 0){
            cout << ".";
        }
        game->moves = parseMove(game->data[ChessGame::MOVES]);

        //cout << i << ". " << game->moves[0];
    }
    cout << endl;
}

void DataReader::writeMoveListToFile(const vector<string> &moveList)  {
    auto filename = moveSetFilePath;
    std::ofstream outFile(filename, std::ios::app); // Open in append mode
    if (!outFile.is_open()) {
        cout << " > error: could not open " << filename << " for writing." << endl;
        return;
    }

    for (const auto& move : moveList) {
        outFile << move << " "; // Separate moves by space
    }
    outFile << "\n"; // Separate vectors by comma


    outFile.close();
}

void DataReader::setMoveSetFilePath(string path) {
    moveSetFilePath = path;
}

void DataReader::readMoveSetDotTxt() {
    //Assumes that CSV and Moves.txt are properly synced!
    ifstream inFile(moveSetFilePath);

    if (!inFile.is_open()) {
        cout << " > error: could not open " << moveSetFilePath << endl;
        return;
    }

    string line;
    int i = 0;

    while (getline(inFile, line)) { // Read each line
        if(line.empty()){
            continue;
        }

        istringstream lineStream(line);
        vector<string> moves;
        string move;

        //Split up each line
        while (lineStream >> move) { // split by space
            moves.push_back(move);
        }
        games[i]->moves = moves; // store each element into vector
        i++;
    }

}


