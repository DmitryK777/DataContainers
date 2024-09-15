using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataContainers
{
	internal class ForwardList
	{
		Element Head;
		public uint Size { get; private set; }

		public ForwardList()
		{
			Head = null;
			Size = 0;
			Console.WriteLine($"ForwardListConstructor:\t {GetHashCode()}");
		}

		~ForwardList()
		{
			Console.WriteLine($"ForwardListDestructor:\t {GetHashCode()}");
		}

		public void Clear()
		{
			//while (Head != null) pop_front();
			Head = null;
		}

		// Adding Elements
		public void push_front(int Data)
		{
			// 1) создаём новый элемент
			Element New = new Element(Data);

			// 2) Подключаем новый элемент к списку
			New.pNext = Head;

			// 3) Смещаем голову на новый элемент
			Head = New;
			Size++;
		}

		public void push_back(int Data)
		{
			if (Head == null) { push_front(Data); }
			else
			{
				Element Temp = Head;
				while (Temp.pNext != null)
				{
					Temp = Temp.pNext;
				}
				Element New = new Element(Data);
				Temp.pNext = New;
			}
			Size++;
		}

		// Removing Elements
		public void pop_front()
		{
			Head = Head.pNext;
			Size--;
		}

		public void pop_back()
		{
			if (Head == null) { return; }
			else if (Head.pNext == null) { Head = null; }
			else
			{
				Element Temp = Head;
				while (Temp.pNext.pNext != null)
				{
					Temp = Temp.pNext;
				}

				Temp.pNext = null;
			}
			Size--;
		}

		public void insert(int Data, int index)
		{
			if (index > Size) return;

			Element Temp = Head;
			if (index == 0) push_front(Data);
			else
			{
				for (int i = 0; i < index - 1; i++) Temp = Temp.pNext;

				Element New = new Element(Data);
				New.pNext = Temp.pNext;
				Temp.pNext = New;
				Size++;
			}
		}

		// Methods
		public void Print()
		{
			Element Temp = Head; // Temp - это итератор (указатель при помощи которого можно получить доступ к элементам структуры данных)

			while (Temp != null)
			{
				Console.Write($"{Temp.Data}\t");
				Temp = Temp.pNext; // Переход на следующий элемент

			}
			Console.WriteLine();
		}
	}
}
