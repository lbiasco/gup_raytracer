#include "interfaces/raytracer.h"

// ------------------------------------------------------------------------- //
// Entry point
// ------------------------------------------------------------------------- //

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  RenderWindow window;
  window.show();
  return app.exec();
}


// ------------------------------------------------------------------------- //
// RenderWindow
// ------------------------------------------------------------------------- //

RenderWindow::RenderWindow() {
  QWidget* widget = new QWidget;
  setCentralWidget(widget);

  _canvas = new RenderCanvas(widget, this);
  _canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  connect(_canvas, &RenderCanvas::Completed, this, &RenderWindow::Complete);

  QVBoxLayout* layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(_canvas);
  widget->setLayout(layout);

  CreateActions();
  CreateMenus();

  setWindowTitle(tr("GUP Raytracer"));
  setFixedSize(300, 300);

  SetStatusText(tr("Ready"), 0);
  SetStatusText(tr(""), 1);
  statusBar()->setSizeGripEnabled(false);
}

void RenderWindow::SetStatusText(const QString text, int num) {
  if(num == 0) {
    statusBar()->removeWidget(_statusLeft);
    _statusLeft = new QLabel(text);
    _statusLeft->setMinimumWidth(80);
    statusBar()->insertWidget(0, _statusLeft);
  } else if(num == 1) {
    statusBar()->removeWidget(_statusRight);
    _statusRight = new QLabel(text);
    _statusRight->setMinimumWidth(80);
    statusBar()->insertWidget(1, _statusRight);
  }
}

void RenderWindow::Open() {
  QString wildcard = tr("BMP files (*.bmp);;"
                        "PNG files (*.png);;"
                        "JPEG files (*.jpg);;"
                        "TIFF files (*.tif);;");
  QString caption = tr("Open file");

  QString fileName = QFileDialog::getOpenFileName(this, caption, QString(), wildcard);

  if (!fileName.isNull()) {
    QImage* image = new QImage();
    bool valid = image->load(fileName);

    if(!valid) {
      delete image;
      QMessageBox::critical(this, tr("Load failed!"), tr("Sorry, could not load file."));
    } else {
      _canvas->SetImage(image);
      _saveAct->setEnabled(true);
    }
  }
}

void RenderWindow::Save() {
  QString wildcard = tr("BMP files (*.bmp);;"
                        "PNG files (*.png);;"
                        "JPEG files (*.jpg);;"
                        "TIFF files (*.tif);;");
  QString caption = tr("Save file");

  QString fileName = QFileDialog::getSaveFileName(this, caption, QString(), wildcard);

  if (!fileName.isNull()) {
    QImage* image = _canvas->GetImage();
    if(!image->save(fileName))
      QMessageBox::critical(this, tr("Save failed!"), tr("Sorry, could not save file."));
  }
}

void RenderWindow::Complete() {
  _startAct->setEnabled(true);
  _pauseAct->setEnabled(false);
  _resumeAct->setEnabled(false);

  _openAct->setEnabled(true);
  SetStatusText(tr("Rendering complete"), 0);
}

void RenderWindow::Start() {
  _startAct->setEnabled(false);
  _pauseAct->setEnabled(true);
  _resumeAct->setEnabled(false);
  
  _canvas->RenderStart();
  
  _openAct->setEnabled(false);
  _saveAct->setEnabled(true);
}

void RenderWindow::Pause() {
  _startAct->setEnabled(false);
  _pauseAct->setEnabled(false);
  _resumeAct->setEnabled(true);
  
  _canvas->RenderPause();
  SetStatusText(tr("Rendering paused"), 0);
}

void RenderWindow::Resume() {
  _startAct->setEnabled(false);
  _pauseAct->setEnabled(true);
  _resumeAct->setEnabled(false);
  
  _canvas->RenderResume();
  SetStatusText(tr("Rendering resumed"), 0);
}

