//
//  main.cpp
//  week02
//
//  Created by Beitong Tian on 1/30/18.
//  Copyright © 2018 Beitong Tian. All rights reserved.
//

#include <iostream>
using namespace std;

int ipow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    
    return result ;
}

int main(int argc, const char * argv[]) {
//    // insert code here...
//    string username;
//    cout << "Please enter your username: ";
//    cin >> username;
//    cout << "Hi " << username << "! \n";
//    return 0;
    int x = 5;
    int *p_pointer_to_integer = & x;
    int y = ipow(2,31);
    cout << p_pointer_to_integer<< endl; // prints the address of x
    cout << y << endl;
}

/*
 cin.get();
 getline(cin, user_name, '\n');
 getline(cin, my_string, ',');
 appending two strings
 #include <string>
 using + to append two strings
 
 while ( true )
 {
 cin >> input;
 if ( ! isValid( input ) )
 {
 continue;
 }
 // go on to process the input as normal
 }
 
 enum TicTacToeSquare { TTTS_BLANK, TTTS_O, TTTS_X };
 if ( board_position == TTTS_O )
 {
 
}
 enum is good for restrict the value and give number a name to be more readable.
 
 #include <ctime>
 #include <cstdlib>
 #include <iostream>
 using namespace std;
 int randRange (int low, int high)
 {
 // we get a random number, get it to be between 0 and the difference
 // between high and low, then add the lowest possible value
 return rand() % ( high - low ) + low;
 }
 int main ()
 {
 srand( time( NULL ) );
 for ( int i = 0; i < 1000; ++i )
 {            cout << randRange( 4, 10 ) << '\n';
 }
 }
 
 int srand_seed = time( NULL );
 cout << seed << '\n';
 srand( srand_seed );
 rand();
 
 array
 int sum_array (int values[]);
 
 copy the value to left and right
 void swap1 (int left, int right)
 {
 int temp;
 temp = left;
 left = right;
 right = temp;
 }
 transmit the real value to the function
 void swap (int& left, int& right)
 {
 int temp = right;
 right = left;
 left = temp; }
 
 
 
 */


