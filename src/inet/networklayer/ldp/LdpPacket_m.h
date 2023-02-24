//
// Generated file, do not edit! Created by nedtool 5.5 from inet/networklayer/ldp/LdpPacket.msg.
//

#ifndef __INET_LDPPACKET_M_H
#define __INET_LDPPACKET_M_H

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

struct FecTlv;
class LdpPacket;
class LdpLabelMapping;
class LdpLabelRequest;
class LdpHello;
class LdpNotify;
class LdpIni;
class LdpAddress;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address


namespace inet {

/**
 * Enum generated from <tt>inet/networklayer/ldp/LdpPacket.msg:24</tt> by nedtool.
 * <pre>
 * //
 * // LDP message types
 * //
 * enum LdpMessageTypes
 * {
 *     NOTIFICATION = 10;
 *     HELLO = 11;
 *     INITIALIZATION = 12;
 *     KEEP_ALIVE = 13;
 *     ADDRESS = 14;
 *     ADDRESS_WITHDRAW = 15;
 *     LABEL_MAPPING = 16;
 *     LABEL_REQUEST = 17;
 *     LABEL_WITHDRAW = 18;
 *     LABEL_RELEASE = 19;
 *     UNKNOWN = 20;
 * }
 * </pre>
 */
enum LdpMessageTypes {
    NOTIFICATION = 10,
    HELLO = 11,
    INITIALIZATION = 12,
    KEEP_ALIVE = 13,
    ADDRESS = 14,
    ADDRESS_WITHDRAW = 15,
    LABEL_MAPPING = 16,
    LABEL_REQUEST = 17,
    LABEL_WITHDRAW = 18,
    LABEL_RELEASE = 19,
    UNKNOWN = 20
};

/**
 * Enum generated from <tt>inet/networklayer/ldp/LdpPacket.msg:40</tt> by nedtool.
 * <pre>
 * enum LdpStatusTypes
 * {
 *     NO_ROUTE = 13;
 * }
 * </pre>
 */
enum LdpStatusTypes {
    NO_ROUTE = 13
};

/**
 * Struct generated from inet/networklayer/ldp/LdpPacket.msg:46 by nedtool.
 */
struct INET_API FecTlv
{
    FecTlv();
    Ipv4Address addr;
    int length;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const FecTlv& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, FecTlv& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const FecTlv& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, FecTlv& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>inet/networklayer/ldp/LdpPacket.msg:55</tt> by nedtool.
 * <pre>
 * //
 * // Base class for LDP packets
 * //
 * class LdpPacket extends FieldsChunk
 * {
 *     int type;
 *     Ipv4Address senderAddress;
 *     Ipv4Address receiverAddress;
 * }
 * </pre>
 */
class INET_API LdpPacket : public ::inet::FieldsChunk
{
  protected:
    int type = 0;
    Ipv4Address senderAddress;
    Ipv4Address receiverAddress;

  private:
    void copy(const LdpPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LdpPacket&);

