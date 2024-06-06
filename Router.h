/*
 Author : Ahmet Furkan KIZIL
 ID: 22203112
 Section : 3
 Homework : 4
 Description : Graphs
*/

#ifndef HW4_ROUTER_H
#define HW4_ROUTER_H
#include <iostream>
#include <fstream>
using namespace std;

struct Node{
    int value;
    Node* next;
    Node(const int value) : value(value), next(nullptr) {}
};

class Router {
public:
    // Queue class
    struct Queue {
        Node* frontOfQueue;
        Node* rearOfQueue;
        Queue() : frontOfQueue(nullptr), rearOfQueue(nullptr) {}
        void enqueue(Node* node);
        void dequeue(Node*& dequeuedNode);
        bool isEmpty() const;
    };

    Router(string fileName, int sourceRouterId, int destRouterId);
    void printTheAdjacencyList();
    void findShortestPath(int sourceRouterId, int destRouterId);
    int findDiameter();
    void printTheVisitedMatrix();
    void printShortestPath(int sourceRouterId, int destRouterId);
    int shortestBFS(int sourceRouterID);

private:
    Node** adjacencyList;
    int numberOfRouters;
    Queue theQueue;
    bool* visitedArray;
    int* parentVertex;  // Array to store parent vertex
    int* costOfWay;     // Array to store the cost of the way

};


#endif //HW4_ROUTER_H
