#include "Akinator.h"

Akinator::Akinator() :
    inputFile_      (NULL),
    outputFile_     (NULL),
    Tree_           (NULL),
    scannedStr_     (NULL),
    questionStr_    (NULL)
{
    inputFile_ = fopen("configFile.txt", "r"); 
	if (inputFile_ == NULL) {
		printf("Can't open configFile\n");
		exit(1);
	}
    size_t fileSize = getFileSize();
    char *buffer = (char*)calloc(fileSize, sizeof(char));
    fread(buffer, sizeof(char), fileSize, inputFile_);    
    size_t counter = 0;
    Tree_ = buildTree(buffer, &counter, NULL);
	if (Tree_ == NULL) {
		printf("Can't build tree\n");
		exit(1);
	}
    free(buffer);
    scannedStr_ = (char*)calloc(MAX_QN_LENGTH, sizeof(char));
    answerStr_ = (char*)calloc(MAX_QN_LENGTH, sizeof(char));
    questionStr_ = (char*)calloc(MAX_QN_LENGTH, sizeof(char));
	if (buffer == NULL || scannedStr_ == NULL || questionStr_ == NULL || answerStr_ == NULL) {
		printf("Can't allocate memory\n");
		exit(1);
	}
    fclose(inputFile_);
}

Akinator::~Akinator() {
    delete Tree_;
    Tree_ = NULL; 
    free(answerStr_);
    free(questionStr_);
    answerStr_ = scannedStr_ = questionStr_ = NULL;
}

//Darth_Vader = parent;
//Luke        = son;

Node *Akinator::buildTree(char* buffer, size_t *counter, Node* Darth_Vader) {
    if(buffer[*counter + 1] == ')') {
        *counter += 2;
        return NULL;
    }
    (*counter)++;
    int len = -1;
    char* data = (char*)malloc(MAX_QN_LENGTH * sizeof(char));
    if (data == NULL) {
        printf("Can't allocate memory\n");
    }
    sscanf(buffer + (*counter), "%[^(]%n", data, &len);
    (*counter) += (size_t)len;
    Node* Luke = new Node(Darth_Vader, data);
    Luke->left_ = buildTree(buffer, counter, Luke);
    Luke->right_ = buildTree(buffer, counter, Luke);
    (*counter)++;
    return Luke; 
}

size_t Akinator::getFileSize() {
    fseek(inputFile_, 0, SEEK_END);
    size_t fileSize = (size_t)ftell(inputFile_) + 1;
	if (fileSize <= 1) {
		printf("configFile is empty\n");
		exit(1);
	}
    rewind(inputFile_);
    return fileSize;
}

void Akinator::findAnswer(Node* nodePointer) {
    if (nodePointer == NULL) return;
    printf("%s\n", nodePointer->data_);
    bool answer = scanfAnswer();
    if(nodePointer->left_ == NULL && nodePointer->right_ == NULL) {
        if(answer == true) {
            printf("Ура, я угадал\n"); 
        }
        if(answer == false) {
            addAnswer(nodePointer);
        }
    }
    else {
        if(answer == true) {
            findAnswer(nodePointer->left_);
        }
        if(answer == false) {
            findAnswer(nodePointer->right_);
        }
    }
}

void Akinator::addAnswer(Node* nodePointer) {						 
    printf("Упс, не знаю такого, давай внесем его в базу\n");
    printf("Введи преподавателя, которого загадали\n");
    scanf("%s", answerStr_);
    printf("Введи отличительную черту от преподавателя по фамилии %s. В конце обязательно поставь вопрос\n", nodePointer->data_);
    int count = -1;
    scanf("%[^?]%n", questionStr_, &count);
    questionStr_[count] = '?';    
    nodePointer->left_ = new Node(nodePointer, answerStr_);
    nodePointer->right_ = new Node(nodePointer, nodePointer->data_);
    nodePointer->data_ = questionStr_;
    outputFile_ = fopen("configFile.txt", "w");
	if (outputFile_ == NULL) {
		printf("Can't open configFile\n");
		exit(1);
	}
    writeFile(outputFile_, Tree_);
    fclose(outputFile_);
}

