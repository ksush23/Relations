#include "Header.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

template <class T> TRel<T>::TRel() : first(nullptr), last(nullptr)
{
}

template<class T> TRel<T>::~TRel()
{
	set0();
}

template <class T> TRel<T>::TRel(const TRel<T>& a)
{
	first = nullptr;
	last = nullptr;
	Node* p = a.first;

	for(auto i = first(); i != end(); ++i)
	{
		add(p->data);
		p = p->next;
	}
}

template <class T> bool TRel<T>::add(Pair<T> a)
{
	Node* ins = new (nothrow) Node;
	if (ins == nullptr)
		return 0;
	ins->data = a;

	if (first == nullptr)
	{
		ins->next = nullptr;
		first = ins;
		last = ins;
		return 1;
	}

	Node* t = first;


	if (t->data.x > ins->data.x || (t->data.x == ins->data.x && t->data.y > ins->data.y))
	{
		ins->next = t;
		first = ins;
		return 1;
	}

	if (ins->data.x > last->data.x || (ins->data.x == last->data.x && ins->data.y > last->data.y))
	{
		last->next = ins;
		ins->next = nullptr;
		last = ins;
		return 1;
	}

	if (t->data == ins->data)
		return 1;

	while ((t != nullptr && ins->data.x > t->data.x) && (t->next->data.x < ins->data.x) || (t->next != nullptr && (ins->data.x == t->next->data.x && ins->data.y > t->next->data.y)))
		t = t->next;

	if (t->data == ins->data)
		return 1;

	if(t != nullptr)
	{
		if (t->next != nullptr && t->next->data.x == ins->data.x && t->next->data.y == ins->data.y)
			return 1;
		ins->next = t->next;
		t->next = ins;
		return 1;
	}
}

template <class T> void TRel<T>::del(Pair<T> a)
{
	Node* t = first;

	if (t == nullptr)
		return;

	if (t->data.x == a.x && t->data.y == a.y)
	{
		first = t->next;
		delete t;
		return;
	}

	Node* t1 = t->next;
	while (t1->next != nullptr)
	{
		if (t1->data.x == a.x && t1->data.y == a.y)
		{
			t->next = t1->next;
			delete t1;
			return;
		}
		t = t1;
		t1 = t1->next;
	}

	if (t1->data == a)
	{
		t->next = t1->next;
		last = t;
		delete t1;
		return;
	}
}

template <class T> TRel<T> TRel<T>::operator + (const TRel<T>& b)
{
	TRel<T> c = *this;
	for (auto i = b.begin(); i != b.end(); ++i)
	while (head != nullptr)
	{
		if (!c.add(*i))
			throw 1;
	}
	return c;
}

template <class T> TRel<T> TRel<T>::operator ^ (const TRel<T>& b)
{
	TRel<T> c;
	Pair<T> x;

	for (auto i = begin(); i != end(); ++i)
	{
		x.x = t1->data.x;
		for (auto i = b.begin(); i != b.end(); ++i)
		{
			if (t1->data.y == t2->data.x)
			{
				x.y = t2->data.y;
				c.add(x);
			}
		}
	}
	return c;
}

template <class T> bool TRel<T>::operator == (const TRel<T>& a)
{
	Node* t1 = first;
	Node* t2 = a.first;
	while (t1 != nullptr && t2 != nullptr)
	{
		if (t1->data.x != t2->data.x || t1->data.y != t2->data.y)
			return 0;
		t1 = t1->next;
		t2 = t2->next;
	}
	if (t1 != nullptr || t2 != nullptr)
		return 0;
	return 1;
}

template <class T> TRel<T> TRel<T>::operator ++ (int)
{
	TRel<T> c;
	c = *this;
	TRel<T> b;
	b = *this;
	c = c + (c ^ *this);
	while (!(b == c))
	{
		b = c;
		c = c + (c ^ *this);
	}
	Pair<T> x;
	for (auto i = begin(); i != end(); ++i)
	{
		x = *i;
		if (!c.add(x))
			throw 1;
		x.y = (*i).y;
		if (!c.add(x))
			throw 1;
	}
	return c;
}

template <class T> TRel<T>& TRel<T>::operator = (const TRel<T> &a)
{
	if (this == &a)
		return *this;

	set0();

	Node* t = a.first;

	while (t != nullptr)
	{
		add(t->data);
		t = t->next;
	}
	return *this;
}

template <class T> void TRel<T>::set0()
{
	Node* t = first;
	Node* t1 = nullptr;

	while (t != nullptr)
	{
		t1 = t;
		t = t->next;
		delete t1;
	}
	first = nullptr;
	last = nullptr;
}

ostream& output(ostream& fout, TRel<int>::Iterator from, TRel<int>::Iterator to)
{
	if (&fout == &cout)
		fout << "{";

	for (auto i = from; i != to; ++i)
	{
		if (&fout == &cout)
		{
			fout << *i;
			fout << ",";
		}
		else
			(ofstream&)fout << *i << ' ';
	}

	if (&fout == &cout)
		fout << "}";
	return fout;
}




template <class T> TRel<T>::Iterator::Iterator()
{
	Node *current = nullptr;
}

template <class T> Iterator& TRel<T>::Iterator::operator ++ ()
{
	if (current != nullptr)
		current = current->next;
	return *this;
}

template <class T> Iterator TRel<T>::Iterator::operator ++ (int)
{
	Iterator temp(current)
		if (current != nullptr)
			current = current->next;
	return temp;
}

/*template<class T>  TRel<T>::Iterator::Iterator(Node * ptr) : Node * ptr : current(ptr)
{
}*/

template <class T> T TRel<T>::Iterator::operator *()
{
	if (current != nullptr)
		return current->next;
	else
		throw out_of_range ("Wrong iterator position");
}

template <class T> bool TRel<T>::Iterator::operator == (const Iterator& a) const
{
	return current == a.current;
}

template <class T>bool TRel<T>::Iterator::operator != (const Iterator& a) const
{
	return current != a.current;
}

template <class T> TRel<T>::Iterator::operator bool() const
{
	return current != nullptr;
}

template <class T> Iterator TRel<T> ::begin() const
{
	return Iterator(first);
}

template <class T> Iterator TRel<T>::end() const
{
	return Iterator(last);
}



template <typename T> ostream& Pair<T>::operator << (ostream& s)
{
	s << "(" << x << "," << y << ")";
	return s;
}

template <typename T> ofstream& Pair<T>::operator << (ofstream& f)
{
	f << x << ' ' << y << ' ';
	return f;
}

template <typename T> ifstream& Pair<T>::operator >> (ifstream& f)
{
	int X, Y;
	f >> X >> Y;

	X = x;
	Y = y;

	return f;
}

template <typename T> bool Pair<T>::operator == (const Pair& a)
{
	return (x == a.x && y == a.y);
}

template <typename T> T& Pair<T>::operator = (const T &)
{
	x = a.x;
	y = a.y;
	return *this;
}



ifstream& operator >> (ifstream& f, TRel<int>& obj)
{
//	Pair <int> b;
	int a, c;
	while (f >> a >> c)
	{
		Pair<int> b = { a,c };
		if (!obj.add(b))
			throw 1;
	}
	return f;
}

/*ostream& operator << (ostream& f, const TRel<int>& obj)
{
	return output(f, obj.begin(), obj.end());
}*/

ostream& operator << (ostream& f, const TRel<int>& obj)
{
	cout << "ahhahaa" << endl;
	return f;
}