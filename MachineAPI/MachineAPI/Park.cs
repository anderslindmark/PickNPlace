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

		String Command.GetCommand()
		{
			throw new NotImplementedException();
		}

		String Command.GetReadyRegister()
		{
			throw new NotImplementedException();
		}

		String Command.ToString()
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
