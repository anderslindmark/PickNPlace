using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;
using System.IO.Ports;

namespace MachineController
{
    public delegate void MachineControllerEventHandler(MachineController source, MachineEvent e);
    
    /// <summary>
	/// API for controlling the machine.
	/// </summary>
	/// <example>
	/// MachineController mc = new MachineController();
	/// mc.Run();
	/// mc.AddCommand(new MoveAbsolute(Axis.X, 100));
	/// mc.StartQueue();
	/// </example>
	public class MachineController
	{
		/// <summary>
		///  The command queue.
		/// </summary>
		private CommandQueue commandQueue;

        /// <summary>
        /// The serial port for comunication.
        /// </summary>
		private SerialPort port;

        /// <summary>
        /// The name of the serial port, example com1.
        /// </summary>
		private String comPort;

        /// <summary>
        /// The thread this object is running in.
        /// </summary>
        private Thread myThread;

        /// <summary>
        /// Event listener holder.
        /// </summary>
        public event MachineControllerEventHandler EventListeners;

		/// <summary>
		/// Indicates whether the queue should be paused.
		/// </summary>
		private Boolean workOnQueue;

		/// <summary>
		/// Indicates whether the machine controller should stop.
		/// </summary>
		private Boolean stop;


        /// <summary>
        /// Constructor for the MachineController.
        /// </summary>
        /// <param name="comPort">Name of the serial port</param>
        public MachineController(String comPort)
        {
            this.comPort = comPort;
            commandQueue = new CommandQueue(this);
			myThread = null;
			workOnQueue = false;
			//Init();
			stop = false;
        }

		/// <summary>
		/// Starts the thread.
		/// </summary>
		public void Run()
		{
			if (myThread == null)
			{
				myThread = new Thread(RunThread);
				myThread.Start();
			}
		}

		/// <summary>
		/// Stop the machine controller, this will terminate the 
		/// thread it is running in. If the machine controller
		/// is working on a command it will finish it before stopping.
		/// </summary>
		public void Stop()
		{
			if (Paused)
			{
				lock (this)
				{
					Monitor.Pulse(this);
				}
			}
			else
			{
				lock (commandQueue)
				{
					Monitor.Pulse(commandQueue);
				}
			}
			stop = true;
		}

        /// <summary>
        /// The function that the thread starts.
        /// </summary>
        private void RunThread()
        {
			Command cmd;
			
			while (!Stopped)
			{
				if (Paused)
				{
					lock (this)
					{
						Monitor.Wait(this);
					}
				}
				else
				{
					cmd = commandQueue.Dequeue();

					//Change this to exception instead??
					if (cmd != null)
					{
						doCommand(cmd);
					}
				}
			}

			//DO STOP CODE
			Console.WriteLine("Stopped");
        }

		/// <summary>
		/// Starts working on the queue.
		/// </summary>
		public void StartQueue()
		{
			if (!workOnQueue)
			{
				lock (this)
				{
					workOnQueue = true;
					Monitor.Pulse(this);
				}
			}
		}

		/// <summary>
		/// Pauses the queue, if the controller is working on a task
		/// it is allowed to be completed.
		/// </summary>
		public void PauseQueue()
		{
			if (!Paused)
			{
				lock (commandQueue)
				{
					workOnQueue = false;
					Monitor.Pulse(commandQueue);
				}
			}
		}

		/// <summary>
		/// Clears the objects currently in the command queue.
		/// It does not stop the command that is being processed
		/// if there is one.
		/// </summary>
		public void ClearQueue()
		{
			commandQueue.Clear();
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

		private void doCommand(Command cmd)
		{
			System.Console.WriteLine(cmd.GetCommand());


		}
		/// <summary>
		/// Check whether the queue is paused.
		/// </summary>
		public Boolean Paused
		{
			get { return !workOnQueue; }
		}

		/// <summary>
		/// Check whether the machine controller should stop
		/// running.
		/// </summary>
		public Boolean Stopped
		{
			get { return stop; }
		}
		/// <summary>
		/// Initiate serial communication
		/// </summary>
		private void Init()
		{
            //CHECK PORT SETTINGS
            port = new SerialPort(comPort, 9800, Parity.Odd, 8, StopBits.None);
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
            if (EventListeners != null)
            {
                EventListeners(this, e);
            }
        }
   	}
}