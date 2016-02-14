// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.

#include "missionlose.hpp"
#include "game/game.hpp"
#include "steam.hpp"
#include "city/city.hpp"
#include "city/victoryconditions.hpp"
#include "scripting/core.hpp"
#include "core/variant_list.hpp"

namespace events
{

GameEventPtr MissionLose::create(bool force)
{
  GameEventPtr ret( new MissionLose(force) );
  ret->drop();

  return ret;
}

void MissionLose::_exec(Game& game, unsigned int)
{
  auto missionName = game.city()->victoryConditions().name();
  if (!_force)
    steamapi::missionLose( missionName );
}

bool MissionLose::_mayExec(Game&, unsigned int) const{  return true; }

MissionLose::MissionLose( bool force ) : _force(force) {}

}//end namepsace events
