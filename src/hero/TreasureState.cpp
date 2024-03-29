/*
 * Copyright (C) 2009 Christopho, Solarus - http://www.solarus-engine.org
 * 
 * Solarus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Solarus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "hero/TreasureState.h"
#include "hero/FreeState.h"
#include "hero/HeroSprites.h"
#include "lowlevel/Sound.h"
#include "lua/MapScript.h"
#include "lua/ItemScript.h"
#include "ItemProperties.h"
#include "Game.h"
#include "DialogBox.h"
#include "Map.h"
#include <sstream>

/**
 * @brief Constructor.
 * @param hero the hero controlled by this state
 * @param treasure the treasure to give to the hero
 */
Hero::TreasureState::TreasureState(Hero &hero, const Treasure &treasure):
  State(hero), treasure(treasure) {

}

/**
 * @brief Destructor.
 */
Hero::TreasureState::~TreasureState() {

}

/**
 * @brief Starts this state.
 * @param previous_state the previous state
 */
void Hero::TreasureState::start(State *previous_state) {

  State::start(previous_state);

  // show the animation
  get_sprites().save_animation_direction();
  get_sprites().set_animation_brandish();

  // play the sound
  const SoundId &sound_id = treasure.get_item_properties().get_sound_when_brandished();
  Sound::play(sound_id);

  // give the treasure
  treasure.give_to_player();

  // show a message
  std::ostringstream oss;
  oss << "_treasure." << treasure.get_item_name() << "." << treasure.get_variant();
  get_dialog_box().start_dialog(oss.str());
}

/**
 * @brief Stops this state.
 * @param next_state the next state
 */
void Hero::TreasureState::stop(State *next_state) {

  State::start(next_state);

  // restore the sprite's direction
  get_sprites().restore_animation_direction();
}

/**
 * @brief Updates this state.
 */
void Hero::TreasureState::update() {

  State::update();

  if (!get_game().is_showing_message()) {

    // the treasure's dialog is over: if the treasure was a tunic,
    // a sword or a shield, we have to reload the hero's sprites now
    const std::string &item_name = treasure.get_item_name();
    if (item_name == "tunic" || item_name == "sword" || item_name == "shield") {
      hero.rebuild_equipment();
    }

    get_equipment().get_item_script(item_name).event_obtained(treasure);
    get_map_script().event_treasure_obtained(treasure);

    if (is_current_state()) { // because the script may have changed the state
      hero.set_state(new FreeState(hero));
    }
  }
}

/**
 * @brief Displays this state.
 */
void Hero::TreasureState::display_on_map() {

  State::display_on_map();

  int x = hero.get_x();
  int y = hero.get_y();

  const Rectangle &camera_position = get_map().get_camera_position();
  treasure.display(get_map().get_visible_surface(),
      x - camera_position.get_x(),
      y - 24 - camera_position.get_y());
}

/**
 * @brief Returns the action to do with an item previously carried by the hero when this state starts.
 * @param carried_item the item carried in the previous state
 * @return the action to do with a previous carried item when this state starts
 */
CarriedItem::Behavior Hero::TreasureState::get_previous_carried_item_behavior(CarriedItem& carried_item) {
  return CarriedItem::BEHAVIOR_DESTROY;
}

