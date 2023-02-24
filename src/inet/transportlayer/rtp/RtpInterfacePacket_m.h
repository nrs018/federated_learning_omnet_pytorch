//
// Generated file, do not edit! Created by nedtool 5.5 from inet/transportlayer/rtp/RtpInterfacePacket.msg.
//

#ifndef __INET__RTP_RTPINTERFACEPACKET_M_H
#define __INET__RTP_RTPINTERFACEPACKET_M_H

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
namespace rtp {

class RtpControlMsg;
class RtpControlInfo;
class RtpSessionControlInfo;
class RtpCiEnterSession;
class RtpCiSessionEntered;
class RtpCiSenderControl;
class RtpCiSenderStatus;
class RtpCiLeaveSession;
class RtpCiSessionLeft;
class RtpCiCreateSenderModule;
class RtpCiSenderModuleCreated;
class RtpCiDeleteSenderModule;
class RtpCiSenderModuleDeleted;
} // namespace rtp
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address

#include "inet/transportlayer/rtp/RtpSenderControlMessage_m.h" // import inet.transportlayer.rtp.RtpSenderControlMessage

#include "inet/transportlayer/rtp/RtpSenderStatusMessage_m.h" // import inet.transportlayer.rtp.RtpSenderStatusMessage


namespace inet {
namespace rtp {

/**
 * Enum generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:32</tt> by nedtool.
 * <pre>
 * //
 * // An enumeration to distinguish the different functions of the
 * // RtpInterfacePacket.
 * //
 * enum RtpIfpType
 * {
 *     RTP_IFP_ENTER_SESSION = 1;
 *     RTP_IFP_SESSION_ENTERED = 2;
 *     RTP_IFP_CREATE_SENDER_MODULE = 3;
 *     RTP_IFP_SENDER_MODULE_CREATED = 4;
 *     RTP_IFP_DELETE_SENDER_MODULE = 5;
 *     RTP_IFP_SENDER_MODULE_DELETED = 6;
 *     RTP_IFP_SENDER_CONTROL = 7;
 *     RTP_IFP_SENDER_STATUS = 8;
 *     RTP_IFP_LEAVE_SESSION = 9;
 *     RTP_IFP_SESSION_LEFT = 10;
 * }
 * 
 * //
 * // The next classes are used for communication between an ~RtpApplication
 * // and an RTPLayer module. Its offers functionality for starting and stopping of an
 * // rtp session, transmission of files and feedback about the success of the
 * // operations.
 * </pre>
 */
enum RtpIfpType {
    RTP_IFP_ENTER_SESSION = 1,
    RTP_IFP_SESSION_ENTERED = 2,
    RTP_IFP_CREATE_SENDER_MODULE = 3,
    RTP_IFP_SENDER_MODULE_CREATED = 4,
    RTP_IFP_DELETE_SENDER_MODULE = 5,
    RTP_IFP_SENDER_MODULE_DELETED = 6,
    RTP_IFP_SENDER_CONTROL = 7,
    RTP_IFP_SENDER_STATUS = 8,
    RTP_IFP_LEAVE_SESSION = 9,
    RTP_IFP_SESSION_LEFT = 10
};

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:52</tt> by nedtool.
 * <pre>
 * message RtpControlMsg
 * {
 * }
 * </pre>
 */
class INET_API RtpControlMsg : public ::omnetpp::cMessage
{
  protected:

  private:
    void copy(const RtpControlMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpControlMsg&);

