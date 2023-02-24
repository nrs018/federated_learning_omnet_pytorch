//
// Generated file, do not edit! Created by nedtool 5.5 from inet/transportlayer/contract/TransportHeaderBase.msg.
//

#ifndef __INET_TRANSPORTHEADERBASE_M_H
#define __INET_TRANSPORTHEADERBASE_M_H

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

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

// cplusplus {{
namespace inet {

class INET_API TransportHeaderBase : public FieldsChunk
{
  protected:
    virtual TransportHeaderBase *dup() const override { throw omnetpp::cRuntimeError("You forgot to manually add a dup() function to class %s", getClassName()); }
  public:
    virtual unsigned int getSourcePort() const = 0;
    virtual void setSourcePort(unsigned int port) = 0;
    virtual unsigned int getDestinationPort() const = 0;
    virtual void setDestinationPort(unsigned int port) = 0;
};

} // namespace inet
// }}


namespace inet {

} // namespace inet

#endif // ifndef __INET_TRANSPORTHEADERBASE_M_H

