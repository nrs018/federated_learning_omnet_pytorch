//
// Generated file, do not edit! Created by nedtool 5.5 from inet/networklayer/rsvpte/RsvpResvMsg.msg.
//

#ifndef __INET_RSVPRESVMSG_M_H
#define __INET_RSVPRESVMSG_M_H

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

class RsvpResvMsg;
class RsvpResvTear;
class RsvpResvError;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address

#include "inet/networklayer/rsvpte/IntServ_m.h" // import inet.networklayer.rsvpte.IntServ

#include "inet/networklayer/rsvpte/RsvpPacket_m.h" // import inet.networklayer.rsvpte.RsvpPacket


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/rsvpte/RsvpResvMsg.msg:27</tt> by nedtool.
 * <pre>
 * //
 * // FIXME missing documentation
 * //
 * class RsvpResvMsg extends RsvpPacket
 * {
 *     RsvpHopObj hop;
 *     FlowDescriptorVector flowDescriptor;
 *     rsvpKind = RESV_MESSAGE;
 * }
 * </pre>
 */
class INET_API RsvpResvMsg : public ::inet::RsvpPacket
{
  protected:
    RsvpHopObj hop;
    FlowDescriptorVector flowDescriptor;

  private:
    void copy(const RsvpResvMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RsvpResvMsg&);

  public:
    RsvpResvMsg();
    RsvpResvMsg(const RsvpResvMsg& other);
    virtual ~RsvpResvMsg();
    RsvpResvMsg& operator=(const RsvpResvMsg& other);
    virtual RsvpResvMsg *dup() const override {return new RsvpResvMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const RsvpHopObj& getHop() const;
    virtual RsvpHopObj& getHopForUpdate() { handleChange();return const_cast<RsvpHopObj&>(const_cast<RsvpResvMsg*>(this)->getHop());}
    virtual void setHop(const RsvpHopObj& hop);
    virtual const FlowDescriptorVector& getFlowDescriptor() const;
    virtual FlowDescriptorVector& getFlowDescriptorForUpdate() { handleChange();return const_cast<FlowDescriptorVector&>(const_cast<RsvpResvMsg*>(this)->getFlowDescriptor());}
    virtual void setFlowDescriptor(const FlowDescriptorVector& flowDescriptor);

  public:
    inline Ipv4Address getNHOP() const { return getHop().Next_Hop_Address; }
    inline Ipv4Address getLIH() const { return getHop().Logical_Interface_Handle; }
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RsvpResvMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RsvpResvMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/rsvpte/RsvpResvMsg.msg:43</tt> by nedtool.
 * <pre>
 * //
 * // FIXME missing documentation
 * //
 * class RsvpResvTear extends RsvpPacket
 * {
 *     RsvpHopObj hop;
 *     FlowDescriptorVector flowDescriptor;
 *     rsvpKind = RTEAR_MESSAGE;
 * }
 * </pre>
 */
class INET_API RsvpResvTear : public ::inet::RsvpPacket
{
  protected:
    RsvpHopObj hop;
    FlowDescriptorVector flowDescriptor;

  private:
    void copy(const RsvpResvTear& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RsvpResvTear&);

  public:
    RsvpResvTear();
    RsvpResvTear(const RsvpResvTear& other);
    virtual ~RsvpResvTear();
    RsvpResvTear& operator=(const RsvpResvTear& other);
    virtual RsvpResvTear *dup() const override {return new RsvpResvTear(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const RsvpHopObj& getHop() const;
    virtual RsvpHopObj& getHopForUpdate() { handleChange();return const_cast<RsvpHopObj&>(const_cast<RsvpResvTear*>(this)->getHop());}
    virtual void setHop(const RsvpHopObj& hop);
    virtual const FlowDescriptorVector& getFlowDescriptor() const;
    virtual FlowDescriptorVector& getFlowDescriptorForUpdate() { handleChange();return const_cast<FlowDescriptorVector&>(const_cast<RsvpResvTear*>(this)->getFlowDescriptor());}
    virtual void setFlowDescriptor(const FlowDescriptorVector& flowDescriptor);

  public:
    inline Ipv4Address getNHOP() { return getHop().Next_Hop_Address; }
    inline Ipv4Address getLIH() { return getHop().Logical_Interface_Handle; }
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RsvpResvTear& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RsvpResvTear& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/rsvpte/RsvpResvMsg.msg:59</tt> by nedtool.
 * <pre>
 * //
 * // FIXME missing documentation
 * //
 * class RsvpResvError extends RsvpPacket
 * {
 *     RsvpHopObj hop;
 *     Ipv4Address errorNode;
 *     int errorCode;
 *     rsvpKind = RERROR_MESSAGE;
 * }
 * </pre>
 */
class INET_API RsvpResvError : public ::inet::RsvpPacket
{
  protected:
    RsvpHopObj hop;
    Ipv4Address errorNode;
    int errorCode = 0;

  private:
    void copy(const RsvpResvError& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RsvpResvError&);

  public:
    RsvpResvError();
    RsvpResvError(const RsvpResvError& other);
    virtual ~RsvpResvError();
    RsvpResvError& operator=(const RsvpResvError& other);
    virtual RsvpResvError *dup() const override {return new RsvpResvError(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const RsvpHopObj& getHop() const;
    virtual RsvpHopObj& getHopForUpdate() { handleChange();return const_cast<RsvpHopObj&>(const_cast<RsvpResvError*>(this)->getHop());}
    virtual void setHop(const RsvpHopObj& hop);
    virtual const Ipv4Address& getErrorNode() const;
    virtual Ipv4Address& getErrorNodeForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<RsvpResvError*>(this)->getErrorNode());}
    virtual void setErrorNode(const Ipv4Address& errorNode);
    virtual int getErrorCode() const;
    virtual void setErrorCode(int errorCode);

  public:
    inline Ipv4Address getNHOP() { return getHop().Next_Hop_Address; }
    inline Ipv4Address getLIH() { return getHop().Logical_Interface_Handle; }
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RsvpResvError& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RsvpResvError& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_RSVPRESVMSG_M_H

