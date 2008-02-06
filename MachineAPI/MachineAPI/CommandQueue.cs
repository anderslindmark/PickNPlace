using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace MachineController
{
	/// <summary>
	/// The task queue
	/// </summary>
	internal class CommandQueue
	{
		private List<Command> queue;

		public List<Command> Queue
		{
			get { return queue; }
		}

		public void enqueue(Command cmd)
		{
			throw new System.NotImplementedException();
		}

		public Command dequeue()
		{
			throw new System.NotImplementedException();
		}

		public void clear()
		{
			throw new System.NotImplementedException();
		}
	}
}
