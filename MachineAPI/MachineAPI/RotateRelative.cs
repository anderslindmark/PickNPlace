using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	public class RotateRelative : Command
	{
		public RotateRelative(int angle)
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
