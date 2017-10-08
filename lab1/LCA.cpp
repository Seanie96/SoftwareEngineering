#include <iostream>
#include <vector>

using namespace std;

namespace LCAImplementation{
  template <class T>
  class Node{

  public:
    Node(T);
    ~Node();
    int compareTo(Node*);
    Node<T>* right = NULL;
    Node<T>* left = NULL;
    T val;

  };

  template <class T>
  class BT{

  public:
    BT(vector<T>);
    ~BT();
    Node<T>* LCA(T, T);

  private:
    Node<T>* root = NULL;
    bool valueExists(T, Node<T>*);
    vector<Node<T>> listFromNodeToRoot(T);
  };

  template<class T>
  Node<T>::Node(T value) {
    val = value;
    right = NULL;
    left = NULL;
  }

  template<class T>
  int Node<T>::compareTo(Node<T> *node) {
    if(node->val < val) {
      return -1;
    } else if(node->val > val) {
      return 1;
    } else  {
      return 0;
    }
  }

  template<class T>
  BT<T>::BT(vector<T> values) {
    root = Node<T>(values[0]);
    for(int i = 1; i < values.length; ++i) {

      bool foundPosition = false;
      Node<T>* node = root;
      while(!foundPosition) {
        if(node == NULL) {
          node = Node<T>(values[i]);
          foundPosition = true;
        } else  {
          if(node->val < values[i]) {
            node = node->left;
          } else  {
            node = node->right;
          }
        }
      }
    }
  }

  template<class T>
  Node<T>* BT<T>::LCA(T val1, T val2) {
    if(valueExists(val1, root) && valueExists(val2, root)) {
      vector<T> list1 = listFromNodeToRoot(val1);
      vector<T> list2 = listFromNodeToRoot(val2);


    }
  }

  template<class T>
  bool BT<T>::valueExists(T val, Node<T>* node) {
    if(node != NULL) {
      if(val == node->val) {
        return true;
      } else  {
        if(valueExists(val, node->left) || valueExists(val, node->right)) {
          return true;
        } else  {
          return false;
        }
      }
    } else  {
      return false;
    }
  }


}



int main() {



  return 0;
}
