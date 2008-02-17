using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	/// <summary>
	/// Interface for a machine command
	/// </summary>
	public interface Command
	{
		/// <summary>
		/// Returns a string representing the machine command
		/// </summary>
		String GetCommand();

		/// <summary>
		/// Returns the relevant register that shows if this
		/// command is done.
		/// </summary>
		String GetReadyRegister();

		/// <summary>
		/// Returns a string representing the command (for use in GUI etc)
		/// </summary>
		/// <returns></returns>
		String ToString();

		MachineState GetAfterState(MachineState beforeState);
	}
}
