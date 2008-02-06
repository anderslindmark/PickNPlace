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
	/// mc.run();
	/// mc.addCommand(new MoveAbsolute(Axis.X, 100));
	/// mc.startQueue();
	/// </example>
	public class MachineController : Thread
	{
		CommandQueue commandqueue;
		private int port;

		/// <summary>
		/// Starts the thread
		/// </summary>
		public void run()
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Starts working on the queue
		/// </summary>
		public void startQueue()
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Pauses the queue (the current task in the queue is allowed to complete)
		/// </summary>
		public void pauseQueue()
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Forcefully terminates the running task, and pauseQueue the queue.
		/// IS THIS EVEN POSSIBLE?
		/// </summary>
		public void killCommand()
		{
			throw new System.NotImplementedException();
		}
		/// <summary>
		/// Adds a task to the queue.
		/// </summary>
		/// <param name="cmd"></param>
		public bool addCommand(Command cmd)
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Initiate serial communication
		/// </summary>
		private void init()
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Check whether a command is legal, or if it would put the machine out of bounds.
		/// </summary>
		/// <returns></returns>
		private MachineState testCommand(MachineState beforeState, Command cmd)
		{
			throw new System.NotImplementedException();
		}

		/// <summary>
		/// Add a listener to enable communication between the API and whatever is using it.
		/// </summary>
		public void addListener()
		{
			throw new System.NotImplementedException();
		}


	}
}