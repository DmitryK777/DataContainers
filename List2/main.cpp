#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------------"
//#define DEBUG

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

	} *Head, *Tail; // Объявляем два указателя на объекты класса Element непосредственно после описания класса

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


//////////////////////////////////////////////
// Element:


// Element
//////////////////////////////////////////////

///----------------------------------------------------------------------------------------


//////////////////////////////////////////////
// Iterators:
template<typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}

template<typename T> bool List<T>::ConstBaseIterator::operator !=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T> T List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}
/////////////////////////////////
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++() // Prefix increment
{
	this->Temp = this->Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) // Postfix increment
{
	ConstIterator old = this->Temp;
	this->Temp = this->Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--() // Prefix increment
{
	this->Temp = this->Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int) // Postfix increment
{
	ConstIterator old = this->Temp;
	this->Temp = this->Temp->pPrev;
	return old;
}
/////////////////////////////////
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator++()
{
	this->Temp = this->Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::ConstReversIterator::operator++(int)
{
	ConstReversIterator old = *this;
	this->Temp = this->Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReversIterator& List<T>::ConstReversIterator::operator--()
{
	this->Temp = this->Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReversIterator List<T>::ConstReversIterator::operator--(int)
{
	ConstReversIterator old = *this;
	this->Temp = this->Temp->pNext;
	return old;
}
/////////////////////////////////
template<typename T>T& List<T>::Iterator::operator*()
{
	return this->Temp->Data;
}

template<typename T>T& List<T>::ReversIterator::operator*()
{
	return this->Temp->Data;
}
// Iterators
//////////////////////////////////////////////

///-----------------------------------------------------------------------------------------

//////////////////////////////////////////////
// List members:


template<typename T> typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T> typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T> typename List<T>::ConstReversIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T> typename List<T>::ConstReversIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T> typename List<T>::ReversIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T> typename List<T>::ReversIterator List<T>::rend()
{
	return nullptr;
}


// Конструктор по умолчанию создаёт пустой список
template<typename T > List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor" << this << endl;
}

template<typename T > List<T>::List(const std::initializer_list<T>& il) :List()
{
	//cout << typeid(il.begin()) << endl;
	for (int const* it = il.begin(); it != il.end(); it++) push_back(*it);
}

template<typename T > List<T>::List(const List& other) : List() // Без делегирования может падать программа
{
	*this = other;
	cout << "ListCopyConstructor" << this << endl;
}

template<typename T > List<T>::List(const List&& other) : List() // Без делегирования может падать программа
{
	*this = std::move(other); // явный вызов MoveAssignment
	cout << "ListAssignmentConstructor" << this << endl;
}

template<typename T > List<T>::~List()
{
	//while (Head) pop_front();
	while (Head) pop_back();
	cout << "LDestructor" << this << endl;
}

// Operators
template<typename T > List<T>& List<T>::operator=(const List& other)
{
	if (this == &other) return *this;

	while (Head) pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
	cout << "ListCopyAssignment" << this << endl;
	return *this;
}

template<typename T > List<T>& List<T>::operator=(List&& other)
{
	if (this == &other) return *this;
	while (Head) pop_front();

	this->Head = other.Head;
	this->Tail = other.Tail;
	this->size = other.size;

	other.Head = other.Tail = nullptr;
	other.size = 0;

	cout << "ListMoveAssignment:\t" << this << endl;
}

// Adding Elements
template<typename T> void  List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
	else
	{
		/*
		// 1) Создаём новый элемент
		Element* New = new Element(Data);
		// 2) Присоединяем элемент к списку
		New->pNext = Head;
		// 3) Присоединяем список к элементу
		Head->pPrev = New;
		// 4) Смещаем голову на новый элемент
		Head = New;
		*/

		Head = Head->pPrev = new Element(Data);
	}
	size++;
}

template<typename T >void  List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr) return push_front(Data);
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}

template<typename T> void  List<T>::insert(T Data, int Index)
{
	if (Index == 0) return push_front(Data);
	if (Index == size - 1) return push_back(Data);
	if (Index >= size) throw std::exception("Insert: Out of range exception");

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
	}
	Temp->pNext->pPrev = Temp->pPrev->pNext = new Element(Data, Temp->pNext, Temp->pPrev);
	size++;
}

// Removing elements
template<typename T> void List<T>::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size = 0;;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}

template<typename T> void List<T>::pop_back()
{
	if (Head == Tail) return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

// Methods
template<typename T> void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

	cout << "Tail:\t" << Tail << endl;
	cout << "Количество элементов списка: " << size << endl;
}

template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail:\t" << Tail << endl;
	cout << "Количество элементов списка: " << size << endl;
}

// List members
//////////////////////////////////////////////




template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer;
	for (typename List<T>::ConstIterator it = left.begin(); it != left.end(); ++it) buffer.push_back(*it);
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}


//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#if defined BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand()%100);
	}

	list.print();
	list.reverse_print();

	/*
	for (int i = 0; i < n*2; i++) list.pop_back();
	list.print();
	list.reverse_print();
	*/
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	try
	{
		list.insert(value, index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
#endif

#if defined ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReversIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif


	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;

	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;


	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 10;
	}

	for (int i : list1) cout << i << tab; cout << endl;

}