using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace MachineController
{
	/// <summary>
	/// Usage: MachineController mc = new MachineController()
	/// mc.add(new MoveAbsolute(Axis.X, 100));
	/// mc.start()
	/// </summary>
	public class MachineController
	{
		CommandQueue commandqueue;
		private int port;
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
		}

		public void Method()
		{
			throw new System.NotImplementedException();
		}

		public void start()
		{
			throw new System.NotImplementedException();
		}

		public void pause()
		{
			throw new System.NotImplementedException();
		}

		public void add(Command cmd)
		{
			throw new System.NotImplementedException();
		}
	}
}