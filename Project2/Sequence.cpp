#include "Sequence.h"
#include <iostream>



Sequence::Sequence()
{						//initialize the size to zero and head and tail to null
	m_size = 0;
	head = nullptr;
	tail = head;
}
Sequence::~Sequence()
{							//go through the nodes and delete them
	Node *p;
	p = head;
	while (p != nullptr)
	{
		Node *n = p->next;
		delete p;
		p = n;
	}
}

Sequence::Sequence(const Sequence& other)
{
	m_size = other.m_size;						//copy the size
	if (other.tail == nullptr && head == tail)	//if copying and empty object set head and tail to null
	{
		head = tail = nullptr;
	}
	else
	{
		Node *q = other.head;		//set copy head to original head
		Node *p = new Node();		
		p->data = q->data;			//copy data of head
		head = tail = p;			
		q = q->next;					//start from beginning and loop through copying data
		while (q)
		{
			p = new Node();
			p->data = q->data;
			tail->next = p;
			p->prev = tail;
			tail = tail->next;
			q = q->next;
		}
		head->prev = nullptr;
		tail->next = nullptr;
	}
}

Sequence& Sequence::operator=(const Sequence& rhs)
{
	if (this != &rhs)						//check for alisasing
	{
		Sequence temp = rhs;
		swap(temp);				//use swap function to swap witha temp object, essentially copying
	}
	return *this;
}

int Sequence::size() const
{
	return m_size;		//return size
}


void Sequence::dump() const
{
	for (Node* p = head; p != nullptr; p = p->next)
	{
		std::cerr << p->data << std::endl;
	}
}

bool Sequence::empty() const
{
	if (head == nullptr && tail == head && m_size == 0)		//return true if head and tail are null and size is 0
	{
		return true;
	}
	return false;
}

bool Sequence::insert(int pos, const ItemType& value)
{

	//INSERT WHEN THE LIST IS EMPTY I.E SIZE = 0

	if (m_size == 0 && head == nullptr && tail == head)
	{
		Node *p = new Node();		
		p->data = value;
		head = p;
		tail = head;
		p->next = nullptr;
		p->prev = nullptr;
		m_size++;
		return true;
	}
	
	//INSERT BEFORE THE HEAD I.E POS = 0;
	
	else if (pos == 0 && m_size != 0)
	{
		Node *p = new Node();
		p->data = value;
		head->prev = p;
		p->next = head;
		head = p;
		head->prev = nullptr;
		m_size++;
		return true;
	}

	//INSERT AFTER THE TAIL I.E POS = SIZE

	else if (pos == m_size && pos != 0)
	{
		Node* p = new Node();
		p->data = value;
		tail->next = p;
		p->prev = tail;
		tail = p;
		p->next = nullptr;
		m_size++;
		return true;
	}

	//DON'T ALLOW INSERTION IF POSITION IS GREATER THAN SIZE
	else if (pos > m_size || pos < 0)
	{
		return false;
	}

	//INSERT IN MIDDLE OF LINKED LIST BEFORE A NODE
	else
	{
		int posTracker = 0;
		Node* replaceNode;
		replaceNode = head;
		while (replaceNode->next != nullptr && posTracker < pos)
		{
			replaceNode = replaceNode->next;
			posTracker++;
		}
		Node* p = new Node();
		p->data = value;
		p->next = replaceNode;
		p->prev = replaceNode->prev;
		replaceNode->prev->next = p;
		replaceNode->prev = p;
		m_size++;
		return true;
	}
}

int Sequence::insert(const ItemType& value)
{
	int posTracker = 0;
	bool posFound = false;
	Node* p;
	for (p = head; p != nullptr; p = p->next)
	{
		if (value <= p->data) //FIND THE POSITION WHERE WE ARE GOING TO INSERT
		{
			posFound = true;
			break;
		}
		posTracker++;
	}
	//Now p will be at the node position we want to insert a value
	if (posFound)
	{
		insert(posTracker, value);		//Use the other insert function to insert at that value
		return posTracker;
	}
	return -1;
}

