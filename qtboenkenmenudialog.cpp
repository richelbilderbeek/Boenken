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
#include "ui_qtboenkenmenudialog.h"

#pragma GCC diagnostic pop

ribi::bnkn::QtMenuDialog::QtMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtBoenkenMenuDialog),
    m_controls{new QtControlsDialog(this)},
    m_players{new QtPlayersDialog(this)},
    m_arena{new QtArenaDialog(this)}
{
  ui->setupUi(this);
  QObject::connect(ui->button_set_controls,SIGNAL(clicked(bool)),this,SLOT(onControlsClick()));
  QObject::connect(ui->button_set_players ,SIGNAL(clicked(bool)),this,SLOT(onPlayersClick()) );
  QObject::connect(ui->button_set_arena   ,SIGNAL(clicked(bool)),this,SLOT(onArenaClick())   );
  QObject::connect(ui->button_start       ,SIGNAL(clicked(bool)),this,SLOT(onStartClick())   );
  QObject::connect(ui->button_about       ,SIGNAL(clicked(bool)),this,SLOT(onAboutClick())   );
  QObject::connect(ui->button_quit        ,SIGNAL(clicked(bool)),this,SLOT(close())          );
}

ribi::bnkn::QtMenuDialog::~QtMenuDialog() noexcept
{
  delete ui;
}

std::vector<ribi::bnkn::SpritePlayer> ribi::bnkn::CreatePlayers(
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
      const double face_angle = i % 2 ? 1.5 * pi : 0.5 * pi;
      const unsigned char r = (i % 2 ?   0 : 255);
      const unsigned char g = 0;
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
      const unsigned char g = 0;
      const unsigned char b = (i % 2 ? 255 :   0);
      const double face_angle = angle
        + (a.formation == Formation::circle_inward ? pi : 0.0);

      SpritePlayer p(x,y,face_angle,size,r,g,b);
      v.push_back(p);
    }
  }

  return v;
}

std::vector<ribi::bnkn::SpriteBall> ribi::bnkn::CreateBalls(
  const ArenaSettings& a) noexcept
{
  const int size = 32;
  //A ball is always green
  const unsigned char r =   0;
  const unsigned char g = 255;
  const unsigned char b =   0;
  std::vector<SpriteBall> v;
  if (a.n_balls == 1)
  {
    const double x{static_cast<double>((a.screen_size.first ) / 2 - (size / 2))};
    const double y{static_cast<double>((a.screen_size.second) / 2 - (size / 2))};
    SpriteBall s{x,y,size,r,g,b};
    v.push_back(s);
    return v;
  }
  assert(a.n_balls == 2);
  const double x1{static_cast<double>(a.screen_size.first / 2) - size};
  const double x2{x1 + size + 1.0};
  const double y{static_cast<double>((a.screen_size.second / 2)- (size / 2))};
  SpriteBall s1{x1,y,size,r,g,b};
  SpriteBall s2{x2,y,size,r,g,b};
  v.push_back(s1);
  v.push_back(s2);
  return v;
}

///Always creates the four goalposts
std::vector<ribi::bnkn::SpriteNonMoving> ribi::bnkn::CreateObstacles(
  const ArenaSettings& a
)
{
  const int size{32};
  //A obstacle is always grey
  const unsigned char r{255};
  const unsigned char g{255};
  const unsigned char b{255};

  std::vector<SpriteNonMoving> v;
  {
    //Top-left goalpost
    const double x{static_cast<double>(0)};
    const double y{static_cast<double>(a.screen_size.second / 4)};
    SpriteNonMoving s{x,y,size,r,g,b};
    v.push_back(s);
  }
  {
    //Bottom-left goalpost
    const double x{static_cast<double>(0)};
    const double y{static_cast<double>(3 * a.screen_size.second / 4)};
    SpriteNonMoving s{x,y,size,r,g,b};
    v.push_back(s);
  }
  {
    //Top-left goalpost
    const double x{static_cast<double>(a.screen_size.first - size)};
    const double y{static_cast<double>(a.screen_size.second / 4)};
    SpriteNonMoving s{x,y,size,r,g,b};
    v.push_back(s);
  }
  {
    //Bottom-left goalpost
    const double x{static_cast<double>(a.screen_size.first - size)};
    const double y{static_cast<double>(3 * a.screen_size.second / 4)};
    SpriteNonMoving s{x,y,size,r,g,b};
    v.push_back(s);
  }
  if (a.n_obstacles == 2)
  {
    {
      //Left obstacle
      const double x{static_cast<double>(( (1 * a.width() ) / 8) - (size / 2))};
      const double y{static_cast<double>(( (1 * a.height()) / 2) - (size / 2))};
      SpriteNonMoving s{x,y,size,r,g,b};
      v.push_back(s);
    }
    {
      //Right obstacle
      const double x{static_cast<double>(( (7 * a.width() ) / 8) - (size / 2))};
      const double y{static_cast<double>(( (1 * a.height()) / 2) - (size / 2))};
      SpriteNonMoving s{x,y,size,r,g,b};
      v.push_back(s);
    }

  }
  return v;
}

void ribi::bnkn::QtMenuDialog::onControlsClick()
{
  this->ShowChild(m_controls);
}

void ribi::bnkn::QtMenuDialog::onPlayersClick()
{
  this->ShowChild(m_players);
}

void ribi::bnkn::QtMenuDialog::onArenaClick()
{
  this->ShowChild(m_arena);
}

void ribi::bnkn::QtMenuDialog::onStartClick()
{
  const ArenaSettings a{this->m_arena->GetSettings()};
  const Controls c{this->m_controls->GetControls()};
  const std::vector<SpritePlayer> players{CreatePlayers(a)};
  const std::vector<SpriteBall> balls{CreateBalls(a)};
  const std::vector<SpriteNonMoving> obstacles{CreateObstacles(a)};
  const Game b{a,c,players,balls,obstacles};
  QtMainDialog d{b};

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
