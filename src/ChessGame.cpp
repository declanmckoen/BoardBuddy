#include <iostream>

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

    score = s;
}

double ChessGame::getScore() {
    return score;
}

void ChessGame::displayInfo() {
    cout << data[ChessGame::WHITE] << " (" << data[ChessGame::WHITE_ELO] << ") " << " vs. " << data[ChessGame::BLACK] << " (" << data[ChessGame::BLACK_ELO] << ") " << endl;
    if(data[ChessGame::RESULT] == "1-0"){
        cout << "Winner: White (" << data[ChessGame::WHITE] << ")";
    }else if(data[ChessGame::RESULT] == "1-0"){
        cout << "Winner: Black (" << data[ChessGame::BLACK] << ")";
    }else{
        cout << "Result: Draw!";
    }
    cout << " / Total Moves: " << data[TOTAL_MOVES] << endl;
    cout << " - " << "Opening: " << data[OPENING] << endl;
    cout << " - " << "Game Link: " << data[ChessGame::SITE] << endl;
    cout << " - " << "Similarity Score: " << score << endl;
}
