#ifndef __PICKANDPLACECOMMAND_H__
#define __PICKANDPLACECOMMAND_H__

#include "Coordinate.h"
#include "MachineCommands.h"
#include "GuiMachineCommand.h"

namespace PicknPlaceGui
{
	class PickAndPlaceCommand : public GuiMachineCommand
	{
	public:
		/// \brief Create a new PickAndPlace command by using 3 reference points
		///			for both the pick coordinate and place coordinate.
		///
		/// \param pickOrientTL (T)op (L)eft coordinate of pick component
		/// \param pickOrientTR (T)op (R)ight coordinate of pick component
		/// \param pickOrientBR (B)ottom (R)ight coordinate of pick component
		/// \param placeOrientTL (T)op (L)eft coordinate of place component
		/// \param placeOrientTR (T)op (R)ight coordinate of place component
		/// \param placeOrientBR (B)ottom (R)ight coordinate of place component
		PickAndPlaceCommand(Coordinate2D pickOrientTL,
							Coordinate2D pickOrientTR,
							Coordinate2D pickOrientBR,
							Coordinate2D placeOrientTL,
							Coordinate2D placeOrientTR,
							Coordinate2D placeOrientBR,
							PickStateStruct settings);
		
		/// \brief Create a new PickAndPlace command by supplying the orientation
		///			of the pick and place of the component to be picked and placed.
		PickAndPlaceCommand(int pickX, int pickY, float pickAngle,
							int placeX, int placeY, float placeAngle, PickStateStruct settings);
		
		~PickAndPlaceCommand(void);
		
		/// \brief Get a command that can be supplied to a MachineController of this 
		///			PickAndPlaceCommand.
		///
		/// The command will be deleted by the object it was retrieved by when the
		/// object gets destroyed or when a call to GetMachineCommand is called again.
		///
		/// \return A MachineWrapperCommand including all MachineController commands needed to do this command.
		MachineWrapperCommand& GetMachineCommand();

		/// \brief Set the different time parameters for the pick and place.
		///	
		/// Offset X and Y will be ignored, maybe change (?).
		/// Se the MachineSetPickTimeCommand for more information.
		void SetSettings(PickStateStruct settings);
		
		/// \brief Get the different time parameters for the pick and place.
		PickStateStruct GetSettings();

		/// \brief Set pick coordinates and orientation.
		void SetPickCoordinate(int x, int y, float angle);

		/// \brief Set pick coordinates and orientation using reference points and offset.
		void SetPickCoordinate(Coordinate2D pickOrientTL,
								Coordinate2D pickOrientTR,
								Coordinate2D pickOrientBR);

		void SetPickX(int x);
		void SetPickY(int y);
		void SetPickAngle(float angle);

		/// \brief Get pick coordinates.
		///
		/// \return A Coordinate2D struct containing the coordinate.
		Coordinate2D GetPickCoordinate();

		/// \brief Get pick orientation.
		///
		/// \return The angle in radians.
		float GetPickAngle();

		/// \brief Set place coordinates and orientation.
		void SetPlaceCoordinate(int x, int y, float angle);

		/// \brief Set place coordinates and orientation using reference points and offset.
		void SetPlaceCoordinate(Coordinate2D placeOrientTL,
								Coordinate2D placeOrientTR,
								Coordinate2D placeOrientBR);

		void SetPlaceX(int x);
		void SetPlaceY(int y);
		void SetPlaceAngle(float angle);

		/// \brief Get place coordinates.
		///
		/// \return A Coordinate2D struct containing the coordinate.
		Coordinate2D GetPlaceCoordinate();

		/// \brief Get place orientation.
		///
		/// \return The angle in radians.
		float GetPlaceAngle();

		/*
		void SetOrientationTL(int x, int y);
		void SetOrientationTL(Coordinate2D coordinate);
		Coordinate2D GetOrientationTL();

		void SetOrientationTR(int x, int y);
		void SetOrientationTR(Coordinate2D coordinate);
		Coordinate2D GetOrientationTR();

		void SetOrientationBR(int x, int y);
		void SetOrientationBR(Coordinate2D coordinate);
		Coordinate2D GetOrientationBR();
		*/
		

	private:
		Coordinate2D m_pick;
		float m_pickAngle;
		
		Coordinate2D m_place;
		float m_placeAngle;

		void Init();
		void CalcCoordinate(Coordinate2D orientTL,
									Coordinate2D orientTR,
									Coordinate2D orientBR,
									Coordinate2D &coordinate,
									float &angle);
		// Settings
		PickStateStruct m_settings;

		MachineWrapperCommand *m_cmd;
		/*
		Coordinate2D m_pickOrientationTL;
		Coordinate2D m_pickOrientationTR;
		Coordinate2D m_pickOrientationBR;

		Coordinate2D m_placeOrientationTL;
		Coordinate2D m_placeOrientationTR;
		Coordinate2D m_placeOrientationBR;
		*/
	};
}

#endif // __PICKANDPLACECOMMAND_H__
