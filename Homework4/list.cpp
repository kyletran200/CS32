

void listAll(string path, const File* f)  // two-parameter overload
{
	if (f->files() == nullptr)
	{
		return;
	}
	vector<File*>::const_iterator it;
	it = f->files()->begin();
	while (it != f->files()->end())
	{
		if (path == "")
		{
			path += "/" + f->name();
			cout << path << endl;
		}
		cout << path + "/" + (*it)->name() << endl;
		listAll(path + "/" + (*it)->name(), (*it));
		it++;
	}	
}


