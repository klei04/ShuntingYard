#include <iostream>
#include <cstring>

#include "BTNode.h"

BTNode::BTNode() {
  left = NULL;
  right = NULL;
}

BTNode::~BTNode() {
  left = NULL;
  right = NULL;
}

void BTNode::setLeft(BTNode* newLeft) {
  left = newLeft;
}

BTNode* BTNode::getLeft() {
  return left;
}

void BTNode::setRight(BTNode* newRight) {
  right = newRight;
}

BTNode* BTNode::getRight() {
  return right;
}

void BTNode::setData(char* newData) {
  strcpy(data, newData);
}

char* BTNode::getData() {
  return data;
}
