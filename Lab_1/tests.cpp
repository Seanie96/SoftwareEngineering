#include "../../../../catch.hpp"
#include "LCA.hpp"

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

  REQUIRE(*(binary_tree.LCA(7, 10)) == 8);
}
