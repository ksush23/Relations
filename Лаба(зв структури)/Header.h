#pragma once
#include <fstream>
#include <iostream>

using namespace std;


template <typename T> struct Pair
{
	int x, y;
	ostream& operator << (ostream&);
	ofstream& operator << (ofstream&);
	ifstream& operator >> (ifstream&);
	bool operator == (const Pair&);
	T& operator = (const T&);
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
	TRel();
	~TRel();
	TRel(const TRel<T>&);
	TRel<T>& operator = (const TRel<T> &);
	bool add(Pair<T>);
	void del(Pair<T>);
	void set0();
	TRel<T> operator + (const TRel<T>&);
	TRel<T> operator ^ (const TRel<T>&);
	TRel<T> operator ++ (int);
	bool operator == (const TRel<T>&);

	class Iterator
	{
	protected:
		Node * current;
	public:
		explicit Iterator();
		//Iterator(Node* ptr);
		Iterator& operator ++ ();
		Iterator operator ++ (int);
		T operator *();
		bool operator == (const Iterator&) const;
		bool operator != (const Iterator&) const;
		template <class T> Pair operator *();
		operator bool() const;
	};
	Iterator begin() const;
	Iterator end() const;
};

ifstream& operator >> (ifstream&, TRel<int>&);
ostream& operator << (ostream&, const TRel<int>&);
ostream& output(ostream& fout, TRel<int>::Iterator from, TRel<int>::Iterator to);