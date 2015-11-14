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
#include "qtboenkenmenudialog.h"

#include <cassert>


#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/timer.hpp>

#include "boenkenarenasettings.h"
#include "boenkenmenudialog.h"
#include "qtaboutdialog.h"
#include "qtboenkenarenadialog.h"
#include "qtboenkencontrolsdialog.h"
#include "qtboenkengame.h"
#include "qtboenkenmaindialog.h"
#include "qtboenkenplayersdialog.h"
#include "qtboenkenspriteball.h"
#include "qtboenkenspritemoving.h"
#include "qtboenkenspritenonmoving.h"
#include "qtboenkenspriteplayer.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtboenkenmenudialog.h"

#pragma GCC diagnostic pop

ribi::bnkn::QtMenuDialog::QtMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtBoenkenMenuDialog),
    m_controls(new QtControlsDialog),
    m_players( new QtPlayersDialog),
    m_arena(new QtArenaDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  QObject::connect(ui->button_set_controls,&QAbstractButton::clicked,this,&ribi::bnkn::QtMenuDialog::onControlsClick);
  QObject::connect(ui->button_set_players ,&QAbstractButton::clicked,this,&ribi::bnkn::QtMenuDialog::onPlayersClick );
  QObject::connect(ui->button_set_arena   ,&QAbstractButton::clicked,this,&ribi::bnkn::QtMenuDialog::onArenaClick   );
  QObject::connect(ui->button_start       ,&QAbstractButton::clicked,this,&ribi::bnkn::QtMenuDialog::onStartClick   );
  QObject::connect(ui->button_about       ,&QAbstractButton::clicked,this,&ribi::bnkn::QtMenuDialog::onAboutClick   );
  QObject::connect(ui->button_quit        ,&QAbstractButton::clicked,this,&ribi::bnkn::QtMenuDialog::close          );
}

ribi::bnkn::QtMenuDialog::~QtMenuDialog() noexcept
{
  delete ui;
}

std::vector<ribi::bnkn::SpritePlayer> ribi::bnkn::QtMenuDialog::CreatePlayers(
  const ArenaSettings& a)
{
  //Create two
  std::vector<SpritePlayer> v;
  const int n_players = 2;
  const int size = 32;

  const double mid_x
    = boost::numeric_cast<double>(a.screen_size.first) / 2.0;
  const double mid_y
    = boost::numeric_cast<double>(a.screen_size.second) / 2.0;

  if (a.formation == Formation::straight_line)
  {
    const int x_left  = (1 * (a.width() / 4) ) - (size / 2);
    const int x_right = (3 * (a.width() / 4) ) - (size / 2);
    const int players_height = size * (n_players / 2);
    int y = (a.height()) / 2 - (players_height / 2);
    for (int i=0; i!=n_players; ++i,y+=(size/2))
    {
      const int x = (i % 2 ? x_right : x_left);
      const double pi = boost::math::constants::pi<double>();
      const double face_angle = (i % 2 ? 1.5 * pi : 0.5 * pi);
      const unsigned char r = (i % 2 ?   0 : 255);
      const unsigned char g = (i % 2 ?   0 :   0);
      const unsigned char b = (i % 2 ? 255 :   0);
      SpritePlayer p(x,y,face_angle,size,r,g,b);
      v.push_back(p);
    }

  }
  else
  {
    assert(a.formation == Formation::circle_inward || a.formation == Formation::circle_outward);
    const double ray_x = mid_x / 2.0;
    const double ray_y = mid_y / 2.0;
    const double pi = boost::math::constants::pi<double>();
    const double d_angle = (2.0 * pi) / boost::numeric_cast<double>(n_players);
    double angle = 1.5 * pi;

    for (int i=0; i!=n_players; ++i,angle+=d_angle)
    {
      const double x
       = mid_x + (std::sin(angle) * ray_x)
       - (boost::numeric_cast<double>(size) / 2.0);
      const double y
        = mid_y - (std::cos(angle) * ray_y)
        - (boost::numeric_cast<double>(size) / 2.0);
      const unsigned char r = (i % 2 ?   0 : 255);
      const unsigned char g = (i % 2 ?   0 :   0);
      const unsigned char b = (i % 2 ? 255 :   0);
      const double face_angle = angle
        + (a.formation == Formation::circle_inward ? pi : 0.0);

      SpritePlayer p(x,y,face_angle,size,r,g,b);
      v.push_back(p);
    }
  }

  return v;
}

std::vector<boost::shared_ptr<ribi::bnkn::SpriteBall> > ribi::bnkn::QtMenuDialog::CreateBalls(
  const bnkn::ArenaSettings& a)
{
  const int size = 32;
  //A ball is always green
  const unsigned char r =   0;
  const unsigned char g = 255;
  const unsigned char b =   0;
  std::vector<boost::shared_ptr<bnkn::SpriteBall> > v;
  switch (a.n_balls)
  {
    case 1:
    {
      const int x
        = a.screen_size.first / 2 - (size / 2);
      const int y
        = a.screen_size.second / 2 - (size / 2);
      boost::shared_ptr<bnkn::SpriteBall> s(
        new bnkn::SpriteBall(x,y,size,r,g,b));
      assert(s);
      v.push_back(s);
    }
    break;
    case 2:
    {
      const int x1
        = (a.screen_size.first / 2)
        - size;
      const int x2 = x1 + size + 1;
      const int y
        = (a.screen_size.second / 2)
        - (size / 2);
      boost::shared_ptr<bnkn::SpriteBall> s1(
        new bnkn::SpriteBall(x1,y,size,r,g,b));
      boost::shared_ptr<bnkn::SpriteBall> s2(
        new bnkn::SpriteBall(x2,y,size,r,g,b));
      assert(s1);
      assert(s2);
      v.push_back(s1);
      v.push_back(s2);
    }
    break;
    default:
      assert(!"Should not get here");
  }
  return v;
}

