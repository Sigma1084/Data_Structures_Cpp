#include <iostream>
#include <float.h>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;

#define inf INT32_MAX
#define TOTAL 2000



// A Point is just a point in a 20-dimensional space
// The location of the Point is stored in an array of floats of size 20

class Point {

public:

    // Just defining a static integer called dim which stores the dimension of every point
    // To access the dimension, use Point::dim
    static const int dim{ 20 };

    // This is Minkowski's metric of degree n
    static int metric;

    // The precession of the point to print
    static int precession;

    // Location is a list of (dim) number of floats
    // Note: (Point::dim) is used to access the dimension of the point
    float location[Point::dim] {};

    // We can have a data element associated with every Point (A data pointer)
    // int data;


public:

    // We have a constructor to take an array of 20 floats and a data (of type int)
    Point (float givenLoc[Point::dim]) {
        for (int i = 0; i < Point::dim; i++)
            location[i] = givenLoc[i];
    }

    // A Copy constructor
    Point (Point const &p) {
        for (int i = 0; i < Point::dim; i++)
            location[i] = p.location[i];
    }

    // An Empty Constructor
    Point () {}


    // Returns distance based on the static variable metric
    static float distance(Point &p1, Point &p2) {
        switch (Point::metric) {
            case 2: return euclidianDistance(p1, p2);
            case 1: return d1(p1, p2);
            case inf: return dInf(p1, p2);
        }
        return dn(p1, p2, Point::metric);
    }

    // Returns the dot product
    static float dotProduct(Point &p1, Point &p2) {
        float dotP = 0.0;
        for (int i=0; i < Point::dim; i++)
            dotP += p1[i] * p2[i];
        return dotP;
    }

    // Makes the passed point to be the origin
    static void makeOrigin(Point &p) {
        for (int i=0; i < Point::dim; i++)
            p[i] = 0;
    }


    // Operator Overloading []
    // p is of type Point. p[i] is similar to p.location[i]
    float& operator [] (int index) {
        if (index >= Point::dim || index < 0)
            exit(1);
        return this->location[index];
    }

    // Operator Overloading ==
    // Returns true if p1 is extremely close to p1 in the order of
    bool operator == (Point &p) {
        if (Point::distance(*this, p) < 1e-15)
            return true;
        return false;
    }

    // Operator overloading +=
    // p1 += p2 updates p1
    void operator += (Point &p2) {
        for (int i=0; i < Point::dim; i++)
            (*this)[i] += p2[i];
    }

    // Operator overloading -=
    // p1 -= p2 updates p1
    void operator -= (Point &p2) {
        for (int i=0; i < Point::dim; i++)
            (*this)[i] -= p2[i];
    }

    // Operator overloading *
    // p * c where p is a point and c is a float updates c
    void operator *= (float f) {
        for (int i=0; i < Point::dim; i++)
            (*this)[i] *= f;
    }


    // Used to print a point
    void printPoint () {
        cout << "( ";
        for (int i=0; i < Point::dim; i++)
            cout << std::fixed << std::setprecision(Point::precession) << location[i] << " ";
        cout << ")\n";
    }


private:

    // A static function is like the property of the whole class and not of a single variable
    // This takes in 2 Points and gives the euclidian distance between them
    static float euclidianDistance(Point &p1, Point &p2) {
        float dist = 0.0;
        float temp;
        for (int i=0; i<Point::dim; i++) {
            temp = p2[i] - p1[i];
            dist += temp * temp;  // Not accessing the locations 2 times
        }
        dist = sqrt(dist);
        return dist;
    }

    // Calculating d1 = |x1 - y1| + |x2 - y2| + ... + |xn - yn| where n = dimension
    static float d1(Point &p1, Point &p2) {
        float dist = 0.0;
        float temp;
        for (int i=0; i<Point::dim; i++) {
            temp = p2[i] - p1[i];
            dist += abs(temp);
        }
        return dist;
    }

    // Calculating d_inf = max|xi - yi| for 1<=i<=dim
    static float dInf(Point &p1, Point &p2) {
        float dist = 0.0;
        float temp;
        for (int i=0; i<Point::dim; i++) {
            temp = abs(p2[i] - p1[i]);
            if (temp > dist)
                dist = temp;
        }
        return dist;
    }