bool Sequence::erase(int pos)
{
	if (0 <= pos && pos < m_size && m_size != 0) //CHeck that position is valid and that the Sequence is not empty
	{
		//Must check for 4 cases during removal


		//Removal for Node at head of list, but not the only node, i.e  pos == 0 and size > 1
		
		if (pos == 0 && m_size > 1)
		{
			Node* p = head;
			head = head->next;
			delete p;
			head->prev = nullptr;
			m_size--;
			return true;

		}

		//Removal for Node at tail of list, but not only node i.e pos == size - 1 and size > 1
		else if (m_size > 1 && pos == (m_size - 1))
		{
			Node* p = tail;
			tail = tail->prev;
			delete p;
			tail->next = nullptr;
			m_size--;
			return true;
		}

		//Removal for a single Node in a linked list i.e size == 1
		else if (m_size == 1)
		{
			Node* p = head;
			head = tail = nullptr;
			delete p;
			m_size--;
			return true;
		}
		//Removal if the Node is in the middle of the linked list  ---- this might be wrong?? CHECK HERE AGAIN
		else
		{
			Node *p;
			int posTracker = 0;
			for (p = head; p != nullptr; p = p->next) //Here we need to find the node we need to remove
			{
				if (posTracker == pos)
				{
					break;
				}
				posTracker++;
			}
			//Now node P should be at the position we want to erase
			Node * previous = p->prev;
			Node * next = p->next;
			previous->next = next;
			next->prev = previous;
			delete p;
			m_size--;
			return true;

		}
	
	}
	return false;
}

int Sequence::remove(const ItemType& value)
{
	int numRemoved = 0;
	Node *p;
	p = head;
	while (p != nullptr)
	{
		if (m_size == 0)		//cant remove if size is 0
		{
			return 0;
		}
		if (p->data == value)			//check to see if the data matches the value
		{
			if (p == head)					//Removal at the head of linked list
			{				
				Node* temp = p;				
				head = temp->next;			//update the head and reaarange the pointers then delete the temporary pointer
				head->prev = nullptr;
				p = p->next;
				delete temp;
				numRemoved++;			//make sure to increment numRemoved and decrement size every time something is removed
				m_size--;
				
			}
			else if (p != head && p != tail)  //Case for when removal is in the middle
			{
				Node* temp = p;
				p->prev->next = temp->next;  //Concatenate the 2 nodes that are before and after the one we want to remove
				p->next->prev = temp->prev;
				p = p->next;
				delete temp;
				numRemoved++;
				m_size--;
				
			}
			else if (p == tail) // p is equal to the tail and data is equal to value -- this is for at the end
			{
				Node * temp = p;   //similar to head, but update the tail 
				p = p->prev;
				tail = temp->prev;
				tail->next = nullptr;
				delete temp;
				numRemoved++;
				m_size--;
			} 
			else {

			}

		}
		else //Node not equal to value
		{
			p = p->next;
		}
	}

	return numRemoved;
	
}


bool Sequence::get(int pos, ItemType& value) const
{
	int posTracker = 0;							//Track the position in the linked list
	bool positionmatch = false;
	Node *p;
	for (p = head; p != nullptr; p = p->next)			//Loop through the linked list
	{
		if (posTracker == pos)
		{									//Break once we find the value
			positionmatch = true;
			break;
		}
		posTracker++; //Increment position tracker
	}
	if (positionmatch)					//If the position is a match, geet the data at that position
	{
		value = p->data;
		return true;
	}
	return (positionmatch);
}

