#ifndef DUST3D_APPLICATION_MODEL_WIDGET_H_
#define DUST3D_APPLICATION_MODEL_WIDGET_H_

#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QMutex>
#include <QVector2D>
#include <QTimer>
#include <QString>
#include "model_mesh.h"
#include "model_opengl_program.h"
#include "model_opengl_object.h"
#include "monochrome_mesh.h"
#include "monochrome_opengl_program.h"
#include "monochrome_opengl_object.h"

class ModelWidget : public QOpenGLWidget
{
    Q_OBJECT
signals:
    void mouseRayChanged(const QVector3D &near, const QVector3D &far);
    void mousePressed();
    void mouseReleased();
    void addMouseRadius(float radius);
    void renderParametersChanged();
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void eyePositionChanged(const QVector3D &eyePosition);
    void moveToPositionChanged(const QVector3D &moveToPosition);
public:
    ModelWidget(QWidget *parent = 0);
    ~ModelWidget();
    void updateMesh(ModelMesh *mesh);
    void updateWireframeMesh(MonochromeMesh *mesh);
    void updateHudMesh(MonochromeMesh *mesh);
    void toggleWireframe();
    bool isWireframeVisible();
    void toggleRotation();
    void enableMove(bool enabled);
    void enableZoom(bool enabled);
    void enableMousePicking(bool enabled);
    void setMoveAndZoomByWindow(bool byWindow);
    void disableCullFace();
    void setMoveToPosition(const QVector3D &moveToPosition);
    bool inputMousePressEventFromOtherWidget(QMouseEvent *event, bool notGraphics=false);
    bool inputMouseMoveEventFromOtherWidget(QMouseEvent *event);
    bool inputWheelEventFromOtherWidget(QWheelEvent *event);
    bool inputMouseReleaseEventFromOtherWidget(QMouseEvent *event);
    QPoint convertInputPosFromOtherWidget(QMouseEvent *event);
    int widthInPixels();
    int heightInPixels();
    void setNotGraphics(bool notGraphics);
    int xRot();
    int yRot();
    int zRot();
    const QVector3D &eyePosition();
    const QVector3D &moveToPosition();
    const QString &openGLVersion();
public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setEyePosition(const QVector3D &eyePosition);
    void cleanup();
    void zoom(float delta);
    void setMousePickTargetPositionInModelSpace(QVector3D position);
    void setMousePickRadius(float radius);
    void reRender();
    void canvasResized();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    int m_xRot = m_defaultXRotation;
    int m_yRot = m_defaultYRotation;
    int m_zRot = m_defaultZRotation;
    int m_directionOnMoveStart = 0;
    std::unique_ptr<ModelOpenGLProgram> m_modelOpenGLProgram;
    std::unique_ptr<ModelOpenGLObject> m_modelOpenGLObject;
    std::unique_ptr<MonochromeOpenGLProgram> m_monochromeOpenGLProgram;
    std::unique_ptr<MonochromeOpenGLObject> m_wireframeOpenGLObject;
    std::unique_ptr<MonochromeOpenGLObject> m_hudOpenGLObject;
    bool m_moveStarted = false;
    bool m_moveEnabled = true;
    bool m_zoomEnabled = true;
    bool m_mousePickingEnabled = false;
    QVector3D m_mousePickTargetPositionInModelSpace;
    QPoint m_lastPos;
    QMatrix4x4 m_projection;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    float m_mousePickRadius = 0.0;
    QVector3D m_eyePosition = m_defaultEyePosition;
    static float m_minZoomRatio;
    static float m_maxZoomRatio;
    QPoint m_moveStartPos;
    QRect m_moveStartGeometry;
    int m_modelInitialHeight = 0;
    QTimer *m_rotationTimer = nullptr;
    int m_widthInPixels = 0;
    int m_heightInPixels = 0;
    QVector3D m_moveToPosition;
    bool m_moveAndZoomByWindow = true;
    bool m_enableCullFace = true;
    bool m_notGraphics = false;
    bool m_isWireframeVisible = false;
    std::pair<QVector3D, QVector3D> screenPositionToMouseRay(const QPoint &screenPosition);
    void updateProjectionMatrix();
    void normalizeAngle(int &angle);
    void drawModel();
    void drawMonochrome();
public:
    static int m_defaultXRotation;
    static int m_defaultYRotation;
    static int m_defaultZRotation;
    static QVector3D m_defaultEyePosition;
    static QString m_openGLVersion;
    static QString m_openGLShadingLanguageVersion;
    static bool m_openGLIsCoreProfile;
};

#endif