    // Minkowski's distance of degree n
    static float dn(Point &p1, Point &p2, unsigned int n) {
        // Minkowski's distance greater than 15
        if (n > 15)
            return dInf(p1, p2);
        float dist = 0.0;
        double temp;
        for (int i=0; i<Point::dim; i++) {
            temp = abs(p2[i] - p1[i]);
            dist += pow(temp, n);
        }
        dist = pow(dist, 1/n);
        return dist;
    }
};
// The Metric is initially set to 2
int Point::metric = 2;

int Point::precession = 2;



// A Node in an R Tree is basically a rectangle of dimension n
// The structure of the R Tree being constructed is similar to a B Tree of degree 5
// We have at least 5 pointers in a Node and at most 10

// A Pointer might point to a Point or another Node
// If the type of the Node is Leaf, it points to Points, otherwise, it points to other Nodes

// We split a Node into 2 children containing 5 elements if it has 10 elements

class Node {

public:

    // Similar to defining Node::maxSize = 10 to be used repeatedly
    static const int maxSize{ 10 };

    // 2 Points which completely determine the hypervolume contained by the Rectangle or the Node
    Point lowerLimit, upperLimit, center;

    // Determines whether the current Node is a root node
    bool isLeaf;

    // Used to know the number of children in the Node/Rectangle
    // If the node is a leaf node, tells the number of Points stored in the Node
    int size;

    // The parent of the Node
    Node *parent;

    // Pointers pointing to either Nodes or Points
    void *children[Node::maxSize];


    // Padding is the amount of empty space put around the border in every dimension
    // Use it as (Node::padding)
    static constexpr float padding{ 1e-3 };


public:
    // Constructor
    // Pass in true to create a leaf node, false to create an inner node
    Node (bool _isLeaf) {
        size = 0;
        isLeaf = _isLeaf;
        for (int i = 0; i < Node::maxSize; i++)
            children[i] = NULL;
        parent = NULL;
    }

    // Copy Constructor
    Node (Node& n) {
        this->isLeaf = n.isLeaf;
        this->upperLimit = n.upperLimit;
        this->lowerLimit = n.lowerLimit;
        this->size = n.size;

        for (int i=0; i<size; i++)
            this->children[i] = n.children[i];

    }

    // Since we don't know which type of pointer we get for insertion
    // ptr can be a Node or a Point
    void insert(void *ptr, int pos=-1, bool resizeParents=false) {

        // Does not happen but just in case
        if (size == Node::maxSize)
            return;


        if (pos == -1)
            pos = size;

        if (pos < 0 || pos > size) {
            return;
        }

        // Right shift
        for (int i=size; i>pos; i--)
            children[i] = children[i-1];

        children[pos] = ptr;
        size++;

        if (isLeaf)
            expand((Point*) ptr);
        else
            expand((Node*) ptr);

        if (not resizeParents)
            return;

        // Resizing parents
        // Expanding every Node above this
        Node *curr = this;
        Node *par = parent;

        // Condition is false when the current node is the root node
        while (par != NULL) {
            par->expand(curr);
            curr = par;
            par = par->parent;
        }
    }

    // Check if a point is contained in the current node
    bool isContaining(Point &p) {

        for (int i=0; i < Point::dim; i++) {

            // Checking if the point is out of the rectangle in some dimension
            if (p[i] < lowerLimit[i] || p[i] > upperLimit[i])
                return false;
        }

        // If the point is contained in the rectangle in every dimension, it is contained in the rectangle
        return true;
    }

