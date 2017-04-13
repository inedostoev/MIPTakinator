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
	FILE			*inputFile_;
	FILE			*outputFile_;
    
    void            callMenu();
private:
	Node			*Tree_;
    char            *scannedStr_;
    char            *questionStr_;

    Node*           buildTree(char* buffer, size_t *counter, Node* Darth_Vader);

    size_t          getFileSize();
    void            scanfCmd();
    void            playGame();
    void            definition();
    void            comparison();
    void            findAnswer(Node* nodePointer);
    bool            scanfAnswer();
    void            addAnswer(Node *nodePointer); 
	void			searchNode(Node* rootNode, Node** neededNode);
	void			printDefinition(Node* neededNode, char* dataDaughter);
    bool            checkDaughter(Node* parentNode, char* dataDaughter);
    void            findSimilarity(Node* firstNode, Node* secondNode);
    void            dumpNode(FILE* stream, Node* node);
    void            stdoutDump(Node* node);
    void            visitor(Traverse mode, Node* node, void act(Node*));
    void            writeFile(FILE *outputFile, Node *nodePointer);
};

#endif // !TREE_H_INCLUDED
