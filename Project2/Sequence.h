#ifndef Sequence_H
#define Sequence_H

#include <string>


using ItemType = std::string;

struct Node
{
	Node* next;
	Node* prev;
	ItemType data;
};

class Sequence
{
public:
	Sequence();
	~Sequence(); //DESTRUCTOR
	Sequence(const Sequence& other); //COPY CONSTRUCTOR
	Sequence& operator=(const Sequence& rhs); //ASSIGNMENT OPERATOR
	void dump() const;
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);

private:
	Node* head;
	Node* tail;
	int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);





#endif
