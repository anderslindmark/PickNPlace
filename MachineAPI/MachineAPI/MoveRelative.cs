using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	internal class MoveRelative : Command
	{
		public MoveRelative(Axis axis, int distance)
		{
			throw new System.NotImplementedException();
		}

		#region Command Members

		string Command.getCommand()
		{
			throw new NotImplementedException();
		}

		string Command.getReadyRegister()
		{
			throw new NotImplementedException();
		}

		string Command.ToString()
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
