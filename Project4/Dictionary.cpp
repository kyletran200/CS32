// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

const int NUM_BUCKETS = 50000;		//Creates Hash Table of size 50,000 .... i.e. 50,000 buckets

									// This class does the real work of the implementation.
struct WORD					//Each word will be represented by this struct. The word has a string, an anagram value, and a bucket number
{
	string word;
	int anagramValue;
	int bucketNumber;
};

class DictionaryImpl
{
public:
	DictionaryImpl() {}
	~DictionaryImpl() {}
	void insert(string word);
	void lookup(string letters, void callback(string));
private:
	unsigned int hashFunction(string& word);
	unsigned int getAnagramValue(string& word) const;
	list<WORD> hash_table[NUM_BUCKETS];

};


unsigned int DictionaryImpl::getAnagramValue(string& word) const //This function returns a number that is a factor of only prime numbers which represents a word
{
	unsigned int anagramValue = 1;
	unsigned int primeNumbers[26] = { 2, 3 , 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101 };
	for (int i = 0; i < word.length(); i++)
	{
		unsigned int lettersPlaceInAlphabet = word[i] - 97;  //the char a for example would be 0, because it is first the in alphabet. b would be 1 and etc..
		unsigned int primeEquivalent = primeNumbers[lettersPlaceInAlphabet];	//Convert the char in the alphabet to its respctive prime number value
		anagramValue = anagramValue * primeEquivalent;	//Update the anagram value for each character
	}
	return anagramValue; //Return the total value of the word based off its chars
}

unsigned int DictionaryImpl::hashFunction(string& word)
{
	removeNonLetters(word);		//Get rid of any nonletters in the word
	unsigned int anagramValue = getAnagramValue(word);	//Get the numerical value of the word and divide by the number of buckets to get a bucket value
	return anagramValue % NUM_BUCKETS;
}



void DictionaryImpl::insert(string word)
{
	removeNonLetters(word);		//Get rid of any nonletters in the word
	if (!word.empty())				//If the word is not empty....
	{
		WORD dictionaryWord = WORD();						//Create a new word struct
		unsigned int anagramValue = getAnagramValue(word);		//Get the numerical value of the word and assign it
		unsigned int bucket = hashFunction(word);		//Get the bucket where it belongs and assign it
		dictionaryWord.word = word;							//Assign the string word value to the word struct
		dictionaryWord.anagramValue = anagramValue;
		dictionaryWord.bucketNumber = bucket;
		hash_table[bucket].push_back(dictionaryWord);		//Push the struct onto the list at the bucket in the array
	}
}

void DictionaryImpl::lookup(string letters, void callback(string))
{
	if (callback == nullptr)		//If the letters entered is empty or if the callback is called on a nullptr return and do nothing
	{
		return;
	}
	removeNonLetters(letters);
	if (letters.empty())
	{
		return;
	}
	string permutation = letters;
	unsigned int bucket = hashFunction(permutation);				//Find the bucket in which the permutation of the word should be located
	int anagramValue = getAnagramValue(permutation);  //Now search the linked list at the bucket for the word
	list<WORD>::iterator it;
	it = hash_table[bucket].begin();			//Use an iterator to loop through the list at that bucket
	while (it != hash_table[bucket].end())
	{
		if (anagramValue == (*it).anagramValue)	//If the anagram value matches the anagram value in the linked list, callback on the string
		{
			callback((*it).word);
		}
		it++;
	}
}


void removeNonLetters(string& s)
{
	string::iterator to = s.begin();
	for (string::const_iterator from = s.begin(); from != s.end(); from++)
	{
		if (isalpha(*from))
		{
			*to = tolower(*from);
			to++;
		}
	}
	s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
	string::iterator last = permutation.end() - 1;
	string::iterator p;

	for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
		;
	if (p != permutation.begin())
	{
		string::iterator q;
		for (q = p + 1; q <= last && *q > *(p - 1); q++)
			;
		swap(*(p - 1), *(q - 1));
	}
	for (; p < last; p++, last--)
		swap(*p, *last);
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
	m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
	delete m_impl;
}

void Dictionary::insert(string word)
{
	m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
	m_impl->lookup(letters, callback);
}
