using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using System.Threading;

namespace MachineController
{
	/// <summary>
	/// The task queue
	/// </summary>
	internal class CommandQueue
	{
		private List<Command> queue;

        public CommandQueue()
        {
            queue = new List<Command>();
        }
		public List<Command> Queue
		{
			get { return queue; }
		}

		public void Enqueue(Command cmd)
		{
            lock (this)
            {
                queue.add(cmd);
                Monitor.pulse(this);
            }
		}

        public Command Dequeue()
        {
            lock (this)
            {
                while (true)
                {
                    if (queue.Count == 0)
                    {
                        Monitor.Wait(this);
                    }
                    else
                    {
                        Command cmd = queue.Item(0);
                        queue.RemoveAt(0);
                        return cmd;
                    }
                }
            }
        }

		public void Clear()
		{
            queue.Clear();
		}
	}
}
