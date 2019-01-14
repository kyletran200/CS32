#include "ScoreList.h"

ScoreList::ScoreList()
	:m_size(0)
{

}

bool ScoreList::add(unsigned long score)
{
	if (score >= 0 && score <= 100 && m_size < DEFAULT_MAX_ITEMS)
	{
		scores.insert(score);
		m_size++;
		return true;
	}
	return false;
}

bool ScoreList::remove(unsigned long score)
{
	int pos = scores.find(score);
	if (pos == -1)
	{
		return false;
	}
	else
	{
		scores.erase(pos);
		m_size--;
		return true;
	}
}

int ScoreList::size() const
{
	return m_size;
}

unsigned long ScoreList::minimum() const
{
	if (m_size == 0)
	{
		return NO_SCORE;
	}
	unsigned long min = 100;
	for (int i = 0;i < m_size; i++)
	{
		unsigned long x;
		scores.get(i, x);
		if (x < min)
		{
			min = x;
		}
	}
	return min;
}

unsigned long ScoreList::maximum() const
{
	if (m_size == 0)
	{
		return NO_SCORE;
	}
	unsigned long max = 0;
	for (int i = 0; i < m_size; i++)
	{
		unsigned long x;
		scores.get(i, x);
		if (x > max)
		{
			max = x;
		}
	}
	return max;
}
