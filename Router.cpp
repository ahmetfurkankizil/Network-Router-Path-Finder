/*
 Author : Ahmet Furkan KIZIL
 ID: 22203112
 Section : 3
 Homework : 4
 Description : Graphs
*/

#include "Router.h"


// Real one
int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <filename> <param1> <param2>" << endl;
        return 1;
    }

    string fileName = argv[1];
    int sourceRouterId = stoi(argv[2]);
    int destRouterId = stoi(argv[3]);

    Router router(fileName, sourceRouterId, destRouterId);
    router.findShortestPath(sourceRouterId, destRouterId);
    router.printShortestPath(sourceRouterId, destRouterId);
    cout << endl;
    cout << "Diameter of the graph is " << router.findDiameter() << endl;
    return 0;
}

/*
int main(){
    string fileName = "/Users/ahmetfurkankizil/Desktop/hw4 tests/input4.txt";
    int sourceRouterId = 14;
    int destRouterId = 77;
    Router router(fileName, sourceRouterId, destRouterId);
    router.findShortestPath(sourceRouterId, destRouterId);
    router.printShortestPath(sourceRouterId, destRouterId);
    cout << endl;
    cout << "Diameter of the graph is " << router.findDiameter();
}
*/


Router::Router(string fileName, int sourceRouterId, int destRouterId) {

    // Retrieving the number of routers
    ifstream file(fileName);
    file >> this->numberOfRouters;

    this->visitedArray = new bool[this->numberOfRouters];
    this->parentVertex = new int[this->numberOfRouters];
    this->costOfWay = new int[this->numberOfRouters];

    for (int i = 0; i < this->numberOfRouters ; ++i) {
        visitedArray[i] = false;
        parentVertex[i] = -1;
        costOfWay[i] = -1;
    }

    // Creating and initialising the adjacency list accordingly
    this->adjacencyList = new Node *[this->numberOfRouters];
    for (int i = 0; i < this->numberOfRouters; ++i) {
        adjacencyList[i] = nullptr;
    }

    int routerId;
    int degreeOfRouter;

    while(file >> routerId) {
        file >> degreeOfRouter;
        int adjacencyIndex = 0;
        while (adjacencyIndex < degreeOfRouter) {
            int currValue;
            file >> currValue;
            Node* currNode = new Node(currValue);
            // Constructing the adjacency list
            if (this->adjacencyList[routerId] == nullptr) {
                this->adjacencyList[routerId] = currNode;
            } else {
                Node* temp = this->adjacencyList[routerId];
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = currNode;
            }
            adjacencyIndex++;
        }
    }

    this->theQueue = Queue();
}


void Router::findShortestPath(int sourceRouterId, int destinationRouterId) {

    Node* adjacencyListCopy[this->numberOfRouters];
    for (int i = 0; i < this->numberOfRouters; ++i) {
        adjacencyListCopy[i] = nullptr;
    }

    for (int i = 0; i < this->numberOfRouters; ++i) {
        Node* current = this->adjacencyList[i];
        Node* prevCopyNode = nullptr;

        // Copying the adjacency list for each router
        while (current != nullptr) {
            Node* newNode = new Node(current->value);
            if (prevCopyNode == nullptr) {
                adjacencyListCopy[i] = newNode;
            } else {
                prevCopyNode->next = newNode;
            }
            prevCopyNode = newNode;
            current = current->next;
        }
    }

    Node *sourceRouter = new Node(sourceRouterId);
    this->theQueue.enqueue(sourceRouter);
    this->visitedArray[sourceRouterId] = true;

    this->parentVertex[sourceRouterId] = sourceRouterId;
    this->costOfWay[sourceRouterId] = 0;

    while (!theQueue.isEmpty()) {
        Node* dequeuedNode;
        theQueue.dequeue(dequeuedNode);                          // Dequeued node
        int currVertexId = dequeuedNode->value;

        Node* currVertex = adjacencyListCopy[currVertexId];       // First adjacent vertex of the dequeued node
        while (currVertex != nullptr) {
            if (!visitedArray[currVertex->value]) {
                visitedArray[currVertex->value] = true;
                this->theQueue.enqueue(currVertex);

                this->parentVertex[currVertex->value] = currVertexId;
                this->costOfWay[currVertex->value] = this->costOfWay[currVertexId] + 1;
            }
            currVertex = currVertex->next;

        }
    }
}


int Router::findDiameter() {
    int diameter = 0;
    for (int i = 0; i < numberOfRouters; ++i) {
        int diameterCandidate = shortestBFS(i);
        if(diameter < diameterCandidate) {
            diameter = diameterCandidate;
        }
    }

    return diameter;
}

