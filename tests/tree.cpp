#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating tree")
{
	tree_t tree;
	REQUIRE( tree.root() == nullptr );
}

TEST_CASE("adding tree")
{
	tree_t tree;
	std::string input1{"+2/n"};
	std::string input2{"+1/n"};
	std::string input3{"+3/n"};
	std::string result{"----3
	--2
	----1
	"};
	
	std::istringstream istream1{ input1 };
	std::istringstream istream2{ input2 };
	std::istringstream istream3{ input3 };
	REQUIRE(read(tree, istream1));
	REQUIRE(read(tree, istream2));
	REQUIRE(read(tree, istream3));
	std::ostringstream ostream;
	tree.print(ostream, tree.root());
	REQUIRE( result == ostream.str() );
} 
/*

TEST_CASE("printing tree")
{
	tree_t tree;
	REQUIRE(  );
}

TEST_CASE("finding tree")
{
	tree_t tree;
	REQUIRE(  );
}*/
