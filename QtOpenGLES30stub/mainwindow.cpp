#include "mainwindow.h"
#include <QDebug>
#include <QImage>
#include <QFile>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLExtraFunctions>

MainWindow::MainWindow()
    : _prg(0),
      _vbo(0),
      _vao(0),
      _tex(0),
      _vecEye(0,0,0),
      _vecTarget(0,0,-10)
{
    qDebug() << "MainWindow::MainWindow()";
    this->setWidth(360);
    this->setHeight(360);

    _mtxWorld.setToIdentity();
    _mtxWorld.translate(0,0,-20);
    _mtxWorld.rotate(180, 1, 0, 0);

    _mtxCam.setToIdentity();
    _mtxMy.setToIdentity();
    _mtxProj.setToIdentity();

    _data.resize((3+3+2)*cnMeshSize);
    GLfloat *p = _data.data();

    *p++ = -7.0f; *p++ = -7.0f;  *p++ = 0.0f;   //v0
    *p++ = 0.0f;  *p++ = 0.0f;   *p++ = 1.0f;   //n0
    *p++ = 0.0f;  *p++ = 0.0f;                  //t0

    *p++ = -7.0f;  *p++ = 7.0f;  *p++ = 0.0f;   //v1
    *p++ = 0.0f;  *p++ = 0.0f;   *p++ = 1.0f;   //n1
    *p++ = 0.0f;  *p++ = 1.0f;                  //t1

    *p++ = 7.0f;  *p++ = 7.0f;   *p++ = 0.0f;   //v2
    *p++ = 0.0f;  *p++ = 0.0f;   *p++ = 1.0f;   //n2
    *p++ = 1.0f;  *p++ = 1.0f;                  //t2

    *p++ = 7.0f;  *p++ = -7.0f;  *p++ = 0.0f;   //v3
    *p++ = 0.0f;  *p++ = 0.0f;   *p++ = 1.0f;   //n3
    *p++ = 1.0f;  *p++ = 0.0f;                  //t3
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow()";
    this->makeCurrent();
    delete _prg;
    delete _vbo;
    delete _vao;
    delete _tex;
}

QByteArray versionedShaderCode(const char *fileName)
{
    QByteArray versionedSrc;
    QFile file(fileName);

    Q_ASSERT(file.exists());
    Q_ASSERT(file.open(QIODevice::ReadOnly | QIODevice::Text));

    if (QOpenGLContext::currentContext()->isOpenGLES())
        versionedSrc.append(QByteArrayLiteral("#version 300 es\n"));
    else
        versionedSrc.append(QByteArrayLiteral("#version 330\n"));

    versionedSrc.append(file.readAll());
    file.close();
    //qDebug() << "final shader source" << versionedSrc;
    return versionedSrc;
}

void
MainWindow::initializeGL()
{
    qDebug() << "MainWindow::initializeGL()";
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    if (_prg) { delete _prg; _prg = 0;}
    if (_tex) { delete _tex; _tex = 0;}

    QImage img(":/res/64x64.png");
    Q_ASSERT(!img.isNull());
    _tex = new QOpenGLTexture(img);

    _prg = new QOpenGLShaderProgram;
    _prg->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                  versionedShaderCode(":/res/main.vsh"));
    _prg->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                  versionedShaderCode(":/res/main.fsh"));
    _prg->link();

    _posMtxProj = _prg->uniformLocation("mtxProj");
    _posMtxWorld = _prg->uniformLocation("mtxWorld");
    _posMtxCam = _prg->uniformLocation("mtxCam");
    _posMtxMy = _prg->uniformLocation("mtxMy");
    qDebug() << _posMtxProj << _posMtxWorld << _posMtxCam << _posMtxMy;

    if (_vao) { delete _vao; _vao = 0;}

    _vao = new QOpenGLVertexArrayObject;
    if (_vao->create())
        _vao->bind();

    _prg->bind();

    if (_vbo) { delete _vbo; _vbo = 0;}
    _vbo = new QOpenGLBuffer;
    _vbo->create();
    _vbo->bind();
    _vbo->allocate(_data.constData(), _data.count()*sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void *>(6 * sizeof(GLfloat)));
    _vbo->release();

    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);
    _prg->setUniformValue(_posMtxWorld, _mtxWorld);
    //_prg->setUniformValue(_posMtxProj, _mtxProj);
    qDebug() << "mtxWorld" << _mtxWorld;

}

void
MainWindow::resizeGL(int w, int h)
{
    qDebug() << "MainWindow::resizeGL(int w, int h)" << w << h;
    _mtxProj.setToIdentity();
    //_mtxProj.frustum(-50.0f, 50.0f, -50.0f, 50.0f, 0.01f, 1000.0f);
    _mtxProj.perspective(60.0f, GLfloat(w)/h, 0.01f, 100.0f);
    //_mtxProj.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 1000.0f);
    _prg->setUniformValue(_posMtxProj, _mtxProj);
    qDebug() << "mtxProj" << _mtxProj;
}

void
MainWindow::paintGL()
{
    qDebug() << "MainWindow::paintGL()";

    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    f->glClearColor(0, 0.5, 0, 1);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _prg->bind();
    _tex->bind();
    _vecEye = QVector3D(0,0,10);                // eye position can be changed here
    _vecTarget = QVector3D(0,0,-10);            // center of view is here
    _mtxCam.lookAt(_vecEye, _vecTarget, QVector3D(0,1,0));
    _prg->setUniformValue(_posMtxCam, _mtxCam);

    _mtxMy.rotate(0,QVector3D(0,0,1));          //move/rotate/scale scene here
    _prg->setUniformValue(_posMtxMy, _mtxMy);

    f->glDrawArrays(GL_TRIANGLE_FAN,0, cnMeshSize);
}
