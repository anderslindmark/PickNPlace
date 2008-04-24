#ifndef __MACHINECOMMANDMACROS_H__
#define __MACHINECOMMANDMACROS_H__

#define STEP_PRECISION_X	10.0
#define STEP_PRECISION_Y	5.0
#define STEP_PRECISION_Z	5.0

#define ROUND(val)	(int)floor(val+0.5)

#define TOOL_MOUNT_MAX_Z		89000	// The distance before the tool mount hits the floor (in micrometers)

#define M_ANS_ERROR	"E1"
#define M_ANS_OK	"OK"
#define M_ANS_1		"1"
#define M_ANS_CC	"CC"

// Ready
#define M_READY_1515			"RD 1515"
#define M_READY_1915			"RD 1915"

// Moves:
#define M_DO_ABS_MOVE(axis)		"WR DM3"#axis"0 16384"
#define M_DO_ABS_MOVE_X			M_DO_ABS_MOVE(0)
#define M_DO_ABS_MOVE_Y			M_DO_ABS_MOVE(1)
#define M_DO_ABS_MOVE_Z			M_DO_ABS_MOVE(2)

#define M_POS_ABS_MOVE(axis)	"WR DM3"#axis"1 "
#define M_POS_ABS_MOVE_X		M_POS_ABS_MOVE(0) << pos
#define M_POS_ABS_MOVE_Y		M_POS_ABS_MOVE(1) << pos
#define M_POS_ABS_MOVE_Z		M_POS_ABS_MOVE(2) << pos

#define M_STORE_ABS_MOVE(axis)	"WR DM"#axis"1 2"
#define M_STORE_ABS_MOVE_X		M_STORE_ABS_MOVE(5)
#define M_STORE_ABS_MOVE_Y		M_STORE_ABS_MOVE(6)
#define M_STORE_ABS_MOVE_Z		M_STORE_ABS_MOVE(7)

#define M_EXEC_MOVE(axis1, axis2)	"WR DM"#axis1"0 3"#axis2"0"
#define M_EXEC_MOVE_X			M_EXEC_MOVE(5, 0)
#define M_EXEC_MOVE_Y			M_EXEC_MOVE(6, 1)
#define M_EXEC_MOVE_Z			M_EXEC_MOVE(7, 2)

#define M_DO_ABS_ROTATE			M_DO_ABS_MOVE(3)
#define M_POS_ABS_ROTATE		M_POS_ABS_MOVE(3) << pos
#define M_STORE_ABS_ROTATE		M_STORE_ABS_MOVE(8)
#define M_EXEC_ROTATE			M_EXEC_MOVE(8, 3)

#define M_DO_CR					"CR"


#endif // __MACHINECOMMANDMACROS_H__