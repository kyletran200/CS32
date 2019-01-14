#include "Sequence.h"
#include <iostream>


Sequence::Sequence()
	:m_size(0)
{

}

bool Sequence::empty() const
{
	if (m_size == 0)
	{
		return true;
	}
	return false;
}

int Sequence::size() const
{
	return m_size;
}

bool Sequence::insert(int pos, const ItemType& value)
{
	if (pos >= 0 && pos <= m_size && pos < DEFAULT_MAX_ITEMS)
	{
		for (int i = m_size; i > pos; i--)
		{
			sequence[i] = sequence[i - 1];
		}
		sequence[pos] = value;
		m_size++;
		return true;
	}
	return false;
}
int Sequence::insert(const ItemType& value)
{
	int p = m_size;
	for (int i = 0; i < m_size; i++)
	{
		if (value <= sequence[i])
		{
			p = i;
			break;
		}
	}
	if (m_size == DEFAULT_MAX_ITEMS)
	{
		return -1;
	}
	for (int j = m_size; j > p; j--)
	{
		sequence[j] = sequence[j - 1];
	}
	sequence[p] = value;
	m_size++;
	return p;
}

bool Sequence::erase(int pos)
{
	if (0 <= pos && pos < m_size)
	{
		while (pos < m_size - 1)
		{
			sequence[pos] = sequence[pos + 1];
			pos++;
		}
		m_size--;
		return true;
	}
	return false;
} 

int Sequence::remove(const ItemType& value)   
{
	int removeCount = 0;
	for (int i = m_size - 1; i >= 0; i--)
	{
		if (sequence[i] == value)
		{
			int pos = i;
			while (pos < m_size - 1)
			{
				sequence[pos] = sequence[pos + 1];
				pos++;
			}
			removeCount++;
			m_size--;
		}
	}
	return removeCount++;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= 0 && pos < m_size)
	{
		value = sequence[pos];
		return true;
	}
	return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (0 <= pos && pos < m_size)
	{
		sequence[pos] = value;
		return true;
	}
	return false;
}

int Sequence::find(const ItemType& value) const
{
	int found = -1;
	for (int p = 0; p < m_size; p++)
	{
		if (sequence[p] == value)
		{
			found = p;
			break;
		}
	}
	return found;
}

void Sequence::swap(Sequence& other)
{
	if (this != &other)
	{
		ItemType temp[DEFAULT_MAX_ITEMS];
		int largest_size;
		if (m_size > other.m_size)
		{
			largest_size = m_size;
		}
		else
		{
			largest_size = other.m_size;
		}
		int temp_size = other.m_size;
		other.m_size = m_size;
		m_size = temp_size;
		for (int i = 0; i < largest_size; i++)
		{
			temp[i] = other.sequence[i];
			other.sequence[i] = sequence[i];
			sequence[i] = temp[i];
		}
	}
}


