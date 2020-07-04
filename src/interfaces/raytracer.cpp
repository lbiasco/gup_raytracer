#include "interfaces/raytracer.h"

/******************************************************************************/
/*********************** entry point ******************************************/
/******************************************************************************/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    RenderWindow window;
    window.show();
    return app.exec();
}


/******************************************************************************/
/********************* RenderWindow *******************************************/
/******************************************************************************/

RenderWindow::RenderWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    canvas_ = new RenderCanvas(widget, this);
    canvas_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(canvas_, &RenderCanvas::Completed, this, &RenderWindow::Complete);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(canvas_);
    widget->setLayout(layout);

    CreateActions();
    CreateMenus();

    setWindowTitle(tr("GUP Raytracer"));
    setMinimumSize(160, 160);
    resize(700, 500);

    SetStatusText(tr("Ready"), 0);
    SetStatusText(tr(""), 1);
    statusBar()->setSizeGripEnabled(true);
}

void RenderWindow::SetStatusText(const QString text, int num)
{
    if(num == 0)
    {
        statusBar()->removeWidget(status_left_);
        status_left_ = new QLabel(text);
        status_left_->setMinimumWidth(80);
        statusBar()->insertWidget(0, status_left_);
    } else if(num == 1)
    {
        statusBar()->removeWidget(status_right_);
        status_right_ = new QLabel(text);
        status_right_->setMinimumWidth(80);
        statusBar()->insertWidget(1, status_right_);
    }
}

void RenderWindow::Open()
{
    QString wildcard = tr("BMP files (*.bmp);;"
                            "PNG files (*.png);;"
                            "JPEG files (*.jpg);;"
                            "TIFF files (*.tif);;");
    QString caption = tr("Open file");

    QString file_name = QFileDialog::getOpenFileName(this, caption, QString(), wildcard);

    if (!file_name.isNull())
    {
        QImage* image = new QImage();
        bool valid = image->load(file_name);

        if(!valid)
        {
            delete image;
            QMessageBox::critical(this, tr("Load failed!"), tr("Sorry, could not load file."));
        } else
        {
            canvas_->SetImage(image);
            save_act_->setEnabled(true);
        }
    }
}

void RenderWindow::Save()
{
    QString wildcard = tr("BMP files (*.bmp);;"
                            "PNG files (*.png);;"
                            "JPEG files (*.jpg);;"
                            "TIFF files (*.tif);;");
    QString caption = tr("Save file");

    QString file_name = QFileDialog::getSaveFileName(this, caption, QString(), wildcard);

    if (!file_name.isNull())
    {
        QImage* image = canvas_->GetImage();
        if(!image->save(file_name))
        {
            QMessageBox::critical(this, tr("Save failed!"), tr("Sorry, could not save file."));
        }
    }
}

void RenderWindow::Complete()
{
    start_act_->setEnabled(true);
    pause_act_->setEnabled(false);
    resume_act_->setEnabled(false);

    open_act_->setEnabled(true);
    SetStatusText(tr("Rendering complete"), 0);
}

void RenderWindow::Start()
{
    start_act_->setEnabled(false);
    pause_act_->setEnabled(true);
    resume_act_->setEnabled(false);
    
    canvas_->RenderStart();
    
    open_act_->setEnabled(false);
    save_act_->setEnabled(true);
}

void RenderWindow::Pause()
{
    start_act_->setEnabled(false);
    pause_act_->setEnabled(false);
    resume_act_->setEnabled(true);
   
    canvas_->RenderPause();
    SetStatusText(tr("Rendering paused"), 0);
}

void RenderWindow::Resume()
{
    start_act_->setEnabled(false);
    pause_act_->setEnabled(true);
    resume_act_->setEnabled(false);
   
    canvas_->RenderResume();
    SetStatusText(tr("Rendering resumed"), 0);
}

void RenderWindow::CreateActions()
{
    open_act_ = new QAction(tr("&Open..."), this);
    open_act_->setShortcuts(QKeySequence::Open);
    open_act_->setStatusTip(tr("Open an existing file"));
    connect(open_act_, &QAction::triggered, this, &RenderWindow::Open);

    save_act_ = new QAction(tr("&Save"), this);
    save_act_->setShortcuts(QKeySequence::Save);
    save_act_->setStatusTip(tr("Save the document to disk"));
    connect(save_act_, &QAction::triggered, this, &RenderWindow::Save);

    exit_act_ = new QAction(tr("E&xit"), this);
    exit_act_->setShortcuts(QKeySequence::Quit);
    exit_act_->setStatusTip(tr("Exit the application"));
    connect(exit_act_, &QAction::triggered, this, &QWidget::close);

    start_act_ = new QAction(tr("&Start"), this);
    start_act_->setShortcuts(QKeySequence::Refresh);
    start_act_->setStatusTip(tr("Start the render"));
    connect(start_act_, &QAction::triggered, this, &RenderWindow::Start);

    pause_act_ = new QAction(tr("&Pause"), this);
    pause_act_->setStatusTip(tr("Pause the render"));
    connect(pause_act_, &QAction::triggered, this, &RenderWindow::Pause);

    resume_act_ = new QAction(tr("&Resume"), this);
    resume_act_->setStatusTip(tr("Resume the render"));
    connect(resume_act_, &QAction::triggered, this, &RenderWindow::Resume);
}

