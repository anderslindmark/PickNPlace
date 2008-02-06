using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	/// <summary>
	/// Moves relative to the current position
	/// </summary>
	public class MoveRelative : Command
	{
		/// <summary>
		/// Move relative to current position
		/// </summary>
		/// <param name="axis">The axis to move in</param>
		/// <param name="distance">The distance to move, specified in um</param>
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
