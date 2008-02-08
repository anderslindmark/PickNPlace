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

		#region Command Members


		public MachineState GetAfterState(MachineState beforeState)
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