void RenderWindow::CreateMenus()
{
    file_menu_ = menuBar()->addMenu(tr("&File"));
    file_menu_->addAction(open_act_);
    file_menu_->addAction(save_act_);
    file_menu_->addAction(exit_act_);

    render_menu_ = menuBar()->addMenu(tr("&Render"));
    render_menu_->addAction(start_act_);
    render_menu_->addSeparator();
    render_menu_->addAction(pause_act_);
    render_menu_->addAction(resume_act_);
}


/******************************************************************************/
/********************* RenderCanvas *******************************************/
/******************************************************************************/

RenderCanvas::RenderCanvas(QWidget *parent, RenderWindow *window)
   : QWidget(parent), image_(NULL), w_(NULL), window_(window), 
   controller_(NULL), timer_(NULL)
{
    update_timer_ = new QTimer();
    connect(update_timer_, &QTimer::timeout, this, &RenderCanvas::TimerUpdate);

    //SetOwnBackgroundColour(wxColour(143,144,150));
}

RenderCanvas::~RenderCanvas(void)
{
    if(image_ != NULL)
        delete image_;
    
    if(controller_ != NULL)
        delete controller_;
    
    if(w_ != NULL)
        delete w_;
    
    if(timer_ != NULL)
        delete timer_;
}

void RenderCanvas::SetImage(QImage *image)
{
    if(image == NULL || image->isNull())
        return;
    
    image_ = image;
    // NEED TO SUBCLASS QScrollArea ? *****************
    //SetScrollbars(10, 10, (int)(m_image->GetWidth()  / 10.0f),
    //                      (int)(m_image->GetHeight() / 10.0f), 0, 0, true);

    update();
}

QImage* RenderCanvas::GetImage(void)
{
    if(image_ != NULL)
        return image_;
    
    return new QImage();
}

void RenderCanvas::CompleteRender()
{
    controller_ = NULL;
    
    if(w_ != NULL)
    {
        delete w_;
        w_ = NULL;
    }
    
    if(timer_ != NULL)
    {
        QTime timeElapsed = QTime(0, 0).addMSecs(timer_->elapsed());
        QString timeString = timeElapsed.toString("'Elapsed Time: 'H:mm:ss.zzz"); // 
        window_->SetStatusText(timeString, 1);

        delete timer_;
        timer_ = NULL;
    }

    emit Completed();
}

void RenderCanvas::RenderPause(void)
{
    if(controller_ != NULL)
        emit controller_->Pause();
    
    update_timer_->stop();
    
    if(timer_ != NULL)
        // NEED TO IMPLEMENT TIME-STORING LOGIC FOR PAUSE/RESUME *****************
        timer_->restart();
}

void RenderCanvas::RenderResume(void)
{
    if(controller_ != NULL)
        emit controller_->Resume();
    
    update_timer_->start();
    
    if(timer_ != NULL)
        // NEED TO IMPLEMENT TIME-STORING LOGIC FOR PAUSE/RESUME *****************
        timer_->restart();
}

void RenderCanvas::RenderStart(void)
{
    w_ = new World();
   
    window_->SetStatusText("Building world...", 0);
    w_->Build();

    if(w_->tracer_ptr_ == NULL)
    {
        window_->SetStatusText("ERROR: Tracer not set, skipping render", 0);
        return;
    }

    window_->SetStatusText("Rendering...", 0);
    setMinimumSize(w_->vp_.hres_, w_->vp_.vres_);

    pixels_rendered_ = 0;
    pixels_to_render_ = w_->vp_.hres_ * w_->vp_.vres_;

    // Set background
    QImage *temp = new QImage(w_->vp_.hres_, w_->vp_.vres_, QImage::Format_RGB32);
    temp->fill(QColor(50, 50, 50));
    SetImage(temp);

    update_timer_->start(250);

    //start timer
    timer_ = new QElapsedTimer();
    timer_->start();
    
    controller_ = new RenderController(this, w_);
    emit controller_->Start();
}

