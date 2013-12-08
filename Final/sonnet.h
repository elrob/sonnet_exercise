/* MSc C++ Programming – Assessed Exercise No. 1 */

/* Author: Robert Speller
   Program last changed: 23rd October 2012 */

/* This program determines the type of a particular sonnet. */


// RESET is a constant used by function rhyming_letter(...)
#define RESET NULL

/* Maximum line size can be 511 characters plus a null character. */
const int MAX_LINE_SIZE = 512;

/* Nodes for a linked list. Each contains an ending
   and the letter in the rhyme scheme it refers to. */
struct Node;
typedef Node* NodePtr;
struct Node {
  char ending[ MAX_LINE_SIZE ];
  char letter;
  NodePtr next_node;
};


/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int number, char *output_word);


/* Function returns true if and only if 'ending' is found
   in one of the nodes in the linked list. The node pointer 
   is returned using the NodePtr& called 'test_node' */

bool find_ending( NodePtr& test_node, const char *ending );


/* Function to add a dynamic node and ensure
   there is enough space in memory or exit. */

void add_new_node(NodePtr &ptr);


/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending); //Function rewritten by Robert Speller


/* Function which takes a filename as its only input and returns 
   one of four strings to identify the sonnet contained in the file. */

char * identify_sonnet( const char *filename );


/* Function which checks 'file' for its sonnet rhyme scheme and
   passes it to 'scheme' in the form ababcdcdefefgg for example.
   If the file does not exist, it returns false, else true.*/

bool find_rhyme_scheme( const char *filename, char *scheme );


/* Function which only returns true 
   if 'word' includes a vowel. */

bool word_has_vowel( const char* word );


/* Function which passes the phonetic ending (all trailing words 
   starting from the word which includes the last vowel) 
   on 'line' of length 'words' to the c-string 'phon_ending' */

void get_ending( const char *line, int words, char *phon_ending );


/* Function which returns true if a word is found in 'dictionary.txt' 
   and passes the line that it's on back to the c-string 'line' */

bool find_word( const char *word, char *line );


/* Function which returns true if a word is found in 'dictionary.txt'
   and passes its phonetic ending to the c-string 'phon_ending' */ 

bool find_phonetic_ending( const char *word, char *phon_ending );


/* Function which counts the words in a c-string. 
   It returns the number of words as an integer. */

int count_words(const char *line );
