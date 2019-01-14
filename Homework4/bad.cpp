
void removeBad(list<Movie*>& li)
{ 
	list<Movie*>::iterator it;
	it = li.begin();
	while (it != li.end())
	{
		if ((*it)->rating() < 50)
		{
			Movie* temp = *it;
			it = li.erase(it);
			delete temp;
		}
		else
		{
			it++;
		}
	}
}

