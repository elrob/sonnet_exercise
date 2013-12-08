/* MSc C++ Programming – Assessed Exercise No. 1 */

/* Author: Robert Speller
   Program last changed: 23rd October 2012 */

/* This program determines the type of a particular sonnet. */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cctype>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}



/* START WRITING YOUR FUNCTION BODIES HERE */

/* FUNCTION DEFINITION FOR find_ending */
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
/* END FUNCTION DEFINITION */


/* FUNCTION DEFINITION FOR add_new_node */
void add_new_node(NodePtr &ptr)
{
  ptr = new Node;
  if (ptr == NULL )
    {
      cout << "Sorry, ran out of memory";
      exit(1);
    }
}
/* END OF FUNCTION DEFINITION */


/* FUNCTION DEFINITION FOR rhyming_letter */
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
/* END FUNCTION DEFINITION */

  
/* FUNCTION DEFINITION FOR identify_sonnet */
char * identify_sonnet( const char *filename )
{
  char scheme[ MAX_LINE_SIZE ];
  if ( !find_rhyme_scheme( filename, scheme ) )
    return (char*) "Unknown";
  else if ( !strcmp( scheme, "ababcdcdefefgg" ) )
    return (char*) "Shakespearean";
  else if ( !strcmp( scheme, "abbaabbacdcdcd" ) )
    return (char*) "Petrarchan";
  else if ( !strcmp( scheme, "ababbcbccdcdee" ) )
    return (char*) "Spenserian";
  else
    return (char*) "Unknown";
}
/* END OF FUNCTION DEFINITION */


/* FUNCTION DEFINITION FOR find_rhyme_scheme */
bool find_rhyme_scheme( const char *filename, char *scheme )
{
  // open the sonnet file
  ifstream the_file;
  the_file.open( filename );
  if ( the_file.fail() )
    {
      *scheme = '\0';
      return false;
    }

  char line[ MAX_LINE_SIZE ];
  rhyming_letter(RESET);
  // iterate over every line to work out rhyme scheme
  while ( the_file.getline( line, MAX_LINE_SIZE ) )
    {
      char word[ MAX_LINE_SIZE ];
      get_word( line, count_words( line ), word ); // get last word of line
      char phon_ending[ MAX_LINE_SIZE ];
      bool success = find_phonetic_ending( word, phon_ending ); // get the phonetic ending of the word
      if ( !success )
	cout << "\"" << word << "\" was not found in \"dictionary.txt\"\n";
      *scheme = rhyming_letter( phon_ending ); // append the result to the rhyming scheme
      scheme++;
    }
  *scheme = '\0';
  
  the_file.close();
  
  return true;
}
/* END FUNCTION DEFINITION */


/* FUNCTION DEFINITON FOR word_has_vowel */
bool word_has_vowel( const char *word )
{
  while ( *word )
    {
      if ( *word == 'A' ||
	   *word == 'E' ||
	   *word == 'I' ||
	   *word == 'O' ||
	   *word == 'U' )
	return true;
      else
	word++;
    }
  return false;
}
/* END FUNCTION DEFINITON*/


/* FUNCTION DEFINITION FOR get_ending */
void get_ending( const char *line, int words, char *phon_ending )
{
  char the_word[ MAX_LINE_SIZE ];
  get_word( line, words, the_word );

  if ( words < 2 )
    /* avoid testing the first word on 
       the line (the dictionary word itself.) */
    return;

  else if ( !word_has_vowel( the_word ) )
    //recurse to the previous word in the line
    get_ending( line, words-1, phon_ending ); 
  
  if ( word_has_vowel( the_word ) || words == 2 )
    // add first part of phonetic ending to 'phon_ending'
    strcpy( phon_ending, the_word );

  else
    // append other parts of phonetic ending
    strcat( phon_ending, the_word );
}
/* END FUNCTION DEFINITON*/


/* FUNCTION DEFINITION FOR find_word */
bool find_word( const char *word, char *line )
{
  // open dictionary.txt
  ifstream dictionary;
  dictionary.open("dictionary.txt");
  if ( dictionary.fail() )
    {
      cout << "Error opening dictionary.txt." << endl;
      exit(1);
    }
  
  dictionary.getline( line, MAX_LINE_SIZE );

  char first_word[ MAX_LINE_SIZE ];
  while (/*- set 'first_word' to the first word of each line 
	   - end while loop if 'word' and 'first_word' the same
	   - pass the next line to 'line' or end while loop */
	 get_word( line, 1, first_word ) &&
	 strcmp( word, first_word) &&
	 dictionary.getline( line, MAX_LINE_SIZE ) ) ; // no loop body
      
  
  if ( strcmp( word, first_word ) )
    {// 'word' and 'first_word' different
      dictionary.close();
      return false;
    }
  
  else 
    {// 'word' and 'first_word' the same
      dictionary.close();
      return true;
    }
}
/* END FUNCTION DEFINITON*/


/* FUNCTION DEFINITION FOR find_phonetic_ending */
bool find_phonetic_ending( const char *word, char *phon_ending )
{
  char line[ MAX_LINE_SIZE ];
  
  bool found;
  
  found = find_word( word, line );
  
  if ( !found )
    {
      *phon_ending = '\0';
      return false;
    }
  else
    {
      //int words = count_words( line );
      get_ending( line, count_words( line ), phon_ending );
      return true;
    }
}
/* END FUNCTION DEFINITON*/


/* FUNCTION DEFINITION FOR count_words */
int count_words(const char *line )
{
  /* here a word is defined as a string of alphanumeric
     characters separated by nothing except an apostrophe */
  int words = 0;

  while ( *line )
    {     
      // while loop which skips any leading whitespace
      while ( *line && !( isalnum(*line) || *line=='\'' ) )
	line++;

      // increment words when the beginning of a word is found
      if ( *line )
	words++;

      // skip over the other characters in this word
      while ( *line && ( isalnum(*line) || *line=='\'' ) )
	line++;
    }
  return words;
}
/* END FUNCTION DEFINITON*/
