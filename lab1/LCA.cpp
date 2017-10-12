#include "LCA.h"
using namespace LCAImplementation;

  template<class T>
  LCAImplementation::Node<T>::Node(T value) {
    val = value;
    right = NULL;
    left = NULL;
  }

  template<class T>
  LCAImplementation::Node<T>::Node() {
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
    root = new Node<T>;
    root->val = vals[0];
    cout << "size : " << vals.size() << endl;
    for(unsigned i = 1; i < vals.size(); i++) {
      bool foundPosition = false;
      bool right = false;
      Node<T>* prevPointer = root;
      Node<T>* node = root;
      while(!foundPosition) {
        if(node == NULL) {
          if(right) {
            prevPointer->right = new Node<T>();
            prevPointer->right->val = vals[i];
          } else  {
            prevPointer->left = new Node<T>();
            prevPointer->left->val = vals[i];
          }
          foundPosition = true;
        } else  {
          if(node->val < vals[i]) {
            prevPointer = node;
            node = node->left;
            right = false;
          } else {
            prevPointer = node;
            node = node->right;
            right = true;
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
  Node<T>* LCAImplementation::BT<T>::getRoot() {
    return root;
  }

  template<class T>
  void LCAImplementation::BT<T>::postorder(Node<T>* p) {
    int height = getHeight(p) * 2;
    for (int i = 0 ; i < height; i ++) {
       printRow(p, height, i);
    }
  }

  template<class T>
  unsigned LCAImplementation::BT<T>::getHeight() {

  }

  template<class T>
  void LCAImplementation::BT<T>::printRow(const Node<T> *p, const int height, int depth) {
    vector<int> vec;
    int placeholder = (1<<31);
    getLine(p, depth, vec);
    cout << setw((height - depth)*2); // scale setw with depth
    bool toggle = true; // start with left
    if (vec.size() > 1) {
      for (int v : vec) {
        if (v != placeholder) {
          if (toggle) {
            cout << "/" << "   ";
          } else {
            cout << "\\" << "   ";
          }
        }
        toggle = !toggle;
      }
      cout << endl;
      cout << setw((height - depth)*2);
    }
    for (int v : vec) {
      if (v != placeholder)
        cout << v << "   ";
    }
    cout << endl;
  }

  template<class T>
  void LCAImplementation::BT<T>::getLine(const Node<T> *rt, int depth, vector<int>& vals) {
    int placeholder = (1<<31);
    if (depth <= 0 && rt != nullptr) {
      vals.push_back(rt->val);
      return;
    }
    if (rt->left != nullptr)
      getLine(rt->left, depth-1, vals);
    else if (depth-1 <= 0)
      vals.push_back(placeholder);
    if (rt->right != nullptr)
      getLine(rt->right, depth-1, vals);
    else if (depth-1 <= 0)
      vals.push_back(placeholder);
  }

  int main() {
    vector<int> list = vector<int>();
    for(int i = 0; i < 10; i++) {
      int num = (int)(rand() % 1000);
      cout << "num " << i << " : " << num << endl;
      list.push_back(num);
    }

    LCAImplementation::BT<int> binary_tree (list);
    LCAImplementation::Node<int> *root = binary_tree.getRoot();
    binary_tree.postorder(root);

    cout << "root: " << root->val << endl;

    int i1 = (int)(rand()%25);
    int i2 = (int)(rand()%25);

    LCAImplementation::Node<int>* ancestor = binary_tree.LCA(list[i1], list[i2]);

    cout << "child 1 : " << i1 << "." << endl;
    cout << "child 2 : " << i2 << "." << endl;
    cout << "ancestor : " << ancestor << "." << endl;

    binary_tree.postorder(ancestor);

    return 0;
  }
