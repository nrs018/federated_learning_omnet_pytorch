//
// Generated file, do not edit! Created by nedtool 5.5 from inet/networklayer/probabilistic/ProbabilisticBroadcastHeader.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include "ProbabilisticBroadcastHeader_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(ProbabilisticBroadcastHeader)

ProbabilisticBroadcastHeader::ProbabilisticBroadcastHeader() : ::inet::NetworkHeaderBase()
{
}

ProbabilisticBroadcastHeader::ProbabilisticBroadcastHeader(const ProbabilisticBroadcastHeader& other) : ::inet::NetworkHeaderBase(other)
{
    copy(other);
}

ProbabilisticBroadcastHeader::~ProbabilisticBroadcastHeader()
{
}

ProbabilisticBroadcastHeader& ProbabilisticBroadcastHeader::operator=(const ProbabilisticBroadcastHeader& other)
{
    if (this == &other) return *this;
    ::inet::NetworkHeaderBase::operator=(other);
    copy(other);
    return *this;
}

void ProbabilisticBroadcastHeader::copy(const ProbabilisticBroadcastHeader& other)
{
    this->srcAddr = other.srcAddr;
    this->destAddr = other.destAddr;
    this->id = other.id;
    this->nbHops = other.nbHops;
    this->protocolId = other.protocolId;
    this->appTtl = other.appTtl;
    this->initialSrcAddr = other.initialSrcAddr;
    this->finalDestAddr = other.finalDestAddr;
    this->payloadLengthField = other.payloadLengthField;
}

void ProbabilisticBroadcastHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::NetworkHeaderBase::parsimPack(b);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->id);
    doParsimPacking(b,this->nbHops);
    doParsimPacking(b,this->protocolId);
    doParsimPacking(b,this->appTtl);
    doParsimPacking(b,this->initialSrcAddr);
    doParsimPacking(b,this->finalDestAddr);
    doParsimPacking(b,this->payloadLengthField);
}

void ProbabilisticBroadcastHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::NetworkHeaderBase::parsimUnpack(b);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->id);
    doParsimUnpacking(b,this->nbHops);
    doParsimUnpacking(b,this->protocolId);
    doParsimUnpacking(b,this->appTtl);
    doParsimUnpacking(b,this->initialSrcAddr);
    doParsimUnpacking(b,this->finalDestAddr);
    doParsimUnpacking(b,this->payloadLengthField);
}

const L3Address& ProbabilisticBroadcastHeader::getSrcAddr() const
{
    return this->srcAddr;
}

void ProbabilisticBroadcastHeader::setSrcAddr(const L3Address& srcAddr)
{
    handleChange();
    this->srcAddr = srcAddr;
}

const L3Address& ProbabilisticBroadcastHeader::getDestAddr() const
{
    return this->destAddr;
}

void ProbabilisticBroadcastHeader::setDestAddr(const L3Address& destAddr)
{
    handleChange();
    this->destAddr = destAddr;
}

long ProbabilisticBroadcastHeader::getId() const
{
    return this->id;
}

void ProbabilisticBroadcastHeader::setId(long id)
{
    handleChange();
    this->id = id;
}

int ProbabilisticBroadcastHeader::getNbHops() const
{
    return this->nbHops;
}

void ProbabilisticBroadcastHeader::setNbHops(int nbHops)
{
    handleChange();
    this->nbHops = nbHops;
}

inet::IpProtocolId ProbabilisticBroadcastHeader::getProtocolId() const
{
    return this->protocolId;
}

void ProbabilisticBroadcastHeader::setProtocolId(inet::IpProtocolId protocolId)
{
    handleChange();
    this->protocolId = protocolId;
}

omnetpp::simtime_t ProbabilisticBroadcastHeader::getAppTtl() const
{
    return this->appTtl;
}

void ProbabilisticBroadcastHeader::setAppTtl(omnetpp::simtime_t appTtl)
{
    handleChange();
    this->appTtl = appTtl;
}

const L3Address& ProbabilisticBroadcastHeader::getInitialSrcAddr() const
{
    return this->initialSrcAddr;
}

void ProbabilisticBroadcastHeader::setInitialSrcAddr(const L3Address& initialSrcAddr)
{
    handleChange();
    this->initialSrcAddr = initialSrcAddr;
}

const L3Address& ProbabilisticBroadcastHeader::getFinalDestAddr() const
{
    return this->finalDestAddr;
}

void ProbabilisticBroadcastHeader::setFinalDestAddr(const L3Address& finalDestAddr)
{
    handleChange();
    this->finalDestAddr = finalDestAddr;
}

B ProbabilisticBroadcastHeader::getPayloadLengthField() const
{
    return this->payloadLengthField;
}

void ProbabilisticBroadcastHeader::setPayloadLengthField(B payloadLengthField)
{
    handleChange();
    this->payloadLengthField = payloadLengthField;
}

class ProbabilisticBroadcastHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_srcAddr,
        FIELD_destAddr,
        FIELD_id,
        FIELD_nbHops,
        FIELD_protocolId,
        FIELD_appTtl,
        FIELD_initialSrcAddr,
        FIELD_finalDestAddr,
        FIELD_payloadLengthField,
    };
  public:
    ProbabilisticBroadcastHeaderDescriptor();
    virtual ~ProbabilisticBroadcastHeaderDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(ProbabilisticBroadcastHeaderDescriptor)

