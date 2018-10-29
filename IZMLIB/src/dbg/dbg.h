#ifndef IZM_DBG_DBG_H
#define IZM_DBG_DBG_H

#include "debugstream.h"
#include "dsmanipulator.h"

#if !defined(NO_USING_MANIPULATOR)
namespace izm {
using dbg::endl;
using dbg::timestamp;
using dbg::callerInfo;
using dbg::printf;
using dbg::each;
}
#endif

#endif // IZM_DBG_DBG_H
