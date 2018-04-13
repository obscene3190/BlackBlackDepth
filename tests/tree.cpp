#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating tree")
{
	tree_t<int> tree;
	REQUIRE( tree.root() == nullptr );
}

TEST_CASE("creating tree with inicialization")
{
	tree_t<int> tree{2, 1, 3};
	std::string result{"----3\n"
			   "--2\n"
			   "----1\n"
	};
	std::ostringstream ostream;
	tree.print(ostream, tree.root());
	REQUIRE( ostream.str() == result );
}

TEST_CASE("adding + printing tree")
{
	tree_t<int> tree;
	std::string input1{"+2\n"};
	std::string input2{"+1\n"};
	std::string input3{"+3\n"};
	std::string result{"----3\n"
			   "--2\n"
			   "----1\n"
	};
	
	std::istringstream istream1{ input1 };
	std::istringstream istream2{ input2 };
	std::istringstream istream3{ input3 };
	REQUIRE(read(tree, istream1));
	REQUIRE(read(tree, istream2));
	REQUIRE(read(tree, istream3));
	std::ostringstream ostream;
	tree.print(ostream, tree.root());
	REQUIRE( ostream.str() == result );
} 

TEST_CASE("finding tree")
{
	tree_t<int> tree;
	std::string input1{"+2\n"};
	std::string input2{"+1\n"};
	std::string input3{"+3\n"};
	std::istringstream istream1{ input1 };
	std::istringstream istream2{ input2 };
	std::istringstream istream3{ input3 };
	REQUIRE(read(tree, istream1));
	REQUIRE(read(tree, istream2));
	REQUIRE(read(tree, istream3));
	REQUIRE(tree.find(3) == true );
	REQUIRE(tree.find(5) == false );
}

TEST_CASE("equaling tree")
{
    	tree_t<int> tree1, tree2;
    	tree1.insert(5);
    	tree1.insert(3);
    	tree1.insert(6);
    	tree2.insert(5);
    	tree2.insert(3);
    	tree2.insert(6);
	REQUIRE(tree1==tree2);
	tree2.insert(7);
	REQUIRE((tree1==tree2) == false);
}

SCENARIO("BST delete non inserted element", "[delete]") {
    tree_t<int> tree{8};
    REQUIRE( !tree.deleteelement(4) );
    REQUIRE( !tree.isEmpty() );
}
//                +----+
//                |-08-|                                               *
//                +----+
//
//
//                                          08
//                                         ---->
SCENARIO("BST delete root without children", "[delete]") {
    tree_t<int> tree{8};
    REQUIRE( tree.deleteelement(8) );
    REQUIRE( tree.isEmpty() );
}
//                +----+                                              +----+
//                |-08-|                                              | 04 |
//                +----+                                              +----+
//                  /                                                   /
//                 /                                                   /
//           +----+                                              +----+
//           | 04 |                                              | 03 |
//           +----+                                              +----+
//             /
//            /
//      +----+                              08
//      | 03 |                             ---->
//      +----+
SCENARIO("BST delete root with one child", "[delete]") {
    tree_t<int>  tree{8, 4, 3};
    REQUIRE( tree.deleteelement(8) );
    REQUIRE( tree == tree_t<int>({4, 3}) );
}
//                +----+                                              +----+
//                |-08-|                                              | 09 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /          \
//            /         /  \                                      /            \
//      +----+    +----+    +----+          08              +----+              +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |              | 13 |
//      +----+    +----+    +----+                          +----+              +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 11 |
//                     +----+                                              +----+
//                        \                                                   \
//                         \                                                   \
//                          +----+                                              +----+
//                          | 12 |                                              | 12 |
//                          +----+                                              +----+
SCENARIO("BST delete root with children", "[delete]") {
    tree_t<int>  tree{8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.deleteelement(8) );
    REQUIRE( tree == tree_t<int>({9, 4, 3, 10, 13, 11, 12}) );
}
//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                                  /\
//            /         /  \                                                /  \
//      +----+    +----+    +----+          03                        +----+    +----+
//      |-03-|    | 09 |    | 13 |         ---->                      | 09 |    | 13 |
//      +----+    +----+    +----+                                    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 11 |
//                     +----+                                              +----+
//                        \                                                   \
//                         \                                                   \
//                          +----+                                              +----+
//                          | 12 |                                              | 12 |
//                          +----+                                              +----+
SCENARIO("BST delete non root without children", "[delete]") {
    tree_t<int>  tree{8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.deleteelement(3) );
    REQUIRE( tree == tree_t<int>({8, 4, 10, 9, 13, 11, 12}) );
}
//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /         /\
//            /         /  \                                      /         /  \
//      +----+    +----+    +----+          11              +----+    +----+    +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |    | 09 |    | 13 |
//      +----+    +----+    +----+                          +----+    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     |-11-|                                              | 12 |
//                     +----+                                              +----+
//                        \
//                         \
//                          +----+
//                          | 12 |
//                          +----+
SCENARIO("BST delete non root with one child", "[delete]") {
    tree_t<int>  tree{8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.deleteelement(11) );
    REQUIRE( tree == tree_t<int>({8, 4, 3, 10, 9, 13, 12}) );
}
//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    |-10-|                                    | 04 |    | 11 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /         /\
//            /         /  \                                      /         /  \
//      +----+    +----+    +----+          10              +----+    +----+    +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |    | 09 |    | 13 |
//      +----+    +----+    +----+                          +----+    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 12 |
//                     +----+                                              +----+
//                        \
//                         \
//                          +----+
//                          | 12 |
//                          +----+
SCENARIO("BST delete non root with children", "[delete]") {
    tree_t<int>  tree{8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.deleteelement(10) );
    REQUIRE( tree == tree_t<int>({8, 4, 3, 11, 9, 13, 12}) );
}