ProbabilisticBroadcastHeaderDescriptor::ProbabilisticBroadcastHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ProbabilisticBroadcastHeader)), "inet::NetworkHeaderBase")
{
    propertynames = nullptr;
}

ProbabilisticBroadcastHeaderDescriptor::~ProbabilisticBroadcastHeaderDescriptor()
{
    delete[] propertynames;
}

bool ProbabilisticBroadcastHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ProbabilisticBroadcastHeader *>(obj)!=nullptr;
}

const char **ProbabilisticBroadcastHeaderDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ProbabilisticBroadcastHeaderDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ProbabilisticBroadcastHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int ProbabilisticBroadcastHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_srcAddr
        0,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_id
        FD_ISEDITABLE,    // FIELD_nbHops
        0,    // FIELD_protocolId
        0,    // FIELD_appTtl
        0,    // FIELD_initialSrcAddr
        0,    // FIELD_finalDestAddr
        FD_ISEDITABLE,    // FIELD_payloadLengthField
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *ProbabilisticBroadcastHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "srcAddr",
        "destAddr",
        "id",
        "nbHops",
        "protocolId",
        "appTtl",
        "initialSrcAddr",
        "finalDestAddr",
        "payloadLengthField",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int ProbabilisticBroadcastHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "srcAddr") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destAddr") == 0) return base+1;
    if (fieldName[0] == 'i' && strcmp(fieldName, "id") == 0) return base+2;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nbHops") == 0) return base+3;
    if (fieldName[0] == 'p' && strcmp(fieldName, "protocolId") == 0) return base+4;
    if (fieldName[0] == 'a' && strcmp(fieldName, "appTtl") == 0) return base+5;
    if (fieldName[0] == 'i' && strcmp(fieldName, "initialSrcAddr") == 0) return base+6;
    if (fieldName[0] == 'f' && strcmp(fieldName, "finalDestAddr") == 0) return base+7;
    if (fieldName[0] == 'p' && strcmp(fieldName, "payloadLengthField") == 0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ProbabilisticBroadcastHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::L3Address",    // FIELD_srcAddr
        "inet::L3Address",    // FIELD_destAddr
        "long",    // FIELD_id
        "int",    // FIELD_nbHops
        "inet::IpProtocolId",    // FIELD_protocolId
        "omnetpp::simtime_t",    // FIELD_appTtl
        "inet::L3Address",    // FIELD_initialSrcAddr
        "inet::L3Address",    // FIELD_finalDestAddr
        "inet::B",    // FIELD_payloadLengthField
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **ProbabilisticBroadcastHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_protocolId: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *ProbabilisticBroadcastHeaderDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_protocolId:
            if (!strcmp(propertyname, "enum")) return "inet::IpProtocolId";
            return nullptr;
        default: return nullptr;
    }
}

int ProbabilisticBroadcastHeaderDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ProbabilisticBroadcastHeader *pp = (ProbabilisticBroadcastHeader *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ProbabilisticBroadcastHeaderDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ProbabilisticBroadcastHeader *pp = (ProbabilisticBroadcastHeader *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ProbabilisticBroadcastHeaderDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ProbabilisticBroadcastHeader *pp = (ProbabilisticBroadcastHeader *)object; (void)pp;
    switch (field) {
        case FIELD_srcAddr: return pp->getSrcAddr().str();
        case FIELD_destAddr: return pp->getDestAddr().str();
        case FIELD_id: return long2string(pp->getId());
        case FIELD_nbHops: return long2string(pp->getNbHops());
        case FIELD_protocolId: return enum2string(pp->getProtocolId(), "inet::IpProtocolId");
        case FIELD_appTtl: return simtime2string(pp->getAppTtl());
        case FIELD_initialSrcAddr: return pp->getInitialSrcAddr().str();
        case FIELD_finalDestAddr: return pp->getFinalDestAddr().str();
        case FIELD_payloadLengthField: return unit2string(pp->getPayloadLengthField());
        default: return "";
    }
}

bool ProbabilisticBroadcastHeaderDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ProbabilisticBroadcastHeader *pp = (ProbabilisticBroadcastHeader *)object; (void)pp;
    switch (field) {
        case FIELD_id: pp->setId(string2long(value)); return true;
        case FIELD_nbHops: pp->setNbHops(string2long(value)); return true;
        case FIELD_payloadLengthField: pp->setPayloadLengthField(B(string2long(value))); return true;
        default: return false;
    }
}

const char *ProbabilisticBroadcastHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *ProbabilisticBroadcastHeaderDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ProbabilisticBroadcastHeader *pp = (ProbabilisticBroadcastHeader *)object; (void)pp;
    switch (field) {
        case FIELD_srcAddr: return toVoidPtr(&pp->getSrcAddr()); break;
        case FIELD_destAddr: return toVoidPtr(&pp->getDestAddr()); break;
        case FIELD_initialSrcAddr: return toVoidPtr(&pp->getInitialSrcAddr()); break;
        case FIELD_finalDestAddr: return toVoidPtr(&pp->getFinalDestAddr()); break;
        default: return nullptr;
    }
}

} // namespace inet

