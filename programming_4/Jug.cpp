#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Jug.h"

using namespace std;

Jug::Jug(int Ca,int Cb,int N,int cfA,int cfB,int ceA,int ceB,int cpAB,int cpBA) :
    Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA)
{

    //create graph

    vertex cfA_v("cfA");
    vertex cfB_v("cfB");
    vertex ceA_v("ceA");
    vertex ceB_v("ceB");
    vertex cpAB_v("cpAB");
    vertex cpBA_v("cpBA");

    cfA_v.adjacent.push_back(pair<int, int>(1, cfB));
    cfA_v.adjacent.push_back(pair<int, int>(4, cpAB));

    cfB_v.adjacent.push_back(pair<int, int>(0, cfA));
    cfB_v.adjacent.push_back(pair<int, int>(5, cpBA));

    ceA_v.adjacent.push_back(pair<int, int>(1, cfB));
    ceA_v.adjacent.push_back(pair<int, int>(3, ceB));
    ceA_v.adjacent.push_back(pair<int, int>(5, cpBA));

    ceB_v.adjacent.push_back(pair<int, int>(0, cfA));
    ceB_v.adjacent.push_back(pair<int, int>(2, ceA));
    ceB_v.adjacent.push_back(pair<int, int>(4, cpAB));

    cpAB_v.adjacent.push_back(pair<int, int>(0, cfA));
    cpAB_v.adjacent.push_back(pair<int, int>(3, ceB));
    cpAB_v.adjacent.push_back(pair<int, int>(5, cpBA));

    cpBA_v.adjacent.push_back(pair<int, int>(0, cfA));
    cpBA_v.adjacent.push_back(pair<int, int>(1, cfB));
    cpBA_v.adjacent.push_back(pair<int, int>(2, ceA));
    cpBA_v.adjacent.push_back(pair<int, int>(3, ceB));
    cpBA_v.adjacent.push_back(pair<int, int>(4, cpAB));

    graph.push_back(cfA_v); 
    graph.push_back(cfB_v); 
    graph.push_back(ceA_v); 
    graph.push_back(ceB_v); 
    graph.push_back(cpAB_v);
    graph.push_back(cpBA_v);
}

Jug::~Jug() {
    graph.clear();
}

// // This looks up an A:B combination in the graph and returns its
// // id (same as its index)
// int Jug::findInGraph(int A, int B, vector<int>& unfinishedVertices) {
//     // We may already have this combination of A and B.  If so, return it
//     for(int i=0; i < graph.size(); ++i) {
//       if (graph[i].A == A and graph[i].B == B) return i;
//     }

//     // We did not have it, so create a new vertex with this combination
//     // Also add the index to the list of unfinished nodes so we remember
//     // to set its six outedges
//     int id = graph.size();
//     unfinishedVertices.push_back(id);
//     // cout << "Add: " << A << "," << B << " at index " << id << endl;
//     graph.push_back( vertex(A, B, id) );
//     return id;
// }

//solve is used to check input and find the solution if one exists
//returns -1 if invalid inputs. solution set to empty string.
//returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
//returns 1 if solution is found and stores solution steps in solution string.
int Jug::solve(string &solution) {
    //Check input to make sure capacities are positive and Ca is less than or equal to Cb
    if (((Ca < 0) || (Cb < 0)) || (Ca > Cb)) {
        solution = "";
        return -1;
    }
    //Checkinput to make sure costs are positive
    if ((cfA < 0) || (cfB < 0) || (ceA < 0) || (ceB < 0)) {
        solution = "";
        return -1;
    }
    //Check input to make sure goal is less than or equal to capacity B and both are less than 1000
    if ((N > 1000) || (N > Cb) || (Cb > 1000)) {
        solution = "";
        return -1;
    } 

    vector<int> steps;

    steps = solveHelper();

    if (!steps.empty()) {
        result(steps, solution);
        return 1;
    }
    else {
        solution = "";
        return 0;
    }
    return -1;
}

