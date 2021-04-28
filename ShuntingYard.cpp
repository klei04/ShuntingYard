//This is a program that uses stacks, queues, and the shunting yard algorithm
//to convert an infix expression to a postfix expression. The program then
//uses the postfix expression to create a binary expression tree and uses the
//binary expression tree to print out the infix, postfix, or prefix versions
//of the expression.
//Author: Kevin Lei
//Date: 4/27/2021

#include <iostream>
#include <cstring>
#include "BTNode.h"
#include <cctype>
#include <stack>

using namespace std;

//Struct for nodes used in the stack
struct StackNode {
  StackNode* next = NULL;
  char data[10];
};

//Struct for nodes used in the queue
struct QueueNode {
  QueueNode* next = NULL;
  char data[10];;
};

//Function prototypes
void PUSH(StackNode* & stackHead, char* newData);
char* POP(StackNode* & stackHead);
char* PEEK(StackNode* stackHead);

void ENQUEUE(QueueNode* & queueHead, char* newData);
char* DEQUEUE(QueueNode* & queueHead);

bool isOperator(char* data);
int precedence(char* data);

BTNode* makeTree(QueueNode* queueNode);
void DISPLAY(BTNode* root, int depth);

void printInfix(BTNode* root);
void printPostfix(BTNode* root);
void printPrefix(BTNode* root);

