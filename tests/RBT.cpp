#include <catch.hpp>
#include <sstream>

#include "RBT.hpp"

TEST_CASE("creating tree")
{
	RBT<int> tree;
	REQUIRE( tree.root() == nullptr );
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

TEST_CASE( "elements can be inserted in rb tree", "[insert]" ) {
    RBT<int> tree;
    REQUIRE( tree.root() == nullptr );
    REQUIRE( tree.print(ostream, tree.root()) == "" );
    tree.insert( 10 );
    REQUIRE( tree.print(ostream, tree.root()) == "--b10\n" );
    tree.insert( 85 );
    REQUIRE( tree.print(ostream, tree.root()) == "----r85\n"
	    					 "--b10\n" );
    tree.insert( 15 );
    REQUIRE( tree.print(ostream, tree.root()) == "----r85\n"
	    					 "--b15\n"
	   					 "----r10\n");
    tree.insert( 70 );
    REQUIRE( tree.print(ostream, tree.root()) == "----b85\n"
						 "------r70\n"
						 "--b15\n"
						 "----b10\n" );
    tree.insert( 20 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"------r85\n"
							"----b70\n"
							"------r20\n"
							"--b15\n"
							"----b10\n" );
    tree.insert( 60 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"------b85\n"
							"----r70\n"
							"--------r60\n"
							"------b20\n"
							"--b15\n"
							"----b10\n" );
    tree.insert( 30 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"------b85\n"
							"----r70\n"
							"--------r60\n"
							"------b30\n"
							"--------r20\n"
							"--b15\n"
							"----b10\n" );
    tree.insert( 50 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"------b85\n"
							"----r70\n"
							"------b60\n"
							"--------r50\n"
							"--b30\n"
							"------b20\n"
							"----r15\n"
							"------b10\n" );
    tree.insert( 65 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"------b85\n"
							"----r70\n"
							"--------r65\n"
							"------b60\n"
							"--------r50\n"
							"--b30\n"
							"------b20\n"
							"----r15\n"
							"------b10\n" );
    tree.insert( 80 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"------b85\n"
							"--------r80\n"
							"----r70\n"
							"--------r65\n"
							"------b60\n"
							"--------r50\n"
							"--b30\n"
							"------b20\n"
							"----r15\n"
							"------b10\n" );
    tree.insert( 90 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"--------r90\n"
							"------b85\n"
							"--------r80\n"
							"----r70\n"
							"--------r65\n"
							"------b60\n"
							"--------r50\n"
							"--b30\n"
							"------b20\n"
							"----r15\n"
							"------b10\n" );
    tree.insert( 40 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"--------r90\n"
							"------b85\n"
							"--------r80\n"
							"----b70\n"
							"--------b65\n"
							"------r60\n"
							"--------b50\n"
							"----------r40\n"
							"--b30\n"
							"------b20\n"
							"----b15\n"
							"------b10\n" );
    tree.insert( 5 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"--------r90\n"
							"------b85\n"
							"--------r80\n"
							"----b70\n"
							"--------b65\n"
							"------r60\n"
							"--------b50\n"
							"----------r40\n"
							"--b30\n"
							"------b20\n"
							"----b15\n"
							"------b10\n"
							"--------r5\n" );
    tree.insert( 55 );
    REQUIRE( tree.print(ostream, tree.root()) == 	"--------r90\n"
							"------b85\n"
							"--------r80\n"
							"----b70\n"
							"--------b65\n"
							"------r60\n"
							"----------r55\n"
							"--------b50\n"
							"----------r40\n"
							"--b30\n"
							"------b20\n"
							"----b15\n"
							"------b10\n"
							"--------r5\n" );
}
TEST_CASE( "elements can be removde from rb tree", "[remove]" ) {
    RBT<int> tree;
    REQUIRE( tree.root() == nullptr );
    REQUIRE( tree.print(ostream, tree.root()) == "" );
    tree.insert( 10 );
    REQUIRE( tree.print(ostream, tree.root()) == "--b10" );
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
        REQUIRE( tree.print(ostream, tree.root()) == 	"------r5\n"
							"----b4\n"
							"------r3\n"
							"--b2\n"
							"----b1\n" );
        //std::cout << tree << std::endl;
        tree.remove( 2 );
        //std::ofstream("tmp") << tree << std::endl;
    }
}
TEST_CASE( "elements can be removed from rb tree ", "[remove, bug]" ) {
    {
        RBT<int> tree;
        SECTION( "when brother is black and his sons" ) {
        RBT<int> tree;
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
        REQUIRE( tree.print(ostream, tree.root()) == 	"----b9\n"
							"------r7\n"
							"--b6\n"
							"------b2\n"
							"----r2\n"
							"------b1\n" );
        tree.remove( 9 );
        REQUIRE( tree.print(ostream, tree.root()) == 	"----b7\n"
							"--b6\n"
							"------b2\n"
							"----r2\n"
							"------b1\n" );
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
            REQUIRE( tree.print(ostream, tree.root()) =="----------r11\n"
							"--------b10\n"
							"----------r9\n"
							"------r8\n"
							"--------b7\n"
							"----b6\n"
							"------b5\n"
							"--b4\n"
							"------b2\n"
							"----b1\n"
							"------b0\n" );
            tree.remove( 2 );
            REQUIRE( tree.print(ostream, tree.root()) =="--------r11\n"
							"------b10\n"
							"--------r9\n"
							"----b8\n"
							"------b7\n"
							"--b6\n"
							"------b5\n"
							"----b4\n"
							"------b1\n"
							"--------r0\n" );
        }
        SECTION( "when brother is red" ) {
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
            tree.insert( 5 );
            tree.insert( 5 );
            tree.insert( 5 );
            tree.insert( 5 );
            tree.insert( 5 );
            REQUIRE( tree.print(ostream, tree.root())== "------b8\n"
							"--------b7\n"
							"----r6\n"
							"------------r5\n"
							"----------b5\n"
							"--------r5\n"
							"----------b5\n"
							"------b5\n"
							"--------b5\n"
							"--b4\n"
							"------b2\n"
							"----b1\n"
							"------b0\n" );
            tree.remove( 2 );
            REQUIRE( tree.print(ostream, tree.root()) == "--------r11\n"
							"------b10\n"
							"--------r9\n"
							"----b8\n"
							"------b7\n"
							"--b6\n"
							"----------r5\n"
							"--------b5\n"
							"------b5\n"
							"--------b5\n"
							"----r5\n"
							"--------b5\n"
							"------b4\n"
							"--------b1\n"
							"----------r0\n" );
        }
    }
}
