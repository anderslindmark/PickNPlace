using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	public class MachineControllerStoppedEvent : MachineEvent
	{

		#region MachineEvent Members

		public override string ToString()
		{
			return "Machine controller stopped";
		}

		#endregion
	}
}
