using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	/// <summary>
	/// Move to an absolute position
	/// </summary>
	public class MoveAbsolute : Command
	{
		/// <summary>
		/// Move to an absolute position
		/// </summary>
		/// <param name="axis">Axis to move in</param>
		/// <param name="position">Position as distance in um from origo</param>
		public MoveAbsolute(Axis axis, uint position)
		{
			throw new System.NotImplementedException();
		}

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
