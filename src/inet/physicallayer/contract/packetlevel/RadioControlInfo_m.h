//
// Generated file, do not edit! Created by nedtool 5.5 from inet/physicallayer/contract/packetlevel/RadioControlInfo.msg.
//

#ifndef __INET__PHYSICALLAYER_RADIOCONTROLINFO_M_H
#define __INET__PHYSICALLAYER_RADIOCONTROLINFO_M_H

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

class ConfigureRadioCommand;
} // namespace physicallayer
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Units_m.h" // import inet.common.Units

#include "inet/physicallayer/contract/packetlevel/IModulation_m.h" // import inet.physicallayer.contract.packetlevel.IModulation


namespace inet {
namespace physicallayer {

/**
 * Enum generated from <tt>inet/physicallayer/contract/packetlevel/RadioControlInfo.msg:28</tt> by nedtool.
 * <pre>
 * //
 * // Message kinds for sending commands to the radio.
 * //
 * enum RadioCommandCode
 * {
 *     RADIO_C_CONFIGURE = 1;
 * }
 * </pre>
 */
enum RadioCommandCode {
    RADIO_C_CONFIGURE = 1
};

/**
 * Class generated from <tt>inet/physicallayer/contract/packetlevel/RadioControlInfo.msg:36</tt> by nedtool.
 * <pre>
 * //
 * // Control info attached to a configure command that is sent to the ~Radio.
 * //
 * class ConfigureRadioCommand extends cObject
 * {
 *     int radioMode = -1;                  // new radio mode or -1 if not set.
 *     W power = W(NaN);                    // new default transmission power in the range (0, +infinity) or NaN if not set.
 *     bps bitrate = bps(NaN);              // new default bitrate in the range (0, +infinity) or NaN if not set.
 *     IModulation *modulation = nullptr;   // new default modulation or nullptr if not set.
 *     Hz centerFrequency = Hz(NaN);       // new default carrier frequency in the range (0, +infinity) or NaN if not set.
 *     Hz bandwidth = Hz(NaN);              // new default bandwidth in the rage (0, +infinity) or NaN if not set.
 * }
 * </pre>
 */
class INET_API ConfigureRadioCommand : public ::omnetpp::cObject
{
  protected:
    int radioMode = -1;
    W power = W(NaN);
    bps bitrate = bps(NaN);
    IModulation * modulation = nullptr;
    Hz centerFrequency = Hz(NaN);
    Hz bandwidth = Hz(NaN);

  private:
    void copy(const ConfigureRadioCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ConfigureRadioCommand&);

  public:
    ConfigureRadioCommand();
    ConfigureRadioCommand(const ConfigureRadioCommand& other);
    virtual ~ConfigureRadioCommand();
    ConfigureRadioCommand& operator=(const ConfigureRadioCommand& other);
    virtual ConfigureRadioCommand *dup() const override {return new ConfigureRadioCommand(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getRadioMode() const;
    virtual void setRadioMode(int radioMode);
    virtual W getPower() const;
    virtual void setPower(W power);
    virtual bps getBitrate() const;
    virtual void setBitrate(bps bitrate);
    virtual const IModulation * getModulation() const;
    virtual IModulation * getModulationForUpdate() { return const_cast<IModulation *>(const_cast<ConfigureRadioCommand*>(this)->getModulation());}
    virtual void setModulation(IModulation * modulation);
    virtual Hz getCenterFrequency() const;
    virtual void setCenterFrequency(Hz centerFrequency);
    virtual Hz getBandwidth() const;
    virtual void setBandwidth(Hz bandwidth);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ConfigureRadioCommand& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ConfigureRadioCommand& obj) {obj.parsimUnpack(b);}

} // namespace physicallayer
} // namespace inet

#endif // ifndef __INET__PHYSICALLAYER_RADIOCONTROLINFO_M_H

