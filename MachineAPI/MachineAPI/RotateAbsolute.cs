using System;
using System.Collections.Generic;
using System.Text;

namespace MachineController
{
	/// <summary>
	/// Rotate to an absolute angle
	/// </summary>
	public class RotateAbsolute : Command
	{
		/// <summary>
		/// Rotate 
		/// </summary>
		/// <param name="angle">The angle in degrees</param>
		public RotateAbsolute(float angle)
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
