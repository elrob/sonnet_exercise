#include <iostream>
#include <cstring>
#include <cstdlib>

#define RESET NULL

using namespace std;



const int MAX_LINE_SIZE = 512;

struct Node;
typedef Node* NodePtr;

/* Nodes for a linked list. Each contains an ending
   and the letter in the rhyme scheme it refers to. */
struct Node {
  char ending[ MAX_LINE_SIZE ];
  char letter;
  NodePtr next_node;
};

/* Function returns true if and only if 'ending' is found
   in one of the nodes in the linked list. The node pointer 
   is returned using the NodePtr& called 'test_node' */
bool find_ending( NodePtr& test_node, const char *ending )
{
  while ( test_node->next_node != NULL &&
	  strcmp( test_node->ending, ending ))
    test_node = test_node->next_node;

  if ( !strcmp( test_node->ending, ending ) )
    return true;
  else
    return false;
}

/* Function to add a dynamic node and ensure
   there is enough space in memory or exit. */
void add_new_node(NodePtr &ptr)
{
  ptr = new Node;
  if (ptr == NULL )
    {
      cout << "Sorry, ran out of memory";
      exit(1);
    }
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */
char rhyming_letter(const char *ending) {
  static bool first_call = true;
  static NodePtr first_node = NULL, last_node = NULL;
  static char next = 'a';

  if (ending == RESET) //reset all values
    {
      next = 'a';
      first_call = true;
      NodePtr current_node = first_node;
      NodePtr the_next_node = first_node;
      while ( the_next_node ) //delete linked list
	{
	  the_next_node = current_node->next_node;
	  delete current_node;
	  current_node = the_next_node;
	}
      first_node = NULL;
      last_node = NULL;
      return '\0';
    }

  NodePtr a_node;
  NodePtr current_node = first_node;

  if ( first_call || !find_ending( current_node, ending ))
    {
      add_new_node( a_node );
      if ( first_call )
	{
	  last_node = a_node;
	  first_node = last_node;
	  first_call = false;
	}
      else
	{
	  last_node->next_node = a_node;
	  last_node = a_node;
	}
      strcpy( last_node->ending, ending ); //copy ending to node 
      last_node->letter = next; //copy letter to node
      last_node->next_node = NULL;
      return next++;
    }
  else
    {
      //current_node has been found in the if statement above
      return current_node->letter;
    }
}
  
int main()
{
 
  cout << rhyming_letter( "AYE" ) << endl;
  cout << rhyming_letter( "BYE" ) << endl;
  cout << rhyming_letter( "AYE" ) << endl;
  cout << rhyming_letter( "AYE" ) << endl;
  cout << rhyming_letter( "BYE" ) << endl;
  cout << rhyming_letter( "CYE" ) << endl;
  cout << rhyming_letter( RESET ) << endl;
  cout << rhyming_letter( "DYE" ) << endl;
  cout << rhyming_letter( "EYE" ) << endl;
  cout << rhyming_letter( "DYE" ) << endl;
  cout << rhyming_letter( "DYE" ) << endl;
  cout << rhyming_letter( "EYE" ) << endl;
  cout << rhyming_letter( "FYE" ) << endl;



  return 0;
}
