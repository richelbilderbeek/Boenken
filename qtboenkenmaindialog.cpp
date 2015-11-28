//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtboenkenmaindialog.h"

#include <cassert>
#include <cstdlib>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>

#include "qtboenkengame.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtboenkenmaindialog.h"

#pragma GCC diagnostic pop

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
  ///Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );

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

/*
void golf::QtGameOfLifeFighterWidget::OnJoystickCheck()
{
  sf::Joystick::update();
  const int key_activate{0};
  const int key_build{2};
  const int key_glider{3};
  const int key_spaceship{1};
  const int key_grower{4};

  if (sf::Joystick::isConnected(0))
  {
    //First move, then build
    RemoveKey(Key::up2);
    RemoveKey(Key::right2);
    RemoveKey(Key::down2);
    RemoveKey(Key::left2);
    if (sf::Joystick::hasAxis(0, sf::Joystick::X))
    {
      const double dx{sf::Joystick::getAxisPosition(0, sf::Joystick::X)};
      if (dx < -50.0) { AddKey(Key::left2 ); }
      if (dx >  50.0) { AddKey(Key::right2); }
    }
    if (sf::Joystick::hasAxis(0, sf::Joystick::Y))
    {
      const double dy{sf::Joystick::getAxisPosition(0, sf::Joystick::Y)};
      if (dy < -50.0) { AddKey(Key::up2  );  }
      if (dy >  50.0) { AddKey(Key::down2);  }
    }

    const bool pressed0{sf::Joystick::isButtonPressed(0,key_activate)};
    if (pressed0) { AddKey(Key::toggle_hangar2); }
    const bool pressed1{sf::Joystick::isButtonPressed(0,key_build)};
    if ( pressed1) { AddKey(Key::toggle_cell2); }
    if (!pressed1) { RemoveKey(Key::toggle_cell2); }
    const bool pressed2{sf::Joystick::isButtonPressed(0,key_glider)};
    if ( pressed2) { AddKey(Key::pattern_a2); }
    const bool pressed3{sf::Joystick::isButtonPressed(0,key_spaceship)};
    if ( pressed3) { AddKey(Key::pattern_b2); }
    const bool pressed4{sf::Joystick::isButtonPressed(0,key_grower)};
    if ( pressed4) { AddKey(Key::pattern_c2); }
  }

  if (sf::Joystick::isConnected(1))
  {
    //First move, then build
    RemoveKey(Key::up1);
    RemoveKey(Key::right1);
    RemoveKey(Key::down1);
    RemoveKey(Key::left1);
    if (sf::Joystick::hasAxis(1, sf::Joystick::X))
    {
      const double dx{sf::Joystick::getAxisPosition(1, sf::Joystick::X)};
      if (dx < -50.0) { AddKey(Key::left1 ); }
      if (dx >  50.0) { AddKey(Key::right1); }
    }
    if (sf::Joystick::hasAxis(1, sf::Joystick::Y))
    {
      const double dy{sf::Joystick::getAxisPosition(1, sf::Joystick::Y)};
      if (dy < -50.0) { AddKey(Key::up1  );  }
      if (dy >  50.0) { AddKey(Key::down1);  }
    }

    const bool pressed0{sf::Joystick::isButtonPressed(1,key_activate)};
    if (pressed0) { AddKey(Key::toggle_hangar1); }
    const bool pressed1{sf::Joystick::isButtonPressed(1,key_build)};
    if ( pressed1) { AddKey(Key::toggle_cell1); }
    if (!pressed1) { RemoveKey(Key::toggle_cell1); }
    const bool pressed2{sf::Joystick::isButtonPressed(1,key_glider)};
    if ( pressed2) { AddKey(Key::pattern_a1); }
    const bool pressed3{sf::Joystick::isButtonPressed(1,key_spaceship)};
    if ( pressed3) { AddKey(Key::pattern_b1); }
    const bool pressed4{sf::Joystick::isButtonPressed(1,key_grower)};
    if ( pressed4) { AddKey(Key::pattern_c1); }
  }
}
*/

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
      = QString(boost::lexical_cast<std::string>(scores.first).c_str());
    const QString score_right
      = boost::lexical_cast<std::string>(scores.second).c_str();
    painter.drawText(120,0,80,20,0,score_left);
    painter.drawText(440,0,80,20,0,score_right);
  }
}

void ribi::bnkn::QtMainDialog::keyPressEvent(QKeyEvent * e)
{
  assert(e->type() == QEvent::KeyPress);
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

void ribi::bnkn::QtMainDialog::Paint(
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

#ifndef NDEBUG
void ribi::bnkn::QtMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
