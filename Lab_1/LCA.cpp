#include "LCA.hpp"
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
    for(unsigned i = 0; i < vals.size(); i++) {
      cout << "num: " << vals[i] << endl;
      root = insert(root, vals[i]);
    }
  }

  template<class T>
  Node<T>* LCAImplementation::BT<T>::insert(Node<T>* root, T val) {
    if(root == NULL) {
      cout << "Inserting number: " << val << endl;
      root = new Node<T>(val);
    } else  {
      if(root->val >= val) {
        cout << "At node: " << root->val << endl;
        Node<T>* tmp = insert(root->left, val);
        root->left = tmp;
      } else  {
        cout << "At node: " << root->val << endl;
        Node<T>* tmp = insert(root->right, val);
        root->right = tmp;
      }
    }
    return root;
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
        bool found = false;
        if(node->val > val) {
          found = valueExists(val, node->left);
        } else  {
          found = valueExists(val, node->right);
        }
        return found;
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
  Node<T>* LCAImplementation::BT<T>::getRoot() {
    return root;
  }
