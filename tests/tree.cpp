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

TEST_CASE("delete non inserted element")
{
    	tree_t<int> tree1{8};
	tree_t<int> tree2{8};
	REQUIRE(  !tree.deletenode(4) );
	REQUIRE( tree1 == tree2 );
}

TEST_CASE("delete root")
{
    	tree_t<int> tree1{8};
	tree_t<int> tree2;
	REQUIRE(  tree.deletenode(8) );
	REQUIRE( tree1 == tree2 );
}

TEST_CASE("delete root with one child")
{
    	tree_t<int> tree1{8, 4, 3};
	tree_t<int> tree2{4, 3};
	REQUIRE(  tree.deletenode(8) );
	REQUIRE( tree1 == tree2 );
}

TEST_CASE("delete root with children")
{
    	tree_t<int> tree1{8, 4, 3, 10, 9, 13, 11, 12};
	tree_t<int> tree2{9, 4, 3, 10, 13, 11, 12};
	REQUIRE(  tree.deletenode(8) );
	REQUIRE( tree1 == tree2 );
}

TEST_CASE("delete non root without children")
{
    	tree_t<int> tree1{8, 4, 3, 10, 9, 13, 11, 12};
	tree_t<int> tree2{8, 4, 10, 9, 13, 11, 12};
	REQUIRE(  tree.deletenode(3) );
	REQUIRE( tree1 == tree2 );
}

TEST_CASE("delete non root with one child")
{
    	tree_t<int> tree1{8, 4, 3, 10, 9, 13, 11, 12};
	tree_t<int> tree2{8, 4, 3, 10, 9, 13, 12};
	REQUIRE(  tree.deletenode(11) );
	REQUIRE( tree1 == tree2 );
}

TEST_CASE("delete non root with children")
{
    	tree_t<int> tree1{8, 4, 3, 10, 9, 13, 11, 12};
	tree_t<int> tree2{8, 4, 3, 11, 9, 13, 12};
	REQUIRE(  tree.deletenode(10) );
	REQUIRE( tree1 == tree2 );
}

