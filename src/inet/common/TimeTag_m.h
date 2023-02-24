//
// Generated file, do not edit! Created by nedtool 5.5 from inet/common/TimeTag.msg.
//

#ifndef __INET_TIMETAG_M_H
#define __INET_TIMETAG_M_H

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

class CreationTimeTag;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/TagBase_m.h" // import inet.common.TagBase

#include "inet/common/Units_m.h" // import inet.common.Units


namespace inet {

/**
 * Class generated from <tt>inet/common/TimeTag.msg:12</tt> by nedtool.
 * <pre>
 * class CreationTimeTag extends TagBase
 * {
 *     simtime_t creationTime;
 * }
 * </pre>
 */
class INET_API CreationTimeTag : public ::inet::TagBase
{
  protected:
    omnetpp::simtime_t creationTime = SIMTIME_ZERO;

  private:
    void copy(const CreationTimeTag& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CreationTimeTag&);

  public:
    CreationTimeTag();
    CreationTimeTag(const CreationTimeTag& other);
    virtual ~CreationTimeTag();
    CreationTimeTag& operator=(const CreationTimeTag& other);
    virtual CreationTimeTag *dup() const override {return new CreationTimeTag(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual omnetpp::simtime_t getCreationTime() const;
    virtual void setCreationTime(omnetpp::simtime_t creationTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CreationTimeTag& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CreationTimeTag& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_TIMETAG_M_H

