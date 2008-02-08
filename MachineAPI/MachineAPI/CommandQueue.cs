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
		private MachineController mc;

        public CommandQueue(MachineController mc)
        {
			this.mc = mc;
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
                queue.Add(cmd);
				Monitor.Pulse(this);
            }
		}

        public Command Dequeue()
        {
            lock (this)
            {
                while (true)
                {
					if (mc.Paused || mc.Stopped)
					{
						return null;
					}
					else if (queue.Count == 0)
                    {
                        Monitor.Wait(this);
                    }
                    else
                    {
                        Command cmd = queue[0];
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