bool Sequence::set(int pos, const ItemType& value)
{
	Node* p;
	int posTracker = 0;
	if (0 <= pos && pos < m_size)
	{
		for (p = head; p != nullptr; p = p->next) //Loop through linked list and find the position at which we want to set the value
		{
			if (posTracker == pos)  //Here the position is found
			{
				//CHANGE THE VALUE HERE
				p->data = value;
				return true;
			}
			posTracker++;
		}
	}
	return false;

}

int Sequence::find(const ItemType& value) const
{
	int foundPosition = 0;
	bool valueFound = false;
	Node* p;

	for (p = head; p != nullptr ; p = p->next)   //Loop through the linked list and break once the value is found
	{
		if (p->data == value)
		{
			valueFound = true;
			break;
		}
		foundPosition++;
	}
	if (valueFound)				//Return the foundposition once loop is broken
	{
		return foundPosition;
	}
	return -1;
}


void Sequence::swap(Sequence& other)
{
	//Swap Sizes
	int tempSize = other.m_size;
	other.m_size = m_size;
	m_size = tempSize;

	//Swap pointers to the elements
	Node* tempHead = other.head;
	other.head = head;
	head = tempHead;

	Node* tempTail = other.tail;		
	other.tail = tail;
	tail = tempTail;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	ItemType data1;				
	ItemType data2;
	int start;
	bool sequenceChain = false;
	int seq1Traverser;
	for (int i = 0; i < seq1.size(); i++)			//First loop through sequence 1
	{
		seq1.get(i, data1);
		seq2.get(0, data2);
		if (data1 == data2)					//if the data anywhere in sequence1 matches sequence 2 make that a potential candidate for a subsequence start
		{
			start = i;
			sequenceChain = true;
			int j = 1;
			seq1Traverser = start + 1;
			while (j < seq2.size())			//Start looping throug the second sequence comparing values
			{
				seq1.get(seq1Traverser, data1);
				seq2.get(j, data2);
				if (data1 != data2)					//If the subsequence chain is broken, end the loop and try again
				{
					sequenceChain = false;
					break;
				}
				j++;
				seq1Traverser++;		//If it wasn't broken, that means we have found a subsequence
			}
			if (sequenceChain)
			{
				return start;
			}
		}
	}
	return -1;
} 

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	ItemType data1;
	ItemType data2;
	Sequence finalResult;


	if (seq2.empty()) //If one sequence is empty, copy it into the other one
	{
		finalResult = seq1;
	}
	if (seq1.empty())
	{
		finalResult = seq2;
	}
	else
	{
		if (seq1.size() == seq2.size())  //Case where m and n are equal
		{
			int m = seq1.size() - 1;
			for (m; m >= 0; m--)
			{
				seq2.get(m, data2);
				seq1.get(m, data1);
				finalResult.insert(0, data2);
				finalResult.insert(0, data1);
			}
		}
		if (seq1.size() < seq2.size()) // Case in which m is less than n
		{
			int j = 2 * seq1.size();
			for (int i = 0; i < seq2.size(); i++)
			{
				if (i < seq1.size())
				{
					seq1.get(i, data1);
					seq2.get(i, data2);
					finalResult.insert(i + i, data1);//Insert at the end if looping forward
					finalResult.insert(i + i + 1, data2);
				}
				else
				{
					//at this point no more adding in from the smaller sequence. only insert from longer sequence
					seq2.get(i, data2);
					finalResult.insert(j, data2);
					j++;
				}
			}
		}
		if (seq1.size() > seq2.size()) //Case in which n is less than m
		{
			int j = 2 * seq2.size();				//DO same thing as last one but switch sequences
			for (int i = 0; i < seq1.size(); i++)
			{
				if (i < seq2.size())
				{
					seq1.get(i, data1);
					seq2.get(i, data2);
					finalResult.insert(i + i, data1);
					finalResult.insert(i + i + 1, data2);
				}
				else
				{
					seq1.get(i, data1);
					finalResult.insert(j, data1);
					j++;
				}
			}
		}
		result = finalResult;		//Change the value for result;
	}


}


