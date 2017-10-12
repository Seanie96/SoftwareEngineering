#include <iostream>
#include <vector>
#include <iomanip>
//#include <cstdlib>
#include <random>

using namespace std;

namespace LCAImplementation{
  template <class T>
  class Node{

  public:
    Node();
    Node(T);
    //~Node();
    int compareTo(Node*);
    Node<T>* right = NULL;
    Node<T>* left = NULL;
    T val;
  };

  template <class T>
  class BT{

  public:
    BT(vector<T>);
    //~BT();
    Node<T>* LCA(T, T);
    void postorder(Node<T>*);
    Node<T>* getRoot();

  private:
    Node<T>* root = NULL;
    vector<Node<T>*> list;
    bool valueExists(T, Node<T>*);
    bool listFromNodeToRoot(T, Node<T>*);
    void printRow(const Node<T>*, const int, int);
    void getLine(const Node<T>*, int, vector<int>&);
    unsigned getHeight(Node<T>*);
  };
}