vector<int> Jug::solveHelper() {
    list<pair<int, int>> A;
    list<pair<int, int>> B;

    vector<int> aSteps;
    vector<int> bSteps;

    A.push_back(pair<int,int>(0,0));
    B.push_back(pair<int, int>(0,0));

    aSteps = traverse(0, aSteps, A);
    bSteps = traverse(1, bSteps, B);

    if (aSteps.empty()) {
        return bSteps;
    }
    else if (bSteps.empty()) {
        return aSteps;
    }
    
    if (aSteps < bSteps) {
        return aSteps;
    }
    else {
        return bSteps;
    }

    if (calculateCost(aSteps) < calculateCost(bSteps)) {
        return aSteps;
    }

    return bSteps;

}

vector<int> Jug::traverse(int index, vector<int> steps, list<pair<int, int>> route) {
    vector<int> v;
    vector<int> v2;

    int A;
    int B;
    int stepTaken;

    if ((route.back().first == 0) && (route.back().second == N)) {
        return steps;
    }

    auto iterator = graph.at(index).adjacent.begin();

    while (iterator != graph.at(index).adjacent.end()) {
        A = route.back().first;
        B = route.back().second;
        stepTaken = newState(A, B, iterator->first);    

        if (!(ifVisited(A, B, route))) {
            steps.push_back(stepTaken);
            route.push_back(pair<int, int>(A, B));
            if (v.size() == 0) {
                v = traverse(stepTaken, steps, route);
            }
            else {
                v2 = traverse(stepTaken, steps, route);
                if (calculateCost(v2) < calculateCost(v)) {
                    v = v2;
                }
            }
            steps.pop_back();
            route.pop_back();
        }
        iterator++;
    }

return v;

}

int Jug::newState(int& A, int& B, const int& stepIndex) {
   if (graph.at(stepIndex).key == "cfA") {
        A = Ca;
    } 
    else if (graph.at(stepIndex).key == "cfB") {
        B = Cb;
    } 
    else if (graph.at(stepIndex).key == "ceA") {
        A = 0;
    } 
    else if (graph.at(stepIndex).key == "ceB") {
        B = 0;
    } 
    else if (graph.at(stepIndex).key == "cpAB"){
        if (A + B <= Cb) {
            B += A;
            A = 0;
        }
        else {
            A -= (Cb - B);
            B = Cb;
        }
    } 
    else if (graph.at(stepIndex).key == "cpBA") {
        if (A + B <= Ca) {
            A += B;
            B = 0;
        } 
        else {
            B -= (Ca - A);
            A = Ca;
        }
    }
    return stepIndex; 
}

bool Jug::ifVisited(int A, int B, list<pair<int, int>> route) {
    auto iterator = route.begin();
    while (iterator != route.end()) {
        if (iterator->first == A && iterator->second == B) {
            return true;
        }
        iterator++;
    }
    return false;
}

int Jug::calculateCost(vector<int> steps) {
    int cost = 0;
    for (unsigned int i = 0; i < steps.size(); ++i) {
        if (steps.at(i) == 0) {
            cost += cfA;
        }
        else if (steps.at(i) == 1) {
            cost += cfB;
        }
        else if (steps.at(i) == 2) {
            cost += ceA;
        }
        else if (steps.at(i) == 3) {
            cost += ceB;
        }
        else if (steps.at(i) == 4) {
            cost += cpAB;
        }
        else if (steps.at(i) == 5) {
            cost += cpBA;
        }
    }

return cost;
    
}

int Jug::result(vector<int>& steps, string& solution) const {
    ostringstream outSS;
    int cost = 0;

    for (unsigned int i = 0; i < steps.size(); ++i) {
        if (steps.at(i) == 0) {
            cost += cfA;
            outSS << "fill A" << endl;
        }
        else if (steps.at(i) == 1) {
            cost += cfB;
            outSS << "fill B" << endl;
        }
        else if (steps.at(i) == 2) {
            cost += ceA;
            outSS << "empty A" << endl;
        }
        else if (steps.at(i) == 3) {
            cost += ceB;
            outSS << "empty B" << endl;
        }
        else if (steps.at(i) == 4) {
            cost += cpAB;
            outSS << "pour A B" << endl;
        }
        else if (steps.at(i) == 5) {
            cost += cpBA;
            outSS << "pour B A" << endl;
        }
    }
    outSS << "success " << cost;
    solution = outSS.str();

    return cost;
}