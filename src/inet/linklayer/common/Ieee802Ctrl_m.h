//
// Generated file, do not edit! Created by nedtool 5.5 from inet/linklayer/common/Ieee802Ctrl.msg.
//

#ifndef __INET_IEEE802CTRL_M_H
#define __INET_IEEE802CTRL_M_H

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

class Ieee802PauseCommand;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress


namespace inet {

/**
 * Enum generated from <tt>inet/linklayer/common/Ieee802Ctrl.msg:27</tt> by nedtool.
 * <pre>
 * //
 * // Message kind values used with in communication between L3 and IEEE 802 L2
 * //
 * enum Ieee802MessageKind
 * {
 *     IEEE802CTRL_DATA = 2003;  // data to/from higher layer
 *     IEEE802CTRL_SENDPAUSE = 2006;  // higher layer wants MAC to send PAUSE frame
 * }
 * </pre>
 */
enum Ieee802MessageKind {
    IEEE802CTRL_DATA = 2003,
    IEEE802CTRL_SENDPAUSE = 2006
};

/**
 * Class generated from <tt>inet/linklayer/common/Ieee802Ctrl.msg:34</tt> by nedtool.
 * <pre>
 * // used with IEEE802CTRL_SENDPAUSE
 * class Ieee802PauseCommand extends cObject
 * {
 *     MacAddress destinationAddress;
 *     int pauseUnits;
 * }
 * </pre>
 */
class INET_API Ieee802PauseCommand : public ::omnetpp::cObject
{
  protected:
    MacAddress destinationAddress;
    int pauseUnits = 0;

  private:
    void copy(const Ieee802PauseCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee802PauseCommand&);

  public:
    Ieee802PauseCommand();
    Ieee802PauseCommand(const Ieee802PauseCommand& other);
    virtual ~Ieee802PauseCommand();
    Ieee802PauseCommand& operator=(const Ieee802PauseCommand& other);
    virtual Ieee802PauseCommand *dup() const override {return new Ieee802PauseCommand(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const MacAddress& getDestinationAddress() const;
    virtual MacAddress& getDestinationAddressForUpdate() { return const_cast<MacAddress&>(const_cast<Ieee802PauseCommand*>(this)->getDestinationAddress());}
    virtual void setDestinationAddress(const MacAddress& destinationAddress);
    virtual int getPauseUnits() const;
    virtual void setPauseUnits(int pauseUnits);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee802PauseCommand& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee802PauseCommand& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_IEEE802CTRL_M_H

