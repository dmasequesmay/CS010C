#ifndef JUG_H
#define JUG_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>

using namespace std;


class vertex {
  public:
    int A;			// How much in jug A
    int B;			// How much in jug B
	  int id;     //unique node id
    string key;

    // This is our adjacency list... each vertex can go one of six
    // places for our six possible actions.  Sometimes this is right
    // back to this vertex (e.g. if we are empty (0,0) and we do an
    // emptyA action, we are still empty.  -1 means unset here
    vector<int> newStateAfterAction;

    vertex(int A, int B, int id)
      : A(A), B(B), id(id), newStateAfterAction(6,-1)
    {}

    // vertex(int A, int B, int id, string key)
    //   : A(A), B(B), id(id), key(""), newStateAfterAction(6, -1)
    // {}

    vertex(string key) : key(key) 
    {}

    list<pair<int, int>> adjacent;
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
        int findInGraph(int, int, vector<int>&);
    private:
        //anything else you need
        int Ca;
        int Cb;
        int N;
        int cfA;
        int cfB;
        int ceA;
        int ceB;
        int cpAB;
        int cpBA;
        // This is the graph we are trying to build.  Each vertex has six
        // outedges that represent the new state AFTER you do a...
        // * fillA
        // * fillB
        // * emptyA
        // * emptyB
        // * pourAToB
        // * pourBToA
        vector<vertex> graph;
        vector<int> solveHelper();
        vector<int> traverse(int, vector<int>, list<pair<int, int>>);
        int newState(int& A, int& B, const int& stepIndex);
        bool ifVisited(int, int, list<pair<int, int>>);
        int calculateCost(vector<int>);
        int result(vector<int>& steps, string& solution) const;

};

#endif
