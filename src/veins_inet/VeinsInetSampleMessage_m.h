//
// Generated file, do not edit! Created by nedtool 5.5 from veins_inet/VeinsInetSampleMessage.msg.
//

#ifndef __VEINSINETSAMPLEMESSAGE_M_H
#define __VEINSINETSAMPLEMESSAGE_M_H

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



class VeinsInetSampleMessage;
#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

/**
 * Class generated from <tt>veins_inet/VeinsInetSampleMessage.msg:34</tt> by nedtool.
 * <pre>
 * //
 * // Example message definition
 * //
 * class VeinsInetSampleMessage extends inet::FieldsChunk
 * {
 *     string roadId;
 * }
 * </pre>
 */
class INET_API VeinsInetSampleMessage : public ::inet::FieldsChunk
{
  protected:
    omnetpp::opp_string roadId;

  private:
    void copy(const VeinsInetSampleMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const VeinsInetSampleMessage&);

  public:
    VeinsInetSampleMessage();
    VeinsInetSampleMessage(const VeinsInetSampleMessage& other);
    virtual ~VeinsInetSampleMessage();
    VeinsInetSampleMessage& operator=(const VeinsInetSampleMessage& other);
    virtual VeinsInetSampleMessage *dup() const override {return new VeinsInetSampleMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getRoadId() const;
    virtual void setRoadId(const char * roadId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const VeinsInetSampleMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, VeinsInetSampleMessage& obj) {obj.parsimUnpack(b);}

#endif // ifndef __VEINSINETSAMPLEMESSAGE_M_H

