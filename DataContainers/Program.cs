﻿//#define BASE_CHECK
#define HOME_WORK

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace DataContainers
{
	internal class Program
	{
		static void Main(string[] args)
		{
			Random rand = new Random(0);

#if BASE_CHECK
			
			Console.Write($"Введите размер списка: ");
			int n = Convert.ToInt32(Console.ReadLine());

			ForwardList list = new ForwardList();

			for (int i = 0; i < n; i++)
			{
				list.push_front(rand.Next(100));
			}

			list.Print();

			
			//list.pop_front();
			//list.Print();

			//list.pop_back();
			//list.Print();

			//list.Clear();
			//list.Print();

			/*
			Console.Write("Введите индекс добавляемого элемента: ");
			int index = Convert.ToInt32(Console.ReadLine());
			Console.Write("Введите значение добавляемого элемента: ");
			int value = Convert.ToInt32(Console.ReadLine());

			list.insert(value, index);
			list.Print();
			*/

			
			Console.Write("Введите индекс удаляемого элемента: ");
			int index = Convert.ToInt32(Console.ReadLine());
			list.erase(index);
			list.Print();
			
#endif

#if HOME_WORK
			ForwardList new_list = new ForwardList() { 3, 5, 8, 13, 21 };
			new_list.Print();
			
			foreach (int i in new_list)
			{
                Console.Write(i + "\t");
            }
            Console.WriteLine();
#endif


		}
	}
}
