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
    Node<T>*[] nextNodes = NULL;
    T val;
  };

  template <class T>
  class BT{

  public:
    BT();
    void LCA(T, T, T*);
    Node<T>* getRoot();
    Node<T>* insert(Node<T>*, Node<T>*, T);
    bool cycleExist(Node<T>*);

  private:
    Node<T>* root = NULL;
    void listFromNodeToRoot(T, Node<T>*, vector<T>*);
    bool nodeExists(T, Node<T>*);
  };
}
