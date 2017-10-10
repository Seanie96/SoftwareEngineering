#include "LCA.h"
using namespace LCAImplementation;

  template<class T>
  LCAImplementation::Node<T>::Node(T value) {
    val = value;
    right = NULL;
    left = NULL;
  }

  template<class T>
  int LCAImplementation::Node<T>::compareTo(Node<T> *node) {
    if(node->val < val) {
      return -1;
    } else if(node->val > val) {
      return 1;
    } else  {
      return 0;
    }
  }

  template<class T>
  LCAImplementation::BT<T>::BT(vector<T> vals) {
    Node<T> tmp (vals[0]);
    for(unsigned i = 1; i < vals.size(); i++) {
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
  Node<T>* LCAImplementation::BT<T>::LCA(T val1, T val2) {
    if(valueExists(val1, root) && valueExists(val2, root)) {
      listFromNodeToRoot(val1, root);
      vector<Node<T>*> list1 = list;
      listFromNodeToRoot(val2, root);
      vector<Node<T>*> list2 = list;

      for(unsigned i = 0; i < list1.size(); i++) {
        for(unsigned j = 0; j < list2.size(); j++) {
          if(list1[i]->val == list2[j]->val) {
            return  list[i];
          }
        }
      }
    }
    return NULL;
  }

  template<class T>
  bool LCAImplementation::BT<T>::valueExists(T val, Node<T>* node) {
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
  bool LCAImplementation::BT<T>::listFromNodeToRoot(T val, Node<T>* node) {
    if(val == node->val) {
      list = vector<Node<T>*>();
      list.push_back(node);
      return true;
    } else {
      bool func1 = listFromNodeToRoot(val, node->left);
      bool func2 = listFromNodeToRoot(val, node->right);
      if(func1 || func2) {
        list.push_back(node);
        return true;
      } else  {
        return false;
      }
    }
  }

  template<class T>
  void LCAImplementation::BT<T>::postorder(Node<T>* p, int indent) {
    if(p != NULL) {
        if(p->left) postorder(p->left, indent+4);
        if(p->right) postorder(p->right, indent+4);
        if (indent) {
            cout << setw(indent) << ' ';
        }
        cout << p->val << "\n ";
    }
  }


int main() {
  vector<int> l = vector<int>();
  for(int i = 0; i < 25; i++) {
    int num = (int)(rand() % 1000);
    l.push_back(num);
  }
  LCAImplementation::BT<int> binary_tree (l);
  binary_tree.postorder(binary_tree.getRoot(), 0);

  int i1 = (int)(rand()%25);
  int i2 = (int)(rand()%25);
  LCAImplementation::Node<int>* ancestor = binary_tree.LCA(l[i1], l[i2]);

  cout << "child 1 : " << i1 << "." << endl;
  cout << "child 2 : " << i2 << "." << endl;
  cout << "ancestor : " << ancestor << "." << endl;

  binary_tree.postorder(ancestor, 0);

  return 0;
}
