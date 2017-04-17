#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Node.h"

const int MAX_QN_LENGTH = 256;
enum Traverse {
    INORDER,
    PREORDER,
    POSTORDER
};

class Akinator
{
public:
                     Akinator();
                    ~Akinator();
    FILE            *inputFile_;
    FILE            *outputFile_;
    Akinator& operator = (const Akinator&);
    Akinator(const Akinator&);
    
    void            callMenu();
private:
    Node*           Tree_;
    char            *scannedStr_;
    char            *answerStr_;
    char            *questionStr_;
    Node*           similarRoot_;

    Node*           buildTree(char* buffer, size_t *counter, Node* Darth_Vader);

    size_t          getFileSize();
    void            scanfCmd();
    void            playGame();
    void            definition();
    void            comparison();
    void            findAnswer(Node* nodePointer);
    bool            scanfAnswer();
    void            addAnswer(Node *nodePointer); 
    void            searchNode(Node* rootNode, Node** neededNode);
    void            printDefinition(Node* neededNode, char* dataDaughter);
    bool            checkDaughter(Node* parentNode, char* dataDaughter);
    void            findSimilarity(Node* firstNode, Node* secondNode, Node* constPointer);
    void            printComparison(Node* similarRoot, Node* condition);
    void            dumpTree(FILE* stream, Node* node);
    void            dotDump(Node* root);
    void            dotNodeDump(Node* root, FILE* stream);
    void            visitor(Traverse mode, Node* node, void act(Node*));
    void            writeFile(FILE *outputFile, Node *nodePointer);
};

#endif // !TREE_H_INCLUDED