void RenderWindow::CreateActions() {
  _openAct = new QAction(tr("&Open..."), this);
  _openAct->setShortcuts(QKeySequence::Open);
  _openAct->setStatusTip(tr("Open an existing file"));
  connect(_openAct, &QAction::triggered, this, &RenderWindow::Open);

  _saveAct = new QAction(tr("&Save"), this);
  _saveAct->setShortcuts(QKeySequence::Save);
  _saveAct->setStatusTip(tr("Save the document to disk"));
  connect(_saveAct, &QAction::triggered, this, &RenderWindow::Save);

  _exitAct = new QAction(tr("E&xit"), this);
  _exitAct->setShortcuts(QKeySequence::Quit);
  _exitAct->setStatusTip(tr("Exit the application"));
  connect(_exitAct, &QAction::triggered, this, &QWidget::close);

  _startAct = new QAction(tr("&Start"), this);
  _startAct->setShortcut(QKeySequence(Qt::Key_Space));
  //_startAct->setStatusTip(tr("Start the render"));
  connect(_startAct, &QAction::triggered, this, &RenderWindow::Start);

  _pauseAct = new QAction(tr("&Pause"), this);
  //_startAct->setShortcut(QKeySequence(Qt::Key_A));
  //_pauseAct->setStatusTip(tr("Pause the render"));
  connect(_pauseAct, &QAction::triggered, this, &RenderWindow::Pause);

  _resumeAct = new QAction(tr("&Resume"), this);
  //_startAct->setShortcut(QKeySequence(Qt::Key_B));
  //_resumeAct->setStatusTip(tr("Resume the render"));
  connect(_resumeAct, &QAction::triggered, this, &RenderWindow::Resume);
}

void RenderWindow::CreateMenus() {
  _fileMenu = menuBar()->addMenu(tr("&File"));
  _fileMenu->addAction(_openAct);
  _fileMenu->addAction(_saveAct);
  _fileMenu->addAction(_exitAct);

  _renderMenu = menuBar()->addMenu(tr("&Render"));
  _renderMenu->addAction(_startAct);
  _renderMenu->addSeparator();
  _renderMenu->addAction(_pauseAct);
  _renderMenu->addAction(_resumeAct);
}


// ------------------------------------------------------------------------- //
// RenderCanvas
// ------------------------------------------------------------------------- //

RenderCanvas::RenderCanvas(QWidget* parent, RenderWindow* window)
   : QWidget(parent), 
     _image(NULL), 
     _w(NULL), 
     _window(window), 
     _controller(NULL), 
     _timer(NULL),
     _elapsedAtPause(0) {
  _updateTimer = new QTimer();
  connect(_updateTimer, &QTimer::timeout, this, &RenderCanvas::TimerUpdate);
}

RenderCanvas::~RenderCanvas(void) {
  if(_image != NULL)
    delete _image;
  
  if(_controller != NULL)
    delete _controller;
  
  if(_w != NULL)
    delete _w;
  
  if(_timer != NULL)
    delete _timer;
}

void RenderCanvas::SetImage(QImage* image) {
  if(image == NULL || image->isNull())
    return;
    
  _image = image;

  update();
}

QImage* RenderCanvas::GetImage(void) {
  if(_image != NULL)
    return _image;
  return new QImage();
}

void RenderCanvas::CompleteRender() {
  _controller = NULL;
  
  if(_w != NULL) {
      delete _w;
      _w = NULL;
  }
  
  if(_timer != NULL) {
      QTime timeElapsed = QTime(0, 0).addMSecs(_timer->elapsed() + _elapsedAtPause);
      QString timeString = timeElapsed.toString("'Elapsed Time: 'H:mm:ss.zzz"); // 
      _window->SetStatusText(timeString, 1);

      delete _timer;
      _timer = NULL;
  }

  emit Completed();
}

void RenderCanvas::RenderPause(void) {
  if(_controller != NULL)
    _controller->Pause();
  
  _updateTimer->stop();
  
  if(_timer != NULL)
    _elapsedAtPause = _timer->elapsed();
}

void RenderCanvas::RenderResume(void) {
  if(_controller != NULL)
    _controller->Resume();
  
  _updateTimer->start();
  
  if(_timer != NULL)
    _timer->restart();
}

void RenderCanvas::RenderStart(void) {
  _w = new World();
  
  _window->SetStatusText("Building world...", 0);
  _w->Build();

  if(_w->tracerPtr() == NULL) {
    _window->SetStatusText("ERROR: Tracer not set, skipping render", 0);
    return;
  }

  _window->SetStatusText("Rendering...", 0);
  const int w = std::max(300, _w->viewPlane().hres());
  const int h = _w->viewPlane().vres();
  _window->setFixedSize(w, h);

  _pixelsRendered = 0;
  _pixelsToRender = _w->viewPlane().hres() * _w->viewPlane().vres();

  // Set background
  QImage* temp = new QImage(_w->viewPlane().hres(), _w->viewPlane().vres(), QImage::Format_RGB32);
  temp->fill(QColor(50, 50, 50));
  SetImage(temp);

  _updateTimer->start(250);

  //start timer
  _timer = new QElapsedTimer();
  _timer->start();
  
  _controller = new RenderController(this, _w);
  emit _controller->Start();
}

