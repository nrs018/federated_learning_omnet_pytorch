//
// Generated file, do not edit! Created by nedtool 5.5 from inet/physicallayer/ieee80211/packetlevel/Ieee80211Tag.msg.
//

#ifndef __INET__PHYSICALLAYER_IEEE80211TAG_M_H
#define __INET__PHYSICALLAYER_IEEE80211TAG_M_H

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
namespace physicallayer {

class Ieee80211ModeTagBase;
class Ieee80211ModeReq;
class Ieee80211ModeInd;
class Ieee80211ChannelTagBase;
class Ieee80211ChannelReq;
class Ieee80211ChannelInd;
} // namespace physicallayer
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/TagBase_m.h" // import inet.common.TagBase

#include "inet/physicallayer/ieee80211/mode/IIeee80211Mode_m.h" // import inet.physicallayer.ieee80211.mode.IIeee80211Mode

#include "inet/physicallayer/ieee80211/mode/Ieee80211Channel_m.h" // import inet.physicallayer.ieee80211.mode.Ieee80211Channel


namespace inet {
namespace physicallayer {

/**
 * Class generated from <tt>inet/physicallayer/ieee80211/packetlevel/Ieee80211Tag.msg:29</tt> by nedtool.
 * <pre>
 * //
 * // This is an abstract base class that should not be directly added as a tag.
 * //
 * class Ieee80211ModeTagBase extends TagBase
 * {
 *     const IIeee80211Mode *mode = nullptr; // IEEE 802.11 transmission mode
 * }
 * </pre>
 */
class INET_API Ieee80211ModeTagBase : public ::inet::TagBase
{
  protected:
    const IIeee80211Mode * mode = nullptr;

  private:
    void copy(const Ieee80211ModeTagBase& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211ModeTagBase&);

  public:
    Ieee80211ModeTagBase();
    Ieee80211ModeTagBase(const Ieee80211ModeTagBase& other);
    virtual ~Ieee80211ModeTagBase();
    Ieee80211ModeTagBase& operator=(const Ieee80211ModeTagBase& other);
    virtual Ieee80211ModeTagBase *dup() const override {return new Ieee80211ModeTagBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const IIeee80211Mode * getMode() const;
    virtual void setMode(const IIeee80211Mode * mode);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211ModeTagBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211ModeTagBase& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/ieee80211/packetlevel/Ieee80211Tag.msg:38</tt> by nedtool.
 * <pre>
 * //
 * // This request determines the IEEE 802.11 mode that should be used to transmit the packet.
 * // It may be present on a packet from the application to the phyisical layer.
 * //
 * class Ieee80211ModeReq extends Ieee80211ModeTagBase
 * {
 * }
 * </pre>
 */
class INET_API Ieee80211ModeReq : public ::inet::physicallayer::Ieee80211ModeTagBase
{
  protected:

  private:
    void copy(const Ieee80211ModeReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211ModeReq&);

  public:
    Ieee80211ModeReq();
    Ieee80211ModeReq(const Ieee80211ModeReq& other);
    virtual ~Ieee80211ModeReq();
    Ieee80211ModeReq& operator=(const Ieee80211ModeReq& other);
    virtual Ieee80211ModeReq *dup() const override {return new Ieee80211ModeReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211ModeReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211ModeReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/ieee80211/packetlevel/Ieee80211Tag.msg:46</tt> by nedtool.
 * <pre>
 * //
 * // This indication specifies the IEEE 802.11 mode that was used to receive the packet.
 * // It may be present on a packet from the phyiscal layer to the application.
 * //
 * class Ieee80211ModeInd extends Ieee80211ModeTagBase
 * {
 * }
 * </pre>
 */
class INET_API Ieee80211ModeInd : public ::inet::physicallayer::Ieee80211ModeTagBase
{
  protected:

  private:
    void copy(const Ieee80211ModeInd& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211ModeInd&);

  public:
    Ieee80211ModeInd();
    Ieee80211ModeInd(const Ieee80211ModeInd& other);
    virtual ~Ieee80211ModeInd();
    Ieee80211ModeInd& operator=(const Ieee80211ModeInd& other);
    virtual Ieee80211ModeInd *dup() const override {return new Ieee80211ModeInd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211ModeInd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211ModeInd& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/ieee80211/packetlevel/Ieee80211Tag.msg:53</tt> by nedtool.
 * <pre>
 * //
 * // This is an abstract base class that should not be directly added as a tag.
 * //
 * class Ieee80211ChannelTagBase extends TagBase
 * {
 *     const Ieee80211Channel *channel = nullptr; // IEEE 802.11 band and channel
 * }
 * </pre>
 */
class INET_API Ieee80211ChannelTagBase : public ::inet::TagBase
{
  protected:
    const Ieee80211Channel * channel = nullptr;

  private:
    void copy(const Ieee80211ChannelTagBase& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211ChannelTagBase&);

  public:
    Ieee80211ChannelTagBase();
    Ieee80211ChannelTagBase(const Ieee80211ChannelTagBase& other);
    virtual ~Ieee80211ChannelTagBase();
    Ieee80211ChannelTagBase& operator=(const Ieee80211ChannelTagBase& other);
    virtual Ieee80211ChannelTagBase *dup() const override {return new Ieee80211ChannelTagBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const Ieee80211Channel * getChannel() const;
    virtual void setChannel(const Ieee80211Channel * channel);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211ChannelTagBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211ChannelTagBase& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/ieee80211/packetlevel/Ieee80211Tag.msg:62</tt> by nedtool.
 * <pre>
 * //
 * // This request determines the IEEE 802.11 channel that should be used to transmit the packet.
 * // It may be present on a packet from the application to the phyisical layer.
 * //
 * class Ieee80211ChannelReq extends Ieee80211ChannelTagBase
 * {
 * }
 * </pre>
 */
class INET_API Ieee80211ChannelReq : public ::inet::physicallayer::Ieee80211ChannelTagBase
{
  protected:

  private:
    void copy(const Ieee80211ChannelReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211ChannelReq&);

  public:
    Ieee80211ChannelReq();
    Ieee80211ChannelReq(const Ieee80211ChannelReq& other);
    virtual ~Ieee80211ChannelReq();
    Ieee80211ChannelReq& operator=(const Ieee80211ChannelReq& other);
    virtual Ieee80211ChannelReq *dup() const override {return new Ieee80211ChannelReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211ChannelReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211ChannelReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/ieee80211/packetlevel/Ieee80211Tag.msg:70</tt> by nedtool.
 * <pre>
 * //
 * // This indication specifies the IEEE 802.11 channel that was used to receive the packet.
 * // It may be present on a packet from the phyiscal layer to the application.
 * //
 * class Ieee80211ChannelInd extends Ieee80211ChannelTagBase
 * {
 * }
 * </pre>
 */
class INET_API Ieee80211ChannelInd : public ::inet::physicallayer::Ieee80211ChannelTagBase
{
  protected:

  private:
    void copy(const Ieee80211ChannelInd& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Ieee80211ChannelInd&);

  public:
    Ieee80211ChannelInd();
    Ieee80211ChannelInd(const Ieee80211ChannelInd& other);
    virtual ~Ieee80211ChannelInd();
    Ieee80211ChannelInd& operator=(const Ieee80211ChannelInd& other);
    virtual Ieee80211ChannelInd *dup() const override {return new Ieee80211ChannelInd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee80211ChannelInd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee80211ChannelInd& obj) {obj.parsimUnpack(b);}

} // namespace physicallayer
} // namespace inet

#endif // ifndef __INET__PHYSICALLAYER_IEEE80211TAG_M_H