void RenderCanvas::TimerUpdate()
{
    if(timer_ == NULL)
        return;

    //percent
    float completed = (float)pixels_rendered_ / (float)pixels_to_render_;
        
    QString progress_string = QString("Rendering...%1%").arg((int)(completed*100));
    window_->SetStatusText(progress_string , 0);

    //time elapsed
    long elapsed = timer_->elapsed();
    QTime time_elapsed = QTime(0, 0).addMSecs(elapsed);
    
    //time remaining
    float remaining = 1.0f - completed;
    long msec_remaining = (long)(((double)elapsed / (completed*100)) * 100 * remaining);
    QTime time_remaining = QTime(0, 0).addMSecs(msec_remaining);
    
    QString time_remaining_string = time_remaining.toString("' / ETA: 'H:mm:ss.zzz");
    QString time_string = time_elapsed.toString("'Elapsed Time: 'H:mm:ss.zzz");

    //only display ETA if something has been completed
    if(msec_remaining >= 0)
        window_->SetStatusText(time_string + time_remaining_string, 1);
    else
        window_->SetStatusText(time_string, 1);
}

void RenderCanvas::UpdatePixels(std::vector<RenderPixel*> *pixels)
{
    for(std::vector<RenderPixel*>::iterator itr = pixels->begin();
                            itr != pixels->end(); itr++)
    {
        RenderPixel* pixel = *itr;
        const QColor color(pixel->red_, pixel->green_, pixel->blue_);
        image_->setPixelColor(pixel->x_, pixel->y_, color);

        pixels_rendered_++;
        delete pixel;
    }
    update();
}

void RenderCanvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    if(!(image_ == NULL) && !(image_->isNull()))
        painter.drawImage(0, 0, *image_);
}


/******************************************************************************/
/********************* RenderController ***************************************/
/******************************************************************************/

// Implement a  QThread::currentThread()->isInterruptionRequested() check for pausing *****************
RenderController::RenderController(RenderCanvas* c, World* w)
{
    RenderWorker *worker = new RenderWorker(w);
    worker->moveToThread(&worker_thread_);
    connect(&worker_thread_, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &RenderController::Start, worker, &RenderWorker::Start);
    connect(this, &RenderController::Pause, worker, &RenderWorker::Pause);
    connect(this, &RenderController::Resume, worker, &RenderWorker::Resume);
    connect(this, &RenderController::Terminate, worker, &RenderWorker::Terminate);

    connect(worker, &RenderWorker::Completed, c, &RenderCanvas::CompleteRender);
    connect(worker, &RenderWorker::PixelsUpdated, c, &RenderCanvas::UpdatePixels);
    worker_thread_.start();
}
RenderController::~RenderController()
{
    // NEED TO MAKE SURE DELETION PERFORMS ALL THE PROPER STEPS
    worker_thread_.quit();
    worker_thread_.wait();
}


/******************************************************************************/
/********************* RenderWorker *******************************************/
/******************************************************************************/

RenderWorker::RenderWorker(World* w)
{
    world_ = w;
    world_->paint_area_ = this;
}

void RenderWorker::Pause()
{
    // NEED TO IMPLEMENT *****************
}

void RenderWorker::Resume()
{
    // NEED TO IMPLEMENT *****************
}

void RenderWorker::SendUpdate()
{
    timer_->restart();
    
    //copy rendered pixels into a new vector and reset
    std::vector<RenderPixel*> *pixels_update = new std::vector<RenderPixel*>(pixels_);
    pixels_.clear();
   
    emit PixelsUpdated(pixels_update);
}

void RenderWorker::SetPixel(int x, int y, int red, int green, int blue)
{
    pixels_.push_back(new RenderPixel(x, y, red, green, blue));

    if(timer_->elapsed() > 40)
        SendUpdate();
}

void* RenderWorker::Start()
{
    timer_ = new QElapsedTimer();
    timer_->start();
    
    // NEED TO WRAP IN INTERRUPT LOOP IN ORDER TO PAUSE/RESUME *****************
    //world_->RenderOrthographic();
    world_->RenderPerspective();

    return NULL;
}

void RenderWorker::Terminate()
{
    SendUpdate();
    emit Completed();
}


/******************************************************************************/
/********************* RenderPixel ********************************************/
/******************************************************************************/

RenderPixel::RenderPixel(int x, int y, int red, int green, int blue)
 : x_(x), y_(y), red_(red), green_(green), blue_(blue)
{}