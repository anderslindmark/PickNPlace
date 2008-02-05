using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	public interface Command
	{
		/// <summary>
		/// Returns a string representing the machine command
		/// </summary>
		String getCommand();

		/// <summary>
		/// Returns the relevant register that shows if this
		/// command is done.
		/// </summary>
		string getReadyRegister();

		/// <summary>
		/// Returns a string representing the command (for use in GUI etc)
		/// </summary>
		/// <returns></returns>
		String ToString();
	}
}
