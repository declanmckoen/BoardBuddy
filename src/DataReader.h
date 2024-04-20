
#include <string>
#include <regex>
#include "ChessGame.h"

using namespace std;

class DataReader {


public:
    vector<ChessGame*> games;

    DataReader();

    bool read(string filepath);

    vector<ChessGame*> getAllData();

    void assignAllSimilarityScores(ChessGame* userGame);

    vector<string> parseMove(const string& moveString);
};

