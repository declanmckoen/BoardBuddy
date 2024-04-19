// Nicholas Lucindo - 4/18/2024

#include <iostream>
#include "ChessGame.h"

#include <random> // Testing purposes
#include <algorithm> // For std::reverse


// Code for running tests
double generateRandomNumber() {
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0); // Define the range [0.0, 1.0)

    // Generate a random number between 0 and 1
    return dis(gen);
}

// Function to print elements of the vector
void printTest(vector<ChessGame*>& games, int size) {
    for (int i = 0; i < size; i++)
        cout << games[i]->getScore() << " ";
    cout << endl;
}

//Partitions according to pivot
int partition(vector<ChessGame*>& games, int low, int high) {
    double pivot = games[low]->getScore();
    int up = low;
    int down = high;

    while (up < down) {
        for (int j = up; j < high; j++) {
            if (games[up]->getScore() > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (games[down]->getScore() < pivot)
                break;
            down--;
        }
        if (up < down)
            swap(games[up], games[down]);
    }
    swap(games[low],games[down]);
    return down;
}


void quickSort(vector<ChessGame*>& games, int low, int high) {
    if (low < high) {
        int pivot = partition(games, low, high);
        quickSort(games, low, pivot - 1);
        quickSort(games, pivot + 1, high);
    }
}