//
// Generated file, do not edit! Created by nedtool 5.5 from inet/applications/udpapp/InfoFL.msg.
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
#include "InfoFL_m.h"

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

Register_Class(InfoFL)

InfoFL::InfoFL() : ::inet::FieldsChunk()
{
}

InfoFL::InfoFL(const InfoFL& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

InfoFL::~InfoFL()
{
}

InfoFL& InfoFL::operator=(const InfoFL& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void InfoFL::copy(const InfoFL& other)
{
    this->sequenceNumber = other.sequenceNumber;
    this->sno = other.sno;
    this->payloadTimestamp = other.payloadTimestamp;
    this->globalInfo = other.globalInfo;
    this->srcId = other.srcId;
    this->x_pos = other.x_pos;
    this->y_pos = other.y_pos;
}

void InfoFL::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->sno);
    doParsimPacking(b,this->payloadTimestamp);
    doParsimPacking(b,this->globalInfo);
    doParsimPacking(b,this->srcId);
    doParsimPacking(b,this->x_pos);
    doParsimPacking(b,this->y_pos);
}

void InfoFL::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->sno);
    doParsimUnpacking(b,this->payloadTimestamp);
    doParsimUnpacking(b,this->globalInfo);
    doParsimUnpacking(b,this->srcId);
    doParsimUnpacking(b,this->x_pos);
    doParsimUnpacking(b,this->y_pos);
}

uint32_t InfoFL::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void InfoFL::setSequenceNumber(uint32_t sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

unsigned int InfoFL::getSno() const
{
    return this->sno;
}

void InfoFL::setSno(unsigned int sno)
{
    handleChange();
    this->sno = sno;
}

omnetpp::simtime_t InfoFL::getPayloadTimestamp() const
{
    return this->payloadTimestamp;
}

void InfoFL::setPayloadTimestamp(omnetpp::simtime_t payloadTimestamp)
{
    handleChange();
    this->payloadTimestamp = payloadTimestamp;
}

double InfoFL::getGlobalInfo() const
{
    return this->globalInfo;
}

void InfoFL::setGlobalInfo(double globalInfo)
{
    handleChange();
    this->globalInfo = globalInfo;
}

int InfoFL::getSrcId() const
{
    return this->srcId;
}

void InfoFL::setSrcId(int srcId)
{
    handleChange();
    this->srcId = srcId;
}

double InfoFL::getX_pos() const
{
    return this->x_pos;
}

void InfoFL::setX_pos(double x_pos)
{
    handleChange();
    this->x_pos = x_pos;
}

double InfoFL::getY_pos() const
{
    return this->y_pos;
}

void InfoFL::setY_pos(double y_pos)
{
    handleChange();
    this->y_pos = y_pos;
}

class InfoFLDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_sequenceNumber,
        FIELD_sno,
        FIELD_payloadTimestamp,
        FIELD_globalInfo,
        FIELD_srcId,
        FIELD_x_pos,
        FIELD_y_pos,
    };
  public:
    InfoFLDescriptor();
    virtual ~InfoFLDescriptor();

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

Register_ClassDescriptor(InfoFLDescriptor)

InfoFLDescriptor::InfoFLDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(InfoFL)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

InfoFLDescriptor::~InfoFLDescriptor()
{
    delete[] propertynames;
}

bool InfoFLDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<InfoFL *>(obj)!=nullptr;
}

const char **InfoFLDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *InfoFLDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int InfoFLDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int InfoFLDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_sno
        0,    // FIELD_payloadTimestamp
        FD_ISEDITABLE,    // FIELD_globalInfo
        FD_ISEDITABLE,    // FIELD_srcId
        FD_ISEDITABLE,    // FIELD_x_pos
        FD_ISEDITABLE,    // FIELD_y_pos
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *InfoFLDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sequenceNumber",
        "sno",
        "payloadTimestamp",
        "globalInfo",
        "srcId",
        "x_pos",
        "y_pos",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int InfoFLDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sequenceNumber") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sno") == 0) return base+1;
    if (fieldName[0] == 'p' && strcmp(fieldName, "payloadTimestamp") == 0) return base+2;
    if (fieldName[0] == 'g' && strcmp(fieldName, "globalInfo") == 0) return base+3;
    if (fieldName[0] == 's' && strcmp(fieldName, "srcId") == 0) return base+4;
    if (fieldName[0] == 'x' && strcmp(fieldName, "x_pos") == 0) return base+5;
    if (fieldName[0] == 'y' && strcmp(fieldName, "y_pos") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *InfoFLDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32_t",    // FIELD_sequenceNumber
        "unsigned int",    // FIELD_sno
        "omnetpp::simtime_t",    // FIELD_payloadTimestamp
        "double",    // FIELD_globalInfo
        "int",    // FIELD_srcId
        "double",    // FIELD_x_pos
        "double",    // FIELD_y_pos
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **InfoFLDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *InfoFLDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int InfoFLDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    InfoFL *pp = (InfoFL *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *InfoFLDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    InfoFL *pp = (InfoFL *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string InfoFLDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    InfoFL *pp = (InfoFL *)object; (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return ulong2string(pp->getSequenceNumber());
        case FIELD_sno: return ulong2string(pp->getSno());
        case FIELD_payloadTimestamp: return simtime2string(pp->getPayloadTimestamp());
        case FIELD_globalInfo: return double2string(pp->getGlobalInfo());
        case FIELD_srcId: return long2string(pp->getSrcId());
        case FIELD_x_pos: return double2string(pp->getX_pos());
        case FIELD_y_pos: return double2string(pp->getY_pos());
        default: return "";
    }
}

bool InfoFLDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    InfoFL *pp = (InfoFL *)object; (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2ulong(value)); return true;
        case FIELD_sno: pp->setSno(string2ulong(value)); return true;
        case FIELD_globalInfo: pp->setGlobalInfo(string2double(value)); return true;
        case FIELD_srcId: pp->setSrcId(string2long(value)); return true;
        case FIELD_x_pos: pp->setX_pos(string2double(value)); return true;
        case FIELD_y_pos: pp->setY_pos(string2double(value)); return true;
        default: return false;
    }
}

const char *InfoFLDescriptor::getFieldStructName(int field) const
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

void *InfoFLDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    InfoFL *pp = (InfoFL *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

