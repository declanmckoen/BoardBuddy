
#include <string>
#include <regex>
#include "ChessGame.h"

using namespace std;

class DataReader {
public:
    vector<ChessGame*> games;
    string moveSetFilePath;

    DataReader();

    //Reads in the CSV data
    bool read(const string& filepath);

    //Returns data
    vector<ChessGame*> getAllData();

    //Assigns similarity scores to all games according to userGame
    void assignAllSimilarityScores(ChessGame* userGame);

    //Assigns random similarity scores to all games
    void assignAllRandomSimilarityScores();

    //Parses the move data of every game
    void parseAllMoves();

    //Returns a vector of moves parsed from a string of moves
    vector<string> parseMove(const string& moveString);

    //Returns whether a string is a valid move
    static bool isValidMove(const string& moveString);

    //Writes move data to a text file
    void writeMoveListToFile(const vector<string>& moveList);

    //Sets the moveset filepath
    void setMoveSetFilePath(string path);

    //Reads moves.txt and assigns the moves vectors
    void readMoveSetDotTxt();
};

