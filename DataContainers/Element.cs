using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataContainers
{
	internal class Element
	{
		public int Data { get; set; } // Значение элемента
		public Element pNext { get; set; } // Следующий элемент

		public Element(int data, Element pNext = null)
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
