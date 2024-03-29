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
#ifndef SOLARUS_CONVEYOR_BELT_H
#define SOLARUS_CONVEYOR_BELT_H

#include "Common.h"
#include "entities/Detector.h"

/**
 * @brief A special terrain where the hero is moved towards a specific direction.
 *
 * The hero cannot resist to the movement of the conveyor belt.
 */
class ConveyorBelt: public Detector {

  public:

    ConveyorBelt(Layer layer, int x, int y, int direction);
    ~ConveyorBelt();
    static CreationFunction parse;

    EntityType get_type();

    bool is_obstacle_for(MapEntity &other);
    void notify_collision(MapEntity &entity_overlapping, CollisionMode collision_mode);
};

#endif