///Always creates the four goalposts
std::vector<boost::shared_ptr<ribi::bnkn::SpriteNonMoving> > ribi::bnkn::QtMenuDialog::CreateObstacles(
  const bnkn::ArenaSettings& a)
{
  const int size = 32;
  //A obstacle is always grey
  const unsigned char r = 255;
  const unsigned char g = 255;
  const unsigned char b = 255;

  std::vector<boost::shared_ptr<bnkn::SpriteNonMoving> > v;
  {
    //Top-left goalpost
    const int x = 0;
    const int y = a.screen_size.second / 4;
    boost::shared_ptr<bnkn::SpriteNonMoving> s(
      new bnkn::SpriteNonMoving(x,y,size,r,g,b));
    v.push_back(s);
  }
  {
    //Bottom-left goalpost
    const int x = 0;
    const int y = 3 * a.screen_size.second / 4;
    boost::shared_ptr<bnkn::SpriteNonMoving> s(
      new bnkn::SpriteNonMoving(x,y,size,r,g,b));
    assert(s);
    v.push_back(s);
  }
  {
    //Top-left goalpost
    const int x = a.screen_size.first - size;
    const int y = a.screen_size.second / 4;
    boost::shared_ptr<bnkn::SpriteNonMoving> s(
      new bnkn::SpriteNonMoving(x,y,size,r,g,b));
    assert(s);
    v.push_back(s);
  }
  {
    //Bottom-left goalpost
    const int x = a.screen_size.first - size;
    const int y = 3 * a.screen_size.second / 4;
    boost::shared_ptr<bnkn::SpriteNonMoving> s(
      new bnkn::SpriteNonMoving(x,y,size,r,g,b));
    assert(s);
    v.push_back(s);
  }
  if (a.n_obstacles == 2)
  {
    {
      //Left obstacle
      const int x = ( (1 * a.width() ) / 8) - (size / 2);
      const int y = ( (1 * a.height()) / 2) - (size / 2);
      boost::shared_ptr<bnkn::SpriteNonMoving> s(
        new bnkn::SpriteNonMoving(x,y,size,r,g,b));
      assert(s);
      v.push_back(s);
    }
    {
      //Right obstacle
      const int x = ( (7 * a.width() ) / 8) - (size / 2);
      const int y = ( (1 * a.height()) / 2) - (size / 2);
      boost::shared_ptr<bnkn::SpriteNonMoving> s(
        new bnkn::SpriteNonMoving(x,y,size,r,g,b));
      assert(s);
      v.push_back(s);
    }

  }
  return v;
}

void ribi::bnkn::QtMenuDialog::onControlsClick()
{
  this->ShowChild(m_controls.get());
}

void ribi::bnkn::QtMenuDialog::onPlayersClick()
{
  this->ShowChild(m_players.get());
}

void ribi::bnkn::QtMenuDialog::onArenaClick()
{
  this->ShowChild(m_arena.get());
}

void ribi::bnkn::QtMenuDialog::onStartClick()
{
  const bnkn::ArenaSettings a = this->m_arena->GetSettings();
  const bnkn::Controls c = this->m_controls->GetControls();
  const std::vector<SpritePlayer> players = CreatePlayers(a);
  const std::vector<boost::shared_ptr<bnkn::SpriteBall     > > balls     = CreateBalls(a);
  const std::vector<boost::shared_ptr<bnkn::SpriteNonMoving> > obstacles = CreateObstacles(a);
  boost::shared_ptr<Game> b(new Game(a,c,players,balls,obstacles));
  assert(b);
  QtMainDialog d(0,b);

  this->hide();
  d.exec();
  this->show();
}

void ribi::bnkn::QtMenuDialog::onAboutClick()
{
  About a = bnkn::MenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

#ifndef NDEBUG
void ribi::bnkn::QtMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  bnkn::MenuDialog();
  {

    ArenaSettings a;
    a.formation = Formation::circle_inward;
    a.friction = 0.999;
    a.n_balls = 1;
    a.n_obstacles = 4;
    a.screen_size = std::make_pair(320,200);
    Controls c;
    const std::vector<SpritePlayer> players{CreatePlayers(a)};
    const std::vector<boost::shared_ptr<bnkn::SpriteBall     > > balls     = CreateBalls(a);
    const std::vector<boost::shared_ptr<bnkn::SpriteNonMoving> > obstacles = CreateObstacles(a);
    boost::shared_ptr<Game> b(new Game(a,c,players,balls,obstacles));
    assert(b);
    QtMainDialog d(0,b);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
