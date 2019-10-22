#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

template <class T> struct Pair
{
	T x, y;
};

template <class T> class TRel
{
protected:
	struct Node
	{
		Pair<T> data;
		Node* next;
	};

	Node *first, *last;
public:
	TRel() : first(nullptr), last(nullptr)
	{
	}
	 
	~TRel()
	{
		set0();
	}

	TRel(const TRel<T>& a)
	{
		first = nullptr;
		last = nullptr;
		Node* p = a.first;

		while (p != nullptr)
		{
			add(p->data);
			p = p->next;
		}
	}

	TRel<T>& operator = (const TRel<T>& a)
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

	bool add(Pair<T> a)
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

		if (t != nullptr)
		{
			if (t->next != nullptr && t->next->data.x == ins->data.x && t->next->data.y == ins->data.y)
				return 1;
			ins->next = t->next;
			t->next = ins;
			return 1;
		}
	}

	void del(Pair<T> a)
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

	void set0()
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

	TRel<T> operator + (const TRel<T>& b)
	{
		TRel<T> c;
		c = *this;
		for (auto i = b.begin(); i != b.end(); ++i)
		{
			if (!c.add(*i))
				throw 1;
		}
		return c;
	}

	TRel<T> operator ^ (const TRel<T>& b)
	{
		TRel<T> c;
		Pair<T> x;

		for (auto i = begin(); i != end(); ++i)
		{
			x.x = (*i).x;
			for (auto j = b.begin(); j != b.end(); ++j)
			{
				if ((*i).y == (*j).x)
				{
					x.y = (*j).y;
					c.add(x);
				}
			}
		}
		return c;
	}

	TRel<T> operator ++ (int)
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
			x = (*i);
			if (!c.add(x))
				throw 1;
			x.y = (*i).y;
			if (!c.add(x))
				throw 1;
		}
		return c;
	}

	bool operator == (const TRel<T>& a)
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

	class Iterator
	{
	protected:
		Node* current;
	public:
		explicit Iterator()
		{
			current = nullptr;
		}

		Iterator(Node *c) :current(c) {}

		Iterator& operator ++ ()
		{
			if (current != nullptr)
				current = current->next;
			return *this;
		}

		Iterator operator ++ (int)
		{
			Iterator temp(current);
				if (current != nullptr)
					current = current->next;
			return temp;
		}

		bool operator == (const Iterator& a) const
		{
			return current == a.current;
		}

		bool operator != (const Iterator& a) const
		{
			return current != a.current;
		}

		Pair<T> operator *()
		{
			if (current != nullptr)
				return current->data;
			else
				throw out_of_range("Wrong iterator position");
		}

		operator bool() const
		{
			return current != nullptr;
		}
	};

	Iterator begin() const
	{
		return Iterator(first);
	}

	Iterator end() const
	{
		return Iterator();
	}

};

template <class T> ifstream& operator >> (ifstream&, TRel<T>&);
template <class T> ostream& operator << (ostream&, const TRel<T>&);
template <class T> void input(TRel<T>& a);
template <class T> ifstream& operator >> (ifstream&, Pair<T>&);
template <class T> ostream& operator << (ostream&, const Pair<T>&);
template <class T> ofstream& operator << (ofstream&, const Pair<T>&);
template <class T> bool operator == (const Pair<T>& obj, const Pair<T>& a);
void output(ostream& fout, ofstream& f);
void close(ostream & s);

int main()
{
	TRel<int> a;
	input(a);
	TRel<int> b;
	input(b);

	ofstream fout;
	ofstream f;

	TRel<int> c;

	try { c = (a + b); }
	catch (int)
	{
		cout << "MEMORY ALLOC: IMPOSSIBLE " << endl;
		return 0;
	}

	cout << "Merge of two relations: " << endl;
	output(fout, f);
	fout << c << endl;
	close(fout);
	close(f);

	c = a ^ b;
	cout << "Composition of two relations: " << endl;
	output(fout, f);
	fout << c << endl;
	close(fout);
	close(f);

	try { c = a++; }
	catch (int)
	{
		cout << "MEMORY ALLOC: IMPOSSIBLE " << endl;
		return 0;
	}
	cout << "Transitive reflexsive closure of a relation" << endl;
	output(fout, f);
	fout << c << endl;
	close(fout);
	close(f);

	try { c = b++; }
	catch (int)
	{
		cout << "MEMORY ALLOC: IMPOSSIBLE " << endl;
		return 0;
	}
	cout << "Transitive reflexsive closure of a relation" << endl;
	output(fout, f);
	fout << c << endl;
	close(fout);
	close(f);

	system("pause");

	return 0;
}

template <class T> ifstream& operator >> (ifstream& f, TRel<T>& obj)
{
	T a, c;
	while (f >> a >> c)
	{
		Pair<T> b = { a,c };
		if (!obj.add(b))
			throw 1;
	}
	return f;
}

template <class T> ostream& operator << (ostream& fout, const TRel<T>& obj)
{
	if (cout.rdbuf() == fout.rdbuf())
		cout << "{";

	for (auto i = obj.begin(), j = obj.begin(); i != obj.end(); ++i)
	{
		if (cout.rdbuf() == fout.rdbuf())
		{
			fout << *i;
			if (++j != obj.end())
				fout << ",";
		}
		else
			(ofstream&)fout << *i << ' ';
	}

	if (cout.rdbuf() == fout.rdbuf())
		fout << "}";
	return fout;
}

template <class T> ifstream& operator >> (ifstream& f, Pair<T>& obj)
{
	int X, Y;
	f >> X >> Y;

	obj.x = X;
	obj.y = Y;

	return f;
}

template <class T> ostream& operator << (ostream& s, const Pair<T>& obj)
{
	s << "(" << obj.x << "," << obj.y << ")";
	return s;
}

template <class T> ofstream& operator << (ofstream& f, const Pair<T>& obj)
{
	f << obj.x << ' ' << obj.y << ' ';
	return f;
}

template <class T> bool operator == (const Pair<T>& obj, const Pair<T>& a)
{
	return (obj.x == a.x && obj.y == a.y);
}

template <class T> void input(TRel<T>& a)
{
	string filepath;
	cout << "Enter a filepath you want to have your values from: " << endl;
	getline(cin, filepath);

	ifstream fin;
	fin.open(filepath);
	while (!fin)
	{
		cout << "Enter a filepath you want to have your values from: " << endl;
		getline(cin, filepath);
		fin.open(filepath);
	}
	try { fin >> a; }
	catch (int)
	{
		fin.close();
		cout << "MEMORY ALLOC: IMPOSSIBLE " << endl;
		return;
	}
	fin.close();
}

void output(ostream& fout, ofstream& f)
{
	int option;
	do
	{
		cout << "Enter 1 to have results on screen, 2 to have them in the file" << endl;
		cout << "Enter where you want to have results: " << endl;
		cin >> option;
	} while (option != 1 && option != 2);

	if (option == 2)
	{
		string filepath;
		cout << "Enter a filepath where you want to have your results in: " << endl;
		cin.get();
		getline(cin, filepath);

		f.open(filepath);

		while (!f)
		{
			cout << "Enter a filepath where you want to have your results in: " << endl;
			cin.get();
			getline(cin, filepath);
			f.open(filepath);
		}

		fout.rdbuf(f.rdbuf());
	}
	else
		fout.rdbuf(cout.rdbuf());
}

void close(ostream & s)
{
	if (&s != &cout)
	{
		((ofstream&)s).close();
	}
}