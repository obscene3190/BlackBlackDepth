#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating tree")
{
	tree_t<int> tree;
	REQUIRE( tree.root() == nullptr );
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

TEST_CASE("fequaling tree")
{
    	tree_t<int> tree1, tree2;
    	tree1.insert(5);
    	tree1.insert(3);
    	tree1.insert(7);
    	tree2.insert(5);
    	tree2.insert(3);
    	tree2.insert(6);
	REQUIRE((tree1==tree2) == true);
	tree2.insert(7);
	REQUIRE((tree1==tree2) == false);
}
