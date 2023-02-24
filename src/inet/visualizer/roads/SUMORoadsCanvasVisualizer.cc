

#include "inet/visualizer/roads/SUMORoadsCanvasVisualizer.h"
#include "libsumo/libsumo.h"


namespace inet {
namespace visualizer {
Define_Module(SUMORoadsCanvasVisualizer);

//SUMORoadsCanvasVisualizer::SUMORoadsCanvasVisualizer(){}
//SUMORoadsCanvasVisualizer::~SUMORoadsCanvasVisualizer(){}

void SUMORoadsCanvasVisualizer::initialize(int stage)
{
    if (stage == 0) {
        updateMap = new cMessage("updateMap");
        scheduleAt(simTime(), updateMap);
    }
}

void SUMORoadsCanvasVisualizer::handleMessage(cMessage* msg)
{
    if(isloadMap == false){
        figures = new cGroupFigure("roads");
        double zindex = par("lineZIndex");
        #if OMNETPP_VERSION >= 0x501
            figures->setZIndex(zindex);
        #endif
        cCanvas* canvas = getParentModule()->getCanvas();
        canvas->addFigure(figures);

        std::string colorStr = par("lineColor");
        auto color = cFigure::Color(colorStr.c_str());
        double width = par("lineWidth");
        bool zoom = par("lineWidthZoom");

        auto laneIds = libsumo::Lane::getIDList();
        for (auto laneId : laneIds) {
            libsumo::TraCIPositionVector ls = libsumo::Lane::getShape(laneId);
            std::list<inet::Coord> coords;
            for(unsigned int i=0;i<ls.value.size();i++){
                inet::Coord tmp;
                tmp.x = ls.value[i].x;
                tmp.y = ls.value[i].y;
                tmp.z = ls.value[i].z;
                coords.push_back(tmp);
            }
            auto line = createLine(coords, color, width, zoom);
            figures->addFigure(line);
        }
        isloadMap = true;
    }
}

void SUMORoadsCanvasVisualizer::finish()
{
}

inet::cPolylineFigure* SUMORoadsCanvasVisualizer::createLine(std::list<inet::Coord> coords, cFigure::Color color, double width, bool zoom)
{
    std::vector<cFigure::Point> points;
    for (auto coord : coords) {
        points.push_back(cFigure::Point(coord.x, coord.y));
    }

    auto* line = new cPolylineFigure();
    line->setPoints(points);
    line->setLineColor(color);
    line->setLineWidth(width);
    line->setZoomLineWidth(zoom);

    return line;
}
}
}
