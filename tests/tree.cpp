#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating tree")
{
	tree_t tree;
	REQUIRE( tree.root() == 0 );
}

/*TEST_CASE("adding tree")
{
	tree_t tree;
  
	REQUIRE();
}

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