    // Returns the Distance from the Point to the nearest point on the rectangle
    void pointOfIntersection(Point &p, Point &contact) {
        this->updateCenter();

        Point relativeP = p;  // Taking center as the origin
        Point relativeUpper = this->upperLimit;
        Point relativeLower = this->lowerLimit;
        Point relativeContact;

        // Shift of origin
        relativeP -= center;
        relativeUpper -= center;
        relativeLower -= center;

        if (p == center) {
            contact = center;
            contact[0] = upperLimit[0];
            return;
        }

        int winningDimension = 0;
        int i, j=0;

        for (i=0; i < Point::dim && j < Point::dim; i++) {
            if (upperLimit[i] == 0)
                i++;

            for (j=i+1; j < Point::dim; j++) {
                float tanTheta = upperLimit[j] / upperLimit[i];
                float projectionTanTheta;

                // Point tan theta infinity
                if (relativeP[i] == 0)
                    projectionTanTheta = FLT_MAX;
                else
                    projectionTanTheta = abs(relativeP[j]) / abs(relativeP[i]);

                if (projectionTanTheta <= tanTheta) {
                    i = j;
                    winningDimension = j;
                    break;  // The inside for loop only
                }
            }
        }

        if (relativeP[winningDimension] > 0)
            relativeContact[winningDimension] = relativeUpper[winningDimension];
        else
            relativeContact[winningDimension] = relativeLower[winningDimension];


        float distFactor = relativeContact[winningDimension] / relativeP[winningDimension];

        for (i=0; i < Point::dim; i++) {
            if (i == winningDimension)
                continue;
            relativeContact[i] = distFactor * relativeP[i];
        }

        contact = relativeContact;
        contact += center;
    }

    // Makes the passed point as the center of the node
    void updateCenter() {
        for (int i=0; i < Point::dim; i++)
            center[i] = (upperLimit[i] + lowerLimit[i])/2;
    }

    // Checks if the 2 rectangles (of dimension Point::dim) are intersecting or not
    static bool isIntersecting(Node &n1, Node &n2) {

        // The rectangles are intersecting if
        // In ALL dimensions, some line drawn in the direction of the basis vector of that direction intersects
        for (int i=0; i < Point::dim; i++) {

            // n1 is located above n2 completely and hence intersection is not possible
            if (n1.upperLimit[i] > n2.lowerLimit[i] && n1.lowerLimit[i] > n2.upperLimit[i])
                return false;

            // n2 is located above n1 completely and hence intersection is not possible
            if (n2.upperLimit[i] > n1.lowerLimit[i] && n2.lowerLimit[i] > n1.upperLimit[i])
                return false;
        }

        return true;
    }

    // This just resizes the current Node with just enough padding along all the dimensions
    void resize() {

        float minVal = FLT_MAX;  // It is the greatest value attainable by float to be changed
        float maxVal = -FLT_MAX;  // Negative of the greatest value attainable by a float

        // Iterating through all the dimensions
        for (int d=0; d < Point::dim; d++) {

            // Iterating through all the children
            for (int i=0; i < size; i++) {

                // Case 1 when the current Node / Rectangle is a leaf
                if (isLeaf) {
                    Point tempPoint = * (Point *) children[i];
                    if (tempPoint[d] < minVal)
                        minVal = tempPoint[d];
                    else if (tempPoint[d] > maxVal)
                        maxVal = tempPoint[d];
                }

                    // Case 2 when the current Node / Rectangle is an inner Node
                else {
                    Node tempNode = * (Node *) children[i];
                    if (tempNode.lowerLimit[d] < minVal)
                        minVal = tempNode.lowerLimit[d];
                    else if (tempNode.upperLimit[d] > maxVal)
                        maxVal = tempNode.upperLimit[d];
                }
            }

            this->lowerLimit[d] = minVal - Node::padding;
            this->upperLimit[d] = maxVal + Node::padding;
        }
    }

    void expand (Point *p) {
        // During the first initialization, we make sure to keep some empty space around the point
        if (size == 1) {
            for (int i=0; i < Point::dim; i++) {
                lowerLimit[i] = (*p)[i] - Node::padding;
                upperLimit[i] = (*p)[i] + Node::padding;
            }
            return;
        }

        // We check if the point is completely inside the
        for (int i=0; i < Point::dim; i++) {

            if ((*p)[i] - lowerLimit[i] < Node::padding)
                lowerLimit[i] = (*p)[i] - Node::padding;

            if (upperLimit[i] - (*p)[i] < Node::padding)
                upperLimit[i] = (*p)[i] + Node::padding;
        }
    }

