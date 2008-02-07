using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;

namespace MachineController
{
	/// <summary>
	/// API for controlling the machine.
	/// </summary>
	/// <example>
	/// MachineController mc = new MachineController();
	/// mc.Run();
	/// mc.AddCommand(new MoveAbsolute(Axis.X, 100));
	/// mc.StartQueue();
	/// </example>
	public class MachineController : Thread
	{
		CommandQueue commandqueue;
		private int port;

		/// <summary>
		/// Starts the thread
		/// </summary>
		public void Run()
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Starts working on the queue
		/// </summary>
		public void StartQueue()
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Pauses the queue (the current task in the queue is allowed to complete)
		/// </summary>
		public void PauseQueue()
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Forcefully terminates the running task, and PauseQueue the queue.
		/// IS THIS EVEN POSSIBLE?
		/// </summary>
		public void KillCommand()
		{
			throw new System.NotImplementedException();
		}
		/// <summary>
		/// Adds a task to the queue.
		/// Throws an exception if the command would lead to an illegal state
		/// </summary>
		/// <param name="cmd"></param>
		public void AddCommand(Command cmd)
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Initiate serial communication
		/// </summary>
		private void Init()
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Check whether a command is legal, or if it would put the machine out of bounds.
		/// </summary>
		/// <returns></returns>
		private MachineState TestCommand(MachineState beforeState, Command cmd)
		{
			throw new System.NotImplementedException();
		}

		// Removed AddListener
		// Use C# event-magic instead
		// http://www.csharphelp.com/archives/archive253.html


	}
}