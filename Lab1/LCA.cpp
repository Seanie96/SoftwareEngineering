#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../../../../catch.hpp"
#include "LCA.hpp"
#include <climits>

using namespace LCAImplementation;

  /*
   *  Constructor for a Node
   */
  template<class T>
  LCAImplementation::Node<T>::Node(T value) {
    val = value;
    right = NULL;
    left = NULL;
  }

  /*
   *  Constructor for a Binary Tree
   */
  template<class T>
  LCAImplementation::BT<T>::BT(vector<T> vals) {
    for(unsigned i = 0; i < vals.size(); i++) {
      root = insert(root, vals[i]);
    }
  }

  /*
   *  Returns the new root node, when a given node is placed in the BST.
   */
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

  /*
   *  Returns a list of nodes from the node that contains val, back up to the root node.
   */
  template<class T>
  void LCAImplementation::BT<T>::LCA(T val1, T val2, T* res) {
    if(nodeExists(val1, root) && nodeExists(val2, root)) {
      vector<T> list1;
      listFromNodeToRoot(val1, root, &list1);
      vector<T> list2;
      listFromNodeToRoot(val2, root, &list2);

      for(unsigned i = list1.size(); i-- > 0; ) {
        for(unsigned j = list2.size(); j-- > 0 ; ) {
          if(list1[i] == list2[j]) {
            res[0] = list2[j];
            return;
          }
        }
      }
    } else  {
      res[0] = (T)INT_MIN;
    }
  }

  /*
   *  Returns boolean. True => there exists a node in the BST which contains val.
   *                   False => there does not exist a node in the BST which contains val.
   */
  template<class T>
  bool LCAImplementation::BT<T>::nodeExists(T val, Node<T>* node) {
    Node<T>* tmp = node;
    bool found = false;
    while(tmp != NULL && !found) {
      if(val < tmp->val) {
        tmp = tmp->left;
      } else if(val > tmp->val) {
        tmp = tmp->right;
      } else  {
        found = true;
      }
    }
    return found;
  }

  /*
   *  Returns a list of nodes from the node that contains val, back up to the root node.
   */
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

  /*
   *  Returns a pointer to the root node of a BST.
   */
  template<class T>
  Node<T>* LCAImplementation::BT<T>::getRoot() {
    return root;
  }


  TEST_CASE( "LCA tests being ran on full tree...........", "[LCA]" ) {
    vector<int> list = vector<int>();

    /*

      Check for Cycles...
      Therefore build a graph that has one.
    */

    list.push_back(6);                      /*                          6  <----
                                                                      /   \     \
                                                                     4 --> 5 --> 17
                                                                    /
                                                                   15  
                                            */

    LCAImplementation::BT<int> binary_tree (list);

    int* num = new int [1];

    SECTION( "Checking the LCA of nodes within the BST, which contains one node" ) {
      binary_tree.LCA(6, 6, num);
      REQUIRE(num[0] == 6);
    }

    SECTION( "hecking the LCA of a node/s that is/are not in the BST, which contains one node" ) {
      binary_tree.LCA(7, 6, num);
      int n = (int)num[0];
      REQUIRE(n == INT_MIN);
      binary_tree.LCA(8, 7, num);
      n = (int)num[0];
      REQUIRE(n == INT_MIN);
    }


    list.clear();
    list = vector<int>();

    list.push_back(6);                      //                          6 - root
    list.push_back(8);                      /*                        /   \                           */
    list.push_back(4);                      /*                      4       8                         */
    list.push_back(3);                      /*                    /   \   /   \                       */
    list.push_back(5);                      /*                   3     5 7     10                     */
    list.push_back(7);                      /*                    \   /   \     \                     */
    list.push_back(10);                     /*                     17       9 - 15                    */
    list.push_back(9);                      /*                       \___    ___/                     */
                                            /*                           \  /                         */
    LCAImplementation::BT<int> binary_tree_2 (list);      /*              27                          */

    SECTION( "Checking the LCA of nodes within the BST" ) {
      binary_tree_2.LCA(7, 10, num);
      REQUIRE(num[0] == 8);
      binary_tree_2.LCA(7, 9, num);
      REQUIRE(num[0] == 8);
      binary_tree_2.LCA(3, 5, num);
      REQUIRE(num[0] == 4);
      binary_tree_2.LCA(3, 9, num);
      REQUIRE(num[0] == 6);
    }

    SECTION( "Checking the LCA of a node/s that is/are not in the BST" ) {
      binary_tree_2.LCA(12, 10, num);
      int n = (int)num[0];
      REQUIRE(n == INT_MIN);
      binary_tree_2.LCA(50, 80, num);
      n = (int)num[0];
      REQUIRE(n == INT_MIN);
    }

    SECTION( "Checking if the ancestor of two nodes which are the same, is the node itself" ) {
      binary_tree_2.LCA(8, 8, num);
      REQUIRE(num[0] == 8);
      binary_tree_2.LCA(9, 9, num);
      REQUIRE(num[0] == 9);
      binary_tree_2.LCA(6, 6, num);
      REQUIRE(num[0] == 6);
    }

    SECTION( "Checking if the ancestor of two nodes, where one node is the ancestor of the other, is the ancestoral node of the two" ) {
      binary_tree_2.LCA(8, 10, num);
      REQUIRE(num[0] == 8);
      binary_tree_2.LCA(9, 6, num);
      REQUIRE(num[0] == 6);
      binary_tree_2.LCA(5, 6, num);
      REQUIRE(num[0] == 6);
    }

    SECTION( "Checking for Cycle in graph" ) {

    }

 }
