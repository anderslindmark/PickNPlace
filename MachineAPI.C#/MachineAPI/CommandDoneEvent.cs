using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	public class CommandDoneEvent : MachineEvent
	{
		private Command cmd;

		public CommandDoneEvent(Command cmd)
		{
			this.cmd = cmd;
		}

		#region MachineEvent Members

		public override string ToString()
		{
			return "Done with Command: " + cmd.ToString();
		}

		#endregion
	}
}
