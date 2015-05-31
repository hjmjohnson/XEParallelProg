#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
  int Spaces = 0;
  char Message[]="The Beauty of Lambda!";

  for_each( // use STL for_each
     Message, // beginning of string
     Message + sizeof(Message), // end of string

     // The lambda function
     [&Spaces] (char c) { if (c == ' ') Spaces++;}
  ); // end of for_each

  cout << "'" << Message << "'" << " has " << Spaces << " spaces " <<endl;
 }