//
// Generated file, do not edit! Created by nedtool 5.5 from lte/apps/vod/M1Message.msg.
//

#ifndef __M1MESSAGE_M_H
#define __M1MESSAGE_M_H

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



class M1Message;
#include "inet/networklayer/common/L3Address_m.h" // import inet.networklayer.common.L3Address

/**
 * Class generated from <tt>lte/apps/vod/M1Message.msg:12</tt> by nedtool.
 * <pre>
 * message M1Message
 * {
 *     inet::L3Address clientAddr;   // client address
 *     int clientPort;           // client UDP port
 *     long numPkSent;           // number of packets sent
 * }
 * </pre>
 */
class INET_API M1Message : public ::omnetpp::cMessage
{
  protected:
    inet::L3Address clientAddr;
    int clientPort = 0;
    long numPkSent = 0;

  private:
    void copy(const M1Message& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const M1Message&);

  public:
    M1Message(const char *name=nullptr, short kind=0);
    M1Message(const M1Message& other);
    virtual ~M1Message();
    M1Message& operator=(const M1Message& other);
    virtual M1Message *dup() const override {return new M1Message(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const inet::L3Address& getClientAddr() const;
    virtual inet::L3Address& getClientAddrForUpdate() { return const_cast<inet::L3Address&>(const_cast<M1Message*>(this)->getClientAddr());}
    virtual void setClientAddr(const inet::L3Address& clientAddr);
    virtual int getClientPort() const;
    virtual void setClientPort(int clientPort);
    virtual long getNumPkSent() const;
    virtual void setNumPkSent(long numPkSent);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const M1Message& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, M1Message& obj) {obj.parsimUnpack(b);}

#endif // ifndef __M1MESSAGE_M_H
