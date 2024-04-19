
#include "ChessGame.h"

// Overload the > operator
bool ChessGame::operator>(const ChessGame& other) const {
    return score > other.score;
}

// Overload the < operator
bool ChessGame::operator<(const ChessGame& other) const {
    return score < other.score;
}

// Overload the == operator
bool ChessGame::operator==(const ChessGame& other) const {
    return score == other.score;
}

// Overload the >= operator
bool ChessGame::operator>=(const ChessGame& other) const {
    return score >= other.score;
}

// Overload the <= operator
bool ChessGame::operator<=(const ChessGame& other) const {
    return score <= other.score;
}

void ChessGame::assignScore(ChessGame *otherGame) {
    auto otherMoves = otherGame->moves;

    double s = 0;
    int error = 0;
    int i = 0;

    //Loop through moves.
    //Matching moves grant score, non-matching moves reduce score gained in the future until 10 errors.
    while(i < otherMoves.size() && i < moves.size()){
        if(moves[i] == otherMoves[i]){
            s += 1 * (1 - 0.1 * error);
        }else{
            error++;
        }

        if(error == 10){
            break;
        }
    }

    score = s / min(otherMoves.size(), moves.size());
}

double ChessGame::getScore() {
    return score;
}
