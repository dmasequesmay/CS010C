#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

void Playlist::Print(string title) const {
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;    
    //Test case: empty playlist
    if (head == nullptr) {
        cout << "Playlist is empty" << endl;
    }
    else {
        PlaylistNode *curr = head;
        int count = 1;
        //Start from beginning of the list and call PrintPlaylistNode for each node in the list  
        while (curr->GetNext() != nullptr) {
            cout << count << "." << endl;
            count++;
            curr->PrintPlaylistNode();
            curr = curr->GetNext();
            cout << endl;
        }
        //Makes sure the last playlist node does not end with a newline
        cout << count << "." << endl;
        curr->PrintPlaylistNode();
    }
}

void Playlist::AddSong(string ID, string songName, string artistName, int length) {

    //Use parameterized constructor
    PlaylistNode *target = new PlaylistNode(ID, songName, artistName, length);
    //Test case: empty playlist
    if (head == nullptr) {
        head = target;
        tail = target;
    }
    //Insert at end 
    else {
        tail->InsertAfter(target);
        tail = target;
    }
    
}

void Playlist::RemoveSong(string ID) {
    //If there is only 1 Node
    if (head == tail) {
        cout << '"' << head->GetSongName() << '"' << " removed." << endl;
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    //If removing the first node
    if (head != nullptr) {
        if (head->GetID() == ID) {
            PlaylistNode *target = nullptr;
            cout << '"' << head->GetSongName() << '"' << " removed." << endl;
            target = head;
            head = target->GetNext();
            delete target;
            target = nullptr;
        }
    }
    
    PlaylistNode *prev = head;
    PlaylistNode *curr = head->GetNext();
    PlaylistNode *target = nullptr;
    //Start at beginning of the list and match song names to find node to delete
    while (curr != nullptr) {
        if (curr->GetID() == ID) {
            cout << '"' << curr->GetSongName() << '"' << " removed." << endl;
            target = curr;
            prev->SetNext(target->GetNext());
            delete target;
            target = nullptr;
            curr = nullptr;
        }
        else {
            prev = prev->GetNext();
            curr = curr->GetNext();
        }
    }
}

void Playlist::ChangePosition(int currPosition, int newPosition) {
    //Find number of nodes in playlist and currPosition
    PlaylistNode *target = head;
    PlaylistNode *prev = nullptr;
    PlaylistNode *currPositionNode = nullptr;
    PlaylistNode *newPositionNode = nullptr;
    string songName;
    int count = 1;
    //Locate currPositionNode and prev
    if (currPosition == 1) {
        currPositionNode = target;
        songName = target->GetSongName();
    } else {
        while (target != nullptr) {
            if ((count + 1) == currPosition) {
                prev = target;
                currPositionNode = target->GetNext();
                songName = target->GetNext()->GetSongName();
            }
            count++;
            target = target->GetNext();
            }
    }

    target = head;

    //If curr position is 1
    if (currPosition == 1) {
        cout << '"' << songName << '"' << " moved to position " << newPosition << endl;
        //Start at beginning of the list and find node to insert at new position
        while (target != nullptr) {
            if (count == newPosition) {
                newPositionNode = target;
            }
            count++;
            target = target->GetNext();
        }
        head = currPositionNode->GetNext(); 
        currPositionNode->SetNext(newPositionNode->GetNext());
        newPositionNode->SetNext(currPositionNode);
    }
    //If new position is less than 1, move node to position 1
    else if (newPosition <= 1) {
        cout << '"' << songName << '"' << " moved to position 1" << endl;
        prev->SetNext(currPositionNode->GetNext());
        currPositionNode->SetNext(head);
        head = currPositionNode;
    }
    //If new position is greater than number of nodes, move to tail
    else if (newPosition >= count) {
        cout << '"' << songName << '"' << " moved to position " << count << endl;
        prev->SetNext(currPositionNode->GetNext());
        tail->SetNext(currPositionNode);
        tail = currPositionNode;
        currPositionNode->SetNext(nullptr);
    }
    else if (newPosition > currPosition) {
        cout << '"' << songName << '"' << " moved to position " << newPosition << endl;
        //Locate newPositionNode
        count = 1;
        while (target != nullptr) {
            if (count == newPosition) {
                newPositionNode = target;
            }
            count++;
            target = target->GetNext();
        }
        prev->SetNext(currPositionNode->GetNext());
        currPositionNode->SetNext(newPositionNode->GetNext());
        newPositionNode->SetNext(currPositionNode);
    }
    else if (newPosition < currPosition) {
        cout << '"' << songName << '"' << " moved to position " << newPosition << endl;
        //Locate the node before the newPosition node
        count = 1;
        while (target != nullptr) {
            if (count + 1 == newPosition) {
                newPositionNode = target;
            }
            count++;
            target = target->GetNext();
        }
        prev->SetNext(currPositionNode->GetNext());
        currPositionNode->SetNext(newPositionNode->GetNext());
        newPositionNode->SetNext(currPositionNode);
    }
    //Makes sure tail is not dangling pointer
    if (newPosition == count) {
        tail = currPositionNode;
    }
}

void Playlist::SpecificArtist(string userInput) {
    PlaylistNode *target = head;
    int count = 1;
    //Start at beginning of list and call PrintPlaylistNode if artist names match
    while (target->GetNext() != nullptr) {
        if (target->GetArtistName() == userInput) {
            cout << endl;
            cout << count << '.' << endl;
            target->PrintPlaylistNode();
        }
        count++;
        target = target->GetNext();
    }
    //Makes sure the last playlist node does not end with a newline
    if (target->GetArtistName() == userInput) {
        cout << endl;
        cout << count << '.' << endl;
        target->PrintPlaylistNode();
    }
}

int Playlist::TotalTime() {
    int totalTime = 0;
    PlaylistNode *target = head;
    while (target != nullptr) {
        totalTime += target->GetSongLength();
        target = target->GetNext();
        //cout << totalTime << endl;
    }
    return totalTime;
}