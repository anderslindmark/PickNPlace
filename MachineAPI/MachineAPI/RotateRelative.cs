using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	/// <summary>
	/// Rotate relative to current rotation
	/// </summary>
	public class RotateRelative : Command
	{
		/// <summary>
		/// Rotate
		/// </summary>
		/// <param name="angle">The angle in degrees</param>
		public RotateRelative(float angle)
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
