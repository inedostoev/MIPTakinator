#include "TREE.h"

TREE::TREE() :
	Tree_		(NULL),
	inputFile_	(NULL),
	outputFile_	(NULL)
{}

TREE::~TREE() {
	Tree_ = NULL;
	fclose(inputFile_);
	fclose(outputFile_);
	inputFile_ = NULL;
	outputFile_ = NULL;
}

void TREE::execute() {
	assert(inputFile_ != NULL);
	assert(outputFile_ != NULL);
	readFile(&Tree_);
	//prinf(Tree_);
	writeFile(stdout, Tree_);
	writeFile(outputFile_, Tree_);
}

void TREE::addNode(Data_t data, Node **nodePointer) {
	if (*nodePointer == NULL) {
		(*nodePointer) = new Node;
		(*nodePointer)->data = data;
		(*nodePointer)->left = (*nodePointer)->right = NULL;
	}
}

void TREE::readFile(Node **nodePointer) {
	char *scannedString = (char*)malloc(MAX_SCANNEDSTR_SIZE * sizeof(char));
	fscanf(inputFile_, "%s", scannedString);
	if (!strcmp(scannedString, "(")) {
		fscanf(inputFile_, "%s", scannedString);	
		addNode(atof(scannedString), &(*nodePointer));
		readFile(&(*nodePointer)->left);
		readFile(&(*nodePointer)->right);
		fscanf(inputFile_, "%s", scannedString);
		if (!strcmp(scannedString, ")")) {
			return;
		}
	}
	else {
		addNode(atof(scannedString), &(*nodePointer));
	}
	free(scannedString);
}

void TREE::prinf(Node *pointer) {
	if (pointer == NULL) {
		printf("NULL ");
		return;
	}
	printf("%lg ", pointer->data);
	prinf(pointer->left);
	prinf(pointer->right);
}

void TREE::writeFile(FILE *outputFile, Node *nodePointer) {
	if (nodePointer == NULL) {
		fprintf(outputFile, "NULL ");
		return;
	}
	fprintf(outputFile, "( ");
	fprintf(outputFile, "%lg ", nodePointer->data);
	writeFile(outputFile, nodePointer->left);
	writeFile(outputFile, nodePointer->right);
	fprintf(outputFile, ") ");
}
