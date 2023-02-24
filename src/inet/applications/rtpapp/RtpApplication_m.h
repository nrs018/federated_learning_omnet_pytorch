//
// Generated file, do not edit! Created by nedtool 5.5 from inet/applications/rtpapp/RtpApplication.msg.
//

#ifndef __INET_RTPAPPLICATION_M_H
#define __INET_RTPAPPLICATION_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0505
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs


namespace inet {

/**
 * Enum generated from <tt>inet/applications/rtpapp/RtpApplication.msg:22</tt> by nedtool.
 * <pre>
 * enum RtpAppSelfMsgKinds
 * {
 *     RTPAPP_ENTER_SESSION = 1;
 *     RTPAPP_START_TRANSMISSION = 2;
 *     RTPAPP_STOP_TRANSMISSION = 3;
 *     RTPAPP_LEAVE_SESSION = 4;
 * }
 * </pre>
 */
enum RtpAppSelfMsgKinds {
    RTPAPP_ENTER_SESSION = 1,
    RTPAPP_START_TRANSMISSION = 2,
    RTPAPP_STOP_TRANSMISSION = 3,
    RTPAPP_LEAVE_SESSION = 4
};

} // namespace inet

#endif // ifndef __INET_RTPAPPLICATION_M_H
