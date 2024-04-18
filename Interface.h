#include <iostream>
#include <string>
#include <vector>
#include "ChessGame.h"
#include "DataReader.h"
#include "MergeSort.h"
#include "QuickSort.h"
#pragma once
using namespace std;


bool VerifyMove(string& move) {
    if (move.length() == 0)
        return false;
    if (move.length() > 5)
        return false;
    if (isdigit(move[0]))
        return false;
    if (isupper(move[0])) {
        if (move[0] != 'K' && move[0] != 'Q' && move[0] != 'R' && move[0] != 'B' && move[0] != 'N')
            return false;
    }
    return true;
}

bool ParseInput(string& totalMove, string& move1, string& move2) {
    bool invalid = true;
    int start;
    for (int i = 0; i < totalMove.length(); ++i) {
        if (totalMove[i] == ' ') {
            invalid = false;
            move1 = totalMove.substr(0, i);
            start = i+1;
            break;
        }
    }
    if (invalid)
        return false;
    move2 = totalMove.substr(start, totalMove.length()-move1.length()-1);
    return true;
}

void userInterface() {
    ChessGame userGame;
    vector<string> userMoves;

    DataReader reader("games_metadata_profile_2024_01.csv");
    reader.read();

    string numMovesString;
    int numMoves;
    string optionString;
    int option;
    cout << "Welcome to Board Buddy!" << endl;
    cout << "Enter 1 to manually input moves." << endl;
    cout << "Enter 2 to copy and paste a valid string of moves from a pre-existing game." << endl;
    cout << "Option: ";
    std::getline(cin, optionString);
    option = stoi(optionString);

    if (option == 1) {
        while (true) {
            cout << "Number of Moves: ";
            std::getline(cin, numMovesString);
            try {
                numMoves = stoi(numMovesString);
                cout << endl;
                break;
            }
            catch (const invalid_argument& e) {
                cout << "Please enter a valid number" << endl;
            }
        }
        cout << "Please enter each move in algebraic chess notation (i.e. e4 e5). Then press Enter." << endl;
        string totalMove;
        string p1move;
        string p2move;
        for (int i = 1; i <= numMoves; ++i) {
            cout << "Move " << i << ": ";
            std::getline(cin, totalMove);
            if (!ParseInput(totalMove, p1move, p2move)) {
                cout << "You have entered an invalid move. Please make sure your input is in the format [white move] [black move]." << endl;
                i--;
                continue;
            }
            if (!VerifyMove(p1move) || !VerifyMove(p2move)) {
                cout << "You have entered an invalid move. Please check your entries." << endl;
                i--;
                continue;
            }
            userMoves.push_back(p1move);
            userMoves.push_back(p2move);
        }

    }
    else if (option == 2) {
        string userInputString;
        getline(cin, userInputString);
        userMoves = reader.parseMove(userInputString);
    }
    else {
        cout << "Please Enter a valid number." << endl;
        exit(1);
    }

    userGame.moves = userMoves;
    reader.assignAllSimilarityScores(userGame);

    string sortString;
    int sortOption;
    cout << "Which sort would you like to use?" << endl;
    cout << "1. QuickSort" << endl << "2. MergeSort" << endl;

    while (true) {
        cout << "Enter a number: ";
        std::getline(cin, sortString);
        try {
            sortOption = stoi(sortString);
            cout << endl;
            break;
        }
        catch (const invalid_argument& e) {
            cout << "Please enter a valid number." << endl;
        }
    }
    std::getline(cin, sortString);
    sortOption = stoi(sortString);
    if (sortOption == 1) {
        quickSort(reader.games, 0, reader.games.size()-1);
    }
    else if (sortOption == 2) {
        MergeSort(reader.games, 0, reader.games.size()-1);
    }
    else {
        cout << "Please enter a valid number." << endl;
        exit(1);
    }

    string numGamesString;
    int numGames;
    cout << "How many games would you like to view?" << endl;
    cout << "Number of games: ";
    getline(cin, numGamesString);
    numGames = stoi(numGamesString);
    for (int i = 0; i < numGames; ++i) {
        cout << "Game " << i + 1 << ":" << endl;
        reader.games[i]->displayInfo();
        cout << endl;
    }
}
