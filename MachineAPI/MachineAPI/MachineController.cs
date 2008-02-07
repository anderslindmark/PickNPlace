using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;
using System.IO.Ports;

namespace MachineController
{
    delegate void MachineControllerEventHandler(MachineController source, MachineEvent e);
    
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
		/// <summary>
		///  The command queue.
		/// </summary>
        CommandQueue commandQueue;

        /// <summary>
        /// The serial port for comunication.
        /// </summary>
		SerialPort port;

        /// <summary>
        /// The name of the serial port, example com1.
        /// </summary>
        String comPort;

        /// <summary>
        /// The thread this object is running in.
        /// </summary>
        Thread myThread;

        /// <summary>
        /// Event listener holder.
        /// </summary>
        public event MachineControllerEventHandler EventListener;

        /// <summary>
        /// Constructor for the MachineController.
        /// </summary>
        /// <param name="comPort">Name of the serial port</param>
        public MachineController(String comPort)
        {
            this.comPort = comPort;
            commandQueue = new CommandQueue();
            Init();
        }

		/// <summary>
		/// Starts the thread
		/// </summary>
		public void Run()
		{
            myThread = new Thread(RunThread);
            myThread.Start();
		}

        /// <summary>
        /// The function that the thread starts
        /// </summary>
        private void RunThread()
        {

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
            commandQueue.Enqueue(cmd);
		}

		/// <summary>
		/// Initiate serial communication
		/// </summary>
		private void Init()
		{
            //CHECK PORT SETTINGS
            port = new SerialPort(sPort, 9800, Parity.Odd, 8, StopBits.None);
		}

		/// <summary>
		/// Check whether a command is legal, or if it would put the machine out of bounds.
		/// </summary>
		/// <returns></returns>
		private MachineState TestCommand(MachineState beforeState, Command cmd)
		{
			throw new System.NotImplementedException();
		}

        /// <summary>
        /// Send a event to all listeners.
        /// </summary>
        /// <param name="e">The event to be sent.</param>
        private void SendEvent(MachineEvent e)
        {
            if (EventListener != null)
            {
                EventListener(this, e);
            }
        }
   	}
}