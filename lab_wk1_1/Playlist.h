#include <iostream>
#include <string>

#ifndef PLAYLIST_H
#define PLAYLIST_H

using namespace std;

class PlaylistNode {

    public:
        //Default constructor
        PlaylistNode () 
            :   uniqueID("none"),
                songName("none"),
                artistName("none"),
                songLength(0),
                nextNodePtr(nullptr)
        {

        }
        //Parameterized constructor
        PlaylistNode (string uniqueID, string songName, string artistName, int songLength) 
                :   uniqueID(uniqueID), 
                    songName(songName), 
                    artistName(artistName), 
                    songLength(songLength)
        {

        }
        //Mutator
        void InsertAfter(PlaylistNode *target) {
            nextNodePtr = target;
        }
        //Mutator
        void SetNext(PlaylistNode *target) {
            nextNodePtr = target;
        }
        //Accessor
        const string& GetID() const {
            return uniqueID;
        }
        //Accessor
        const string& GetSongName() const {
            return songName;
        }
        //Accessor
        const string& GetArtistName() const {
            return artistName;
        }
        //Accessor
        int GetSongLength() const {
            return songLength;
        }
        //Accessor
        PlaylistNode* GetNext() {
            return nextNodePtr;
        }

        void PrintPlaylistNode();



    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;

};

class Playlist {

    public: 
        //Default constructor
        Playlist() 
            :   head(nullptr),
                tail(nullptr)
        {

        }
        //Destructor
        ~Playlist() {
            PlaylistNode* curr = head;
            PlaylistNode* temp = curr;
            while (curr != nullptr) {
                curr = curr->GetNext();
                delete temp;
                temp = curr;        
            }
        }

        void Print(string) const ;

        void AddSong(string ID, string songName, string artistName, int length);

        void RemoveSong(string ID);

        void ChangePosition(int , int);

        void SpecificArtist(string);

        int TotalTime();

    private: 
        PlaylistNode *head;
        PlaylistNode *tail;
        //Copy constructor can not be accessed or implemented
        Playlist(const Playlist&); 

};

#endif