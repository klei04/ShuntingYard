#include <iostream>
#include <cstring>

class BTNode {
 private:
  BTNode* left;
  BTNode* right;
  char data[10];;

 public:
  BTNode();
  ~BTNode();
  void setLeft(BTNode* newLeft);
  BTNode*  getLeft();
  void setRight(BTNode* newRight);
  BTNode* getRight();
  void setData(char* newData);
  char* getData();
};
