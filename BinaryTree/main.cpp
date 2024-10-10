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

		~Element() { cout << "ElementDestructor:\t" << this << endl; }

		// Operators

		/*
		int operator+(const Element& other)const
		{
			return this->Data + other.Data;
		}
		*/

		friend class Tree;
	} *Root;

public:
	Element* getRoot()const { return Root; }

	Tree()
	{
		Root = nullptr;
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
	}

	Element* minValue()const
	{
		Element* Temp = this->Root;
		if (Temp == nullptr) return nullptr;
		while(Temp->pLeft != nullptr) Temp = Temp->pLeft;
		return Temp;
	}

	Element* maxValue()const
	{
		Element* Temp = this->Root;
		if (Temp == nullptr) return nullptr;
		while (Temp->pRight != nullptr) Temp = Temp->pRight;
		return Temp;
	}

	int count(const Element* Root)const
	{
		int leftCount, rightCount;
		if (Root != nullptr)
		{
			leftCount = (Root->pLeft != nullptr) ? count(Root->pLeft) : 0;
			rightCount = (Root->pRight != nullptr) ? count(Root->pRight) : 0;
			return 1 + leftCount + rightCount;
		}
		else return 0;
	}

	int sum(const Element* Root)const
	{
		int leftSum, rightSum;
		if (Root != nullptr)
		{
			leftSum = (Root->pLeft != nullptr) ? sum(Root->pLeft) : 0;
			rightSum = (Root->pRight != nullptr) ? sum(Root->pRight) : 0;
			return Root->Data + leftSum + rightSum;
		}
		return 0;
	}

	double avg(const Element* Root)const
	{
		return ((double)sum(Root) / count(Root));
	}

	void clear(Element* Root)
	{
		if (Root != nullptr)
		{
			if (Root->pLeft != nullptr) clear(Root->pLeft);
			if (Root->pRight != nullptr) clear(Root->pRight);
			this->Root = nullptr;
		}
		else
		{
			cout << "Дерево уже и так пустое!" << endl;
			return;
		}
	}

	Element* erase(int Data, Element* Root)
	{
		if (this->Root == nullptr) return nullptr;
		if (Root == nullptr) return Root;
		if (Data == Root->Data)
		{
			Element* Temp;
			if (Root->pRight == nullptr) Temp = Root->pLeft;
			else
			{
				Element* element = Root->pRight;
				if (element->pLeft == nullptr)
				{
					element->pLeft = Root->pLeft;
					Temp = element;
				}
				else
				{
					Element* elementMin = element->pLeft;
					while (elementMin->pLeft != nullptr)
					{
						element = elementMin;
						elementMin = element->pLeft;
					}
					element->pLeft = elementMin->pRight;
					elementMin->pLeft = Root->pLeft;
					elementMin->pRight = Root->pRight;
					Temp = elementMin;
				}
			}
			Root = nullptr;
			return Temp;
		}
		else if (Data < Root->Data)
		{
			Root->pLeft = erase(Data, Root->pLeft);
		}
		else Root->pRight = erase(Data, Root->pRight);

		return Root;
	}

	int depth(const Element* Root)const
	{
		int leftDepth, rightDepth;
		if (Root != nullptr)
		{
			leftDepth = (Root->pLeft != nullptr) ? depth(Root->pLeft) : 0;
			rightDepth = (Root->pRight != nullptr) ? depth(Root->pRight) : 0;
			return (leftDepth >= rightDepth) ? (1 + leftDepth) : (1 + rightDepth) ;
		}
		else return 0;
	}

	void print(const Element* Root)const
	{
		if (Root == nullptr)  return; 
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

	
	void printTree(Element* Root, int count)
	{
		if (Root == nullptr)  return;
		
		printTree(Root->pRight, count + 1);
		
		for (int i = 0; i < count; i++) cout << " ";
		cout << Root->Data << endl;
		
		printTree(Root->pLeft, count + 1);
	}
};



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
	cout << "Сумма элементов в дереве: " << tree.sum(tree.getRoot()) << endl;
	cout << "Среднее арифметическое элементов в дереве: " << tree.avg(tree.getRoot()) << endl;
	cout << "Глубина дерева: " << tree.depth(tree.getRoot()) << endl;
	//cout << "Вывод дерева как дерева: " << endl;
	//tree.printTree(tree.getRoot(), tree.count(tree.getRoot()));


	tree.erase(0, tree.getRoot());
	cout << "Дерево после удаления узла '0':" << endl;
	tree.print(tree.getRoot());
	cout << endl;

	
	tree.clear(tree.getRoot());
	cout << "Дерево после очистки:" << endl;
	tree.print(tree.getRoot());
	
}