//Main Function
int main() {

  StackNode* stackHead = NULL;
  QueueNode* queueHead = NULL;
  
  cout << "Welcome to Shunting Yard" << endl;
  cout << "Please type in a mathematical expression in infix notation" << endl;
  cout << "Only integers allowed" << endl;
  cout << "Valid operators include + - * / ^" << endl;
  cout << "Parentheses () are allowed" << endl;
  cout << "Please include a space between each integer, operator, or parentheses" << endl;
  cout << "Your expression: ";

  char expression[100];
  //cin.get();
  cin.get(expression, 100);
  cin.get();

  char* ptr;
  ptr = strtok(expression, " ");

  int success = 1;

  //Start of Shunting Yard Algorithm
  
  while (ptr != NULL) {
    if (isdigit(ptr[0])) { //If operand, add to queue
      ENQUEUE(queueHead, ptr);
    } else if (isOperator(ptr)) { //If operator
      while (stackHead != NULL &&
	     strcmp(PEEK(stackHead), "(") != 0 &&
	     strcmp(ptr, "^") != 0 &&
	     precedence(PEEK(stackHead)) >= precedence(ptr)) {
	ENQUEUE(queueHead, POP(stackHead));
      }
      PUSH(stackHead, ptr);
    } else if (strcmp(ptr, "(") == 0) {//Push left parentheses to stack
      PUSH(stackHead, ptr);
    } else if (strcmp(ptr, ")") == 0) {//If right parentheses, search for the left parentheses and pop the operators to the queue 
      while (strcmp(PEEK(stackHead), "(") != 0) {
	ENQUEUE(queueHead, POP(stackHead));
      }
      //Remove left parentheses
      char* toDelete;
      toDelete = POP(stackHead);
    } else {
      cout << "Invalid input" << endl;
      success = 0;
      break;
    }
    ptr = strtok(NULL, " ");
  }

  if (success == 0) {
    return 0;
  }

  //Move all stack operators to queue
  while (stackHead != NULL) {
    ENQUEUE(queueHead, POP(stackHead));
  }

  //Print postfix expression
  cout << "POSTFIX: ";
  QueueNode* current = queueHead;
  while (current != NULL) {
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;

  //End of Shunting Yard Algorithm

  //Making binary expression tree
  BTNode* root = makeTree(queueHead);
  cout << "BINARY EXPRESSION TREE:" << endl;
  DISPLAY(root, 0);

  char input[10];

  //Continues as long as use does not input QUIT
  while (strcmp(input, "QUIT") != 0) {
     cout << endl << "Type INFIX, POSTFIX, PREFIX, or QUIT" << endl;
     cin.get(input, 10);
     cin.get();
     if (strcmp(input, "INFIX") == 0) {//Infix conversion
       printInfix(root);
     } else if (strcmp(input, "POSTFIX") == 0) {//Postfix conversion
       printPostfix(root);
     } else if (strcmp(input, "PREFIX") == 0) {//Prefix conversion
       printPrefix(root);
     } else if (strcmp(input, "QUIT") != 0) {
       cout << "Invalid input" << endl;
     }
  }

  cout << "Goodbye" << endl;
  
  return 0;
}

//PUSH function adds a node to the end of the stack linked list
void PUSH(StackNode* & stackHead, char* newData) {
  StackNode* newNode = new StackNode;
  strcpy(newNode->data, newData);
  if (stackHead != NULL) {
    StackNode* current = stackHead;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  } else {
    stackHead = newNode;
  }

  /*if (stackHead != NULL) {
    StackNode* temp = new StackNode;
    strcpy(temp->data, stackHead->data);
    temp->next = stackHead->next;
    strcpy(stackHead->data, newData);
    stackHead->next = temp;
  } else {
    strcpy(stackHead->data, newData);
  }*/
}

//POP function removes a node from the end of the stack linked list
char* POP(StackNode* & stackHead) {
  StackNode* current = stackHead;
  if (current == NULL) {
    return NULL;
  } else if (current->next == NULL) {
    char* returnData = new char[10];
    strcpy(returnData, current->data);
    stackHead = NULL;
    return returnData;
  } else {
    while (current->next->next != NULL) {
      current = current->next;
    }
    StackNode* temp = current->next;
    current->next = NULL;
    return temp->data;

    //current->next = NULL;
    //return current->data;
  }
  /*StackNode* current = stackHead;
  if (current != NULL) { 
    char* returnData = new char[10];
    strcpy(returnData, current->data);
    StackNode* toDelete = stackHead;
    stackHead = current->next;
    delete(current);
    return returnData;
  }
  return NULL;*/
}

//PEEK function returns the node at the end of the stack linked list
char* PEEK(StackNode* stackHead) {
  StackNode* current = stackHead;
  if (current != NULL) {
    while (current->next != NULL) {
      current = current->next;
    }
    return current->data;
  }
  return NULL;
}

//ENQUEUE function adds a node to the end of the queue linked list
void ENQUEUE(QueueNode* & queueHead, char* newData) {
  QueueNode* current = queueHead;
  QueueNode* newNode = new QueueNode;
  strcpy(newNode->data, newData);
  if (current != NULL) {
    //QueueNode* current = queueHead;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  } else {
    queueHead = newNode;
  }

  /*if (queueHead != NULL) {
    QueueNode* temp = new QueueNode;
    strcpy(temp->data, queueHead->data);
    temp->next = queueHead->next;
    strcpy(queueHead->data, newData);
    queueHead->next = temp;
  } else {
    strcpy(queueHead->data, newData);
  }*/
}

//DEQUEUE function removes a node from the beginning of the queue linked list
char* DEQUEUE(QueueNode* & queueHead) {
  QueueNode* current = queueHead;
  if (current != NULL) { 
    char* returnData = new char[10];
    strcpy(returnData, current->data);
    QueueNode* toDelete = queueHead;
    queueHead = current->next;
    delete(current);
    return returnData;
  }
  return NULL;

  /*QueueNode* current = queueHead;
  if (current == NULL) {
    return NULL;
  } else if (current->next == NULL) {
    char* returnData = new char[10];
    strcpy(returnData, current->data);
    queueHead = NULL;
    return returnData;
  } else {
    while (current->next->next != NULL) {
      current = current->next;
    }
    char* returnData = new char[10];
    strcpy(returnData, current->next->data);
    delete(current->next);
    current->next = NULL;
    return returnData;
    }*/
}

//Function checks if the data is an operator
bool isOperator(char* data) {
  if (strcmp(data, "+") == 0 ||
      strcmp(data, "-") == 0 ||
      strcmp(data, "*") == 0 ||
      strcmp(data, "/") == 0 ||
      strcmp(data, "^") == 0) {
    return true;
  }
  return false;
}

//Function returns the precedence of an operator
int precedence(char* data) {
 if (strcmp(data, "^") == 0) {
   return 3;
 } else if (strcmp(data, "*") == 0 || strcmp(data, "/") == 0) {
   return 2;
 } else if (strcmp(data, "+") == 0 || strcmp(data, "-") == 0) {
   return 1;
 } else {
  return 0;
 }
}

//Function makes a Binary Expression Tree from the postfix queue
BTNode* makeTree(QueueNode* queueNode) {
  stack<BTNode*>* binaryTree = new stack<BTNode*>;
  QueueNode* current = queueNode;
  while (current != NULL) {
    if (! isOperator(current->data)) {//If number add to the binary tree stack
      BTNode* newNode = new BTNode();
      newNode->setData(current->data);
      binaryTree->push(newNode);
    } else {//If operator, link two subtrees
      BTNode* newNode = new BTNode();
      newNode->setData(current->data);
      
      BTNode* right = binaryTree->top();
      binaryTree->pop();
      BTNode* left = binaryTree->top();
      binaryTree->pop();

      newNode->setRight(right);
      newNode->setLeft(left);
      binaryTree->push(newNode);
    }
    current = current->next;
  }

  //Remaining node in the stack is the root of the binary expression tree
  BTNode* root = binaryTree->top();
  //tempStack->pop();
  return root;
}

//Nicely prints out the binary expression tree
void DISPLAY(BTNode* root, int depth) {
  if (root != NULL) {
    DISPLAY(root->getRight(), depth + 1);
    for (int i = 0; i < depth; i++) {
      cout << "    ";
    }
    cout << root->getData() << endl;
    DISPLAY(root->getLeft(), depth + 1);
  }
  return;
}

//Function recursively prints the infix expression using the binary expression tree
void printInfix(BTNode* root) {
  if (root != NULL) {
    if (isOperator(root->getData())) {
      cout << "( ";
      }
    printInfix(root->getLeft());
    cout << root->getData() << " ";
    printInfix(root->getRight());
    if (isOperator(root->getData())) {
      cout << ") ";
      }
  }
}

//Function recursively prints the postfix expression using the binary expression tree
void printPostfix(BTNode* root) {
  if (root != NULL) {
    printPostfix(root->getLeft());
    printPostfix(root->getRight());
    cout << root->getData() << " ";
  }
  return;
}

//Function recursively prints the prefix expression using the binary expression tree
void printPrefix(BTNode* root) {
  if (root != NULL) {
    cout << root->getData() << " ";
    printPrefix(root->getLeft());
    printPrefix(root->getRight());
  }
  return;
}
