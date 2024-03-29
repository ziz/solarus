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
#ifndef SOLARUS_OBSTACLE_H
#define SOLARUS_OBSTACLE_H

/**
 * @brief Obstacle property for the entities.
 */
enum Obstacle {

  OBSTACLE_LAVA          = -6, /**< the entity is some lava */
  OBSTACLE_PRICKLE       = -5, /**< the entity is some prickles */
  OBSTACLE_LADDER        = -4, /**< the entity is a ladder and the hero walks slower on it */
  OBSTACLE_HOLE          = -3, /**< the entity is a hole */ 
  OBSTACLE_SHALLOW_WATER = -2, /**< the entity is some shallow water */
  OBSTACLE_DEEP_WATER    = -1, /**< the entity is some deep water */
  OBSTACLE_NONE          =  0, /**< the entity is normal ground without obstacle */
  OBSTACLE,                    /**< the entity is entirely an obstacle */
  OBSTACLE_TOP_RIGHT,          /**< the upper-right half of the entity is an obstacle */
  OBSTACLE_TOP_LEFT,           /**< the upper-left half of the entity is an obstacle */
  OBSTACLE_BOTTOM_LEFT,        /**< the lower-left half of the entity is an obstacle */
  OBSTACLE_BOTTOM_RIGHT,       /**< the lower-right half of the entity is an obstacle */
  OBSTACLE_EMPTY               /**< there is no ground: you should look at a lower layer */
};

#endif