bool Akinator::scanfAnswer(){
    char* answer = (char*)malloc(10 * sizeof(char));
    scanf("%9s", answer);
    if(!strcasecmp(answer, "yes") || !strcasecmp(answer, "да") || !strcasecmp(answer, "y")) {	
        free(answer);
        return true;
    }
    if(!strcasecmp(answer, "no") || !strcasecmp(answer, "нет") || !strcasecmp(answer, "n")) {
        free(answer);   
        return false;
    }
    else {
        printf("Вы не ввели ответ, попытайтесь еще\n");
        free(answer);
        return scanfAnswer();
    }
}

void Akinator::playGame() { 
    printf("\n");
    findAnswer(Tree_);
    printf("\n");
}

void Akinator::definition() {
	printf("Введите имя преподавателя\n");
	scanf("%s", scannedStr_);
	Node *neededNode = NULL;
    searchNode(Tree_, &neededNode);
	if (neededNode != NULL) {
		printDefinition(neededNode->parent_, neededNode->data_);
	}
	else printf("По вашему запросу ничего не найдено :( \n");
    printf("\n");
}

void Akinator::searchNode(Node* rootNode, Node** neededNode) { 
    if (rootNode == NULL) return;
    if (!strcmp((rootNode->data_), scannedStr_)) {
		(*neededNode) = rootNode;
	}
	searchNode(rootNode->left_, neededNode);
	searchNode(rootNode->right_, neededNode);
}

void Akinator::printDefinition(Node* neededNode, char* daughterNode) {
	if (neededNode == NULL) return; 
    char *tmpData = neededNode->data_;
    for (int i = 0; tmpData[i] != '\0'; i++) {
        if (tmpData[i] == '?') tmpData[i] = ' ';           
    }
    if(checkDaughter(neededNode, daughterNode)) {
        printf("   %s\n", tmpData);
    }
    else {
        printf("!  %s\n", tmpData);
    }
	printDefinition(neededNode->parent_, neededNode->data_);
}

bool Akinator::checkDaughter(Node *parentNode, char* dataDaughter) {
        if(!strcasecmp((parentNode->left_)->data_, dataDaughter)) 
            return true;
        if(!strcasecmp((parentNode->right_)->data_, dataDaughter))
            return false;
}

void Akinator::comparison() {
	printf("Введите имя первого преподавателя\n");
	scanf("%s", scannedStr_);
	Node *firstNeededNode = NULL;
    searchNode(Tree_, &firstNeededNode);
    if(firstNeededNode == NULL) {
        printf("%s не найден\n", scannedStr_);
        return;
    }
    printf("Введите имя второго преподавателя\n");
	scanf("%s", scannedStr_);
	Node *secondNeededNode = NULL;
    searchNode(Tree_, &secondNeededNode);
    if(secondNeededNode == NULL) {
        printf("%s не найден\n", scannedStr_);
        return;
    }
    similarRoot_ = NULL;
    Node* constPointer = firstNeededNode;
    findSimilarity(firstNeededNode->parent_, secondNeededNode->parent_, constPointer);
    if (similarRoot_ == NULL) printf("Error with findSimilarity\n");  
    if(similarRoot_->parent_ == NULL) {
        printf("Сходств нет :(\n");
    }
    else {
        printf("Сходства :\n");
        printComparison(similarRoot_, NULL);
    }
    //printf("Различия:\n\t%s:\n", firstNeededNode->data_);
    //printComparison(firstNeededNode, similarRoot_);
    //printf("\t%s:\n",secondNeededNode->data_);
    //printComparison(secondNeededNode, similarRoot_);
}
    
void Akinator::printComparison(Node* similarRoot, Node* condition) {
    if (similarRoot == condition) return;
        printDefinition(similarRoot->parent_, similarRoot->data_);
}

void Akinator::findSimilarity(Node* firstNode, Node* secondNode, Node* constPointer) { 
    if (firstNode == NULL) return;
    if (secondNode == NULL) return;
    if(!strcasecmp(firstNode->data_, secondNode->data_)) {   
        similarRoot_= firstNode; 
        return;
    }
    if (similarRoot_ == NULL) {
    findSimilarity(firstNode->parent_, secondNode, constPointer);
    findSimilarity(constPointer, secondNode->parent_, constPointer);
    }
}

