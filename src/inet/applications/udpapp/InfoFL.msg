//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//


//
// Packet used by the ~AlertSender and ~AlertReceiver modules.
//
import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;

class InfoFL extends inet::FieldsChunk
{
    uint32_t sequenceNumber;
    unsigned int sno;
    simtime_t payloadTimestamp;
    
    double globalInfo;
    int srcId;
    
        
    double x_pos;
    double y_pos;

}
