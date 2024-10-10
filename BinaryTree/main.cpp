#include<iostream>
using namespace std;

#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;

	public:
		int getData() { return Data; }

	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) 
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "ElementConstructor:\t" << this << endl;
		}

		/*
		Element(const Element& other)
		{
			this->Data = other.Data;
			this->pLeft = other.pLeft;
			this->pRight = other.pRight;
			cout << "ElementCopyConstructor:\t" << this << endl;
		}

		Element(Element&& other)
		{
			this->pLeft = nullptr;
			this->pRight = nullptr;
			delete this;

			this->Data = other.Data;
			this->pLeft = other.pLeft;
			this->pRight = other.pRight;

			other.pLeft = nullptr;
			other.pRight = nullptr;
			
			cout << "ElementMoveConstructor:\t" << this << endl;
		}
		*/

		~Element() { cout << "ElementDestructor:\t" << this << endl; }

		// Operators
		/*
		Element& operator=(const Element& other)
		{
			this->Data = other.Data;
			this->pLeft = other.pLeft;
			this->pRight = other.pRight;
			cout << "ElementCopyAssignment:\t" << this << endl;
		}
		
		Element& operator=(Element&& other)
		{
			this->pLeft = nullptr;
			this->pRight = nullptr;
			delete this;

			this->Data = other.Data;
			this->pLeft = other.pLeft;
			this->pRight = other.pRight;

			other.pLeft = nullptr;
			other.pRight = nullptr;

			cout << "ElementMoveAssignment:\t" << this << endl;
		}
		*/

		

		friend class Tree;
	} *Root;

	size_t size;

public:
	Element* getRoot()const { return Root; }

	Tree()
	{
		Root = nullptr;
		size = 0;
		cout << "TreeConstructor:\t" << this << endl;
	}

	~Tree() { cout << "TreeDestructor" << this << endl; }

	// Methods:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		size++;
	}

	Element* minValue()
	{
		Element* Temp = this->Root;
		if (Temp == nullptr) return nullptr;
		while(Temp->pLeft != nullptr) Temp = Temp->pLeft;
		return Temp;
	}

	Element* maxValue()
	{
		Element* Temp = this->Root;
		if (Temp == nullptr) return nullptr;
		while (Temp->pRight != nullptr) Temp = Temp->pRight;
		return Temp;
	}

	int count(const Element* Root)
	{
		int leftCount, rightCount;
		if (Root != nullptr)
		{
			leftCount = (Root->pLeft != nullptr) ? count(Root->pLeft) : 0;
			rightCount = (Root->pRight != nullptr) ? count(Root->pRight) : 0;
			return 1 + leftCount + rightCount;
		}
		return 0;
	}

	int sum(const Element* Root)
	{
		int leftSum, rightSum;
		if (Root != nullptr)
		{
			leftSum += (Root->pLeft != nullptr) ? sum(Root->pLeft) : 0;
			rightSum += (Root->pRight != nullptr) ? sum(Root->pRight) : 0;
			return Root->Data + leftSum + rightSum;
		}
		return 0;
	}

	void print(Element* Root)const
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

int static operator+(const std::Tree::Element& left, const Element& right)const
{
	return left.Data + right.Data;
}

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите количество элементов: "; cin >> n;

	Tree tree;
	for (int i = 0; i < n; i++) {tree.insert( rand()%100, tree.getRoot() );}

	tree.print(tree.getRoot());
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue()->getData() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue()->getData() << endl;
	cout << "Количество элементов в дереве: " << tree.count(tree.getRoot()) << endl;
	cout << "Сумма элементов в дереве: " << tree.count(tree.getRoot()) << endl;

}