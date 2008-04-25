/**
 	\file MachineLightBrightnessCommand.h
 
 	\brief
 	Header file for the MachineLightBrightnessCommand class
 

 	\author	Henrik Mäkitaavola & Anders Lindmark
**/


#ifndef __MachineLightBrightnessCommand_H__
#define __MachineLightBrightnessCommand_H__

#include "MachineCommand.h"
#include "MachineState.h"

enum Lamp
{
	LAMP_CAMERA,
	LAMP_LOOKUP
};

/// \class MachineLightBrightnessCommand
/// \brief Control the lightlevel of the lamps.
class MachineLightBrightnessCommand : public MachineCommand
{
	MACHINE_COMMAND_FRIENDS;
public:
	/// \brief Create a new MachineLightBrightnessCommand command
	///
	/// \param lamp Which lamp to set the brightness of
	/// \param brightness The brightness of the lamp [0..15]
	MachineLightBrightnessCommand(Lamp lamp, int brightness); // 0..15
	~MachineLightBrightnessCommand(void);
	string ToString();
	MachineState GetAfterState(MachineState &oldms);
	bool IsValid()
	{
		return true;
	}

private:
	bool DoCommand(SerialPort &sp);
	MachineLightBrightnessCommand* Copy();

	Lamp m_lamp;
	int m_brightness;
};

#endif // __MachineLightBrightnessCommand_H__
