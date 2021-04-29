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

    QMenu *file_menu_;
    QMenu *render_menu_;
    QAction *open_act_;
    QAction *save_act_;
    QAction *exit_act_;
    QAction *start_act_;
    QAction *pause_act_;
    QAction *resume_act_;

    QLabel *status_left_;
    QLabel *status_right_;

    RenderCanvas *canvas_;
};


class RenderCanvas: public QWidget {
    Q_OBJECT

  public:
    RenderCanvas(QWidget *parent, RenderWindow *window);
    virtual ~RenderCanvas(void);
        
    void SetImage(QImage *image);
    QImage *GetImage(void);
      
    void RenderStart(void);
    void RenderPause(void);
    void RenderResume(void);

  public slots:
    void CompleteRender();
    void TimerUpdate();
    void UpdatePixels(std::vector<RenderPixel*> *pixels);

  signals:
    void Completed();

  private:
    void paintEvent(QPaintEvent *event) override;

    RenderController *controller_;

    QImage *image_;
    long pixels_rendered_;
    long pixels_to_render_;

    QElapsedTimer *timer_;
    QTimer *updateTimer_;
    long elapsedAtPause_;

    World *w_;
    RenderWindow *window_;
};

class RenderThread : public QThread {
  public:
    RenderThread() : QThread(), pauseRequested_(false) {}

    void RequestPause(bool pause) { pauseRequested_ = pause; }
    bool IsPauseRequested() { return pauseRequested_; }

  private:
    bool pauseRequested_;
};

class RenderController : public QObject {
    Q_OBJECT
    RenderThread workerThread_;

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
    RenderWorker(World *w, RenderThread *thread);

  public slots:
    virtual void* Run();
    virtual void Terminate();
    virtual void SetPixel(int x, int y, int red, int green, int blue);

  signals:
    void Completed();
    void PixelsUpdated(std::vector<RenderPixel*> *pixels_update);

  private:
    void SendUpdate();
    
    std::vector<RenderPixel*> pixels_;
    QElapsedTimer *timer_;
    World *world_;

    RenderThread *thread_;
};


struct RenderPixel {
    RenderPixel(int x, int y, int r, int g, int b) : x(x), y(y), r(r), g(g), b(b) {};
    int x, y;
    int r, g, b;
};


#endif // INTERFACES_RAYTRACER_H_
