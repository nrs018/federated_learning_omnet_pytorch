
#pragma once
//#include "veins/veins.h"
#include "inet/common/geometry/common/Coord.h"
#include "libsumo/libsumo.h"

#ifndef __INET_SUMOROADSCANVASVISUALIZER_H
#define __INET_SUMOROADSCANVASVISUALIZER_H

namespace inet {
namespace visualizer {
class INET_API SUMORoadsCanvasVisualizer : public cSimpleModule {
public:
//    SUMORoadsCanvasVisualizer();
//    ~SUMORoadsCanvasVisualizer();

    void initialize(int stage) override;
    void handleMessage(cMessage* msg) override;
    void finish() override;
    cMessage * updateMap;
    bool isloadMap = false;

protected:
    cGroupFigure* figures;
    cPolylineFigure* createLine(std::list<inet::Coord> coords, cFigure::Color color, double width, bool zoom);
};
} // namespace visualzier
}// namespace inet

#endif // ifndef __INET_SUMOROADSCANVASVISUALIZER_H
