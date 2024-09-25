#include<iostream>
#include<initializer_list>

using std::cin;
using std::cout;
using std::endl;


#define tab "\t"
#define delimiter "\n-------------------------------------------"

//#define INPUT_LIST
//#define CHECK_ADD_MOVE_METHODS
#define CHECK_FOR
//#define CHECK_CONCAT

template<class T>
class List
{
	
public: 
	template<class T>
	class Element
	{
		T Data;
		Element* pPrev;
		Element* pNext;
		

		// Get Methods:
	public:
		T get_Data()const { return this->Data; }
		Element* get_pPrev()const { return this->pPrev; }
		Element* get_pNext()const { return this->pNext; }

		// Set Methods:
		void set_Data(T Data) { this->Data = Data; }
		void set_pPrev(Element* pPrev) { this->pPrev = pPrev; }
		void set_pNext(Element* pNext) { this->pNext = pNext; }

		// Constructors:
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			
			cout << "ElementConstructor:\t" << this << endl;
		}

		Element(const Element& other)
		{
			this->Data = other.Data;
			this->pPrev = other.pPrev;
			this->pNext = other.pNext;
		}

		Element(Element&& other)
		{
			this->Data = other.Data;
			this->pPrev = other.pPrev;
			this->pNext = other.pNext;

			other.pPrev = nullptr;
			other.pNext = nullptr;
		}

		~Element()
		{
			delete pPrev;
			delete pNext;
			cout << "ElementDestructor:\t" << this << endl;
		}

		// Operators
		Element& operator=(const Element& other)
		{
			if (this == &other) return *this;

			delete this->pPrev;
			delete this->pNext;

			this->Data = other.Data;
			this->pPrev = other.pPrev;
			this->pNext = other.pNext;

			return *this;
		}

		Element& operator=(Element&& other)
		{
			if (this == &other) return *this;

			delete this->pPrev;
			delete this->pNext;

			this->Data = other.Data;
			this->pPrev = other.pPrev;
			this->pNext = other.pNext;

			other.pPrev = nullptr;
			other.pNext = nullptr;

			return *this;
		}

		/*
		Element& operator++()
		{
			return *this->get_pNext();
		}

		Element& operator++(int)
		{
			Element Old = *this;
			*this = *this->get_pNext();
			return Old;
		}
		*/

		// Type-Cast Operators
		operator int()
		{
			return this->Data;
		}

		friend class List;

	} *Head, *Tail; // Объявляем два указателя на объекты класса Element непосредственно после описания класса

	size_t size; // Количество элементов списка

public:
	// Get Methods:
	Element* get_Head() { return this->Head; }
	Element* get_Tail() { return this->Tail; }
	size_t get_size() { return this->size; }

	// Set Methods:
	void set_Head(Element* Head) { this->Head = Head; }
	void set_Tail(Element* Tail) { this->Tail = Tail; }
	void set_size(size_t size) { this->size = size; }

