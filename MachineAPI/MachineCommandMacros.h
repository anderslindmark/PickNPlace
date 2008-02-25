#ifndef __MACHINECOMMANDMACROS_H__
#define __MACHINECOMMANDMACROS_H__

#define M_ANS_ERROR	"E1"
#define M_ANS_OK	"OK"
#define M_ANS_1		"1"
#define M_ANS_CC	"CC"

// Ready
#define M_READY_1515			"RD 1515"
#define M_READY_1915			"RD 1915"

// Moves:
#define M_DO_ABS_MOVE_GENERIC(arg) "WR DM3"#arg"0 16384"
#define M_DO_ABS_MOVE_X			M_DO_ABS_MOVE_GENERIC(0)
#define M_POS_ABS_MOVE_X		"WR DM301 "
#define M_STORE_ABS_MOVE_X		"WR DM51 2"
#define M_EXEC_MOVE_X			"WR DM50 300"




#define M_DO_CR					"CR"


#endif // __MACHINECOMMANDMACROS_H__