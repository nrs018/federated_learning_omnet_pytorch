//
// Generated file, do not edit! Created by nedtool 5.5 from inet/applications/ethernet/EtherApp.msg.
//

#ifndef __INET_ETHERAPP_M_H
#define __INET_ETHERAPP_M_H

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

class EtherAppReq;
class EtherAppResp;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/applications/ethernet/EtherApp.msg:29</tt> by nedtool.
 * <pre>
 * //
 * // Request packet sent by ~EtherAppClient. Contains the number of bytes to be
 * // sent back as response; if this value is greater than ~1400, the reply
 * // will consist of several Ethernet frames. See also ~EtherAppResp.
 * //
 * class EtherAppReq extends FieldsChunk
 * {
 *     long requestId;
 *     long responseBytes;
 * }
 * </pre>
 */
class INET_API EtherAppReq : public ::inet::FieldsChunk
{
  protected:
    long requestId = 0;
    long responseBytes = 0;

  private:
    void copy(const EtherAppReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const EtherAppReq&);

  public:
    EtherAppReq();
    EtherAppReq(const EtherAppReq& other);
    virtual ~EtherAppReq();
    EtherAppReq& operator=(const EtherAppReq& other);
    virtual EtherAppReq *dup() const override {return new EtherAppReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual long getRequestId() const;
    virtual void setRequestId(long requestId);
    virtual long getResponseBytes() const;
    virtual void setResponseBytes(long responseBytes);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EtherAppReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EtherAppReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/applications/ethernet/EtherApp.msg:38</tt> by nedtool.
 * <pre>
 * //
 * // Packet sent back by ~EtherAppServer in response to an ~EtherAppReq.
 * //
 * class EtherAppResp extends FieldsChunk
 * {
 *     int requestId;
 *     int numFrames;
 * }
 * </pre>
 */
class INET_API EtherAppResp : public ::inet::FieldsChunk
{
  protected:
    int requestId = 0;
    int numFrames = 0;

  private:
    void copy(const EtherAppResp& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const EtherAppResp&);

  public:
    EtherAppResp();
    EtherAppResp(const EtherAppResp& other);
    virtual ~EtherAppResp();
    EtherAppResp& operator=(const EtherAppResp& other);
    virtual EtherAppResp *dup() const override {return new EtherAppResp(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getRequestId() const;
    virtual void setRequestId(int requestId);
    virtual int getNumFrames() const;
    virtual void setNumFrames(int numFrames);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EtherAppResp& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EtherAppResp& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_ETHERAPP_M_H

