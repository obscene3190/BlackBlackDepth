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


TEST_CASE( "elements can be inserted in rb tree", "[insert]" ) {
    RBT<int> tree;
    REQUIRE( tree.root() == nullptr );
    REQUIRE( tree.print(ostream, tree.root()) == "" );
    tree.insert( 10 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10" );
    tree.insert( 85 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10r85" );
    tree.insert( 15 );
    REQUIRE( tree.print(ostream, tree.root()) == "r10b15r85" );
    tree.insert( 70 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10b15r70b85" );
    tree.insert( 20 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10b15r20b70r85" );
    tree.insert( 60 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10b15b20r60r70b85" );
    tree.insert( 30 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10b15r20b30r60r70b85" );
    tree.insert( 50 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10r15b20b30r50b60r70b85" );
    tree.insert( 65 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10r15b20b30r50b60r65r70b85" );
    tree.insert( 80 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10r15b20b30r50b60r65r70r80b85" );
    tree.insert( 90 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10r15b20b30r50b60r65r70r80b85r90" );
    tree.insert( 40 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10b15b20b30r40b50r60b65b70r80b85r90" );
    tree.insert( 5 );
    REQUIRE( tree.print(ostream, tree.root()) == "r5b10b15b20b30r40b50r60b65b70r80b85r90" );
    tree.insert( 55 );
    REQUIRE( tree.print(ostream, tree.root()) == "r5b10b15b20b30r40b50r55r60b65b70r80b85r90" );
}
TEST_CASE( "elements can be removde from rb tree", "[remove]" ) {
    RBT<int> tree;
    REQUIRE( tree.root() == nullptr );
    REQUIRE( tree.print(ostream, tree.root()) == "" );
    tree.insert( 10 );
    REQUIRE( tree.print(ostream, tree.root()) == "b10" );
    //REQUIRE( tree.size() == 1 );
    tree.remove( 10 );
    REQUIRE( tree.print(ostream, tree.root()) == "" );
    REQUIRE( tree.root() == nullptr );
    {
        RBT<int> tree;
        tree.insert( 2 );
        tree.insert( 1 );
        tree.insert( 3 );
        tree.insert( 4 );
        tree.insert( 5 );
        //        std::cout << tree << std::endl;
        //        std::ofstream("tmp") << tree << std::endl;
        //         b2
        //        /  \
        //       /    \
        //     b1      b4
        //            /  \
        //           /    \
        //         r3      r5
        REQUIRE( tree.print(ostream, tree.root()) == "b1b2r3b4r5" );
        std::cout << tree << std::endl;
        tree.remove( 2 );
        std::ofstream("tmp") << tree << std::endl;
    }
}
TEST_CASE( "elements can be removed from rb tree ", "[remove, bug]" ) {
    {
        RBT<int> tree;
        SECTION( "when brother is black and his sons" ) {
            tree.insert( 1 );
            tree.insert( 2 );
            tree.insert( 6 );
            tree.insert( 8 );
            tree.insert( 9 );
            tree.insert( 7 );
            tree.insert( 4 );
            tree.insert( 4 );
            tree.insert( 2 );
            tree.insert( 4 );
            tree.insert( 4 );
            tree.remove( 4 );
            tree.remove( 4 );
            tree.remove( 4 );
            tree.remove( 4 );
            tree.remove( 8 );
            REQUIRE( tree.print(ostream, tree.root()) == "b1b2b2b6b7b9" );
            tree.remove( 9 );
            REQUIRE( tree.print(ostream, tree.root()) == "b1r2b2b6b7" );
        }
        SECTION( "when brother is black and his right son is red" ) {
            tree.insert( 1 );
            tree.insert( 2 );
            tree.insert( 3 );
            tree.insert( 4 );
            tree.insert( 5 );
            tree.insert( 6 );
            tree.insert( 7 );
            tree.insert( 8 );
            tree.insert( 9 );
            tree.insert( 10 );
            tree.insert( 11 );
            tree.insert( 0 );
            tree.remove( 3 );
            std::cout << tree << std::endl;
            REQUIRE( tree.print(ostream, tree.root()) == "r0b1b2b4b5b6b7r8r9b10r11" );
            tree.remove( 2 );
            std::cout << tree << std::endl;
            REQUIRE( tree.print(ostream, tree.root()) == "r0b1b4b5b6b7b8r9b10r11" );
        }
        SECTION( "when brother is red" ) {
            tree.insert( 1 );
            std::cout << tree << std::endl;
            tree.insert( 2 );
            std::cout << tree << std::endl;
            tree.insert( 3 );
            std::cout << tree << std::endl;
            tree.insert( 4 );
            std::cout << tree << std::endl;
            tree.insert( 5 );
            std::cout << tree << std::endl;
            tree.insert( 6 );
            std::cout << tree << std::endl;
            tree.insert( 7 );
            std::cout << tree << std::endl;
            tree.insert( 8 );
            std::cout << tree << std::endl;
            tree.insert( 9 );
            std::cout << tree << std::endl;
            tree.insert( 10 );
            std::cout << tree << std::endl;
            tree.insert( 11 );
            std::cout << tree << std::endl;
            tree.insert( 0 );
            std::cout << tree << std::endl;
            tree.remove( 3 );
            std::cout << tree << std::endl;
            tree.insert( 5 );
            std::cout << tree << std::endl;
            tree.insert( 5 );
            std::cout << tree << std::endl;
            tree.insert( 5 );
            std::cout << tree << std::endl;
            tree.insert( 5 );
            std::cout << tree << std::endl;
            tree.insert( 5 );
            std::cout << tree << std::endl;
            REQUIRE( tree.print(ostream, tree.root()) == "r0b1b2b4b5b5b5r5b5r5r6b7b8r9b10r11" );
            tree.remove( 2 );
            std::cout << tree << std::endl;
            REQUIRE( tree.print(ostream, tree.root()) == "r0b1b4b5r5b5b5b5r5b6b7b8r9b10r11" );
        }
    }
}
