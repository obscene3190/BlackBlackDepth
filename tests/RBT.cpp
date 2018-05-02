#include <catch.hpp>
#include <sstream>

#include "RBT.hpp"

TEST_CASE("creating tree")
{
	RBT<int> tree;
	REQUIRE( tree.root() == nullptr );
}

TEST_CASE("simple adding + printing tree")
{
	RBT<int> tree;
	std::string result{"----3\n"
			   "--2\n"
			   "----1\n"
	};
	tree.insert(2);
	tree.insert(3);
	tree.insert(1);
	std::ostringstream ostream;
	tree.print(ostream, tree.root());
	REQUIRE( ostream.str() == result );
} 

TEST_CASE("finding tree")
{
	RBT<int> tree;
	tree.insert(2);
	tree.insert(3);
	tree.insert(1);
	REQUIRE(tree.find(3) == true );
	REQUIRE(tree.find(5) == false );
}

TEST_CASE("adding with simple balancing")
{
	RBT<int> tree;
	std::string result{"------5\n"
			   "----4\n"
			   "--3\n"
			   "----2\n"
	};
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	std::ostringstream ostream;
	tree.print(ostream, tree.root());
	REQUIRE( ostream.str() == result );
} 
