

class Concern
{
public:
	Concern(string person);
	virtual ~Concern();
	virtual bool possibleFelony() const;
	virtual string description() const = 0;
	string person() const;
private:
	string m_person;
};

Concern::Concern(string person)
	:m_person(person)
{

}

string Concern::person() const
{
	return m_person;
}

bool Concern::possibleFelony() const
{
	return false;
}

Concern::~Concern()
{

}

class EthicsMatter : public Concern
{
public:
	EthicsMatter(string person);
	virtual string description() const;
	virtual ~EthicsMatter();
};

EthicsMatter::EthicsMatter(string person)
	:Concern(person)
{

}
string EthicsMatter::description()  const
{
	return "An ethics matter";
} 

EthicsMatter::~EthicsMatter()
{
	cout << "Destroying " << this->person() << "'s ethics matter" << endl;
}

class Investigation : public Concern
{
public:
	Investigation(string person);
	virtual string description() const;
	virtual bool possibleFelony() const;
	virtual ~Investigation();
};

Investigation::Investigation(string person)
	:Concern(person)
{

}

string Investigation::description() const
{
	return "An investigation";
}

bool Investigation::possibleFelony() const
{
	return true;
}

Investigation::~Investigation()
{
	cout << "Destroying " << this->person() << "'s investigation" << endl;
}

class HushPayment : public Concern
{
public:
	HushPayment(string person, int payment);
	virtual string description() const;
	virtual ~HushPayment();
private:
	int m_payment;
};

HushPayment::HushPayment(string person, int payment)
	:Concern(person), m_payment(payment)
{

}


string HushPayment::description() const
{
	return ("A $" + to_string(m_payment) + " payment");
}

HushPayment::~HushPayment()
{
	cout << "Destroying " << this->person() << "'s hush payment" << endl;
}


