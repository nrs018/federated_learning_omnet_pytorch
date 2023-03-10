//
// Generated file, do not edit! Created by nedtool 5.5 from lte/common/LteCommonEnum.msg.
//

#ifndef __LTECOMMONENUM_M_H
#define __LTECOMMONENUM_M_H

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



/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:18</tt> by nedtool.
 * <pre>
 * /// Link Directions
 * enum Direction
 * {
 *     DL = 0;
 *     UL = 1;
 *     D2D = 2;
 *     D2D_MULTI = 3;
 *     UNKNOWN_DIRECTION = 4;
 * }
 * </pre>
 */
enum Direction {
    DL = 0,
    UL = 1,
    D2D = 2,
    D2D_MULTI = 3,
    UNKNOWN_DIRECTION = 4
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:24</tt> by nedtool.
 * <pre>
 * /// Modulations
 * enum LteMod
 * {
 *     _QPSK = 0;
 *     _16QAM = 1;
 *     _64QAM = 2;
 * }
 * </pre>
 */
enum LteMod {
    _QPSK = 0,
    _16QAM = 1,
    _64QAM = 2
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:30</tt> by nedtool.
 * <pre>
 * /// Feedback reporting type
 * enum FeedbackType
 * {
 *     ALLBANDS = 0;
 *     PREFERRED = 1;
 *     WIDEBAND = 2;
 * }
 * </pre>
 */
enum FeedbackType {
    ALLBANDS = 0,
    PREFERRED = 1,
    WIDEBAND = 2
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:36</tt> by nedtool.
 * <pre>
 * /// Feedback periodicity
 * enum FbPeriodicity
 * {
 *     PERIODIC = 0;
 *     APERIODIC = 1;
 * }
 * </pre>
 */
enum FbPeriodicity {
    PERIODIC = 0,
    APERIODIC = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:42</tt> by nedtool.
 * <pre>
 * /// Resource allocation type
 * enum RbAllocationType
 * {
 *     TYPE2_DISTRIBUTED = 0;
 *     TYPE2_LOCALIZED = 1;
 * }
 * </pre>
 */
enum RbAllocationType {
    TYPE2_DISTRIBUTED = 0,
    TYPE2_LOCALIZED = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:49</tt> by nedtool.
 * <pre>
 * /// Gate Direction
 * enum GateDirection
 * {
 *     IN_GATE = 0;
 *     OUT_GATE = 1;
 * }
 * </pre>
 */
enum GateDirection {
    IN_GATE = 0,
    OUT_GATE = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:56</tt> by nedtool.
 * <pre>
 * /// Lte Traffic Classes
 * enum LteTrafficClass
 * {
 *     CONVERSATIONAL = 0;
 *     STREAMING = 1;
 *     INTERACTIVE = 2;
 *     BACKGROUND = 3;
 *     UNKNOWN_TRAFFIC_TYPE = 4;
 * }
 * </pre>
 */
enum LteTrafficClass {
    CONVERSATIONAL = 0,
    STREAMING = 1,
    INTERACTIVE = 2,
    BACKGROUND = 3,
    UNKNOWN_TRAFFIC_TYPE = 4
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:62</tt> by nedtool.
 * <pre>
 * /// Scheduler grant type
 * enum GrantType
 * {
 *     FITALL = 0;
 *     FIXED_ = 1;
 *     URGENT = 2;
 *     UNKNOWN_GRANT_TYPE = 3; // Note: FIXED would clash with <windows.h> 
 * }
 * </pre>
 */
enum GrantType {
    FITALL = 0,
    FIXED_ = 1,
    URGENT = 2,
    UNKNOWN_GRANT_TYPE = 3
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:68</tt> by nedtool.
 * <pre>
 * /// Lte RLC Types
 * enum LteRlcType
 * {
 *     TM = 0;
 *     UM = 1;
 *     AM = 2;
 *     UNKNOWN_RLC_TYPE = 3;
 * }
 * </pre>
 */
enum LteRlcType {
    TM = 0,
    UM = 1,
    AM = 2,
    UNKNOWN_RLC_TYPE = 3
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:74</tt> by nedtool.
 * <pre>
 * /// Index for UL transmission map
 * enum UlTransmissionMapTTI
 * {
 *     PREV_TTI = 0;
 *     CURR_TTI = 1;
 * }
 * </pre>
 */
enum UlTransmissionMapTTI {
    PREV_TTI = 0,
    CURR_TTI = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:82</tt> by nedtool.
 * <pre>
 * /// D2D Modes
 * // IM = Infastructure Mode
 * // DM = Direct (D2D) Mode
 * enum LteD2DMode
 * {
 *     IM = 0;
 *     DM = 1;
 * }
 * 
 * ///
 * //      Applications  
 * //
 * </pre>
 */
enum LteD2DMode {
    IM = 0,
    DM = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:91</tt> by nedtool.
 * <pre>
 * enum ApplicationType
 * {
 *     VOIP = 0;
 *     VOD = 1;
 *     WEB = 2;
 *     CBR = 3;
 *     FTP = 4;
 *     GAMING = 5;
 *     FULLBUFFER = 6;
 *     UNKNOWN_APP = 7;
 * }
 * 
 * 
 * //
 * //  Scheduling discipline
 * //
 * </pre>
 */
enum ApplicationType {
    VOIP = 0,
    VOD = 1,
    WEB = 2,
    CBR = 3,
    FTP = 4,
    GAMING = 5,
    FULLBUFFER = 6,
    UNKNOWN_APP = 7
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:108</tt> by nedtool.
 * <pre>
 * enum SchedDiscipline
 * {
 *     DRR = 0;
 *     PF = 1;
 *     MAXCI = 2;
 *     MAXCI_MB = 3;
 *     MAXCI_OPT_MB = 4;
 *     MAXCI_COMP = 5;
 *     ALLOCATOR_BESTFIT = 6;
 *     UNKNOWN_DISCIPLINE = 7;
 * }
 * </pre>
 */
enum SchedDiscipline {
    DRR = 0,
    PF = 1,
    MAXCI = 2,
    MAXCI_MB = 3,
    MAXCI_OPT_MB = 4,
    MAXCI_COMP = 5,
    ALLOCATOR_BESTFIT = 6,
    UNKNOWN_DISCIPLINE = 7
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:121</tt> by nedtool.
 * <pre>
 * // specifies how the final CQI will be computed from the multiband ones
 * enum PilotComputationModes
 * {
 *     MIN_CQI = 0;
 *     MAX_CQI = 1;
 *     AVG_CQI = 2;
 * }
 * </pre>
 */
enum PilotComputationModes {
    MIN_CQI = 0,
    MAX_CQI = 1,
    AVG_CQI = 2
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:130</tt> by nedtool.
 * <pre>
 * ///   Transmission Modes  
 * enum TxMode
 * {
 *     // Note: If you add more tx modes, update DL_NUM_TXMODE and UL_NUM_TXMODE
 *     SINGLE_ANTENNA_PORT0 = 0;
 *     SINGLE_ANTENNA_PORT5 = 1;
 *     TRANSMIT_DIVERSITY = 2;
 *     OL_SPATIAL_MULTIPLEXING = 3;
 *     CL_SPATIAL_MULTIPLEXING = 4;
 *     MULTI_USER = 5;
 *     UNKNOWN_TX_MODE = 6;
 * }
 * </pre>
 */
enum TxMode {
    SINGLE_ANTENNA_PORT0 = 0,
    SINGLE_ANTENNA_PORT5 = 1,
    TRANSMIT_DIVERSITY = 2,
    OL_SPATIAL_MULTIPLEXING = 3,
    CL_SPATIAL_MULTIPLEXING = 4,
    MULTI_USER = 5,
    UNKNOWN_TX_MODE = 6
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:142</tt> by nedtool.
 * <pre>
 * enum TxDirectionType
 * {
 *     ANISOTROPIC = 0;
 *     OMNI = 1;
 * }
 * </pre>
 */
enum TxDirectionType {
    ANISOTROPIC = 0,
    OMNI = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:149</tt> by nedtool.
 * <pre>
 * // Lte feedback type
 * enum FeedbackGeneratorType
 * {
 *     IDEAL = 0;
 *     REAL = 1;
 *     DAS_AWARE = 2;
 *     UNKNOW_FB_GEN_TYPE = 3;
 * }
 * </pre>
 */
enum FeedbackGeneratorType {
    IDEAL = 0,
    REAL = 1,
    DAS_AWARE = 2,
    UNKNOW_FB_GEN_TYPE = 3
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:158</tt> by nedtool.
 * <pre>
 * /// OFDMA layers (see FIXME lteAllocationModuble.h for "layers" meaning)
 * enum Plane
 * {
 *     MAIN_PLANE = 0;
 *     MU_MIMO_PLANE = 1;
 * }
 * </pre>
 */
enum Plane {
    MAIN_PLANE = 0,
    MU_MIMO_PLANE = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:164</tt> by nedtool.
 * <pre>
 * enum DeploymentScenario
 * {
 *     INDOOR_HOTSPOT = 0;
 *     URBAN_MICROCELL = 1;
 *     URBAN_MACROCELL = 2;
 *     RURAL_MACROCELL = 3;
 *     SUBURBAN_MACROCELL = 4;
 *     UNKNOW_SCENARIO = 5;
 * }
 * </pre>
 */
enum DeploymentScenario {
    INDOOR_HOTSPOT = 0,
    URBAN_MICROCELL = 1,
    URBAN_MACROCELL = 2,
    RURAL_MACROCELL = 3,
    SUBURBAN_MACROCELL = 4,
    UNKNOW_SCENARIO = 5
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:177</tt> by nedtool.
 * <pre>
 * //        DAS Support      
 * /// OFDMA Remotes (see FIXME LteAllocationModule.h for "antenna" meaning)
 * enum Remote
 * {
 *     MACRO = 0;
 *     RU1 = 1;
 *     RU2 = 2;
 *     RU3 = 3;
 *     RU4 = 4;
 *     RU5 = 5;
 *     RU6 = 6;
 *     UNKNOWN_RU = 7;
 * }
 * </pre>
 */
enum Remote {
    MACRO = 0,
    RU1 = 1,
    RU2 = 2,
    RU3 = 3,
    RU4 = 4,
    RU5 = 5,
    RU6 = 6,
    UNKNOWN_RU = 7
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:190</tt> by nedtool.
 * <pre>
 * // Lte PHY Frame Types 
 * enum LtePhyFrameType
 * {
 *     DATAPKT = 0;
 *     BROADCASTPKT = 1;
 *     FEEDBACKPKT = 2;
 *     HANDOVERPKT = 3;
 *     HARQPKT = 4;
 *     GRANTPKT = 5;
 *     RACPKT = 6;
 *     D2DMODESWITCHPKT = 7;
 *     UNKNOWN_TYPE = 8;
 * }
 * </pre>
 */
enum LtePhyFrameType {
    DATAPKT = 0,
    BROADCASTPKT = 1,
    FEEDBACKPKT = 2,
    HANDOVERPKT = 3,
    HARQPKT = 4,
    GRANTPKT = 5,
    RACPKT = 6,
    D2DMODESWITCHPKT = 7,
    UNKNOWN_TYPE = 8
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:205</tt> by nedtool.
 * <pre>
 * //  Lte Node Types  
 * enum LteNodeType
 * {
 *     INTERNET = 0; /// Internet side of the Lte network
 *     ENODEB = 1; /// eNodeB
 *     RELAY = 2; /// Relay
 *     UE = 3; /// UE
 *     UNKNOWN_NODE_TYPE = 4;/// unknown
 * }
 * </pre>
 */
enum LteNodeType {
    INTERNET = 0,
    ENODEB = 1,
    RELAY = 2,
    UE = 3,
    UNKNOWN_NODE_TYPE = 4
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:215</tt> by nedtool.
 * <pre>
 * //  Subframe type 
 * enum LteSubFrameType
 * {
 *     NORMAL_FRAME_TYPE = 0;
 *     MBSFN = 1;
 *     PAGING = 2;
 *     BROADCAST = 3;
 *     SYNCRO = 4;
 *     ABS = 5;
 *     UNKNOWN_FRAME_TYPE = 6;
 * }
 * </pre>
 */
enum LteSubFrameType {
    NORMAL_FRAME_TYPE = 0,
    MBSFN = 1,
    PAGING = 2,
    BROADCAST = 3,
    SYNCRO = 4,
    ABS = 5,
    UNKNOWN_FRAME_TYPE = 6
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:227</tt> by nedtool.
 * <pre>
 * enum X2MsgType
 * {
 *     ABS_INFO = 0;
 *     ABS_STATUS_INFO = 1;
 * }
 * </pre>
 */
enum X2MsgType {
    ABS_INFO = 0,
    ABS_STATUS_INFO = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:235</tt> by nedtool.
 * <pre>
 * // Types of BSR  * TODO add LONG/TRUNCATED BSR  
 * enum BsrType
 * {
 *     SHORT_BSR = 0;
 *     D2D_SHORT_BSR = 1;
 *     D2D_MULTI_SHORT_BSR = 2;
 * }
 * </pre>
 */
enum BsrType {
    SHORT_BSR = 0,
    D2D_SHORT_BSR = 1,
    D2D_MULTI_SHORT_BSR = 2
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:244</tt> by nedtool.
 * <pre>
 * /// H-ARQ feedback (ACK, NACK)
 * enum HarqAcknowledgment
 * {
 *     HARQNACK = 0;
 *     HARQACK = 1;
 * }
 * </pre>
 */
enum HarqAcknowledgment {
    HARQNACK = 0,
    HARQACK = 1
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:250</tt> by nedtool.
 * <pre>
 * /// TX H-ARQ pdu status
 * enum TxHarqPduStatus
 * {
 *     /// pdu is ready for retransmission (nack received)
 *     TXHARQ_PDU_BUFFERED = 0;
 *     /// pdu is waiting for feedback
 *     TXHARQ_PDU_WAITING = 1;
 *     /// no pdu inside this process (empty process)
 *     TXHARQ_PDU_EMPTY = 2;
 *     /// pdu selected for transmission
 *     TXHARQ_PDU_SELECTED = 3;
 * }
 * </pre>
 */
enum TxHarqPduStatus {
    TXHARQ_PDU_BUFFERED = 0,
    TXHARQ_PDU_WAITING = 1,
    TXHARQ_PDU_EMPTY = 2,
    TXHARQ_PDU_SELECTED = 3
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:263</tt> by nedtool.
 * <pre>
 * /// RX H-ARQ pdu status
 * enum RxHarqPduStatus
 * {
 *     /// no pdu, process is empty
 *     RXHARQ_PDU_EMPTY = 0;
 *     /// pdu is in evaluating state
 *     RXHARQ_PDU_EVALUATING = 1;
 *     /// pdu has been evaluated and it is correct
 *     RXHARQ_PDU_CORRECT = 2;
 *     /// pdu has been evaluated and it is not correct
 *     RXHARQ_PDU_CORRUPTED = 3;
 * }
 * </pre>
 */
enum RxHarqPduStatus {
    RXHARQ_PDU_EMPTY = 0,
    RXHARQ_PDU_EVALUATING = 1,
    RXHARQ_PDU_CORRECT = 2,
    RXHARQ_PDU_CORRUPTED = 3
};

/**
 * Enum generated from <tt>lte/common/LteCommonEnum.msg:277</tt> by nedtool.
 * <pre>
 * //  ********************* * Incell Interference Support *********************
 * enum EnbType
 * {
 *     // macro eNb
 *     MACRO_ENB = 0;
 *     // micro eNb
 *     MICRO_ENB = 1;
 * }
 * </pre>
 */
enum EnbType {
    MACRO_ENB = 0,
    MICRO_ENB = 1
};

#endif // ifndef __LTECOMMONENUM_M_H

