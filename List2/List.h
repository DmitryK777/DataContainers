#pragma once
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------------"
//#define DEBUG


/*
////////////////////////////////////////
// ОБЪЯВЛЕНИЕ КЛАССА (Class Declaration)
///////////////////////////////////////
*/
template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;

	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif
		}

		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif
		}

		friend class List;

	} *Head, * Tail; // Объявляем два указателя на объекты класса Element непосредственно после описания класса

	size_t size; // Количество элементов списка

	class ConstBaseIterator
	{
	protected:
		Element* Temp;

	public:
		ConstBaseIterator(Element* Temp) : Temp(Temp) {}

		~ConstBaseIterator() {}

		bool operator==(const ConstBaseIterator& other)const;

		bool operator !=(const ConstBaseIterator& other)const;

		T operator*()const;
	};

public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp) : ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "IteratorConstructor: \t" << this << endl;
#endif // DEBUG
		}

		~ConstIterator()
		{
#ifdef DEBUG
			cout << "IteratorDestructor: \t" << this << endl;
#endif // DEBUG
		}

		ConstIterator& operator++();

		ConstIterator operator++(int);

		ConstIterator& operator--();

		ConstIterator operator--(int);
	};

	class ConstReversIterator : public ConstBaseIterator
	{
		Element* Temp;

	public:
		ConstReversIterator(Element* Temp) : ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RIConstructor" << endl;
#endif // DEBUG
		}

		~ConstReversIterator()
		{
#ifdef DEBUG
			cout << "RIDestructor" << endl;
#endif // DEBUG
		}

		ConstReversIterator& operator++();
		ConstReversIterator operator++(int);
		ConstReversIterator& operator--();
		ConstReversIterator operator--(int);
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) : ConstIterator(Temp) {}
		~Iterator() {}

		T& operator*();
	};

	class ReversIterator :public ConstIterator
	{
	public:
		ReversIterator(Element* Temp) : ConstIterator(Temp) {}
		~ReversIterator() {}

		T& operator*();
	};

	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();

	ConstReversIterator rbegin()const;
	ConstReversIterator rend()const;
	ReversIterator rbegin();
	ReversIterator rend();


public:
	// Конструктор по умолчанию создаёт пустой список
	List();

	List(const std::initializer_list<T>& il);

	List(const List& other);

	List(const List&& other);

	~List();

	// Operators
	List& operator=(const List& other);

	List& operator=(List&& other);

	// Adding Elements
	void push_front(T Data);

	void push_back(T Data);

	void insert(T Data, int Index);

	// Removing elements
	void pop_front();

	void pop_back();

	// Methods
	void print()const;

	void reverse_print()const;
};
///////////////////////////////////////////////////
// КОНЕЦ ОБЪЯВЛЕНИЯ КЛАССА (Class Declaration END)
///////////////////////////////////////////////////

