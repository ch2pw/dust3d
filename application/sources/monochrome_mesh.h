#ifndef DUST3D_APPLICATION_MONOCHROME_MESH_H_
#define DUST3D_APPLICATION_MONOCHROME_MESH_H_

#include <memory>
#include <dust3d/base/object.h>
#include "monochrome_opengl_vertex.h"

class MonochromeMesh
{
public:
    MonochromeMesh(const MonochromeMesh &mesh);
    MonochromeMesh(MonochromeMesh &&mesh);
    MonochromeMesh(const dust3d::Object &object);
    MonochromeMesh(std::vector<float> &&lineVertices);
    const float *lineVertices();
    int lineVertexCount();
private:
    std::vector<float> m_lineVertices;
};

#endif

