using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataContainers
{
	internal class Element<T>
	{
		public T Data { get; set; } // Значение элемента
		public Element<T> pNext { get; set; } // Следующий элемент

		public Element(T data, Element<T> pNext = null)
		{
			this.Data = data;
			this.pNext = pNext;
			Console.WriteLine($"ElementConstructor:\t{GetHashCode()}");
		}
		
		~Element()
		{
			Console.WriteLine($"ElementDestructor:\t{GetHashCode()}");
		}


	}
}
