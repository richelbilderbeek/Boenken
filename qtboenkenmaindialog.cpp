


#include "qtboenkenmaindialog.h"

#include <cassert>
#include <cstdlib>


#include <QScreen>
#include <QKeyEvent>
#include <QPainter>

#include "qtboenkengame.h"
#include "ui_qtboenkenmaindialog.h"



///All parameters are fed into the contructor
ribi::bnkn::QtMainDialog::QtMainDialog(
  const bnkn::Game& game,
  QWidget *parent
)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtBoenkenMainDialog),
    m_background{game.getWidth(),game.getHeight()},
    m_timer{new QTimer(this)},
    m_timer_countdown{new QTimer(this)},
    m_game{game},
    m_verbose{false}
{
  ui->setupUi(this);


  ///Set GUI size to Boenken size
  this->setGeometry(0,0,m_game.getWidth(),m_game.getHeight());
  ///Size the black background

  Paint(m_background,1,1,1); //Black
#ifndef Q_OS_WASM
  ///Put the dialog in the screen center
  const QRect screen = this->screen()->availableGeometry();
  this->move( screen.center() - this->rect().center() );
#endif

  ///Disallow resize from now on
  this->setFixedWidth(m_game.getWidth());
  this->setFixedHeight(m_game.getHeight());

  ///Start the timer
  QObject::connect(
    m_timer,&QTimer::timeout,
    this,&ribi::bnkn::QtMainDialog::onTimer
  );
  QObject::connect(
    m_timer_countdown,&QTimer::timeout,
    this,&ribi::bnkn::QtMainDialog::onCountdownTimer
  );
  m_timer_countdown->start(1000);
}

ribi::bnkn::QtMainDialog::~QtMainDialog() noexcept
{
  m_timer->stop();
  m_timer_countdown->stop();
  delete ui;
}

void ribi::bnkn::QtMainDialog::paintEvent(QPaintEvent*)
{
  //if (m_verbose) { TRACE(__func__); }
  QPainter painter(this);

  ///Draw background on painter
  painter.drawPixmap(rect(),m_background);

  ///Draw all sprites on painter
  {
    //Set the pen to white and 3 pixels wide
    QPen pen = painter.pen();
    pen.setWidth(3);
    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);
  }
  ///Call Boenken to draw the sprites
  m_game.drawPlayers(painter);
  ///Draw score on painter
  {
    QFont font = painter.font();
    font.setFamily("Courier");
    painter.setFont(font);
    const std::pair<int,int> scores = m_game.GetScore();
    const QString score_left
      = QString::number(scores.first);
    const QString score_right
      = QString::number(scores.second);
    painter.drawText(120,0,80,20,0,score_left);
    painter.drawText(440,0,80,20,0,score_right);
  }
}

void ribi::bnkn::QtMainDialog::keyPressEvent(QKeyEvent * e)
{
  assert(e->type() == QEvent::KeyPress);
  if (e->key() == Qt::Key_Escape)
  {
    close();
    return;
  }
  m_game.pressKey(e->key());
}

///This method gives the game 1000 msecs time
///to do those magical start-up things...
void ribi::bnkn::QtMainDialog::onCountdownTimer()
{
  //if (m_verbose) { TRACE(__func__); }
  m_timer_countdown->stop();
  m_timer->start(20);
}

///The main method when not training:
///every 50msec the Sprites
///move and are drawn to the screen
void ribi::bnkn::QtMainDialog::onTimer()
{
  //if (m_verbose) { TRACE(__func__); }
  ///Boenken moves all sprites
  m_game.tick();
  ///Repaint the screen
  this->repaint();
}

void ribi::bnkn::Paint(
  QPixmap& pixmap,
  const unsigned char r,
  const unsigned char g,
  const unsigned char b,
  const unsigned char a
)
{
  const int width = pixmap.width();
  const int height = pixmap.height();

  QImage image = pixmap.toImage();

  assert(image.bytesPerLine() / width == 4
    && "Assume there are 4 bytes per pixel");

  for (int y=0; y!=height; ++y)
  {
    unsigned char * const line
      = static_cast<unsigned char *>(image.scanLine(y));
    for (int x=0; x!=width; ++x)
    {
      line[x*4+3] = a; //Alpha value
      line[x*4+2] = r; //Red
      line[x*4+1] = g; //Green
      line[x*4+0] = b; //Blue
    }
  }
  pixmap = pixmap.fromImage(image);
}
