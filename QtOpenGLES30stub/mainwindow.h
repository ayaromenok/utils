#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>
#include <QMatrix4x4>
#include <QVector3D>

QT_BEGIN_NAMESPACE
class QOpenGLTexture;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
QT_END_NAMESPACE

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
private:

    QOpenGLShaderProgram*       _prg;
    QOpenGLBuffer*              _vbo;
    QOpenGLVertexArrayObject*   _vao;
    QOpenGLTexture*             _tex;

    int                         _posMtxProj;
    int                         _posMtxCam;
    int                         _posMtxWorld;
    int                         _posMtxMy; //additinal matrix

    QMatrix4x4                  _mtxProj;
    QMatrix4x4                  _mtxWorld;
    QMatrix4x4                  _mtxCam;
    QMatrix4x4                  _mtxMy;

    QVector3D                   _vecEye;
    QVector3D                   _vecTarget;

    QVector<GLfloat>            _data;
    const int                   cnMeshSize = 4;
};

#endif // MAINWINDOW_H
