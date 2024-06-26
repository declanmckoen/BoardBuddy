#include <iostream>
#include <string>
#include <vector>
#include <chrono>
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
    cin.ignore(1000, '\n');
    if (optionString == "1") {
        cout << "Please enter how many moves you will input: " << endl;
        while (true) {
            cout << "Moves: ";
            try {
                getline(cin, numMovesString);
                numMoves = stoi(numMovesString);
                break;
            }
            catch (invalid_argument& e) {
                cout << "Please enter a valid number" << endl;
            }
        }
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

    reader.assignAllSimilarityScores(&userGame);
    //reader.assignAllRandomSimilarityScores();
    cout << "Which sort would you like to use?" << endl;
    cout << "1. QuickSort" << endl << "2. MergeSort" << endl;

    cout << "Option: ";
    cin >> optionString;

    while (optionString != "1" && optionString != "2") {
        cout << "Invalid option! Try again: ";
        cin >> optionString;
    }

    if (optionString == "1") {
        auto start = chrono::high_resolution_clock::now();
        quickSort(reader.games, 0, reader.games.size()-1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "QuickSort time: " << duration.count() << " milliseconds" << endl << endl;
    }
    else if (optionString == "2") {
        auto start = chrono::high_resolution_clock::now();
        MergeSort(reader.games, 0, reader.games.size()-1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "MergeSort time: " << duration.count() << " milliseconds" << endl << endl;
    }

    string numGamesString;
    int numGames;
    cin.ignore(1000, '\n');
    cout << endl << "How many games would you like to view?" << endl;
    while (true) {
        cout << "Number of games: ";
        try {
            getline(cin, numGamesString);
            numGames = stoi(numGamesString);
            break;
        }
        catch (invalid_argument& e) {
            cout << "Please enter a valid number" << endl;
        }
    }

    int i;
    for (i = 0; i < numGames; i++) {
        cout << "#" << i + 1 << ". ";
        reader.games[i]->displayInfo();
        cout << endl;
    }

    //Displays extra entries
    cout << "Enter 'm' to display 1 more entry, enter anything else to exit." << endl;

    while(true){
        cout << "Option: ";
        cin >> optionString;
        if(optionString != "m"){
            break;
        }
        cout << "#" << i + 1 << ". ";
        reader.games[i]->displayInfo();
        cout << endl;
        i++;
    }

    cout << "Exiting!" << endl;
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
    cout << endl << "File opened successfully.\n" << endl;

    string movesPath;
    string stringOption;
    cout << "Enter the filepath of the chess game moveset file\n";
    cout << "Enter 'q' if you don't know what that is!\n";
    cout << "Enter 'm' if you do know what that is and it is in ./data/moves.txt\n";
    cout << "Moveset Path: ";
    cin >> stringOption;

    if(stringOption == "q"){ //If the data isn't parsed for some reason
        cout << "The moveset path is where a parsed version of the moves of each game will be stored.\n";
        cout << "What would you like the path of this file to be? Include the extension '.txt'\n";
        cout << "Moveset Path: ";
        cin >> movesPath;
        reader.setMoveSetFilePath(movesPath);

        //Read the moves (contained within data[MOVES])
        cout << "Reading, parsing, and writing move sets for each game... this WILL take a while!" << endl;
        cout << " > Each . represents 1,000 movesets parsed" << endl;
        cout << " > Each ! represents 10,000 movesets parsed" << endl << endl;

        reader.parseAllMoves();
    }else{
        movesPath = stringOption;

        if(movesPath == "m"){
            movesPath = "./data/moves.txt";
        }
        reader.setMoveSetFilePath(movesPath);
        reader.readMoveSetDotTxt();
    }

    //reader.parseAllMoves();

    bool runAgain = true;
    string againString;
    while(runAgain){
        programLoop(reader, userGame);

        cout << "Would you like to create a new search?" << endl;
        cout << "Enter 'y' for yes, and anything else for no.";
        cout << "Option: ";
        cin >> againString;
        if(againString == "y"){
            runAgain = true;
        }else{
            runAgain = false;
        }
    }

    cout << endl << "Goodbye! Thanks for using BoardBuddy!";
}
