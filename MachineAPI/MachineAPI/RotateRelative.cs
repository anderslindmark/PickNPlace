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
