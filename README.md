# Welcome to Board Buddy! #
Authors: Nick Lucindo, Declan McKoen, Justin Wang

My friends and I like to play chess, but the problem is: we suck. We're trying to find ways to improve, but everything online is so restricted, requiring you to pay for their services (I'm looking at you Chess.com).
The solution we came up with? Board Buddy! Board Buddy is a free-to-use platform that allows the user to input a chess game in the form of algebraic chess notation. After entering their game, the program sorts through the database to find games that closely resemble the inputted game via a complex, top-secret algorithm (mergesort / quicksort). These sorts order the games based on their similarity scores with the inputted game, allowing the user to compare their game with the top n similar games. We want to test which sort would work best. Thus, the user can decide which sort he/she would like to use. We hope to collect enough data from each sort in order to settle, helping us determine which sort is better. We also hope that this project will help you all improve your chess abilities.

## Setup Information ##
The program also assumes that the working directory is BoardBuddy (aka outside src/)
The program will ask you for the filepath of your Chess Game database file.
The chess game CSV file can be downloaded here:

https://www.kaggle.com/datasets/shkarupylomaxim/chess-games-dataset-lichess-2017-may

The program will also ask you for the filepath of the Moveset data file.
It can be downloaded here:

https://drive.google.com/file/d/1d8MWVI724-BdOxnStnH22ppi1MFnKDbg/view?usp=sharing

Note that this file corresponds to the CSV file above and will not reflect any changes made to it.
If changes are made to the original CSV file, the program is also able to rewrite the Moveset data file.

Other than that, all this program requires is C++ 17!
One other note: Reading the movesets when there is no Moveset data file can take a while.
One more note: if running the .exe fails via command line, try clicking the .exe in File Explorer (for some reason it makes a difference)

## Thank you! ##
Thank you for your interest in Board Buddy, and we hope you enjoy!
