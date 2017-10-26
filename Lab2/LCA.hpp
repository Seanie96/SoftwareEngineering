#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <random>

using namespace std;

namespace LCAImplementation{
  template <class T>
  class Node{

  public:
    Node(T);
    Node<T>* right = NULL;
    Node<T>* left = NULL;
    T val;
  };

  template <class T>
  class BT{

  public:
    BT(vector<T>);
    void LCA(T, T, T*);
    Node<T>* getRoot();

  private:
    Node<T>* root = NULL;
    void listFromNodeToRoot(T, Node<T>*, vector<T>*);
    bool nodeExists(T, Node<T>*);
    Node<T>* insert(Node<T>*, T);
  };
}
