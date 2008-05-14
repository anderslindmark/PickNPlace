#ifndef __PICKANDPLACECOMMAND_H__
#define __PICKANDPLACECOMMAND_H__

#include "Coordinate.h"
#include "MachineCommands.h"
namespace PicknPlaceGui
{
	class PickAndPlaceCommand
	{
	public:
		/// \brief Create a new PickAndPlace command by using 3 reference points
		///			for both the pick coordinate and place coordinate.
		///
		/// \param pickOrientTL (T)op (L)eft coordinate of pick component
		/// \param pickOrientTR (T)op (R)ight coordinate of pick component
		/// \param pickOrientBR (B)ottom (R)ight coordinate of pick component
		/// \param pickZ		Z offset for pick
		/// \param placeOrientTL (T)op (L)eft coordinate of place component
		/// \param placeOrientTR (T)op (R)ight coordinate of place component
		/// \param placeOrientBR (B)ottom (R)ight coordinate of place component
		/// \param placeZ		Z offset for place
		PickAndPlaceCommand(Coordinate2D pickOrientTL,
							Coordinate2D pickOrientTR,
							Coordinate2D pickOrientBR,
							int pickZ,
							Coordinate2D placeOrientTL,
							Coordinate2D placeOrientTR,
							Coordinate2D placeOrientBR,
							int placeZ);
		
		/// \brief Create a new PickAndPlace command by supplying the orientation
		///			of the pick and place of the component to be picked and placed.
		PickAndPlaceCommand(int pickX, int pickY, int pickZ, float pickAngle,
							int placeX, int placeY, int placeZ, float placeAngle);
		
		~PickAndPlaceCommand(void);
		
		/// \brief Get a command that can be supplied to a MachineController of this 
		///			PickAndPlaceCommand.
		///
		/// \return A MachineWrapperCommand including all MachineController commands needed to do this command.
		MachineWrapperCommand& GetMachineCommand();

		/// \brief Set different time parameters for the pick and place.
		///	
		/// Se the MachineSetPickTimeCommand for more information.
		void SetTimes(int afterPick, int afterPlace, int pressPick, int pressPlace);

		/// \brief Set pick coordinates and orientation.
		void SetPickCoordinate(int x, int y, int z, float angle);

		/// \brief Set pick coordinates and orientation using reference points and offset.
		void SetPickCoordinate(Coordinate2D pickOrientTL,
								Coordinate2D pickOrientTR,
								Coordinate2D pickOrientBR,
								int pickZ);

		/// \brief Set pick coordinates and orientation using a Coordinate3D struct.
		void SetPickCoordinate(Coordinate3D coordinate, float angle);

		void SetPickX(int x);
		void SetPickY(int y);
		void SetPickZ(int z);
		void SetPickAngle(float angle);

		/// \brief Get pick coordinates.
		///
		/// \return A Coordinate3D struct containing the coordinate.
		Coordinate3D GetPickCoordinate();

		/// \brief Get pick orientation.
		///
		/// \return The angle in radians.
		float GetPickAngle();

		/// \brief Set place coordinates and orientation.
		void SetPlaceCoordinate(int x, int y, int z, float angle);

		/// \brief Set palce coordinates and orientation using reference points and offset.
		void SetPlaceCoordinate(Coordinate2D placeOrientTL,
								Coordinate2D placeOrientTR,
								Coordinate2D placeOrientBR,
								int placeZ);

		/// \brief Set place coordinates and orientation using a Coordinate3D struct.
		void SetPlaceCoordinate(Coordinate3D coordinate, float angle);

		void SetPlaceX(int x);
		void SetPlaceY(int y);
		void SetPlaceZ(int z);
		void SetPlaceAngle(float angle);

		/// \brief Get place coordinates.
		///
		/// \return A Coordinate3D struct containing the coordinate.
		Coordinate3D GetPlaceCoordinate();

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
		Coordinate3D m_pick;
		float m_pickAngle;
		
		Coordinate3D m_place;
		float m_placeAngle;

		void Init();
		void CalcCoordinate(Coordinate2D orientTL,
									Coordinate2D orientTR,
									Coordinate2D orientBR,
									Coordinate3D &coordinate,
									float &angle);
		//Times
		int m_pressPick;
		int m_pressPlace;
		int m_afterPick;
		int m_afterPlace;

		MachineWrapperCommand *cmd;
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