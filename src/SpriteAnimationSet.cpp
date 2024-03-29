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
#include "SpriteAnimationSet.h"
#include "SpriteAnimation.h"
#include "SpriteAnimationDirection.h"
#include "lowlevel/FileTools.h"
#include "lowlevel/Debug.h"
#include "lowlevel/StringConcat.h"

/**
 * @brief Empty constructor.
 */
SpriteAnimationSet::SpriteAnimationSet() {

}

/**
 * @brief Loads the animations of a sprite from a file.
 * @param id id of the sprite (used to determine the sprite file)
 */
SpriteAnimationSet::SpriteAnimationSet(const SpriteAnimationSetId &id) {

  // compute the file name
  std::string file_name = (std::string) "sprites/" + id + ".dat";

  // open the file
  std::istream &sprite_file = FileTools::data_file_open(file_name);

  // read the file
  std::string line;

  Rectangle *positions_in_src;
  SpriteAnimationDirection **directions;
  std::string name, image_file_name;
  int nb_directions, nb_frames, x_origin, y_origin, loop_on_frame;
  int x, y, width, height, rows, columns;
  uint32_t frame_delay;

  // read each animation
  while (std::getline(sprite_file, line)) {

    if (line.size() == 0) {
      continue;
    }

    // first line: animation info

    std::istringstream iss0(line);
    FileTools::read(iss0, name);
    FileTools::read(iss0, image_file_name);
    FileTools::read(iss0, nb_directions);
    FileTools::read(iss0, frame_delay);
    FileTools::read(iss0, loop_on_frame);

    directions = new SpriteAnimationDirection*[nb_directions];

    for (int i = 0; i < nb_directions; i++) {

      do {
        if (!std::getline(sprite_file, line)) {
          Debug::die(StringConcat() << "Unexpected end of input in file '" << file_name << "'");
        }
      }
      while (line.size() == 0);

      std::istringstream iss(line);
      FileTools::read(iss, x);
      FileTools::read(iss, y);
      FileTools::read(iss, width);
      FileTools::read(iss, height);
      FileTools::read(iss, x_origin);
      FileTools::read(iss, y_origin);
      FileTools::read(iss, nb_frames);
      FileTools::read(iss, columns);

      if (nb_frames % columns == 0) {
        rows = nb_frames / columns;
      }
      else {
        rows = (nb_frames / columns) + 1;
      }

      positions_in_src = new Rectangle[nb_frames];
      int j = 0; // frame number
      for (int r = 0; r < rows && j < nb_frames; r++) {	
        for (int c = 0; c < columns && j < nb_frames; c++) {

          positions_in_src[j].set_xy(x + c * width, y + r * height);
          positions_in_src[j].set_size(width, height);
          j++;
        }
      }

      directions[i] = new SpriteAnimationDirection(nb_frames, positions_in_src, x_origin, y_origin);
    }

    Debug::check_assertion(animations.count(name) == 0, StringConcat() << "Animation '" << name << "' is defined twice in sprite '" << id << "'");
    animations[name] = new SpriteAnimation(image_file_name, nb_directions, directions,
					   frame_delay, loop_on_frame);

    // default animation
    if (animations.size() == 1) {
      default_animation_name = name;
    }
  }

  FileTools::data_file_close(sprite_file);
}

/**
 * @brief Destructor.
 */
SpriteAnimationSet::~SpriteAnimationSet() {

  // delete the animations
  std::map<SpriteAnimationSetId, SpriteAnimation*>::const_iterator it;

  for (it = animations.begin(); it != animations.end(); it++) {
    delete it->second;
  }
}

/**
 * @brief When the sprite is displayed on a map, sets the map.
 *
 * This function must be called if this sprite image depends on the map's tileset.
 *
 * @param map the map
 */
void SpriteAnimationSet::set_map(Map &map) {

  std::map<SpriteAnimationSetId, SpriteAnimation*>::const_iterator it;

  for (it = animations.begin(); it != animations.end(); it++) {
    it->second->set_map(map);
  }
}

/**
 * @brief Returns whether this animation set has an animation with the specified name.
 * @param animation_name an animation name
 * @return true if this animation exists
 */
bool SpriteAnimationSet::has_animation(const std::string& animation_name) const {
  return animations.count(animation_name) > 0;
}

/**
 * @brief Returns an animation.
 * @param animation_name name of the animation to get
 * @return the specified animation
 */
const SpriteAnimation * SpriteAnimationSet::get_animation(const std::string &animation_name) const {

  Debug::check_assertion(has_animation(animation_name),
      StringConcat() << "No animation '" << animation_name << "' in this animation set");

  return animations.find(animation_name)->second; // the [] operator is not const in std::map
}

/**
 * @brief Returns an animation.
 * @param animation_name name of the animation to get
 * @return the specified animation
 */
SpriteAnimation * SpriteAnimationSet::get_animation(const std::string &animation_name) {

  Debug::check_assertion(has_animation(animation_name),
      StringConcat() << "No animation '" << animation_name << "' in this animation set");

  return animations[animation_name];
}

/**
 * @brief Returns the name of the default animation, i.e. the first one.
 * @return the name of the default animation
 */
const std::string& SpriteAnimationSet::get_default_animation() const {
  return default_animation_name;
}

/**
 * @brief Enables the pixel-perfect collision detection for these animations.
 */
void SpriteAnimationSet::enable_pixel_collisions() {

  if (!are_pixel_collisions_enabled()) {

    std::map<SpriteAnimationSetId, SpriteAnimation*>::const_iterator it;

    for (it = animations.begin(); it != animations.end(); it++) {
      it->second->enable_pixel_collisions();
    }
  }
}

/**
 * @brief Returns whether the pixel-perfect collisions are enabled for these animations.
 * @return true if the pixel-perfect collisions are enabled
 */
bool SpriteAnimationSet::are_pixel_collisions_enabled() const {
  return animations.begin()->second->are_pixel_collisions_enabled();
}

