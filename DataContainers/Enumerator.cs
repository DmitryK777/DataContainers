using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataContainers
{
	internal class Enumerator:IEnumerator
	{
		Element Head {  get; set; }
		public Element Temp {  get; set; }

		public Enumerator(Element Head)
		{
			this.Head = Head;
			this.Temp = null;
            Console.WriteLine($"EnumeratorConstructor:\t{GetHashCode()}");
        }

		~Enumerator()
		{
			Console.WriteLine($"EnumeratorDestructor:\t{GetHashCode()}");
		}

		public object Current { get => Temp.Data; }
		public bool MoveNext()
		{
			//if (Temp == null) Temp = Head;
			//else Temp = Temp.pNext;
			Temp = Temp == null ? Head : Temp.pNext;
			return Temp != null;
		}

		public void Reset() { Temp = null; }
	}
}