void Akinator::writeFile(FILE *outputFile, Node *nodePointer) {
	if (nodePointer == NULL) {
		fprintf(outputFile, "()");
		return;
	}
	fprintf(outputFile, "(");
	fprintf(outputFile, "%s", nodePointer->data_);
	writeFile(outputFile, nodePointer->left_);
	writeFile(outputFile, nodePointer->right_);
	fprintf(outputFile, ")");
}

void Akinator::dumpTree(FILE* stream, Node* node) {
    if(node == NULL) return;
    fprintf(stream, "treeNode[%p]\n", node);
    fprintf(stream, "{\n");
    fprintf(stream, "  parent_ = %p;\n", node->parent_);
    fprintf(stream, "  data_[%p] = '%s';\n", node->data_, node->data_);
    fprintf(stream, "  left_ = %p;\n", node->left_);
    fprintf(stream, "  right_ = %p;\n", node->right_);
    fprintf(stream, "}\n");
    dumpTree(stream, node->left_);
    dumpTree(stream, node->right_);
}

void Akinator::dotDump(Node* root) {
    FILE* ptrFile = fopen("dumpFile.gv", "w");
    if (ptrFile == NULL) {
        printf("Error with dumpFile.gv\n");
        exit(1);
    }
    fprintf(ptrFile, "digraph graf {\n");
    dotNodeDump(root, ptrFile);
    fprintf(ptrFile, "}");
    fclose(ptrFile);
    ptrFile = NULL;
    system("dot dumpFile.gv -Tpng -o dumpFile.png");
    system("xdot dumpFile.gv");
}

void Akinator::dotNodeDump(Node *root, FILE* stream) {
    fprintf(stream, "treeNode_%p [label=\""
                    "treeNode_[%p]\\l",
                    root, root);
    fprintf(stream, "{\\l");
    fprintf(stream, "  parent_ [%p]\\l", root->parent_);
    fprintf(stream, "  data_ [%p] = %s\\l", root->data_, root->data_);
    fprintf(stream, "  left_ [%p]\\l", root->left_);
    fprintf(stream, "  right_ [%p]\\l", root->right_); 
    fprintf(stream, "}\\l");
    fprintf(stream, "\"]\n");
    if(root->left_) {
        fprintf(stream, "treeNode_%p->treeNode_%p\n", root, root->left_);
        dotNodeDump(root->left_, stream);
    }
    if(root->right_) {
        fprintf(stream, "treeNode_%p->treeNode_%p\n", root, root->right_);
        dotNodeDump(root->right_, stream);
    }
}

void Akinator::visitor(Traverse mode, Node* node, void act(Node*)) {
    switch(mode) {
        case INORDER:
            visitor(mode, node->left_, act);
            act(node);
            visitor(mode, node->right_, act);
            break;
        case PREORDER:                          
            act(node);
            visitor(mode, node->left_, act);
            visitor(mode, node->right_, act);
            break;
        case POSTORDER:
            visitor(mode, node->right_, act);
            act(node);
            visitor(mode, node->left_, act);
            break;
        default:
            printf("Unknown Traverse mode\n");
    }
}

void Akinator::callMenu() {
	printf("Играть в игру [p]\n");
    printf("Вывести определение [d]\n");
    printf("Cравнение [с]\n");
    printf("Dump [l]\n");
    printf("Выход [q]\n");
    printf("\nПоддержать автора: MasterCard 5469 3800 6135 6142\n");
    scanfCmd();
}

void Akinator::scanfCmd() {
    printf("\n");
    char *scanfCmd = (char*)calloc(64, sizeof(char));
    scanf("%63s", scanfCmd);
    if(!strcasecmp(scanfCmd, "p")) {
        printf("Я хочу поиграть с тобой в одну игру\n");
        printf("Загадай преподавателя из физтеха\n");
        printf("Сейчас я его отгадаю. на вопросы отвечай [да/нет] [yes/no] [y/n]\n");
        playGame();
    }
    if(!strcasecmp(scanfCmd, "d")) {
        definition();
    }
    if(!strcasecmp(scanfCmd, "c")) {
       comparison();
    }
    if(!strcasecmp(scanfCmd, "l")) {
        dumpTree(stdout, Tree_);
        dotDump(Tree_);
    }
    if(!strcasecmp(scanfCmd, "q")) {
        exit(1);
    }
    else {
        printf("Команда не распознана, попробуй еще\n");
    }
    free(scanfCmd);
  //  callMenu();
}