// For debugging purposes
void Router::printTheAdjacencyList() {
    for (int i = 0; i < this->numberOfRouters; ++i) {
        cout << "Router ID " << i << ":";
        Node* current = this->adjacencyList[i];
        while (current != nullptr) {
            cout << " " << current->value;
            if (current->next != nullptr) {
                cout << " ->";
            }
            current = current->next;
        }
        cout << endl;
    }
}

void Router::printShortestPath(int sourceRouterId, int destRouterId) {
    cout << "Path consists of " << costOfWay[destRouterId] + 1 << " routers:" << endl;
    int pathArray[costOfWay[destRouterId] + 1];

    int vertex = destRouterId;

    int tempIndex = 0;
    while (vertex != sourceRouterId) {
        pathArray[tempIndex] = vertex;
        vertex = parentVertex[vertex];
        tempIndex++;
    }
    pathArray[tempIndex] = sourceRouterId;

    for (int i = (costOfWay[destRouterId]); i >= 0; --i) {
        if (i != 0) {
            cout << pathArray[i] << endl;
        } else {
            cout << pathArray[i];
        }
    }

}


void Router::printTheVisitedMatrix() {
    for (int i = 0; i < numberOfRouters ; ++i) {
        cout << i << ".th router: ";
        if(visitedArray[i]) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
}

void Router::Queue::enqueue(Node *node) {
    if (rearOfQueue == nullptr) {
        frontOfQueue = rearOfQueue = node;
    } else {
        rearOfQueue->next = node;
        rearOfQueue = node;
    }
}

void Router::Queue::dequeue(Node*& dequeuedNode) {
    if (isEmpty()) {
        dequeuedNode = nullptr;
        return;
    }
    dequeuedNode = frontOfQueue;
    frontOfQueue = frontOfQueue->next;
    if (frontOfQueue == nullptr) {
        rearOfQueue = nullptr;
    }
    dequeuedNode->next = nullptr;
}



bool Router::Queue::isEmpty() const {
    return (frontOfQueue == nullptr);
}

int Router::shortestBFS(int sourceRouterId) {
    Queue bfsQueue = Queue();
    bool visitedArrayBFS[this->numberOfRouters];
    int parentVertexBFS[this->numberOfRouters];
    int costOfWayBFS[this->numberOfRouters];

    for (int i = 0; i < this->numberOfRouters; ++i) {
        visitedArrayBFS[i] = false;
        parentVertexBFS[i] = -1;
        costOfWayBFS[i] = -1;
    }

    Node* adjacencyListCopy[this->numberOfRouters];
    for (int i = 0; i < this->numberOfRouters; ++i) {
        adjacencyListCopy[i] = nullptr;
    }

    for (int i = 0; i < this->numberOfRouters; ++i) {
        Node* current = this->adjacencyList[i];
        Node* prevCopyNode = nullptr;

        // Copying the adjacency list for each router
        while (current != nullptr) {
            Node* newNode = new Node(current->value);
            if (prevCopyNode == nullptr) {
                adjacencyListCopy[i] = newNode;
            } else {
                prevCopyNode->next = newNode;
            }
            prevCopyNode = newNode;
            current = current->next;
        }
    }

    Node *sourceRouter = new Node(sourceRouterId);
    bfsQueue.enqueue(sourceRouter);
    visitedArrayBFS[sourceRouterId] = true;

    parentVertexBFS[sourceRouterId] = sourceRouterId;
    costOfWayBFS[sourceRouterId] = 0;

    while (!bfsQueue.isEmpty()) {
        Node* dequeuedNode;
        bfsQueue.dequeue(dequeuedNode);                          // Dequeued node
        int currVertexId = dequeuedNode->value;

        Node* currVertex = adjacencyListCopy[currVertexId];       // First adjacent vertex of the dequeued node
        while (currVertex != nullptr) {
            if (!visitedArrayBFS[currVertex->value]) {
                visitedArrayBFS[currVertex->value] = true;
                bfsQueue.enqueue(currVertex);

                parentVertexBFS[currVertex->value] = currVertexId;
                costOfWayBFS[currVertex->value] = costOfWayBFS[currVertexId] + 1;
            }
            currVertex = currVertex->next;

        }
    }

    int maximumCost = 0;
    for (int i = 0; i < numberOfRouters; ++i) {
        if(maximumCost < costOfWayBFS[i]) {
            maximumCost = costOfWayBFS[i];
        }
    }

    return maximumCost;
}
