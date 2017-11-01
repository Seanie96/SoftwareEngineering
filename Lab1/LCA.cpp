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
      vector<T>* list1 = new vector<T>();
      vector<int>* list2 = new vector<int>();

      getCommonAncestors(list1, list2, 0, val1, val2, getRoot());

      int maxDepth = -1;
      T LCA = (T)INT_MIN;
      for(int i = 0; i < list1->size(); i++) {
        int num = (int)list2[0][i];
        T val = (T)list1[0][i];
        if(num > maxDepth) {
          maxDepth = num;
          LCA = val;
        }
      }
      res[0] = LCA;
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
   *  Returns all of the common ancestors of these two nodes, in listOfCommonNodes...
   */
  template<class T>
  int LCAImplementation::BT<T>::getCommonAncestors(vector<T>* listOfVals, vector<int>* listOfDepths, int depth, T val1, T val2, Node<T>* root) {
    bool isAncestor1 = false, isAncestor2 = false, isCommonAncestor = false;


    if(root->val == val1 && val1 == val2) {
      isCommonAncestor = true;
    } else if(root->val == val1) {
      isAncestor1 = true;
    }  else if(root->val == val2) {
      isAncestor2 = true;
    }

    int size = root->size;
    for(int i = 0; i < size; i++) {
      int ret = getCommonAncestors(listOfVals, listOfDepths, depth + 1, val1, val2, root->nextNodes[i]);
      if(ret == 0) {
        isAncestor1 = true;
      } else if(ret == 1) {
        isAncestor2 = true;
      } else if(ret == 2) {
        isCommonAncestor = true;
      }
    }

    if(isCommonAncestor) {
      listOfVals->push_back(root->val);
      listOfDepths->push_back(depth);
      return 2;
    } else if(isAncestor1 && isAncestor2) {
      listOfVals->push_back(root->val);
      listOfDepths->push_back(depth);
      return 2;
    } else if(isAncestor1) {
      return 0;
    } else if(isAncestor2) {
      return 1;
    } else  {
      return 3;
    }
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

/*
    NOTE!!!!!!!!!
    Did not test for cycles in DAG..
    I assumed that there would be no cycles in the graph given, since it is an Asyclic graph given to test the LCA on.
 */

  TEST_CASE( "LCA tests being ran on full tree...........", "[LCA]" ) {
    /*    !!!!Testing DGA given on Assignment description!!!!   */

    //                          6(root)
    /*                        /   \                     */
    /*                       4     8                    */
    /*                       |     |                    */
    /*                       5     10                   */
    /*                        \    |                    */
    /*                         --->9                    */
    /*                             |                    */
    /*                             27                   */

    /*
      Insert Nodes
    */


    LCAImplementation::BT<int>* binary_tree1 = new LCAImplementation::BT<int>();
    LCAImplementation::Node<int>* root1 = new LCAImplementation::Node<int>(6); 
    binary_tree1->setRoot(root1);
    LCAImplementation::Node<int>* node1 = new LCAImplementation::Node<int>(4);
    binary_tree1->insert(root1, node1, 6);
    node1 = new LCAImplementation::Node<int>(8); 
    binary_tree1->insert(root1, node1, 6);
    node1 = new LCAImplementation::Node<int>(10); 
    binary_tree1->insert(root1, node1, 8);
    node1 = new LCAImplementation::Node<int>(5); 
    binary_tree1->insert(root1, node1, 4);
    node1 = new LCAImplementation::Node<int>(9); 
    binary_tree1->insert(root1, node1, 10);
    binary_tree1->insert(root1, node1, 5);
    node1 = new LCAImplementation::Node<int>(27);
    binary_tree1->insert(root1, node1, 9);

    /*
      Testing the nodeExists method...
    */

    SECTION( "Checking nodeExists method" ) {
      bool res = binary_tree1->nodeExists(6, root1);
      REQUIRE(res == true);
      res = binary_tree1->nodeExists(4, root1);
      REQUIRE(res == true);
      res = binary_tree1->nodeExists(8, root1);
      REQUIRE(res == true);
      res = binary_tree1->nodeExists(10, root1);
      REQUIRE(res == true);
      res = binary_tree1->nodeExists(5, root1);
      REQUIRE(res == true);
      res = binary_tree1->nodeExists(9, root1);
      REQUIRE(res == true);
      res = binary_tree1->nodeExists(27, root1);        
    }

    /*
      Testing the LCA method...
    */
    int* num1 = new int [1];

    SECTION( "Checking the LCA of nodes within the DGA and hence whether insert method worked" ) {
      binary_tree1->LCA(5, 10, num1);
      REQUIRE(num1[0] == 6);
      binary_tree1->LCA(10, 4, num1);
      REQUIRE(num1[0] == 6);
      binary_tree1->LCA(5, 8, num1);
      REQUIRE(num1[0] == 6);
      binary_tree1->LCA(4, 8, num1);
      REQUIRE(num1[0] == 6);
      binary_tree1->LCA(6, 27, num1);
      REQUIRE(num1[0] == 6);
    }


    SECTION( "Checking the LCA of a node/s that is/are not in the DGA" ) {
      binary_tree1->LCA(12, 10, num1);
      int n = (int)num1[0];
      REQUIRE(n == INT_MIN);
      binary_tree1->LCA(50, 80, num1);
      n = (int)num1[0];
      REQUIRE(n == INT_MIN);
    }


    SECTION( "Checking if the ancestor of two nodes which are the same, is the node itself" ) {
      binary_tree1->LCA(8, 8, num1);
      REQUIRE(num1[0] == 8);
      binary_tree1->LCA(27, 27, num1);
      REQUIRE(num1[0] == 27);
      binary_tree1->LCA(6, 6, num1);
      REQUIRE(num1[0] == 6);
    }

    SECTION( "Checking if the ancestor of two nodes, where one node is the ancestor of the other, is the ancestoral node of the two" ) {
      binary_tree1->LCA(8, 10, num1);
      REQUIRE(num1[0] == 8);
      binary_tree1->LCA(10, 27, num1);
      REQUIRE(num1[0] == 10);
      binary_tree1->LCA(9, 5, num1);
      REQUIRE(num1[0] == 5);
    }



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