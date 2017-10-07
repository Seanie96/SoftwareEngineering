#include <iostream>
#include <vector>

using namespace std;

namespace LCAImplementation{
  template <class T>
  class Node{

  public:
    Node();
    ~Node();
    int compareTo(Node* node);

  private:
    Node<T>* right = NULL;
    Node<T>* left = NULL;
  };

  template <class T>
  class BST{

  public:
    BST();
    ~BST();
    Node<T>* LCA(T val);

  private:
    Node<T>* root = NULL;
    vector<Node<T>> listFromNodeToRoot(T val);
  };



}

int main() {



  return 0;
}