    void expand (Node *n) {
        if (size == 1) {
            for (int i=0; i < Point::dim; i++) {
                lowerLimit[i] = (*n).lowerLimit[i] - Node::padding;
                upperLimit[i] = (*n).upperLimit[i] + Node::padding;
            }
        }

        for (int i=0; i < Point::dim; i++) {

            if ((*n).lowerLimit[i] < lowerLimit[i])
                lowerLimit[i] = (*n).lowerLimit[i] - Node::padding;

            if (upperLimit[i] < (*n).upperLimit[i])
                upperLimit[i] = (*n).upperLimit[i] + Node::padding;
        }
    }

    // For debugging
    void printNode() {
        cout << "Printing Node \n";

        cout << "Lower: ";
        lowerLimit.printPoint();
        cout << "Upper: ";
        upperLimit.printPoint();

        if (!isLeaf)
            return;

        cout << "Children: ";
        for (int i=0; i<size; i++)
            ((Point *) (this->children[i]) ) -> printPoint();

        cout << "\n\n\n";
    }
};


// A class Queue what provides with push, pop and peek
class NodeQueue {

private:
    int maxSize;
    int size;
    int front, rear;
    Node **nodePtrArr;


public:
    NodeQueue(int _maxSize) {
        nodePtrArr = new Node*[_maxSize];
        maxSize = _maxSize;
        front = -1;
        rear = -1;
        size = 0;
    }

    void push(Node *n) {
        if (size == maxSize)
            return;

        if (size == 0) {
            front = 0;
            rear = 0;
            nodePtrArr[rear] = n;
            size++;
            return;
        }

        rear = (rear+1) % maxSize;
        size++;
        nodePtrArr[rear] = n;
    }

    Node* peek() {
        if (size == 0)
            return NULL;
        return nodePtrArr[front];
    }

    Node* pop() {
        if (size == 0)
            return NULL;
        size--;

        if (front == maxSize-1) {
            front = 0;
            return nodePtrArr[maxSize-1];
        }

        front++;
        return nodePtrArr[front-1];
    }

    bool isEmpty () {
        return size == 0;
    }
};



// Sorting changing the index array
void sortIndices (int size, int indices[], float vals[]) {

    for (int i=0; i<size; i++) {
        indices[i] = i;
    }

    // Advanced Sorting algorithm can be implemented but selection sort is used
    int minInd;
    for (int i=0; i<size; i++) {
        minInd = i;
        for (int j=i+1; j<size; j++) {
            if (vals[indices[j]] < vals[indices[minInd]])
                minInd = j;
        }
        if (minInd != i) {
            int temp = indices[minInd];
            indices[minInd] = indices[i];
            indices[i] = temp;
        }
    }
}



// The main Data Structure

class RTree {

public:

    Node *root;

    // An empty constructor
    RTree () {
        root = new Node(true);
    }

    // An Algorithm to insert a pointer into the R Tree
    void insertPoint(Point &pt) {
        Point *newPoint = new Point(pt);

        if (root->size == 0) {
            root->insert(newPoint);
            return;
        }

        insertInto(root, newPoint);
    }

    // An algorithm to get the leaf node of a point
    Node* getLeafNode(Point &pt) {

        NodeQueue queue(120);

        Node *tempNode;

        queue.push(root);
        while (!queue.isEmpty()) {
            tempNode = queue.pop();

            // If the popped node is a leaf
            if (tempNode->isLeaf) {
                for (int i=0; i < tempNode->size; i++) {
                    Point *p = (Point *) tempNode->children[i];

                    // We return tempNode if the point is contained in it
                    if (*p == pt)
                        return tempNode;
                }
                continue;
            }

            // Popped node is not the leaf
            for (int i=0; i < tempNode->size; i++) {
                Node *n = (Node *) tempNode->children[i];

                // Pass all the nodes intersecting the MBR
                if (n->isContaining(pt))
                    queue.push(n);
            }
        }

        return NULL;
    }