void RenderCanvas::TimerUpdate() {
  if(_timer == NULL)
    return;

  //percent
  float completed = (float)_pixelsRendered / (float)_pixelsToRender;
      
  QString progressString = QString("Rendering...%1%").arg((int)(completed*100));
  _window->SetStatusText(progressString , 0);

  //time elapsed
  long elapsed = _timer->elapsed() + _elapsedAtPause;
  QTime timeElapsed = QTime(0, 0).addMSecs(elapsed);
  
  //time remaining
  float remaining = 1.0f - completed;
  long msecRemaining = (long)(((double)elapsed / (completed*100)) * 100 * remaining);
  QTime timeRemaining = QTime(0, 0).addMSecs(msecRemaining);
  
  QString timeRemainingString = timeRemaining.toString("' / ETA: 'H:mm:ss.zzz");
  QString timeString = timeElapsed.toString("'Elapsed Time: 'H:mm:ss.zzz");

  //only display ETA if something has been completed
  if(msecRemaining >= 0)
    _window->SetStatusText(timeString + timeRemainingString, 1);
  else
    _window->SetStatusText(timeString, 1);
}

void RenderCanvas::UpdatePixels(std::vector<RenderPixel*>* pixels) {
  for (std::vector<RenderPixel*>::iterator itr = pixels->begin(); 
      itr != pixels->end(); itr++) {
    RenderPixel* pixel =* itr;
    const QColor color(pixel->r, pixel->g, pixel->b);
    _image->setPixelColor(pixel->x, pixel->y, color);

    _pixelsRendered++;
    delete pixel;
  }
  update();
}

void RenderCanvas::paintEvent(QPaintEvent* event) {
  QWidget::paintEvent(event);
  QPainter painter(this);
  if(!(_image == NULL) && !(_image->isNull()))
    painter.drawImage(0, 0, *_image);
}


// ------------------------------------------------------------------------- //
// RenderController
// ------------------------------------------------------------------------- //

RenderController::RenderController(RenderCanvas* c, World* w) {
  RenderWorker* worker = new RenderWorker(w, &_workerThread);
  worker->moveToThread(&_workerThread);

  connect(&_workerThread, &QThread::finished, worker, &QObject::deleteLater);
  connect(this, &RenderController::Start, worker, &RenderWorker::Run);
  connect(this, &RenderController::Terminate, worker, &RenderWorker::Terminate);

  connect(worker, &RenderWorker::Completed, c, &RenderCanvas::CompleteRender);
  connect(worker, &RenderWorker::PixelsUpdated, c, &RenderCanvas::UpdatePixels);
  _workerThread.start();
}

RenderController::~RenderController() {
  _workerThread.terminate();
  _workerThread.wait();
}

void RenderController::Pause() {
  _workerThread.RequestPause(true);
}

void RenderController::Resume() {
  _workerThread.RequestPause(false);
}

// ------------------------------------------------------------------------- //
// RenderWorker
// ------------------------------------------------------------------------- //

RenderWorker::RenderWorker(World* w, RenderThread* thread) {
  _world = w;
  _thread = thread;
  _world->paintArea(this);
}

void RenderWorker::SendUpdate() {
  _timer->restart();
  
  //copy rendered pixels into a new vector and reset
  std::vector<RenderPixel*>* pixelsUpdate = new std::vector<RenderPixel*>(_pixels);
  _pixels.clear();
  
  emit PixelsUpdated(pixelsUpdate);
}

void RenderWorker::SetPixel(int x, int y, int red, int green, int blue) {
  _pixels.push_back(new RenderPixel(x, y, red, green, blue));

  // If a thread interruption is issued (i.e. pause), wait for resume
  // TODO: Holding onto the thread in the workers probably isn't the safest
  while (_thread->IsPauseRequested()) { }

  if(_timer->elapsed() > 40) {
    SendUpdate();
  }
}

void* RenderWorker::Run() {
  _timer = new QElapsedTimer();
  _timer->start();
  
  _world->RenderScene();
  Terminate();

  return NULL;
}

void RenderWorker::Terminate() {
  SendUpdate();
  emit Completed();
}
