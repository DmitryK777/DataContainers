#include<iostream>
#include<ctime>
#include <iomanip>
#include <cmath>
using namespace std;

//#define DEBUG
#define tab "\t"
#define delimiter "----------------------------------------------------"
#define PRINT_TREE_ON_THE_SIDE
//#define PRINT_TREE_DIRECTLY
#define BALANCE_METHOD

class Tree
{
protected:
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
#if defined DEBUG
			cout << "ElementConstructor:\t" << this << endl;
#endif
		}

		~Element() 
		{ 
#if defined DEBUG
			cout << "ElementDestructor:\t" << this << endl; 
#endif
		}

		bool isLeaf()const
		{
			return pLeft == pRight;
		}

		friend class Tree;
		friend class UniqueTree;
	} *Root;

public:
	Element* getRoot()const { return Root; }

	Tree()
	{
		Root = nullptr;
#if defined DEBUG
		cout << "TreeConstructor:\t" << this << endl;
#endif
	}

	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it) insert(*it, Root);
	}

	~Tree() 
	{ 
		clear(Root);
		Root = nullptr;
#if defined DEBUG
		cout << "TreeDestructor" << this << endl;
#endif
	}

	// Methods:
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}

	void erase(int Data)
	{
		erase(Data, Root);
	}

	int minValue()const
	{
		return minValue(Root);
	}

	int maxValue()const
	{
		return maxValue(Root);
	}

	int count() const
	{
		return count(Root);
	}

	int sum()const
	{
		return sum(Root);
	}

	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}

	int depth()const
	{
		return depth(Root);
	}

	int height()const
	{
		return height(Root);
	}

	Element* balance()
	{
		return balance(Root);
	}

	void print()const
	{
		print(Root);
		std::cout << endl;
	}

	void printTree()
	{
		printTree(Root);
		std::cout << endl;
	}


private:
	void clear(Element* Root)
	{
		if (Root == nullptr) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}

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

	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->isLeaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	int minValue(Element* Root)const
	{
		if (Root == nullptr) throw exception("Error in MinValue: Tree is empty!");
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}

	int maxValue(Element* Root)const
	{
		if (Root == nullptr) throw std::exception("Error in MaxValue: Tree is empty!");
		return Root->pRight  ? maxValue(Root->pRight) : Root->Data;
	}

	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}

	int sum(Element* Root)const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}

	int depth(Element* Root)const
	{
		int depthLeft = (!Root) ? 0 : depth(Root->pLeft) + 1;
		int depthRight = (!Root) ? 0 : depth(Root->pRight) + 1;
		return (depthLeft >= depthRight) ? depthLeft : depthRight;
	}

	int	height(Element* Root)const
	{
		if (!Root) return 0;
		return 1 + max(height(Root->pLeft), height(Root->pRight));
	}

	void print(const Element* Root)const
	{
		if (Root == nullptr)  return;
		print(Root->pLeft);
		std::cout << Root->Data << tab;
		print(Root->pRight);
	}

#if defined PRINT_TREE_ON_THE_SIDE
	void printTree(Element* Root, int space = 0, int level_spacing = 4)
	{
		if (Root == nullptr) return;

		space += level_spacing;
		printTree(Root->pRight, space);
		cout << endl;
		for (int i = level_spacing; i < space; i++) cout << " ";
		cout << Root->Data << endl;
		printTree(Root->pLeft, space);
	}
#endif


#if defined PRINT_TREE_DIRECTLY
	// Функция для создания отступов
	void printSpaces(int count) 
	{
		for (int i = 0; i < count; ++i) std::cout << " ";
	}

	// Функция для печати узлов на уровне
	void printLevel(Element* Root, int level, int space, int level_spacing) {
		if (Root == nullptr) 
		{
			printSpaces(space);
			std::cout << " "; // пустое место для отсутствующего узла
			return;
		}

		if (level == 1) 
		{
			printSpaces(space);
			std::cout << Root->Data;
		}
		else if (level > 1) 
		{
			printLevel(Root->pLeft, level - 1, space - level_spacing, level_spacing / 2);
			printLevel(Root->pRight, level - 1, space + level_spacing, level_spacing / 2);
		}
	}

	// Функция для печати соединительных линий
	void printConnectors(Element* Root, int level, int space, int level_spacing) 
	{
		if (Root == nullptr || level == 1) return;

		if (level > 1) 
		{
			if (Root->pLeft != nullptr) {
				printSpaces(space - level_spacing);
				std::cout << "/";
			}
			if (Root->pRight != nullptr) {
				printSpaces(2 * level_spacing);
				std::cout << "\\";
			}
			std::cout << endl;
			printConnectors(Root->pLeft, level - 1, space - level_spacing, level_spacing / 2);
			printConnectors(Root->pRight, level - 1, space + level_spacing, level_spacing / 2);
		}
	}

	// Функция для вывода дерева
	void printTree(Element* Root) 
	{
		int treeHeight = height(Root);
		int maxWidth = pow(2, treeHeight) - 1;  // Максимальная ширина последнего уровня

		// Для каждого уровня дерева
		for (int level = 1; level <= treeHeight; ++level) {
			int space = maxWidth / pow(2, level);  // Начальный отступ для текущего уровня
			int level_spacing = maxWidth / pow(2, level - 1);  // Расстояние между узлами

			printLevel(Root, level, space, level_spacing);
			std::cout << endl;
			if (level != treeHeight) {
				printConnectors(Root, level, space, level_spacing);
				std::cout << endl;
			}
		}
	}
