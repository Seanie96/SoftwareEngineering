#include <iostream>
#include <vector>
#include <iomanip>

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
    Node<T>* root = NULL;
    bool valueExists(T, Node<T>*);
    vector<T> list;
    bool listFromNodeToRoot(T, Node<T>*);
    void postorder(Node<T>*, int);
    Node<T>* getRoot();
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
  BT<T>::BT(vector<T> vals) {
    Node<T> tmp (vals[0]);
    for(int i = 1; i < vals.size(); i++) {
      bool foundPosition = false;
      Node<T>* node = root;
      while(!foundPosition) {
        if(node == NULL) {
          Node<T> node (vals[i]);
          foundPosition = true;
        } else  {
          if(node->val < vals[i]) {
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
      listFromNodeToRoot(val1, root);
      vector<T> list1 = list;
      listFromNodeToRoot(val2, root);
      vector<T> list2 = list;
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

template<class T>
  bool BT<T>::listFromNodeToRoot(T val, Node<T>* node) {
    if(val == node->val) {
      list = vector<T>();
      list.push_back(val);
      return true;
    } else {
      bool func1 = listFromNodeToRoot(val, node->left);
      bool func2 = listFromNodeToRoot(val, node->right);
      if(func1 || func2) {
        list.push_back(val);
        return true;
      }
    }
  }

  template<class T>
  void postorder(Node<T>* p, int indent=0) {
    if(p != NULL) {
        if(p->left) postorder(p->left, indent+4);
        if(p->right) postorder(p->right, indent+4);
        if (indent) {
            cout << setw(indent) << ' ';
        }
        cout << p->val << "\n ";
    }
  }
}


int main() {
  vector<int> l = vector<int>();
  for(int i = 0; i < 25; i++) {
    int num = rand() % 1000;
    l.push_back(num);
  }
  LCAImplementation::BT<int> binary_tree (l);
  binary_tree.postorder(binary_tree.getRoot(), 0);

  int i1 = rand()%25;
  int i2 = rand()%25;
  LCAImplementation::Node<int>* ancestor = binary_tree.LCA(l[i1], l[i2]);

  cout << "child 1 : " << i1 << "." << endl;
  cout << "child 2 : " << i2 << "." << endl;
  cout << "ancestor : " << ancestor << "." << endl;

  binary_tree.postorder(ancestor, 0);

  return 0;
}
