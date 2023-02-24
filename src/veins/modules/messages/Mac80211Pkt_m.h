//
// Generated file, do not edit! Created by nedtool 5.5 from veins/modules/messages/Mac80211Pkt.msg.
//

#ifndef __VEINS_MAC80211PKT_M_H
#define __VEINS_MAC80211PKT_M_H

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


namespace veins {

class Mac80211Pkt;
} // namespace veins

#include "veins/base/messages/MacPkt_m.h" // import veins.base.messages.MacPkt


namespace veins {

/**
 * Class generated from <tt>veins/modules/messages/Mac80211Pkt.msg:35</tt> by nedtool.
 * <pre>
 * //
 * // Defines all fields of an 802.11 MAC frame
 * //
 * packet Mac80211Pkt extends MacPkt
 * {
 *     int address3;
 *     int address4;
 *     int fragmentation; //part of the Frame Control field
 *     int informationDS; //part of the Frame Control field
 *     int sequenceControl;
 *     bool retry;
 *     simtime_t duration;     //the expected remaining duration the current transaction 
 * }
 * </pre>
 */
class INET_API Mac80211Pkt : public ::veins::MacPkt
{
  protected:
    int address3 = 0;
    int address4 = 0;
    int fragmentation = 0;
    int informationDS = 0;
    int sequenceControl = 0;
    bool retry = false;
    omnetpp::simtime_t duration = SIMTIME_ZERO;

  private:
    void copy(const Mac80211Pkt& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Mac80211Pkt&);

  public:
    Mac80211Pkt(const char *name=nullptr, short kind=0);
    Mac80211Pkt(const Mac80211Pkt& other);
    virtual ~Mac80211Pkt();
    Mac80211Pkt& operator=(const Mac80211Pkt& other);
    virtual Mac80211Pkt *dup() const override {return new Mac80211Pkt(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getAddress3() const;
    virtual void setAddress3(int address3);
    virtual int getAddress4() const;
    virtual void setAddress4(int address4);
    virtual int getFragmentation() const;
    virtual void setFragmentation(int fragmentation);
    virtual int getInformationDS() const;
    virtual void setInformationDS(int informationDS);
    virtual int getSequenceControl() const;
    virtual void setSequenceControl(int sequenceControl);
    virtual bool getRetry() const;
    virtual void setRetry(bool retry);
    virtual omnetpp::simtime_t getDuration() const;
    virtual void setDuration(omnetpp::simtime_t duration);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Mac80211Pkt& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Mac80211Pkt& obj) {obj.parsimUnpack(b);}

} // namespace veins

#endif // ifndef __VEINS_MAC80211PKT_M_H

