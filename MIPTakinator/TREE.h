#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

const int MAX_SCANNEDSTR_SIZE = 10;

typedef double Data_t;

class TREE
{
public:
					TREE();
					~TREE();
	FILE			*inputFile_;
	FILE			*outputFile_;
	void			execute();
private:
	typedef struct Node {
		Data_t		data;
		Node		*left;
		Node		*right;
	} Node;

	Node			*Tree_;

	void			addNode(Data_t data, Node **pointer);
	void			readFile(Node **nodePointer);
	void			prinf(Node *pointer);
	void			writeFile(FILE * outputFile, Node * nodePointer);
};

#endif // !TREE_H_INCLUDED