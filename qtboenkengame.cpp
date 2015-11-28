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
#include "qtboenkengame.h"

#include <sstream>

#include <QPainter>

#include "boenkenarenasettings.h"
#include "qtboenkensprite.h"
#include "qtboenkenspriteball.h"
#include "qtboenkenspritemoving.h"
#include "qtboenkenspritenonmoving.h"
#include "qtboenkenspriteplayer.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::bnkn::Game::Game(
  const ArenaSettings& arena_settings,
  const Controls& controls,
  const std::vector<SpritePlayer>& players,
  const std::vector<SpriteBall>& balls,
  const std::vector<SpriteNonMoving>& obstacles
)
  : m_players{players},
    m_balls{balls},
    m_obstacles{obstacles},
    //m_moving_sprites{},
    //m_sprites{},
    m_arena_settings{arena_settings},
    m_controls{controls},
    m_verbose{false}
{
  #ifndef NDEBUG
  Test();
  #endif
  //m_moving_sprites = CollectMovingSprites(m_players,m_balls);
  //m_sprites = CollectSprites(m_players,m_balls,m_obstacles);


  ///Reset the score to 0-0
  SpriteBall::ResetScore();

  ///Set the friction
  SpriteMoving::SetFriction(m_arena_settings.friction);

  ///Set the arena size for the Sprites
  Sprite::setArenaSize(this->getWidth(),this->getHeight());

  assert(m_obstacles.size() >= 4  && "There must be at least four goal posts");

  ///Set the goal area
  const double goal_y_top    = m_obstacles[0].getY();
  const double goal_y_bottom = m_obstacles[1].getY();
  assert(goal_y_top <= goal_y_bottom);
  SpriteBall::SetGoalPoles(goal_y_top,goal_y_bottom);
}

std::vector<ribi::bnkn::SpriteMoving*> ribi::bnkn::Game::CollectMovingSprites(
  std::vector<SpritePlayer>& players,
  std::vector<SpriteBall>& balls
) noexcept
{
  std::vector<SpriteMoving*> v;
  for(auto& i: players)
  {
    SpriteMoving * const s = &i;
    assert(s);
    v.push_back(s);
  }
  for(auto& i: balls)
  {
    SpriteMoving * const s = &i;
    assert(s);
    v.push_back(s);
  }
  return v;
}

std::vector<const ribi::bnkn::Sprite*> ribi::bnkn::Game::CollectSprites(
  const std::vector<SpritePlayer>& players,
  const std::vector<SpriteBall>& balls,
  const std::vector<SpriteNonMoving>& obstacles
) noexcept
{
  std::vector<const Sprite*> v;
  for(auto& i: players)
  {
    v.push_back(&i);
  }
  for(auto& i: balls)
  {
    v.push_back(&i);
  }
  for(auto& i: obstacles)
  {
    v.push_back(&i);
  }
  return v;
}

void ribi::bnkn::Game::drawPlayers(QPainter& painter) const
{
  for(const auto s: CollectSprites(m_players,m_balls,m_obstacles))
  {
    s->Draw(painter);
  }
}

int ribi::bnkn::Game::getHeight() const noexcept
{
  return m_arena_settings.height();
}

std::pair<int,int> ribi::bnkn::Game::GetScore() const noexcept
{
  return SpriteBall::GetScore();
}

int ribi::bnkn::Game::getWidth() const noexcept
{
  return m_arena_settings.width();
}


void ribi::bnkn::Game::pressKey(const int key)
{
  if (m_verbose) { std::stringstream msg; msg << __func__ << ": key '" << key << "' pressed"; TRACE(msg.str()); }
  const int n_players{static_cast<int>(m_controls.m_names.size())};
  for (int i=0; i!=n_players; ++i)
  {
    if (key == m_controls.m_keys_accel[i]) {
      if (m_verbose) { std::stringstream msg; msg << __func__ << ": player[" << i << "] accelerates"; TRACE(msg.str()); }
      m_players[i].Accelerate();
    }
    if (key == m_controls.m_keys_turn[i] ) {
      if (m_verbose) { std::stringstream msg; msg << __func__ << ": player[" << i << "] turns right"; TRACE(msg.str()); }
      m_players[i].TurnRight();
    }
  }
  if (key == Qt::Key_F2) std::exit(1);
}

#ifndef NDEBUG
void ribi::bnkn::Game::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    SpritePlayer p{0.0,0.0,0.0,8,0,0,0};
  }
  {
    const SpriteBall b{0.0,0.0};
  }
  {
    const SpriteNonMoving p{0.0,0.0};
  }
  {
    ArenaSettings arena_settings;
    const Controls controls;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif // NDEBUG

///Moves all sprites
void ribi::bnkn::Game::tick()
{
  std::vector<SpriteMoving*> moving_sprites{CollectMovingSprites(m_players,m_balls)};

  ///Move all moving sprites
  for(SpriteMoving* const s: moving_sprites)
  {
    assert(s);
    s->Move();
  }

  ///Check all moving sprite collisions with moving sprites
  {
    for(SpriteMoving* const s1: moving_sprites)
    {
      for(SpriteMoving* const s2: moving_sprites)
      {
        assert(s1);
        assert(s2);
        if (s1 <= s2) continue;
        SpritePlayer::Collision(s1,s2);
      }
    }
  }

  ///Check all moving sprite collisions with non-moving sprites
  {
    for(const auto& s1: m_obstacles)
    {
      for(const auto& s2: moving_sprites)
      {
        SpriteNonMoving::Collision(s1,*s2);
      }
    }
  }
}
