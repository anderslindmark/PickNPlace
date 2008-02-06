using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	/// <summary>
	/// Parks the machine, returning home.
	/// </summary>
	public class Park : Command
	{
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
