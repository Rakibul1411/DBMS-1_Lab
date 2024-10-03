#include<iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

int numberOfPointer=4, numberOfKey=3;
int hopSize=0;

struct Node{
    int totalKeys;
    Node *parentNode, *nextNode;
    Node **nodePointers;
    bool isLeaf;
    int *words;
};

Node *root;

Node *createNewNode(){
    Node *newNode = new Node();

    newNode->totalKeys = 0;
    newNode->parentNode = nullptr;
    newNode->nextNode = nullptr;
    newNode->nodePointers = new Node *[numberOfPointer + 1];
    for (int i=0; i<=numberOfPointer; i++){
        newNode->nodePointers[i] = nullptr;
    }
    newNode->isLeaf = true;
    newNode->words = new int[numberOfKey + 1];
    return newNode;
}


void createNewRoot(Node *node,int value,Node *leftChild,Node *rightChild){
    node = createNewNode();
    node->isLeaf = false;
    node->words[0] = value;
    node->totalKeys++;
    node->nodePointers[0] = leftChild;
    node->nodePointers[1] = rightChild;
    leftChild->parentNode = node;
    rightChild->parentNode = node;
    root=node;
}

Node *searchPlace(Node *node, int word){
    while(!node->isLeaf){
        int i;
        for(i=0; i<node->totalKeys; i++){
            if(word < node->words[i]){
                break;
            }
        }
        node = node->nodePointers[i];
        hopSize++;
    }
    return node;
}


void addWithParent(Node *parent,int value,Node *rightChild){
    int track = parent->totalKeys;
    track--;

    if(track > -1){
        for(; track>-1; track--){
            if (parent->words[track] <= value)
                break;
            else{
                parent->words[track + 1] = parent->words[track];
                parent->nodePointers[track + 2] = parent->nodePointers[track+1];
            }
        }
    }
    parent->words[track + 1] = value;
    parent->nodePointers[track + 2] = rightChild;
    parent->totalKeys++;
}

void shiftUp(Node *parent, int value, Node *leftChild, Node *rightChild){
    if(!parent){
        createNewRoot(parent, value, leftChild, rightChild);
        return;
    }

    rightChild->parentNode = parent;
    addWithParent(parent, value, rightChild);

    if(parent->totalKeys == numberOfPointer){
        Node *secondNode = createNewNode();
        secondNode->isLeaf = false;

        int mark = parent->totalKeys, j = 0;

        for(int i=mark-(numberOfPointer/2); i<numberOfPointer; i++){
            secondNode->words[j] = parent->words[i];
            if(j==0){
                secondNode->nodePointers[0] = parent->nodePointers[i];   // look up later
                secondNode->nodePointers[0]->parentNode = secondNode;
            }

            secondNode->nodePointers[j + 1] = parent->nodePointers[i+1];
            secondNode->nodePointers[j + 1]->parentNode = secondNode;
            j++;
        }

        parent->totalKeys -= (mark/2);
        secondNode->totalKeys = (mark/2);

        shiftUp(parent->parentNode, parent->words[parent->totalKeys], parent, secondNode);
    }
}

void addToLeaf(int word){

    Node *leaf = searchPlace(root, word);

    int track = leaf->totalKeys;
    track--;

    if(track > -1){
        for(; track>-1; track--){
            if(word < leaf->words[track]){
                leaf->words[track + 1] = leaf->words[track];
            }
            else break;
        }
    }
    leaf->words[track + 1] = word;
    leaf->totalKeys++;

    if(leaf->totalKeys == numberOfPointer){
        Node *secondNode = createNewNode();

        int mark = leaf->totalKeys, j = 0;
        for(int i=mark-(numberOfPointer/2); i<numberOfPointer; i++){
            secondNode->words[j] = leaf->words[i];
            j++;
        }

        leaf->totalKeys -= (numberOfPointer / 2);
        secondNode->totalKeys =(numberOfPointer / 2);
        secondNode->nextNode = leaf->nextNode;
        leaf->nextNode = secondNode;
        shiftUp(leaf->parentNode,secondNode->words[0],leaf,secondNode);
    }
}

bool buildTree(){
    int word;
    root = createNewNode();

    ifstream file;
    file.open("dictionary.txt");

    if(!file){
        cout << "File couldn't be opened" << endl;
        return false;
    }
    else{
        while(file >> word){
            addToLeaf(word);
        }
        file.close();
    }
    return true;
}


void printTree(Node *node, int level) {
    if (node == nullptr) return;

    if (node->isLeaf) {
        cout << "Leaf Node Level " << level << ": ";
        for (int i = 0; i < node->totalKeys; ++i) {
            cout << node->words[i] << " ";
        }
        cout << endl;
    }
    else {
        if(level==0){
            cout << "Root Node Level " << level << ": ";
            for (int i = 0; i < node->totalKeys; ++i) {
                cout << node->words[i] << " ";
            }
            cout << endl;
        }
        else {
            cout << "Internal Node Level " << level << ": ";
            for (int i = 0; i < node->totalKeys; ++i) {
                cout << node->words[i] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i <= node->totalKeys; ++i) {
            printTree(node->nodePointers[i], level + 1);
        }
    }
}


int main(){
    if(buildTree()) cout << "Tree has been built successfully." << endl;
    else cout << "Sorry. Tree couldn't be built" << endl;

    printTree(root, 0);
    return 0;
}