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
#ifndef SOLARUS_JUMP_SENSOR_H
#define SOLARUS_JUMP_SENSOR_H

#include "Common.h"
#include "entities/Detector.h"

/**
 * @brief A sensor that makes the hero jump.
 *
 * A jump sensor is a detector placed on a map.
 * When the hero touches this detetor, he makes a jump with a specified length.
 */
class JumpSensor: public Detector {

  private:

    int jump_length; /**< length of the jump in pixels (should be a multiple of 8) */

  public:

    JumpSensor(const std::string &name, Layer layer, int x, int y, int width, int height,
	int direction, int jump_length);
    ~JumpSensor();
    static CreationFunction parse;

    EntityType get_type();

    bool is_obstacle_for(MapEntity &other);
    bool is_point_in_diagonal(const Rectangle &point);
    bool test_collision_custom(MapEntity &entity);
    void notify_collision(MapEntity &entity_overlapping, CollisionMode collision_mode);
    int get_jump_length();

};

#endif

