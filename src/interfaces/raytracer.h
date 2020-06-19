#ifndef INTERFACES_RAYTRACER_H_
#define INTERFACES_RAYTRACER_H_

/*
 * Ray Tracer based on "Raytracing From the Ground Up"
 *
 * Author : Levi Biasco
 * Version: 0.1
 *
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

class RenderWindow : public QMainWindow
{
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


class RenderCanvas: public QWidget
{
    Q_OBJECT

public:
    RenderCanvas(QWidget *parent, RenderWindow *window);
    virtual ~RenderCanvas(void);
        
    void SetImage(QImage *image);
    QImage *GetImage(void);
      
    void RenderStart(void);
    void RenderPause(void);
    void RenderResume(void);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    QImage *image_;
    World *w_;

private:
    RenderWindow *window_;
    RenderController *controller_;
    long pixels_rendered_;
    long pixels_to_render_;
    QElapsedTimer *timer_;
    QTimer *update_timer_;

public slots:
    void CompleteRender();
    void TimerUpdate();
    void UpdatePixels(vector<RenderPixel*> *pixels);

signals:
    void Completed();
};


class RenderController : public QObject
{
    Q_OBJECT

    QThread worker_thread_;

public:
    RenderController(RenderCanvas* c, World* w);
    ~RenderController();

signals:
    void Pause();
    void Resume();
    void Start();
    void Terminate();
};


class RenderWorker : public QObject
{
    Q_OBJECT
    
public:
    RenderWorker(World *w);

public slots:
    virtual void Pause();
    virtual void Resume();
    virtual void* Start();
    virtual void Terminate();
    virtual void SetPixel(int x, int y, int red, int green, int blue);

signals:
    void Completed();
    void PixelsUpdated(vector<RenderPixel*> *pixels_update);

private:
    void SendUpdate();
    
    World *world_;
    vector<RenderPixel*> pixels_;
    QElapsedTimer *timer_;
};


class RenderPixel
{
public:
    RenderPixel(int x, int y, int red, int green, int blue);

    int x_, y_;
    int red_, green_, blue_;
};


#endif // INTERFACES_RAYTRACER_H_
