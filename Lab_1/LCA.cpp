#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../../../../catch.hpp"
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
      root = insert(root, vals[i]);
    }
  }

  template<class T>
  Node<T>* LCAImplementation::BT<T>::insert(Node<T>* root, T val) {
    if(root == NULL) {
      root = new Node<T>(val);
    } else  {
      if(root->val >= val) {
        Node<T>* tmp = insert(root->left, val);
        root->left = tmp;
      } else  {
        Node<T>* tmp = insert(root->right, val);
        root->right = tmp;
      }
    }
    return root;
  }

  template<class T>
  T LCAImplementation::BT<T>::LCA(T val1, T val2) {
    vector<T> list1;
    listFromNodeToRoot(val1, root, &list1);
    vector<T> list2;
    listFromNodeToRoot(val2, root, &list2);

    for(unsigned i = list1.size(); i-- > 0; ) {
      for(unsigned j = list2.size(); j-- > 0 ; ) {
        if(list1[i] == list2[j]) {
          return  list2[j];
        }
      }
    }
    return -1;
  }

  template<class T>
  void LCAImplementation::BT<T>::listFromNodeToRoot(T val, Node<T>* node, vector<T>* list) {
    if(val == node->val) {
      list->push_back(node->val);
      return;
    } else if(val < node->val) {
      list->push_back(node->val);
      LCAImplementation::BT<T>::listFromNodeToRoot(val, node->left, list);
    } else  {
      list->push_back(node->val);
      LCAImplementation::BT<T>::listFromNodeToRoot(val, node->right, list);
    }
  }

  template<class T>
  Node<T>* LCAImplementation::BT<T>::getRoot() {
    return root;
  }

  TEST_CASE( "LCA is being computed", "[LCA]" ) {
    vector<int> list = vector<int>();

    list.push_back(6);                      //                          6
    list.push_back(8);                      /*                        /   \                           */
    list.push_back(4);                      /*                      4       8                         */
    list.push_back(3);                      /*                    /   \   /   \                       */
    list.push_back(5);                      /*                   3     5 7     10                     */
    list.push_back(7);                      /*                                /                       */
    list.push_back(10);                     /*                               9                        */
    list.push_back(9);

    LCAImplementation::BT<int> binary_tree (list);
    LCAImplementation::Node<int> *root = binary_tree.getRoot();

    int num = binary_tree.LCA(7, 10);
    REQUIRE(num == 8);
    num = binary_tree.LCA(7, 9);
    REQUIRE(num == 8);
    num = binary_tree.LCA(3, 5);
    REQUIRE(num == 4);
    num = binary_tree.LCA(3, 9);
    REQUIRE(num == 6);
  }