  public:
    RtpControlMsg(const char *name=nullptr, short kind=0);
    RtpControlMsg(const RtpControlMsg& other);
    virtual ~RtpControlMsg();
    RtpControlMsg& operator=(const RtpControlMsg& other);
    virtual RtpControlMsg *dup() const override {return new RtpControlMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpControlMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpControlMsg& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:57</tt> by nedtool.
 * <pre>
 * // base class
 * class RtpControlInfo extends cObject
 * {
 *     RtpIfpType type;
 * }
 * </pre>
 */
class INET_API RtpControlInfo : public ::omnetpp::cObject
{
  protected:
    inet::rtp::RtpIfpType type = static_cast<inet::rtp::RtpIfpType>(-1);

  private:
    void copy(const RtpControlInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpControlInfo&);

  public:
    RtpControlInfo();
    RtpControlInfo(const RtpControlInfo& other);
    virtual ~RtpControlInfo();
    RtpControlInfo& operator=(const RtpControlInfo& other);
    virtual RtpControlInfo *dup() const override {return new RtpControlInfo(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::rtp::RtpIfpType getType() const;
    virtual void setType(inet::rtp::RtpIfpType type);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpControlInfo& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpControlInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:63</tt> by nedtool.
 * <pre>
 * // base class
 * class RtpSessionControlInfo extends RtpControlInfo
 * {
 *     uint32 ssrc;
 * }
 * </pre>
 */
class INET_API RtpSessionControlInfo : public ::inet::rtp::RtpControlInfo
{
  protected:
    uint32_t ssrc = 0;

  private:
    void copy(const RtpSessionControlInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpSessionControlInfo&);

  public:
    RtpSessionControlInfo();
    RtpSessionControlInfo(const RtpSessionControlInfo& other);
    virtual ~RtpSessionControlInfo();
    RtpSessionControlInfo& operator=(const RtpSessionControlInfo& other);
    virtual RtpSessionControlInfo *dup() const override {return new RtpSessionControlInfo(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual uint32_t getSsrc() const;
    virtual void setSsrc(uint32_t ssrc);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpSessionControlInfo& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpSessionControlInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:70</tt> by nedtool.
 * <pre>
 * // App to ~Rtp
 * class RtpCiEnterSession extends RtpControlInfo
 * {
 *     type = RTP_IFP_ENTER_SESSION;
 *     string commonName;
 *     string profileName;
 *     int bandwidth;
 *     Ipv4Address destinationAddress;
 *     int port;
 * }
 * </pre>
 */
class INET_API RtpCiEnterSession : public ::inet::rtp::RtpControlInfo
{
  protected:
    omnetpp::opp_string commonName;
    omnetpp::opp_string profileName;
    int bandwidth = 0;
    Ipv4Address destinationAddress;
    int port = 0;

  private:
    void copy(const RtpCiEnterSession& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiEnterSession&);

  public:
    RtpCiEnterSession();
    RtpCiEnterSession(const RtpCiEnterSession& other);
    virtual ~RtpCiEnterSession();
    RtpCiEnterSession& operator=(const RtpCiEnterSession& other);
    virtual RtpCiEnterSession *dup() const override {return new RtpCiEnterSession(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getCommonName() const;
    virtual void setCommonName(const char * commonName);
    virtual const char * getProfileName() const;
    virtual void setProfileName(const char * profileName);
    virtual int getBandwidth() const;
    virtual void setBandwidth(int bandwidth);
    virtual const Ipv4Address& getDestinationAddress() const;
    virtual Ipv4Address& getDestinationAddressForUpdate() { return const_cast<Ipv4Address&>(const_cast<RtpCiEnterSession*>(this)->getDestinationAddress());}
    virtual void setDestinationAddress(const Ipv4Address& destinationAddress);
    virtual int getPort() const;
    virtual void setPort(int port);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiEnterSession& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiEnterSession& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:81</tt> by nedtool.
 * <pre>
 * // ~Rtp to App
 * class RtpCiSessionEntered extends RtpSessionControlInfo
 * {
 *     type = RTP_IFP_SESSION_ENTERED;
 * }
 * </pre>
 */
class INET_API RtpCiSessionEntered : public ::inet::rtp::RtpSessionControlInfo
{
  protected:

  private:
    void copy(const RtpCiSessionEntered& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiSessionEntered&);

  public:
    RtpCiSessionEntered();
    RtpCiSessionEntered(const RtpCiSessionEntered& other);
    virtual ~RtpCiSessionEntered();
    RtpCiSessionEntered& operator=(const RtpCiSessionEntered& other);
    virtual RtpCiSessionEntered *dup() const override {return new RtpCiSessionEntered(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiSessionEntered& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiSessionEntered& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:87</tt> by nedtool.
 * <pre>
 * // App to ~Rtp
 * class RtpCiSenderControl extends RtpSessionControlInfo
 * {
 *     type = RTP_IFP_SENDER_CONTROL;
 *     // from ~RtpSenderControlMessage:
 *     RtpSenderControlMessageCommands command;
 *     float commandParameter1;
 *     float commandParameter2;
 * }
 * </pre>
 */
class INET_API RtpCiSenderControl : public ::inet::rtp::RtpSessionControlInfo
{
  protected:
    inet::rtp::RtpSenderControlMessageCommands command = static_cast<inet::rtp::RtpSenderControlMessageCommands>(-1);
    float commandParameter1 = 0;
    float commandParameter2 = 0;

  private:
    void copy(const RtpCiSenderControl& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiSenderControl&);

  public:
    RtpCiSenderControl();
    RtpCiSenderControl(const RtpCiSenderControl& other);
    virtual ~RtpCiSenderControl();
    RtpCiSenderControl& operator=(const RtpCiSenderControl& other);
    virtual RtpCiSenderControl *dup() const override {return new RtpCiSenderControl(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::rtp::RtpSenderControlMessageCommands getCommand() const;
    virtual void setCommand(inet::rtp::RtpSenderControlMessageCommands command);
    virtual float getCommandParameter1() const;
    virtual void setCommandParameter1(float commandParameter1);
    virtual float getCommandParameter2() const;
    virtual void setCommandParameter2(float commandParameter2);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiSenderControl& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiSenderControl& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:97</tt> by nedtool.
 * <pre>
 * // ~Rtp to App
 * class RtpCiSenderStatus extends RtpSessionControlInfo
 * {
 *     type = RTP_IFP_SENDER_STATUS;
 *     // from ~RtpSenderStatusMessage:
 *     RtpSenderStatus status;
 *     uint32 timeStamp;
 * }
 * </pre>
 */
class INET_API RtpCiSenderStatus : public ::inet::rtp::RtpSessionControlInfo
{
  protected:
    inet::rtp::RtpSenderStatus status = static_cast<inet::rtp::RtpSenderStatus>(-1);
    uint32_t timeStamp = 0;

  private:
    void copy(const RtpCiSenderStatus& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiSenderStatus&);

  public:
    RtpCiSenderStatus();
    RtpCiSenderStatus(const RtpCiSenderStatus& other);
    virtual ~RtpCiSenderStatus();
    RtpCiSenderStatus& operator=(const RtpCiSenderStatus& other);
    virtual RtpCiSenderStatus *dup() const override {return new RtpCiSenderStatus(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::rtp::RtpSenderStatus getStatus() const;
    virtual void setStatus(inet::rtp::RtpSenderStatus status);
    virtual uint32_t getTimeStamp() const;
    virtual void setTimeStamp(uint32_t timeStamp);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiSenderStatus& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiSenderStatus& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:106</tt> by nedtool.
 * <pre>
 * // App to ~Rtp
 * class RtpCiLeaveSession extends RtpControlInfo
 * {
 *     type = RTP_IFP_LEAVE_SESSION;
 *     // TODO do I need any sesson identifier?
 * }
 * </pre>
 */
class INET_API RtpCiLeaveSession : public ::inet::rtp::RtpControlInfo
{
  protected:

  private:
    void copy(const RtpCiLeaveSession& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiLeaveSession&);

  public:
    RtpCiLeaveSession();
    RtpCiLeaveSession(const RtpCiLeaveSession& other);
    virtual ~RtpCiLeaveSession();
    RtpCiLeaveSession& operator=(const RtpCiLeaveSession& other);
    virtual RtpCiLeaveSession *dup() const override {return new RtpCiLeaveSession(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiLeaveSession& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiLeaveSession& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:113</tt> by nedtool.
 * <pre>
 * // ~Rtp to App
 * class RtpCiSessionLeft extends RtpControlInfo
 * {
 *     type = RTP_IFP_SESSION_LEFT;
 *     // TODO do I need any sesson identifier?
 * }
 * </pre>
 */
class INET_API RtpCiSessionLeft : public ::inet::rtp::RtpControlInfo
{
  protected:

  private:
    void copy(const RtpCiSessionLeft& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiSessionLeft&);

  public:
    RtpCiSessionLeft();
    RtpCiSessionLeft(const RtpCiSessionLeft& other);
    virtual ~RtpCiSessionLeft();
    RtpCiSessionLeft& operator=(const RtpCiSessionLeft& other);
    virtual RtpCiSessionLeft *dup() const override {return new RtpCiSessionLeft(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiSessionLeft& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiSessionLeft& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:120</tt> by nedtool.
 * <pre>
 * // App to ~Rtp
 * class RtpCiCreateSenderModule extends RtpSessionControlInfo
 * {
 *     type = RTP_IFP_CREATE_SENDER_MODULE;
 *     int payloadType;
 *     string fileName;
 * }
 * </pre>
 */
class INET_API RtpCiCreateSenderModule : public ::inet::rtp::RtpSessionControlInfo
{
  protected:
    int payloadType = 0;
    omnetpp::opp_string fileName;

  private:
    void copy(const RtpCiCreateSenderModule& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiCreateSenderModule&);

  public:
    RtpCiCreateSenderModule();
    RtpCiCreateSenderModule(const RtpCiCreateSenderModule& other);
    virtual ~RtpCiCreateSenderModule();
    RtpCiCreateSenderModule& operator=(const RtpCiCreateSenderModule& other);
    virtual RtpCiCreateSenderModule *dup() const override {return new RtpCiCreateSenderModule(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getPayloadType() const;
    virtual void setPayloadType(int payloadType);
    virtual const char * getFileName() const;
    virtual void setFileName(const char * fileName);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiCreateSenderModule& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiCreateSenderModule& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:128</tt> by nedtool.
 * <pre>
 * // ~Rtp to App
 * class RtpCiSenderModuleCreated extends RtpSessionControlInfo
 * {
 *     type = RTP_IFP_SENDER_MODULE_CREATED;
 * }
 * </pre>
 */
class INET_API RtpCiSenderModuleCreated : public ::inet::rtp::RtpSessionControlInfo
{
  protected:

  private:
    void copy(const RtpCiSenderModuleCreated& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiSenderModuleCreated&);

  public:
    RtpCiSenderModuleCreated();
    RtpCiSenderModuleCreated(const RtpCiSenderModuleCreated& other);
    virtual ~RtpCiSenderModuleCreated();
    RtpCiSenderModuleCreated& operator=(const RtpCiSenderModuleCreated& other);
    virtual RtpCiSenderModuleCreated *dup() const override {return new RtpCiSenderModuleCreated(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiSenderModuleCreated& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiSenderModuleCreated& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:134</tt> by nedtool.
 * <pre>
 * // App to ~Rtp
 * class RtpCiDeleteSenderModule extends RtpSessionControlInfo
 * {
 *     type = RTP_IFP_DELETE_SENDER_MODULE;
 * }
 * </pre>
 */
class INET_API RtpCiDeleteSenderModule : public ::inet::rtp::RtpSessionControlInfo
{
  protected:

  private:
    void copy(const RtpCiDeleteSenderModule& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiDeleteSenderModule&);

  public:
    RtpCiDeleteSenderModule();
    RtpCiDeleteSenderModule(const RtpCiDeleteSenderModule& other);
    virtual ~RtpCiDeleteSenderModule();
    RtpCiDeleteSenderModule& operator=(const RtpCiDeleteSenderModule& other);
    virtual RtpCiDeleteSenderModule *dup() const override {return new RtpCiDeleteSenderModule(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiDeleteSenderModule& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiDeleteSenderModule& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtpInterfacePacket.msg:140</tt> by nedtool.
 * <pre>
 * // ~Rtp to App
 * class RtpCiSenderModuleDeleted extends RtpSessionControlInfo
 * {
 *     type = RTP_IFP_SENDER_MODULE_DELETED;
 * }
 * </pre>
 */
class INET_API RtpCiSenderModuleDeleted : public ::inet::rtp::RtpSessionControlInfo
{
  protected:

  private:
    void copy(const RtpCiSenderModuleDeleted& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RtpCiSenderModuleDeleted&);

  public:
    RtpCiSenderModuleDeleted();
    RtpCiSenderModuleDeleted(const RtpCiSenderModuleDeleted& other);
    virtual ~RtpCiSenderModuleDeleted();
    RtpCiSenderModuleDeleted& operator=(const RtpCiSenderModuleDeleted& other);
    virtual RtpCiSenderModuleDeleted *dup() const override {return new RtpCiSenderModuleDeleted(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtpCiSenderModuleDeleted& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtpCiSenderModuleDeleted& obj) {obj.parsimUnpack(b);}

} // namespace rtp
} // namespace inet

#endif // ifndef __INET__RTP_RTPINTERFACEPACKET_M_H