#endif


#if defined BALANCE_METHOD
	
	int get_element_by_order(Element* Root)
	{
		if (Root != nullptr)
		{
			get_element_by_order(Root->pLeft);
			return Root->Data;
			get_element_by_order(Root->pRight);
		}
	}

	int* get_ordered_array(Element* Root)
	{
		int size = this->count();
		int* ordered_array = new int[size];
		for (int i = 0; i < size; i++)
			ordered_array[i] = get_element_by_order(Root);
		return ordered_array;
	}

	Element* balance_elements(int* array, int start, int end)
	{
		if (start > end) return nullptr;
		int mid = (start + end) / 2;
		Element* Root = new Element(array[mid]);

		Root->pLeft = balance_elements(array, start, mid - 1);
		Root->pRight = balance_elements(array, mid + 1, end);

		return Root;
	}

	Element* balance(Element* Root)
	{
		int* ordered_array = get_ordered_array(Root);
		int size = sizeof(ordered_array) / sizeof(ordered_array[0]);

		return balance_elements(ordered_array, 0, size - 1);
	}
	
#endif

};

class UniqueTree : public Tree
{

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		if (Data > Root->Data)
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK
//#define PERFECT_CHECK
#define DEGENERATE_TREE

void main()
{
	setlocale(LC_ALL, "");

#if defined BASE_CHECK
	try
	{
		int n;
		cout << "Введите количество элементов: "; cin >> n;

		Tree tree;
		for (int i = 0; i < n; i++) { tree.insert(rand() % 100); }

		tree.print();

		clock_t start, end;

		start = clock(); cout << "Минимальное значение в дереве: " << tree.minValue() << endl; end = clock();
		cout << "Вычислено за " << double(start - end) / CLOCKS_PER_SEC << " секунд" << endl << endl;
				
		start = clock(); cout << "Максимальное значение в дереве: " << tree.maxValue() << endl; end = clock();
		cout << "Вычислено за " << double(start - end) / CLOCKS_PER_SEC << " секунд" << endl << endl;

		start = clock(); cout << "Количество элементов в дереве: " << tree.count() << endl; end = clock();
		cout << "Вычислено за " << double(start - end) / CLOCKS_PER_SEC << " секунд" << endl << endl;

		start = clock(); cout << "Сумма элементов в дереве: " << tree.sum() << endl; end = clock();
		cout << "Вычислено за " << double(start - end) / CLOCKS_PER_SEC << " секунд" << endl << endl;

		start = clock(); cout << "Среднее арифметическое элементов в дереве: " << tree.avg() << endl; end = clock();
		cout << "Вычислено за " << double(start - end) / CLOCKS_PER_SEC << " секунд" << endl << endl;

		start = clock(); cout << "Глубина дерева: " << tree.depth() << endl; end = clock(); end = clock();
		cout << "Вычислено за " << double(start - end) / CLOCKS_PER_SEC << " секунд" << endl << endl;


		tree.printTree();


		/*
		int value;
		cout << "Введите значение удаляемого элемента: "; cin >> value;
		tree.erase(value);
		tree.print();
		cout << "Количество элементов в дереве: " << tree.count() << endl;
		cout << delimiter << endl;
		*/

		/*
		UniqueTree u_tree;
		for (int i = 0; i < n; i++) { u_tree.insert(rand() % 100); }

		u_tree.print();
		cout << endl;

		cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
		cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
		cout << "Количество элементов в дереве: " << u_tree.count() << endl;
		cout << "Сумма элементов в дереве: " << u_tree.sum() << endl;
		cout << "Среднее арифметическое элементов в дереве: " << u_tree.avg() << endl;
		*/
	}
	catch (const std::exception& e )
	{
		std::cerr << e.what() << endl;
	}
#endif


#if defined RERFECT_CHECK
	Tree tree =
	{
						 50,
			25,                      75,
	    16,     32,             64,      85
	};

	tree.print();


	int value;
	cout << "Введите значение удаляемого элемента:"; cin >> value;
	tree.erase(value);
	tree.print();
#endif


#if defined DEGENERATE_TREE
	Tree tree =
	{
		0,
		   5,
		     16,     
			    32,             
				  64,      
				    85
	};

	tree.print();
	tree.printTree();

	tree.balance();

	tree.print();
	tree.printTree();
#endif

}