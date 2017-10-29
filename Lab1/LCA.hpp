#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <random>

using namespace std;

namespace LCAImplementation{
  const int MAX_NODES = 10;

  template <class T>
  class Node{

  public:
    Node(T);
    Node<T>** nextNodes;
    int size = 0;
    T val;
  };

  template <class T>
  class BT{

  public:
    BT();
    void LCA(T, T, T*);
    Node<T>* getRoot();
    void setRoot(Node<T>*);
    bool insert(Node<T>*, Node<T>*, T);
    bool cycleExist(Node<T>*);

  private:
    Node<T>* root = NULL;
    void listFromNodeToRoot(T, Node<T>*, vector<T>*);
    bool nodeExists(T, Node<T>*);
  };
}
