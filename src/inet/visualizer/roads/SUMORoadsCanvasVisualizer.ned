

package inet.visualizer.roads;

simple SUMORoadsCanvasVisualizer
{
    parameters:
        @display("i=block/segm");
        @class(SUMORoadsCanvasVisualizer);
        
        double lineZIndex = default(-1);  
        string lineColor = default("firebrick4");  
        double lineWidth = default(1);  
        bool lineWidthZoom = default(false);  
}

