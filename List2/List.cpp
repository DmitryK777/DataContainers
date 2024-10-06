#include"List.h"

///////////////////////////////////////////////////
// ОПРЕДЕЛЕНИЕ КЛАССА (Class Defenition)
///////////////////////////////////////////////////
///----------------------------------------------------------------------------------------

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

///////////////////////////////////////////////////
// КОНЕЦ ОПРЕДЕЛЕНИЯ КЛАССА (Class Defenition END)
///////////////////////////////////////////////////


