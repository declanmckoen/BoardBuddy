#include <iostream>
#include <string>
#include <vector>
#include "ChessGame.h"
#include "DataReader.h"
#include "MergeSort.h"
#include "QuickSort.h"
#pragma once
using namespace std;

void programLoop(DataReader& reader, ChessGame& userGame){
    vector<string> userMoves;

    string numMovesString;
    int numMoves;

    string optionString;

    cout << "Enter 1 to manually input moves." << endl;
    cout << "Enter 2 to copy and paste a valid string of moves from a pre-existing game." << endl << endl;

    cout << "Option: ";
    cin >> optionString;

    while (optionString != "1" && optionString != "2") {
        cout << "Invalid option! Try again: ";
        cin >> optionString;
    }

    //Move Entries
    if (optionString == "1") {
        cout << "Please enter how many moves you will input: " << endl;
        cout << "Moves: ";
        cin >> numMoves;
        cout << endl << "Please enter each move in algebraic chess notation (i.e. e4). Then press Enter." << endl;
        string totalMove;
        for (int i = 1; i <= numMoves; ++i) {
            for(int j = 0; j < 2; j++){
                if(j % 2 == 0){
                    cout << "Move " << i << " (White): ";
                }else{
                    cout << "Move " << i << " (Black): ";
                }

                cin >> totalMove;
                if (!DataReader::isValidMove(totalMove)) { //is invalid entry
                    cout << " > Error: Invalid Move! Try again." << endl;
                    j--;
                }else{ //is valid entry
                    vector<string> movesToInput = reader.parseMove(totalMove);
                    for(const auto& str : movesToInput){
                        userMoves.push_back(str);
                    }
                }
            }

        }

    }
    else if (optionString == "2") {
        string userInputString;
        cout << "Paste your move data: " << endl;
        cin.ignore();
        getline(cin, userInputString);
        userMoves = reader.parseMove(userInputString);
    }

    cout << endl << "Inputted Moves: " << endl;
    for(const auto& s : userMoves){
        cout << s << " ";
    }
    cout << endl << endl;

    userGame.moves = userMoves;

    //reader.assignAllSimilarityScores(&userGame);
    reader.assignAllRandomSimilarityScores();
    cout << "Which sort would you like to use?" << endl;
    cout << "1. QuickSort" << endl << "2. MergeSort" << endl;

    cout << "Option: ";
    cin >> optionString;

    while (optionString != "1" && optionString != "2") {
        cout << "Invalid option! Try again: ";
        cin >> optionString;
    }

    if (optionString == "1") {
        quickSort(reader.games, 0, reader.games.size()-1);
    }
    else if (optionString == "2") {
        MergeSort(reader.games, 0, reader.games.size()-1);
    }

    string numGamesString;
    int numGames;
    cout << endl << "How many games would you like to view?" << endl;
    cout << "Number of games: ";
    cin >> numGames;
    cout << endl;

    for (int i = 0; i < numGames; ++i) {
        cout << "#" << i + 1 << ". ";
        reader.games[i]->displayInfo();
        cout << endl;
    }
}
void userInterface() {
    ChessGame userGame;

    //Welcome Message
    cout << "Welcome to Board Buddy!\n"
            "Authors: Nick Lucindo, Declan McKoen, Justin Wang \n"<< endl;

    cout << "Enter the filepath of the chess game CSV file\n"
            "... or enter \"d\" and we will assume it is in data\\games_metadata_profile_2024_01.csv folder\n";

    DataReader reader;
    string filepath;

    //File Path Entry
    cout << "Enter filepath: ";
    cin >> filepath;

    if(filepath == "d"){
        filepath = "./data/games_metadata_profile_2024_01.csv";
    }

    //Read the column data
    while(!reader.read(filepath)){
        cout << "Unsuccessful! Try again?: ";
        cin >> filepath;

        if(filepath == "d"){
            filepath = "./data/games_metadata_profile_2024_01.csv";
        }
    }
    cout << endl << "File opened successfully." << endl;

    //Read the moves (contained within data[MOVES])
    cout << "Reading and parsing move sets for each game... this WILL take a while!" << endl;
    cout << " > Each . represents 1,000 movesets parsed" << endl;
    cout << " > Each ! represents 10,000 movesets parsed" << endl << endl;

    //reader.parseAllMoves();

    programLoop(reader, userGame);
}