    // Returns a vector of Points contained in the MBR
    vector<Point> query(Node mbr) {

        vector<Point> points;
        NodeQueue queue(100);

        Node *tempNode;

        queue.push(root);
        while (!queue.isEmpty()) {
            tempNode = queue.pop();

            // If the popped node is a leaf
            if (tempNode->isLeaf) {
                if (tempNode == mbr.parent)
                    continue;

                for (int i=0; i < tempNode->size; i++) {
                    Point *p = (Point *) tempNode->children[i];

                    // Putting all the points contained into the points array
                    if (mbr.isContaining(*p))
                        points.push_back(*p);
                }
                continue;
            }

            // Popped node is not the leaf
            for (int i=0; i < tempNode->size; i++) {
                Node *n = (Node *) tempNode->children[i];

                // Pass all the nodes intersecting the MBR
                if (Node::isIntersecting(*n, mbr))
                    queue.push(n);
            }
        }

        return points;
    }


private:

    // Private insert function
    void insertInto(Node *n, Point *p) {
        if (n->isLeaf) {
            insertIntoLeaf(n, p);
            return;
        }

        // An algorithm to reach a Leaf Node

        int numberOfContains = 0;
        Node *containers[Node::maxSize];

        for (int i=0; i < n->size; i++) {
            Node *child = (Node *) n->children[i];
            if (child->isContaining(*p)) {
                containers[numberOfContains] = child;
                numberOfContains++;
            }
        }

        // If the number of contains is 0

        if (numberOfContains == 0) {
            insertExteriorPoint(n, p);
            return;
        }

        // (ROOM FOR IMPROVEMENT)
        // Algorithm to choose between the containing Rectangles

        // The below algorithm inserts the current Point/Node into the child Node with
        // We just insert it into a Rectangle with lesser Size (Number of Children)

        int currentChildPos = 0;
        int currentLeastSize = Node::maxSize;

        for (int i=0; i<numberOfContains; i++) {
            if (containers[i]->size < currentLeastSize)
                currentChildPos = i;
        }

        insertInto(containers[currentChildPos], p);
    }

    // To insert a Point that is exterior to all the nodes
    void insertExteriorPoint (Node *n, Point *p) {

        // Use the original Inserting algorithm and terminating the recursion
        if (n->isLeaf) {
            insertIntoLeaf(n, p);
            return;
        }

        // (ROOM FOR IMPROVEMENT)
        // Algorithm to choose to which rectangle the point is to be added


        // We're finding the Node which is nearest to the Point

        Node *child;
        Point nearest;

        Node *minDistChild = NULL;
        float minDist = FLT_MAX;
        float dist;

        // Iterating through all the Rectangles and finding the nearest Node
        for (int i=0; i < n->size; i++) {
            child = (Node *) (n->children[i]);
            child->pointOfIntersection(*p, nearest);
            dist = Point::distance(nearest, *p);
            if (dist < minDist) {
                minDist = dist;
                minDistChild = child;
            }
        }

        insertExteriorPoint(minDistChild, p);
    }

    // To insert a Point into a Leaf Node
    void insertIntoLeaf(Node *n, Point *p) {

        // Algorithm to insert a point into a leaf node

        n->insert(p);

        if (n->size < Node::maxSize)
            return;

        // This part of the code is run when the size is (Node::maxSize) and splitting is required

        handleSplits(n);
    }

    // A function to handle splitting of the nodes
    void handleSplits(Node *n) {

        // Exit condition when the node does not overflow to terminate infinite recursion
        if (n->size < Node::maxSize)
            return;

        // The below code runs when the Node n has an overflow


        // (ROOM FOR IMPROVEMENT)
        // The algorithm for splitting points into 2 Nodes
        // Rearrange the children in such a way that the first half share a node and the next half share the next node


        // Rearranging the children
        Point diagonal = n->upperLimit;
        diagonal -= n->lowerLimit;

        // Stores the dot product along the diagonal
        float dotsDiagonal[Node::maxSize];
        int indices[Node::maxSize];

        void *tempChildren[Node::maxSize];
        Point point;

        for (int i=0; i < Node::maxSize; i++) {
            tempChildren[i] = n->children[i];
            if (n->isLeaf)
                point = *((Point *)tempChildren[i]);
            else {
                n->updateCenter();
                point = n->center;
            }
            point -= n->lowerLimit;
            dotsDiagonal[i] = Point::dotProduct(point, diagonal);
        }

        sortIndices(Node::maxSize, indices, dotsDiagonal);
        for (int i=0; i < Node::maxSize; i++)
            n->children[i] = tempChildren[i];

        Node *newNode = new Node(n->isLeaf);  // Making a new node similar to the already existing node

        for (int i = Node::maxSize - 1; i >= Node::maxSize / 2; i--) {
            newNode->insert(n->children[i], -1, false);  // resizing parents not necessary
            n->children[i] = NULL;
            n->size--;
        }

        n->resize();
        newNode->resize();

        // Special case when n is the root Node

        if(n->parent == NULL) {
            Node *newRoot = new Node(false);
            newRoot->insert(n);
            newRoot->insert(newNode);
            root = newRoot;
            n->parent = root;
            newNode->parent = root;
            return;
        }

        n->parent->insert(newNode);
        newNode->parent = n->parent;

        handleSplits(n->parent);
    }
};



