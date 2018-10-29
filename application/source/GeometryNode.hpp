#include "Node.hpp"
#include "model.hpp"


class GeometryNode : public Node
{
public:
    GeometryNode();
    ~GeometryNode();
    model getGeometry();
    void setGeometry(model theModel);

protected:
    model* myModel;

};





