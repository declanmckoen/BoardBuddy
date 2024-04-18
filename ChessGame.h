
#pragma once

#include <string>
#include <vector>

using namespace std;

class ChessGame {
private:
    double score = 0;          // This is our calculated similarity score

public:
    enum ChessAttributes {
        GAME_ID,
        EVENT,
        ROUND,
        SITE,
        DATE,
        TIME,
        WHITE,
        WHITE_ELO,
        WHITE_RATING_DIFF,
        WHITE_IS_DELETED,
        WHITE_TOS_VIOLATION,
        WHITE_PROFILE_FLAG,
        WHITE_CREATED_AT,
        WHITE_PLAY_TIME_TOTAL,
        WHITE_COUNT_ALL,
        WHITE_TITLE,
        BLACK,
        BLACK_ELO,
        BLACK_RATING_DIFF,
        BLACK_IS_DELETED,
        BLACK_TOS_VIOLATION,
        BLACK_PROFILE_FLAG,
        BLACK_CREATED_AT,
        BLACK_PLAY_TIME_TOTAL,
        BLACK_COUNT_ALL,
        BLACK_TITLE,
        MOVES,
        TOTAL_MOVES,
        ECO,
        OPENING,
        TIME_CONTROL,
        TERMINATION,
        RESULT
    };

    vector<string> data;
    vector<string> moves;

    void insertMove();

    //Assigns similarity score based off another game
    void assignScore(ChessGame* otherGame);

    // Overloads >
    bool operator>(const ChessGame& other) const;

    // Overloads <
    bool operator<(const ChessGame& other) const;

    // Overloads ==
    bool operator==(const ChessGame& other) const;

    // Overloads >=
    bool operator>=(const ChessGame& other) const;

    // Overloads <=
    bool operator<=(const ChessGame& other) const;

    double getScore();
};
