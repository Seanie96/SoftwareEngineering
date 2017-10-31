#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "LCA.hpp"
#include <climits>

using namespace LCAImplementation;

  /*
   *  Constructor for a Node
   */
  template<class T>
  LCAImplementation::Node<T>::Node(T value) {
    val = value;
    nextNodes = new Node<T>*[MAX_NODES];
  }

  /*
   *  Constructor for a Binary Tree
   */
  template<class T>
  LCAImplementation::BT<T>::BT() {
    // Do Nothing!
  }

  /*
   *  Returns the new root node, when a given node is placed in the BST.
   */
  template<class T>
  bool LCAImplementation::BT<T>::insert(Node<T>* root, Node<T>* newNode, T valBefore) {
    if(root->val == valBefore) {
       root->nextNodes[root->size] = newNode;
       root->size = root->size + 1;
       return true;
    } else  {
      for(int i = 0; i < root->size; i++) {
        if(insert(root->nextNodes[i], newNode, valBefore)) {
          return true;
        }
      }
      return false;
    }
    return false;
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

      int size1 = list1.size();
      int size2 = list2.size();

      for(int i = 0; i < size1; i++) {
        for(int j = 0; j < size2; j++) {
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
    if(node->val == val) {
      return true;
    } else if(node->size > 0) {
      int size = node->size;
      for(int i = 0; i < size; i++) {
        if(nodeExists(val, node->nextNodes[i])) {
          return true;
        }
      }
      return false;
    } else  {
      return false;
    }
  }

  /*
   *  Returns a list of nodes from the node that contains val, back up to the root node.
   */
  template<class T>
  bool LCAImplementation::BT<T>::listFromNodeToRoot(T val, Node<T>* node, vector<T>* list) {
    if(val == node->val) {
      list->push_back(node->val);
      cout << "AT.......pushing: " << node->val << endl;
      return true;
    } else  {
      int size = node->size;
      for(int i = 0; i < size; i++) {
        if(listFromNodeToRoot(val, node->nextNodes[i], list)) {
          list->push_back(node->val);
          cout << "pushing: " << node->val << endl;
          return true;
        }
      }
      return false;
    }
    return false;
  }

  /*
   *  Returns a pointer to the root node of a BST.
   */
  template<class T>
  Node<T>* LCAImplementation::BT<T>::getRoot() {
    return root;
  }

/*
   *  Returns a pointer to the root node of a BST.
   */
  template<class T>
  void LCAImplementation::BT<T>::setRoot(Node<T>* node) {
    root = node;
  }



  TEST_CASE( "LCA tests being ran on full tree...........", "[LCA]" ) {



    //                          6(root)
    /*                        /   \                           */
    /*                      4       8                         */
    /*                    /   \   /   \                       */
    /*                   3     5 7     10                     */
    /*                    \   /   \     \                     */
    /*                     17      9 -> 15                    */
    /*                       \___    ___/                     */
    /*                           \  /                         */
    /*                            27                          */

    /*
      Insert Nodes
    */


    LCAImplementation::BT<int>* binary_tree = new LCAImplementation::BT<int>();
    LCAImplementation::Node<int>* root = new LCAImplementation::Node<int>(6); 
    binary_tree->setRoot(root);
    LCAImplementation::Node<int>* node = new LCAImplementation::Node<int>(4);
    binary_tree->insert(root, node, 6);
    node = new LCAImplementation::Node<int>(8); 
    binary_tree->insert(root, node, 6);
    node = new LCAImplementation::Node<int>(10); 
    binary_tree->insert(root, node, 8);
    node = new LCAImplementation::Node<int>(7); 
    binary_tree->insert(root, node, 8);
    node = new LCAImplementation::Node<int>(3); 
    binary_tree->insert(root, node, 4);
    node = new LCAImplementation::Node<int>(5); 
    binary_tree->insert(root, node, 4);
    node = new LCAImplementation::Node<int>(17); 
    binary_tree->insert(root, node, 5);
    binary_tree->insert(root, node, 3);
    node = new LCAImplementation::Node<int>(9);
    binary_tree->insert(root, node, 7);
    node = new LCAImplementation::Node<int>(15); 
    binary_tree->insert(root, node, 9);
    binary_tree->insert(root, node, 10);
    node = new LCAImplementation::Node<int>(27); 
    binary_tree->insert(root, node, 17);
    binary_tree->insert(root, node, 15);


    /*
      Testing the nodeExists method...
    */

    SECTION( "Checking nodeExists method" ) {
      bool res = binary_tree->nodeExists(6, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(4, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(8, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(10, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(7, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(3, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(5, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(17, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(9, root);
      REQUIRE(res == true);
      res = binary_tree->nodeExists(15, root);        
    }


    /*
      Testing the listFromNodeToRoot method...
    */

    SECTION( "Checking the listFromNodeToRoot method" ) {
      std::vector<int>* list = new std::vector<int>();
      binary_tree->listFromNodeToRoot(5, root, list);
      std::vector<int>* compList = new std::vector<int>();
      
      compList->push_back(5);
      compList->push_back(4);
      compList->push_back(6);
      bool same = true;
      for(int i = 0; i < compList->size(); i++) {
        int val1 = compList[0][i];
        int val2 = list[0][i];
        if(val1 != val2) {
          same = false;
          break;
        }
      }
      REQUIRE(same);

      

      list->clear();
      binary_tree->listFromNodeToRoot(15, root, list);
      compList->clear();
      compList->push_back(15);
      compList->push_back(10);
      compList->push_back(8);
      compList->push_back(6);
      same = true;
      for(int i = 0; i < compList->size(); i++) {
        int val1 = compList[0][i];
        int val2 = list[0][i];
        if(val1 != val2) {
          same = false;
          break;
        }
      }
      REQUIRE(same);
    }


    /*
      Testing the LCA method...
    */
    int* num = new int [1];

    SECTION( "Checking the LCA of nodes within the DGA and hence whether insert method worked" ) {
      binary_tree->LCA(7, 10, num);
      REQUIRE(num[0] == 8);
      binary_tree->LCA(10, 9, num);
      REQUIRE(num[0] == 8);
      binary_tree->LCA(17, 15, num);
      REQUIRE(num[0] == 6);
      binary_tree->LCA(3, 9, num);
      REQUIRE(num[0] == 6);
      binary_tree->LCA(3, 5, num);
      REQUIRE(num[0] == 4);
    }


    SECTION( "Checking the LCA of a node/s that is/are not in the DGA" ) {
      binary_tree->LCA(12, 10, num);
      int n = (int)num[0];
      REQUIRE(n == INT_MIN);
      binary_tree->LCA(50, 80, num);
      n = (int)num[0];
      REQUIRE(n == INT_MIN);
    }


    SECTION( "Checking if the ancestor of two nodes which are the same, is the node itself" ) {
      binary_tree->LCA(8, 8, num);
      REQUIRE(num[0] == 8);
      binary_tree->LCA(9, 9, num);
      REQUIRE(num[0] == 9);
      binary_tree->LCA(6, 6, num);
      REQUIRE(num[0] == 6);
    }

    SECTION( "Checking if the ancestor of two nodes, where one node is the ancestor of the other, is the ancestoral node of the two" ) {
      binary_tree->LCA(8, 10, num);
      REQUIRE(num[0] == 8);
      binary_tree->LCA(27, 10, num);
      REQUIRE(num[0] == 10);
      binary_tree->LCA(15, 8, num);
      REQUIRE(num[0] == 8);
    }

 }