
#include <string>
#include <regex>
#include "ChessGame.h"

using namespace std;

class DataReader {


public:
    vector<ChessGame*> games;

    DataReader();

    bool read(const string& filepath);

    vector<ChessGame*> getAllData();

    void assignAllSimilarityScores(ChessGame* userGame);

    void assignAllRandomSimilarityScores();

    void parseAllMoves();

    vector<string> parseMove(const string& moveString);

    static bool isValidMove(const string& moveString);
};