// Returns a random float from -10 to 10
float reqRand() {

    // Generates a float f from 0 to 1
    float f = (float) rand() / RAND_MAX;

    // Making float between -10 and 10
    f = 20*f - 10;
    return f;

}

int main() {
    srand(time(0));

    Point::metric = 2; // changing the metric

    // Variables are used throughout the program
    float randFloat;

    // Selecting the point whose nearest neighbour we need to search for randomly
    Point allPoints[TOTAL];
    RTree rTree;

    // Putting 2000 random points into the R Tree
    for (int i=0; i < TOTAL; i++) {

        for (int j=0; j < Point::dim; j++) {
            randFloat = reqRand();
            allPoints[i][j] = randFloat;
        }

        rTree.insertPoint(allPoints[i]);
    }

    // Getting the user input and storing that point in a variable
    int choice;
    cout << "Enter the index of the point whose nearest neighbour is to be calculated: \n";
    cin >> choice;
    Point startingPoint = allPoints[choice];


    // Leaf Node containing the given point
    Node *leaf = rTree.getLeafNode(startingPoint);

    // Stores the nearest Neighbour of the given point by the end of execution
    float nearestDistance = FLT_MAX;
    Point nearestNeighbour;

    // Initially going through all the points in the leaf node and setting nearestNeighbour among these points
    for (int i=0; i < leaf->size; i++) {
        Point *pt = (Point *) leaf->children[i];
        if (startingPoint == *pt)
            continue;
        float dist = Point::distance(startingPoint, *pt);
        if (dist < nearestDistance) {
            nearestDistance = dist;
            nearestNeighbour = *pt;
        }
    }

    // The new query point will be the elongation along all dimensions
    // that is MAX(nearestNeighbour[i] - startingPoint[i]) for all i
    float farthestFromCenter = nearestNeighbour[0] - startingPoint[0];
    for (int i=0; i < Point::dim; i++) {
        if (nearestNeighbour[i] - startingPoint[i] > farthestFromCenter)
            farthestFromCenter = nearestNeighbour[i] - startingPoint[i];
    }

    // Creating a Minimum Bounding Rectangle using the given point
    Node mbr(true);
    for (int i=0; i < Point::dim; i++) {
        mbr.lowerLimit[i] = startingPoint[i] - farthestFromCenter;
        mbr.upperLimit[i] = startingPoint[i] + farthestFromCenter;
    }
    mbr.parent = leaf;  // This is set to eliminate the leaf node from getting checked again

    // A Vector of all points that are contained in the mbr
    vector<Point> nearbyPoints = rTree.query(mbr);

    // We check every possible candidate that can be of minimal distance
    for (Point point: nearbyPoints) {
        if (point == startingPoint)
            continue;
        float dist = Point::distance(point, startingPoint);
        if (dist < nearestDistance) {
            nearestDistance = dist;
            nearestNeighbour = point;
        }
    }

    for (Point i: allPoints) {
        cout << Point::distance(startingPoint, i) << "\n";
    }


    // Printing the given and the nearest point

    cout << "The Given point is: \n";
    startingPoint.printPoint();

    cout << "The Nearest Distance: ";
    cout << Point::distance(startingPoint, nearestNeighbour) << "\n";

    cout << "The nearest point is: " << "\n";
    nearestNeighbour.printPoint();
}
