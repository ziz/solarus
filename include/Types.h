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

/**
 * @file Types.h
 * @brief Some declarations of types.
 *
 * This header is included by Common.h and every class header file should include Common.h.
 */

#ifndef SOLARUS_TYPES_H
#define SOLARUS_TYPES_H

#include <stdint.h>
#include <string>

/*
 * Types of the id of each resource.
 */
typedef std::string ImageId;
typedef uint32_t MapId;
typedef uint32_t TilesetId;
typedef std::string MusicId;
typedef std::string SoundId;
typedef std::string SpriteAnimationSetId;

/*
 * Messages.
 */
typedef std::string MessageId;

/*
 * Declaration of all classes to avoid dependencies between the header files.
 */

// main classes
class Solarus;
class Screen;
class Configuration;
class KeysEffect;

// low level
class System;
class FileTools;
class VideoManager;
class Surface;
class TextSurface;
class Color;
class Sound;
class Music;
class SpcDecoder;
class ItDecoder;
class Random;
class Geometry;
class Rectangle;
class PixelBits;
class IniFile;
class InputEvent;
class Debug;
class StringConcat;

// menus
class LanguageScreen;
class TitleScreen;
class SelectionMenu;
class SelectionMenuPhase;
class SelectionMenuEraseFile;
class SelectionMenuConfirmErase;
class SelectionMenuChooseName;
class SelectionMenuChooseMode;
class SelectionMenuOptions;
class PauseMenu;
class PauseSubmenu;
class PauseSubmenuInventory;
class PauseSubmenuMap;
class PauseSubmenuQuestStatus;
class PauseSubmenuOptions;
class StringResource;

// game
class Game;
class GameControls;
class Savegame;
class Equipment;
class ItemProperties;
class InventoryItem;
class DebugKeys;
class Dungeon;
class Treasure;
class Map;
class MapLoader;
class DialogBox;
class Message;
class Timer;
class GameoverSequence;
class Camera;

// scripts
class Script;
class MapScript;
class ItemScript;
class EnemyScript;

// HUD
class HUD;
class HudElement;
class ActionIcon;
class SwordIcon;
class PauseIcon;
class ItemIcon;
class Counter;
class HeartsView;
class RupeesCounter;
class MagicBar;
class SmallKeysCounter;
class FloorView;

// sprites
class Sprite;
class SpriteAnimationSet;
class SpriteAnimation;
class SpriteAnimationDirection;

// transition effects
class Transition;
class TransitionFade;
class TransitionImmediate;
class TransitionScrolling;

// map entities
class MapEntities;
class MapEntity;
class Hero;
class HeroSprites;
class Tile;
class DynamicTile;
class Detector;
class Teletransporter;
class DestinationPoint;
class PickableItem;
class CarriedItem;
class DestructibleItem;
class Chest;
class JumpSensor;
class Enemy;
class CustomEnemy;
class EnemyReaction;
class InteractiveEntity;
class Block;
class Switch;
class CustomObstacle;
class Sensor;
class CrystalSwitch;
class CrystalSwitchBlock;
class ShopItem;
class Boomerang;
class Arrow;
class ConveyorBelt;
class Stairs;
class Door;
class Explosion;
class Bomb;
class Fire;
class Hookshot;

// tile patterns
class Tileset;
class TilePattern;
class SimpleTilePattern;
class AnimatedTilePattern;
class ParallaxTilePattern;
class ScrollingTilePattern;

// movements
class Movement;
class RectilinearMovement;
class SmoothMovement;
class PlayerMovement;
class TemporalMovement;
class PixelMovement;
class FallingOnFloorMovement;
class JumpMovement;
class PathMovement;
class RandomPathMovement;
class PathFindingMovement;
class PathFinding;
class RandomMovement;
class FollowMovement;
class TargetMovement;
class CircleMovement;

#endif