  public:
    LdpPacket();
    LdpPacket(const LdpPacket& other);
    virtual ~LdpPacket();
    LdpPacket& operator=(const LdpPacket& other);
    virtual LdpPacket *dup() const override {return new LdpPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type);
    virtual const Ipv4Address& getSenderAddress() const;
    virtual Ipv4Address& getSenderAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<LdpPacket*>(this)->getSenderAddress());}
    virtual void setSenderAddress(const Ipv4Address& senderAddress);
    virtual const Ipv4Address& getReceiverAddress() const;
    virtual Ipv4Address& getReceiverAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<LdpPacket*>(this)->getReceiverAddress());}
    virtual void setReceiverAddress(const Ipv4Address& receiverAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LdpPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LdpPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ldp/LdpPacket.msg:66</tt> by nedtool.
 * <pre>
 * //
 * // LDP Label Mapping Message
 * //
 * class LdpLabelMapping extends LdpPacket
 * {
 *     FecTlv fec;
 *     int label;
 * }
 * </pre>
 */
class INET_API LdpLabelMapping : public ::inet::LdpPacket
{
  protected:
    FecTlv fec;
    int label = 0;

  private:
    void copy(const LdpLabelMapping& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LdpLabelMapping&);

  public:
    LdpLabelMapping();
    LdpLabelMapping(const LdpLabelMapping& other);
    virtual ~LdpLabelMapping();
    LdpLabelMapping& operator=(const LdpLabelMapping& other);
    virtual LdpLabelMapping *dup() const override {return new LdpLabelMapping(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const FecTlv& getFec() const;
    virtual FecTlv& getFecForUpdate() { handleChange();return const_cast<FecTlv&>(const_cast<LdpLabelMapping*>(this)->getFec());}
    virtual void setFec(const FecTlv& fec);
    virtual int getLabel() const;
    virtual void setLabel(int label);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LdpLabelMapping& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LdpLabelMapping& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ldp/LdpPacket.msg:75</tt> by nedtool.
 * <pre>
 * //
 * // LDP Label Request Message
 * //
 * class LdpLabelRequest extends LdpPacket
 * {
 *     FecTlv fec;
 * }
 * </pre>
 */
class INET_API LdpLabelRequest : public ::inet::LdpPacket
{
  protected:
    FecTlv fec;

  private:
    void copy(const LdpLabelRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LdpLabelRequest&);

  public:
    LdpLabelRequest();
    LdpLabelRequest(const LdpLabelRequest& other);
    virtual ~LdpLabelRequest();
    LdpLabelRequest& operator=(const LdpLabelRequest& other);
    virtual LdpLabelRequest *dup() const override {return new LdpLabelRequest(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const FecTlv& getFec() const;
    virtual FecTlv& getFecForUpdate() { handleChange();return const_cast<FecTlv&>(const_cast<LdpLabelRequest*>(this)->getFec());}
    virtual void setFec(const FecTlv& fec);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LdpLabelRequest& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LdpLabelRequest& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ldp/LdpPacket.msg:84</tt> by nedtool.
 * <pre>
 * //
 * // LDP Hello Message
 * //
 * class LdpHello extends LdpPacket
 * {
 *     double holdTime;
 *     bool tbit;
 *     bool rbit;
 * }
 * </pre>
 */
class INET_API LdpHello : public ::inet::LdpPacket
{
  protected:
    double holdTime = 0;
    bool tbit = false;
    bool rbit = false;

  private:
    void copy(const LdpHello& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LdpHello&);

  public:
    LdpHello();
    LdpHello(const LdpHello& other);
    virtual ~LdpHello();
    LdpHello& operator=(const LdpHello& other);
    virtual LdpHello *dup() const override {return new LdpHello(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getHoldTime() const;
    virtual void setHoldTime(double holdTime);
    virtual bool getTbit() const;
    virtual void setTbit(bool tbit);
    virtual bool getRbit() const;
    virtual void setRbit(bool rbit);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LdpHello& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LdpHello& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ldp/LdpPacket.msg:94</tt> by nedtool.
 * <pre>
 * //
 * // LDP notification message
 * //
 * class LdpNotify extends LdpPacket
 * {
 *     int status;
 *     FecTlv fec;
 * }
 * </pre>
 */
class INET_API LdpNotify : public ::inet::LdpPacket
{
  protected:
    int status = 0;
    FecTlv fec;

  private:
    void copy(const LdpNotify& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LdpNotify&);

  public:
    LdpNotify();
    LdpNotify(const LdpNotify& other);
    virtual ~LdpNotify();
    LdpNotify& operator=(const LdpNotify& other);
    virtual LdpNotify *dup() const override {return new LdpNotify(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getStatus() const;
    virtual void setStatus(int status);
    virtual const FecTlv& getFec() const;
    virtual FecTlv& getFecForUpdate() { handleChange();return const_cast<FecTlv&>(const_cast<LdpNotify*>(this)->getFec());}
    virtual void setFec(const FecTlv& fec);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LdpNotify& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LdpNotify& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ldp/LdpPacket.msg:104</tt> by nedtool.
 * <pre>
 * //
 * // LDP Ini Message
 * //
 * //# FIXME currently unused
 * class LdpIni extends LdpPacket
 * {
 *     double keepAliveTime;
 *     bool abit;
 *     bool dbit;
 *     int pvLim;
 *     string receiverLDPIdentifier;
 * }
 * </pre>
 */
class INET_API LdpIni : public ::inet::LdpPacket
{
  protected:
    double keepAliveTime = 0;
    bool abit = false;
    bool dbit = false;
    int pvLim = 0;
    omnetpp::opp_string receiverLDPIdentifier;

  private:
    void copy(const LdpIni& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LdpIni&);

  public:
    LdpIni();
    LdpIni(const LdpIni& other);
    virtual ~LdpIni();
    LdpIni& operator=(const LdpIni& other);
    virtual LdpIni *dup() const override {return new LdpIni(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual double getKeepAliveTime() const;
    virtual void setKeepAliveTime(double keepAliveTime);
    virtual bool getAbit() const;
    virtual void setAbit(bool abit);
    virtual bool getDbit() const;
    virtual void setDbit(bool dbit);
    virtual int getPvLim() const;
    virtual void setPvLim(int pvLim);
    virtual const char * getReceiverLDPIdentifier() const;
    virtual void setReceiverLDPIdentifier(const char * receiverLDPIdentifier);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LdpIni& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LdpIni& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ldp/LdpPacket.msg:117</tt> by nedtool.
 * <pre>
 * //
 * // LDP Address Message
 * //
 * //# FIXME currently unused
 * class LdpAddress extends LdpPacket
 * {
 *     bool isWithdraw;
 *     string family;
 *     string addresses[];
 * }
 * </pre>
 */
class INET_API LdpAddress : public ::inet::LdpPacket
{
  protected:
    bool isWithdraw_ = false;
    omnetpp::opp_string family;
    omnetpp::opp_string *addresses = nullptr;
    size_t addresses_arraysize = 0;

  private:
    void copy(const LdpAddress& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LdpAddress&);

  public:
    LdpAddress();
    LdpAddress(const LdpAddress& other);
    virtual ~LdpAddress();
    LdpAddress& operator=(const LdpAddress& other);
    virtual LdpAddress *dup() const override {return new LdpAddress(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual bool isWithdraw() const;
    virtual void setIsWithdraw(bool isWithdraw);
    virtual const char * getFamily() const;
    virtual void setFamily(const char * family);
    virtual void setAddressesArraySize(size_t size);
    virtual size_t getAddressesArraySize() const;
    virtual const char * getAddresses(size_t k) const;
    virtual void setAddresses(size_t k, const char * addresses);
    virtual void insertAddresses(const char * addresses);
    virtual void insertAddresses(size_t k, const char * addresses);
    virtual void eraseAddresses(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LdpAddress& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LdpAddress& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_LDPPACKET_M_H
