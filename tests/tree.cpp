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

TEST_CASE("fequaling tree")
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

TEST_CASE("fequaling tree")
{
    	tree_t<int> tree{7, 3, 8, 2, 5, 4, 9};
	std::string result8{"----9\n"
			    "--7\n"
			    "------5\n"
			    "--------4\n"
			    "----3\n"
			    "------2\n"
        };
    	tree.deleteelement(tree.root(), 8);
	std::ostringstream ostream1;
	tree.print(ostream1, tree.root());
	REQUIRE( ostream.str() == result8 );
	
	std::string result5{"----9\n"
			    "--7\n"
			    "------4\n"
			    "----3\n"
			    "------2\n"
        };
	tree.deleteelement(tree.root(), 5);
	std::ostringstream ostream2;
	tree.print(ostream2, tree.root());
	REQUIRE( ostream.str() == result5 );
	
	std::string result3{"----9\n"
			    "--7\n"
			    "----4\n"
			    "------2\n"
        };
        tree.deleteelement(tree.root(), 3);
	std::ostringstream ostream3;
	tree.print(ostream3, tree.root());
	REQUIRE( ostream.str() == result3 );
}
