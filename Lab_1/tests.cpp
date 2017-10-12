#include "LCA.hpp"
#include <gtest/gtest.h>

int main() {
  vector<int> list = vector<int>();
  for(int i = 0; i < 10; i++) {
    int num = (int)(rand() % 1000);
    cout << "num " << i << " : " << num << endl;
    list.push_back(num);
  }

  LCAImplementation::BT<int> binary_tree (list);
  LCAImplementation::Node<int> *root = binary_tree.getRoot();

  cout << "root: " << root->val << endl;

  int i1 = (int)(rand()%25);
  int i2 = (int)(rand()%25);

  LCAImplementation::Node<int>* ancestor = binary_tree.LCA(list[i1], list[i2]);

  cout << "child 1 : " << i1 << "." << endl;
  cout << "child 2 : " << i2 << "." << endl;
  cout << "ancestor : " << ancestor << "." << endl;


  return 0;
}
