#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

void PrintMenu(string);

int main () {

    //Prompt user for title of playlist
    string title;
    cout << "Enter playlist's title:" << endl;
    getline(cin,title);
    //cout << title << endl;

    //Implement PrintMenu() function
    PrintMenu(title);

    return 0;

}

void PrintMenu(string title) {
    
    char userInput = 'z';
    Playlist myPlaylist;

    while (userInput != 'q') {

        cout << endl;
        cout << title << " PLAYLIST MENU" << endl;
        cout << "a - Add song" << endl;
        cout << "d - Remove song" << endl;
        cout << "c - Change position of song" << endl;
        cout << "s - Output songs by specific artist" << endl;
        cout << "t - Output total time of playlist (in seconds)" << endl;
        cout << "o - Output full playlist" << endl;
        cout << "q - Quit" << endl << endl;

        cout << "Choose an option:" << endl;
        cin >> userInput;
        //cout << userInput << endl;

        if (userInput == 'q') {
            exit(1);
        }
        if (userInput == 'o') {
            myPlaylist.Print(title);
        }
        if (userInput == 'a') {
            string ID;
            string songName;
            string artistName;
            int length;
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> ID;
            cout << "Enter song's name:" << endl;
            getline(cin,songName);
            getline(cin,songName);
            cout << "Enter artist's name:" <<endl;
            getline(cin,artistName);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> length;

            myPlaylist.AddSong(ID, songName, artistName, length);
        }
        if (userInput == 'd') {
            string ID;
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> ID;
            
            myPlaylist.RemoveSong(ID);
        }
        if (userInput == 'c') {
            int currPosition;
            int newPosition;
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            cin >> currPosition;
            cout << "Enter new position for song:" << endl;
            cin >> newPosition;

            myPlaylist.ChangePosition(currPosition, newPosition);
        }
        if (userInput == 's') {
            string userInput;
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;
            cin.ignore();
            getline(cin, userInput);

            myPlaylist.SpecificArtist(userInput);
        }
        if (userInput == 't') {
            int totalTime;
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            
            totalTime = myPlaylist.TotalTime();

            cout << "Total time: " << totalTime << " seconds" << endl;
        }

    }

}