
#include <string>
#include <regex>
#include "ChessGame.h"

using namespace std;

class DataReader {
    string filepath;

public:
    vector<ChessGame*> games;

    DataReader(string path);

    void read();

    vector<ChessGame*> getAllData();

    void assignAllSimilarityScores(ChessGame* userGame);

    vector<string> parseMove(const string& moveString);
};

