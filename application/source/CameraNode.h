#include "Node.hpp"

class GeometryNode : public Node
{
public:
	CameraNode();
	~CameraNode();

	bool getPerspective(void);
	bool getEnabled(void);
	void setEnabled(bool);
	glm::mat4 getProjectionMatrix(void);
	void setProjectionMatrix(glm::mat4);

protected:
	bool isPerspective;
	bool isEnabled;
	glm::mat4 projectionMatrix;

};
