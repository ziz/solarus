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
#ifndef SOLARUS_RECTILINEAR_MOVEMENT_H
#define SOLARUS_RECTILINEAR_MOVEMENT_H

#include "Common.h"
#include "movements/Movement.h"

/**
 * @brief A straight movement represented as a speed vector
 * whose properties (speed and angle) can be changed.
 *
 * Properties:
 * - speed
 * - angle
 * - ignore_obstacles
 */
class RectilinearMovement: public Movement {

  private:

    // speed vector
    double angle;                               /**< angle between the speed vector and the horizontal axis in radians */
    double x_speed;				/**< X speed of the object to move in pixels per second.
						 * 0: stopped
						 * positive value: moving to the right
						 * negative value: moving to the left */
    double y_speed;				/**< Y speed of the object to move in pixels per second.
						 * 0: stopped
						 * positive value: moving downwards
						 * negative value: moving upwards */

    uint32_t next_move_date_x;			/**< Date of the next x move in ticks. */
    uint32_t next_move_date_y;			/**< Date of the next y move in ticks. */

    // the following fields are redundant and can be computed from x_speed and y_speed
    uint32_t x_delay;				/**< Delay in ticks between an x move of 1 pixel.
						 * x_delay = 200 / |x_speed| */
    uint32_t y_delay;				/**< Delay in ticks between an y move of 1 pixel.
						 * y_delay = 200 / |y_speed| */
    int x_move;					/**< Number of pixels of the next x move : 0, 1 or -1. */
    int y_move;					/**< Number of pixels of the next y move : 0, 1 or -1. */

  protected:

    int get_x_move();
    int get_y_move();
    void set_x_move(int x_move);
    void set_y_move(int y_move);

    uint32_t get_next_move_date_x();
    uint32_t get_next_move_date_y();
    void set_next_move_date_x(uint32_t next_move_date_x);
    void set_next_move_date_y(uint32_t next_move_date_y);

    uint32_t get_x_delay();
    uint32_t get_y_delay();
    void set_x_delay(uint32_t x_delay);
    void set_y_delay(uint32_t y_delay);

    virtual void update_x();
    virtual void update_y();

  public:

    RectilinearMovement(bool ignore_obstacles = false);
    virtual ~RectilinearMovement();

    virtual void update();
    virtual void set_suspended(bool suspended);
    bool has_to_move_now();

    // speed vector
    double get_x_speed();
    double get_y_speed();
    double get_speed();
    void set_x_speed(double x_speed);
    void set_y_speed(double y_speed);
    void set_speed(double speed);
    double get_angle();
    void set_angle(double angle);
    int get_displayed_direction4();

    // movement
    virtual bool is_started();
    void stop();

    // properties
    virtual const std::string get_property(const std::string &key);
    virtual void set_property(const std::string &key, const std::string &value);
};

/**
 * @brief Returns the number of pixels of the next x move.
 * @return the number of pixels of the next x move: 0, 1 or -1
 */
inline int RectilinearMovement::get_x_move() {
  return x_move;
}

/**
 * @brief Returns the number of pixels of the next y move.
 * @return the number of pixels of the next y move: 0, 1 or -1
 */
inline int RectilinearMovement::get_y_move() {
  return y_move;
}

/**
 * @brief Sets the number of pixels of the next x move.
 * @param x_move the number of pixels of the next x move: 0, 1 or -1
 */
inline void RectilinearMovement::set_x_move(int x_move) {
  this->x_move = x_move;
}

/**
 * @brief Sets the number of pixels of the next y move.
 * @param y_move the number of pixels of the next y move: 0, 1 or -1
 */
inline void RectilinearMovement::set_y_move(int y_move) {
  this->y_move = y_move;
}

/**
 * @brief Returns the date of the next x move
 * @return the date of the next x move
 */
inline uint32_t RectilinearMovement::get_next_move_date_x() {
  return next_move_date_x;
}

/**
 * @brief Returns the date of the next y move
 * @return the date of the next y move
 */
inline uint32_t RectilinearMovement::get_next_move_date_y() {
  return next_move_date_y;
}

/**
 * @brief Returns the delay between two x moves
 * @return the delay between two x moves in milliseconds
 */
inline uint32_t RectilinearMovement::get_x_delay() {
  return x_delay;
}

/**
 * @brief Returns the delay between two y moves
 * @return the delay between two y moves in milliseconds
 */
inline uint32_t RectilinearMovement::get_y_delay() {
  return y_delay;
}

/**
 * @brief Sets the delay between two x moves
 * @param x_delay the delay between two x moves in milliseconds
 */
inline void RectilinearMovement::set_x_delay(uint32_t x_delay) {
  this->x_delay = x_delay;
}

/**
 * @brief Sets the delay between two y moves
 * @param y_delay the delay between two y moves in milliseconds
 */
inline void RectilinearMovement::set_y_delay(uint32_t y_delay) {
  this->y_delay = y_delay;
}

#endif

