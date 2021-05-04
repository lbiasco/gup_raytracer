#ifndef INTERFACES_RAYTRACER_H_
#define INTERFACES_RAYTRACER_H_

/*
 * Ray Tracer based on "Raytracing From the Ground Up"
 *
 * Author : Levi Biasco
 */

#include <vector>

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include "world/world.h"

// namespace gup_raytracer {

class RenderWindow;
class RenderCanvas;
class RenderController;
class RenderWorker;
class RenderPixel;


class RenderWindow : public QMainWindow {
    Q_OBJECT

public:
    RenderWindow();
    void SetStatusText(const QString text, int col=0);

private slots:
    void Open();
    void Save();
    void Complete();
    void Start();
    void Pause();
    void Resume();

private:
    void CreateActions();
    void CreateMenus();

    QMenu* _fileMenu;
    QMenu* _renderMenu;
    QAction* _openAct;
    QAction* _saveAct;
    QAction* _exitAct;
    QAction* _startAct;
    QAction* _pauseAct;
    QAction* _resumeAct;

    QLabel* _statusLeft;
    QLabel* _statusRight;

    RenderCanvas* _canvas;
};


class RenderCanvas: public QWidget {
    Q_OBJECT

public:
    RenderCanvas(QWidget* parent, RenderWindow* window);
    virtual ~RenderCanvas(void);
        
    void SetImage(QImage* image);
    QImage* GetImage(void);
    
    void RenderStart(void);
    void RenderPause(void);
    void RenderResume(void);

public slots:
    void CompleteRender();
    void TimerUpdate();
    void UpdatePixels(std::vector<RenderPixel*>* pixels);

signals:
    void Completed();

private:
    void paintEvent(QPaintEvent* event) override;

    RenderController* _controller;

    QImage* _image;
    long _pixelsRendered;
    long _pixelsToRender;

    QElapsedTimer* _timer;
    QTimer* _updateTimer;
    long _elapsedAtPause;

    World* _w;
    RenderWindow* _window;
};

class RenderThread : public QThread {
public:
    RenderThread() : QThread(), _pauseRequested(false) {}

    void RequestPause(bool pause) { _pauseRequested = pause; }
    bool IsPauseRequested() { return _pauseRequested; }

private:
    bool _pauseRequested;
};

class RenderController : public QObject {
    Q_OBJECT
    RenderThread _workerThread;

public:
    RenderController(RenderCanvas* c, World* w);
    ~RenderController();

    void Pause();
    void Resume();

signals:
    void Start();
    void Terminate();
};

class RenderWorker : public QObject {
    Q_OBJECT
    
public:
    RenderWorker(World* w, RenderThread* thread);

public slots:
    virtual void* Run();
    virtual void Terminate();
    virtual void SetPixel(int x, int y, int red, int green, int blue);

signals:
    void Completed();
    void PixelsUpdated(std::vector<RenderPixel*>* pixelsUpdate);

private:
    void SendUpdate();
    
    std::vector<RenderPixel*> _pixels;
    QElapsedTimer* _timer;
    World* _world;

    RenderThread* _thread;
};


struct RenderPixel {
    RenderPixel(int x, int y, int r, int g, int b) : x(x), y(y), r(r), g(g), b(b) {};
    int x, y;
    int r, g, b;
};


#endif // INTERFACES_RAYTRACER_H_
