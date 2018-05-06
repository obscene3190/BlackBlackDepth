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
    std::ostringstream ostream;
    REQUIRE( tree.root() == nullptr );
    tree.print(ostream, tree.root());
    REQUIRE( ostream.str() == "" );
    tree.insert( 10 );
    tree.print(ostream, tree.root());
    REQUIRE( ostream.str() == "--b10\n" );
    tree.insert( 85 );
    std::ostringstream ostream1;
    tree.print(ostream1, tree.root());
    REQUIRE( ostream1.str() ==	 "----r85\n"
	    			 "--b10\n" );
    tree.insert( 15 );
	std::ostringstream ostream2;
    tree.print(ostream2, tree.root());
    REQUIRE( ostream2.str() ==	  "----r85\n"
	    					 "--b15\n"
	   					 "----r10\n");
    tree.insert( 70 );
	std::ostringstream ostream3;
    tree.print(ostream3, tree.root());
    REQUIRE( ostream3.str() ==	 		 "----b85\n"
						 "------r70\n"
						 "--b15\n"
						 "----b10\n" );
    tree.insert( 20 );
	std::ostringstream ostream4;
    tree.print(ostream4, tree.root());
    REQUIRE( ostream4.str() ==	 		  	"------r85\n"
							"----b70\n"
							"------r20\n"
							"--b15\n"
							"----b10\n" );
    tree.insert( 60 );
	std::ostringstream ostream5;
    tree.print(ostream5, tree.root());
    REQUIRE( ostream5.str() ==	 		  	"------b85\n"
							"----r70\n"
							"--------r60\n"
							"------b20\n"
							"--b15\n"
							"----b10\n" );
    tree.insert( 30 );
	std::ostringstream ostream6;
    tree.print(ostream6, tree.root());
    REQUIRE( ostream6.str() ==	 		  	"------b85\n"
							"----r70\n"
							"--------r60\n"
							"------b30\n"
							"--------r20\n"
							"--b15\n"
							"----b10\n" );
    tree.insert( 50 );
	std::ostringstream ostream7;
    tree.print(ostream7, tree.root());
    REQUIRE( ostream7.str() ==	 		  	"------b85\n"
							"----r70\n"
							"------b60\n"
							"--------r50\n"
							"--b30\n"
							"------b20\n"
							"----r15\n"
							"------b10\n" );
    tree.insert( 65 );
	std::ostringstream ostream8;
    tree.print(ostream8, tree.root());
    REQUIRE( ostream8.str() ==	 		  	"------b85\n"
							"----r70\n"
							"--------r65\n"
							"------b60\n"
							"--------r50\n"
							"--b30\n"
							"------b20\n"
							"----r15\n"
							"------b10\n" );
    tree.insert( 80 );
	std::ostringstream ostream9;
    tree.print(ostream9, tree.root());
    REQUIRE( ostream9.str() ==	 		  	"------b85\n"
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
	std::ostringstream ostream11;
    tree.print(ostream11, tree.root());
    REQUIRE( ostream11.str() ==	 		  	"--------r90\n"
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
	std::ostringstream ostream12;
    tree.print(ostream12, tree.root());
    REQUIRE( ostream12.str() ==	 		  	"--------r90\n"
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
	std::ostringstream ostream13;
    tree.print(ostream13, tree.root());
    REQUIRE( ostream13.str() ==	 		  	"--------r90\n"
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
	std::ostringstream ostream14;
    tree.print(ostream14, tree.root());
    REQUIRE( ostream14.str() ==	 		  	"--------r90\n"
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
    std::ostringstream ostream;
    REQUIRE( tree.root() == nullptr );
    tree.print(ostream, tree.root());
    REQUIRE( ostream.str() == "" );
    tree.insert( 10 );
    tree.print(ostream, tree.root());
    REQUIRE( ostream.str() == "--b10\n" );
    //REQUIRE( tree.size() == 1 );
    tree.remove( 10 );
    tree.print(ostream, tree.root());
    REQUIRE( ostream.str() == "" );
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
        tree.print(ostream, tree.root());
        REQUIRE( ostream.str() == 	     		"------r5\n"
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
	std::ostringstream ostream;
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
        tree.print(ostream, tree.root());
        REQUIRE( ostream.str() ==			"----b9\n"
							"------r7\n"
							"--b6\n"
							"------b2\n"
							"----r2\n"
							"------b1\n" );
        tree.remove( 9 );
		std::ostringstream ostream1;
        tree.print(ostream1, tree.root());
        REQUIRE( ostream1.str() ==			"----b7\n"
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
            tree.print(ostream, tree.root());
        REQUIRE( ostream.str() ==			"----------r11\n"
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
		std::ostringstream ostream3;
            tree.print(ostream3, tree.root());
        REQUIRE( ostream3.str() ==			"--------r11\n"
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
            tree.print(ostream, tree.root());
        REQUIRE( ostream.str() ==			 "------b8\n"
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
		std::ostringstream ostream2;
            tree.print(ostream2, tree.root());
        REQUIRE( ostream2.str() ==			 "--------r11\n"
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