public:
	// Конструктор по умолчанию создаёт пустой список
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "ListConstructor" << this << endl;
	}
	
	List(const List& other)
	{
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
	}

	List(List&& other)
	{
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		other.Head = nullptr;
		other.Tail = nullptr;
	}

	List(std::initializer_list<T> list) 
	{ 
		for (T obj : list)
		{
			this->push_back(obj);
		}
	}
	
	
	~List()
	{
		//delete Head;
		//delete Tail;
		cout << "ListDestructor" << this << endl;
	}

	
	// Overloaded functions of initializer_list
	Element* begin() {
		return this->Head;
	}

	
	Element* end() {
		return this->Tail;
	}

	// Operators
	List& operator=(const List& other)
	{
		if (this == &other) return *this;

		delete this->Head;
		delete this->Tail;

		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		return *this;
	}

	List& operator=(List&& other)
	{
		if (this == &other) return *this;

		delete this->Head;
		delete this->Tail;

		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		other.Head = nullptr;
		other.Tail = nullptr;

		return *this;
	}

	List& operator=(std::initializer_list<T> list)
	{
		this->clear();
		size = 0;
		for (auto i = list.begin(); i != list.end(); i++)
		{
			this->push_back(*i);
			size++;
		}
		return *this;
	}

	// Type-Cast Operators
	operator T*()
	{
		T* array = new T[this->size];
		Element* Temp = this->Head;
		for (int i = 0; i < this->size; i++)
		{
			array[i] = Temp->get_Data();
			Temp = Temp->get_pNext();
		}
		return array;
	}

	// Adding Elements
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr) Head = Tail = new Element(Data);
		else
		{
			// 1) Создаём новый элемент
			Element* New = new Element(Data);

			// 2) Присоединяем элемент к списку
			New->pNext = Head;

			// 3) Присоединяем список к элементу
			Head->pPrev = New;

			// 4) Смещаем голову на новый элемент
			Head = New;
		}
		size++;
	}

	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr) push_front(Data);
		else
		{
			Element* New = new Element(Data);
			Tail->pNext = New;
			New->pPrev = Tail;
			Tail = New;
			size++;
		}
		
	}

	void insert(T Data, int index)
	{
		if (index > size) return;

		if (index == 0) push_front(Data);
		else if (index == size) push_back(Data);
		else
		{
			Element* New = new Element(Data);
			if (index > 0 && index <= (size / 2))
			{
				Element* Temp = Head;
				for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
				New->pPrev = Temp;
				New->pNext = Temp->pNext;
				Temp->pNext->pPrev = New;
				Temp->pNext = New;
			}
			else if (index > (size / 2) && index < size)
			{
				Element* Temp = Tail;
				for (int i = size - 1; i > index + 1; i--) Temp = Temp->pPrev;
				New->pNext = Temp;
				New->pPrev = Temp->pPrev;
				Temp->pPrev->pNext = New;
				Temp->pPrev = New;
			}
			size++;
		}
	}

	// Moving Methods:
	void pop_front()
	{
		Head = Head->pNext;
		Head->pPrev = nullptr;
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr) return;

		if (Head->pNext == nullptr) 
		{ 
			Head = nullptr; 
		}
		else
		{
			Tail = Tail->pPrev;
			Tail->pNext = nullptr;
		}
		size--;
	}

	void erase(int index)
	{
		if (index > size) return;

		if (index == 0) pop_front();
		else if (index == size-1) pop_back();
		else
		{
			if (index > 0 && index <= (size / 2))
			{
				Element* Temp = Head;
				for (int i = 0; i < index - 1; i++) Temp = Temp->pNext;
				Temp->pNext = Temp->pNext->pNext;
				Temp->pNext->pPrev = Temp;
			}
			else if (index > (size / 2) && index < size)
			{
				Element* Temp = Tail;
				for (int i = size - 1; i > index + 1; i--) Temp = Temp->pPrev;
				Temp->pPrev = Temp->pPrev->pPrev;
				Temp->pPrev->pNext = Temp;
			}
			size--;
		}
	}

	void clear()
	{
		if (this->Head == nullptr && this->Tail == nullptr) return;
		else { this->Head = this->Tail = nullptr; }
		this->size = 0;
	}

	// Methods
	/*
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Head:\t" << Head << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	*/

	std::ostream& print(std::ostream& os = std::cout)const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			os << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		os << "Head:\t" << Head << endl;
		os << "Tail:\t" << Tail << endl;
		os << "Количество элементов списка: " << size << endl;

		return os;
	}

	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}

};

// Operators
template<typename T>
List<T> operator+(List<T> left, List<T> right)
{
	List<T> *list = new List<T>();
	
	for (List<T>::Element* Temp = left.get_Head(); Temp; Temp = Temp->get_pNext()) list->push_back(Temp->get_Data());
	for (List<T>::Element* Temp = right.get_Head(); Temp; Temp = Temp->get_pNext()) list->push_back(Temp->get_Data());

	return *list;
}

template<typename T> 
std::ostream& operator<<(std::ostream& os, List<T>::Element &element)
{
	return os << element.get_Data();
}

void main()
{
	setlocale(LC_ALL, "");

#if defined INPUT_LIST
	
	int n;
	cout << "Введите размер списка: "; cin >> n;
	
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand()%100);
	}
	list.print();
	//list.reverse_print();
	
#endif


#if defined CHECK_ADD_MOVE_METHODS
	list.push_back(2);
	list.print();

	list.insert(5, 6);
	list.print();

	list.pop_front();
	list.print();

	list.pop_back();
	list.print();

	list.erase(2);
	list.print();
#endif


#if defined CHECK_FOR
	List<int> list1 = { 3, 5, 8, 13, 21 };
	list1.print();

	for (int i : list1) cout << i << tab;

	cout << endl;
#endif


#if defined CHECK_CONCAT
	List<int> list2 = { 34, 55, 89 };
	list2.print();

	List<int> list3 = list1 + list2;
	list3.print();

	//for (int i : list3) cout << i << tab;

	cout << endl;
#endif

}