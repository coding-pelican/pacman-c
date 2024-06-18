/**
 * @file pacman.c
 * @author Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 *
 * @brief Pacman game implementation.
 * @details This is a implementation of pacman game.
 *
 * @version 0.1
 * @date 2024-06-10
 *
 * @copyright Released under the MIT License. See LICENSE file for details.
 */


// #region Header_Inclusions
#include <assert.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "audio.h"
// #endregion // Header_Inclusions

// #region Display_Decls
char const* const Window_kTitle = "ASCII PACMAN";

#define Screen_kWidth  ((int)(80))
#define Screen_kHeight ((int)(25))

/*
80x25
MainMenu
"                                                                                "
"                    █████╗    ███████╗    ██████╗   ██╗   ██╗                   "
"                   ██╔══██╗   ██╔════╝   ██╔════╝   ██║   ██║                   "
"+>>>>>>>>>>>>>>>>>>███████║   ███████╗   ██║        ██║   ██║<<<<<<<<<<<<<<<<<<+"
"                   ██╔══██║   ╚════██║   ██║        ██║   ██║                   "
"                   ██║  ██║   ███████║   ╚██████╗   ██║   ██║                   "
"                   ╚═╝  ╚═╝   ╚══════╝    ╚═════╝   ╚═╝   ╚═╝                   "
"                                                                                "
"           ██████╗   █████╗   ██████╗ ███╗   ███╗  █████╗  ███╗   ██╗           "
"           ██╔══██╗ ██╔══██╗ ██╔════╝ ████╗ ████║ ██╔══██╗ ████╗  ██║           "
"+>>>>>>>>>>██████╔╝ ███████║ ██║      ██╔████╔██║ ███████║ ██╔██╗ ██║<<<<<<<<<<+"
"           ██╔═══╝  ██╔══██║ ██║      ██║╚██╔╝██║ ██╔══██║ ██║╚██╗██║           "
"           ██║      ██║  ██║ ╚██████╗ ██║ ╚═╝ ██║ ██║  ██║ ██║ ╚████║           "
"           ╚═╝      ╚═╝  ╚═╝  ╚═════╝ ╚═╝     ╚═╝ ╚═╝  ╚═╝ ╚═╝  ╚═══╝           "
"                                                                                "
"+>>>>>>>>>>>>>>>>>>>>>[ S T A R T ]<<<<++>>>>[ Q U I T ]<<<<<<<<<<<<<<<<<<<<<<<+"
"                       ^^^^^^^^^^^            ^^^^^^^^^                         "
"     __________________|      |____________________________________________     "
"          ,--.    ,--.          ,--.   ,--.                                     "
"+>>>>    |oo  | _  \  `.       | oo | |  oo|                               <<<<+"
"+>>>>o  o|~~  |(_) /   ;       | ~~ | |  ~~|o  o  o  o  o  o  o  o  o  o  o<<<<+"
"+>>>>    |/\/\|   '._,'        |/\/\| |/\/\|                               <<<<+"
"     __________________        ____________________________________________     "
"                       |      |                                                 "
"                                                                                "
*/

wchar_t const* const Menu_kBackground =
    L"                                                                                \n"
    L"                    █████╗    ███████╗    ██████╗   ██╗   ██╗                   \n"
    L"                   ██╔══██╗   ██╔════╝   ██╔════╝   ██║   ██║                   \n"
    L"                   ███████║   ███████╗   ██║        ██║   ██║                   \n"
    L"                   ██╔══██║   ╚════██║   ██║        ██║   ██║                   \n"
    L"                   ██║  ██║   ███████║   ╚██████╗   ██║   ██║                   \n"
    L"                   ╚═╝  ╚═╝   ╚══════╝    ╚═════╝   ╚═╝   ╚═╝                   \n"
    L"                                                                                \n"
    L"           ██████╗   █████╗   ██████╗ ███╗   ███╗  █████╗  ███╗   ██╗           \n"
    L"           ██╔══██╗ ██╔══██╗ ██╔════╝ ████╗ ████║ ██╔══██╗ ████╗  ██║           \n"
    L"           ██████╔╝ ███████║ ██║      ██╔████╔██║ ███████║ ██╔██╗ ██║           \n"
    L"           ██╔═══╝  ██╔══██║ ██║      ██║╚██╔╝██║ ██╔══██║ ██║╚██╗██║           \n"
    L"           ██║      ██║  ██║ ╚██████╗ ██║ ╚═╝ ██║ ██║  ██║ ██║ ╚████║           \n"
    L"           ╚═╝      ╚═╝  ╚═╝  ╚═════╝ ╚═╝     ╚═╝ ╚═╝  ╚═╝ ╚═╝  ╚═══╝           \n"
    L"                                                                                \n"
    L"                      [ S T A R T ]          [ Q U I T ]                        \n"
    L"                       ^^^^^^^^^^^                                              \n"
    L"     __________________|      |____________________________________________     \n"
    L"          ,--.    ,--.          ,--.   ,--.                                     \n"
    L"         |oo  | _  \\  `.       | oo | |  oo|                                    \n"
    L"     o  o|~~  |(_) /   ;       | ~~ | |  ~~|o  o  o  o  o  o  o  o  o  o  o     \n"
    L"         |/\\/\\|   '._,'        |/\\/\\| |/\\/\\|                                    \n"
    L"     __________________        ____________________________________________     \n"
    L"                       |      |                                                 \n"
    L"                                                                                ";

typedef enum eColor {
    Color_BLACK,
    Color_BLUE,
    Color_GREEN,
    Color_JADE,
    Color_RED,
    Color_PURPLE,
    Color_YELLOW,
    Color_WHITE,
    Color_GRAY,
    Color_LIGHT_BLUE,
    Color_LIGHT_GREEN,
    Color_LIGHT_JADE,
    Color_LIGHT_RED,
    Color_LIGHT_PURPLE,
    Color_LIGHT_YELLOW,
    Color_LIGHT_WHITE
} Color;

void Cursor_moveXY(int x, int y);
void Cursor_setVisible(bool visible);
void Cursor_setColor(Color fg, Color bg);
void Screen_clear_onProgramStart();
void Screen_clear_onProgramEnd();
// #endregion // Display_Decls

// #region Input_Decls
enum eKeyCode {
    eKeyCode_None       = -1,
    eKeyCode_Null       = 0,
    eKeyCode_Function   = 0,
    eKeyCode_Backspace  = 8,
    eKeyCode_Tab        = 9,
    eKeyCode_Enter      = 13,
    eKeyCode_Shift      = 16,
    eKeyCode_Ctrl       = 17,
    eKeyCode_Alt        = 18,
    eKeyCode_Pause      = 19,
    eKeyCode_Break      = 19,
    eKeyCode_CapsLock   = 20,
    eKeyCode_Escape     = 27,
    eKeyCode_Space      = 32,
    eKeyCode_PageUp     = 33,
    eKeyCode_PageDown   = 34,
    eKeyCode_End        = 35,
    eKeyCode_Home       = 36,
    eKeyCode_ArrowUp    = 72,
    eKeyCode_ArrowLeft  = 75,
    eKeyCode_ArrowRight = 77,
    eKeyCode_ArrowDown  = 80,
    eKeyCode_Insert     = 45,
    eKeyCode_Delete     = 46,
    eKeyCode_Extension  = 224
};

int  getInputKey();
bool isFunctionKey();
bool isExtentionKey();
// #endregion // Input_Decls

// #region Math_Decls
#define MIN(_x, _y) (((_x) < (_y)) ? (_x) : (_y))
#define MAX(_x, _y) (((_x) > (_y)) ? (_x) : (_y))
int clamp(int x, int low, int high);
int wrap(int x, int low, int high);

typedef struct Point Point;
struct Point {
    int x;
    int y;
};

// p1 + p2
Point Point_add(Point p1, Point p2);
// p1 - p2
Point Point_sub(Point p1, Point p2);
// p * n
Point Point_mul(Point p, int n);
// p / n
Point Point_div(Point p, int n);
// p % n
Point Point_mod(Point p, int n);
// -p
Point Point_neg(Point p);
// |p|
Point Point_abs(Point p);

// Point(0, 0)
Point Point_zero();
// Point(1, 1)
Point Point_one();
// Point(-1, -1)
Point Point_negOne();
// Point(1, 1)
Point Point_unit();
// Point(1, 0)
Point Point_unitX();
// Point(0, 1)
Point Point_unitY();

// p1 == p2
bool Point_eq(Point p1, Point p2);
// p1 != p2
bool Point_ne(Point p1, Point p2);
// p1 <  p2
bool Point_lt(Point p1, Point p2);
// p1 <= p2
bool Point_le(Point p1, Point p2);
// p1 >  p2
bool Point_gt(Point p1, Point p2);
// p1 >= p2
bool Point_ge(Point p1, Point p2);

// p1 < p2 ? p1 : p2
Point Point_min(Point p1, Point p2);
// p1 > p2 ? p1 : p2
Point Point_max(Point p1, Point p2);
// [low, high]
Point Point_clamp(Point p, Point low, Point high);
// [low, high)
Point Point_wrap(Point p, Point low, Point high);

typedef enum eFourDir {
    FourDir_NONE = -1,
    FourDir_UP,
    FourDir_LEFT,
    FourDir_RIGHT,
    FourDir_DOWN,
    FourDir_Count
} FourDir;

// opposite dir
FourDir FourDir_neg(FourDir dir);
// delta x
int FourDir_dx(FourDir dir);
// delta y
int FourDir_dy(FourDir dir);
// delta point
Point FourDir_dp(FourDir dir);
// #endregion // Math_Decls

// #region Pacman_Board
#define Board_kWidth  ((int)(28))
#define Board_kHeight ((int)(24))
#define Board_kSize   ((int)(Board_kWidth * Board_kHeight))
int const Board_kMinX = (Screen_kWidth - Board_kWidth) / 2;
int const Board_kMinY = 0;

/*
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\
1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,\
1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,\
1,4,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,4,1,\
1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,\
1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1,\
1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1,\
1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1,\
0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0,\
0,0,0,0,0,1,2,1,1,0,1,1,1,3,3,1,1,1,0,1,1,2,1,0,0,0,0,0,\
1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1,\
0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,1,0,0,0,2,0,0,0,0,0,0,\
1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1,\
0,0,0,0,0,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,0,0,0,0,0,\
0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0,\
1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1,\
1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,\
1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,\
1,4,2,2,1,1,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,1,1,2,2,4,1,\
1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,\
1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1,\
1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,\
1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,\
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
*/

// clang-format off
// 0 := empty, 1 := wall, 2 := pellet, 3 := door, 4 := power pellet
int const Board_kData[Board_kSize] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,\
    1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,\
    1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,\
    1,4,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,4,1,\
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,\
    1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1,\
    1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1,\
    1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1,\
    0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0,\
    0,0,0,0,0,1,2,1,1,0,1,1,1,3,3,1,1,1,0,1,1,2,1,0,0,0,0,0,\
    1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1,\
    0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,1,0,0,0,2,0,0,0,0,0,0,\
    1,1,1,1,1,1,2,1,1,0,1,0,0,0,0,0,0,1,0,1,1,2,1,1,1,1,1,1,\
    0,0,0,0,0,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,0,0,0,0,0,\
    0,0,0,0,0,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,0,0,0,0,\
    1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1,\
    1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,\
    1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,\
    1,4,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,4,1,\
    1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,\
    1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1,\
    1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,\
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,\
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};
// clang-format on

const wchar_t* const Board_kTileGlyphs     = L" #.-*"; // ' ' := empty, '#' := wall, '.' := pellet, '-': door, '*' := power pellet
const Color          Board_kTileFgColors[] = { Color_BLACK, Color_BLUE, Color_YELLOW, Color_GRAY, Color_LIGHT_RED };
const Color          Board_kTileBgColors[] = { Color_BLACK, Color_BLUE, Color_BLACK, Color_BLACK, Color_BLACK };

void Board_reset();
int* Board_at(int index);
int* Board_atXY(int x, int y);
int* Board_atPoint(Point pos);
int  Board_dataAt(int index);
int  Board_dataAtXY(int x, int y);
int  Board_dataAtPoint(Point pos);
int  Board_countRemainingPoint();
void Board_flashWall(Color color);
void Board_draw();
// #endregion // Pacman_Board

// #region Pacman_Player
typedef struct Player Player;
struct Player {
    clock_t posTimeStep; // Time interval for position update
    clock_t frameTimeStep; // Time interval for frame update
    int     posDeltaTime; // Time change between position updates
    int     renderDeltaTime; // Time change between frame updates
    Point   pos; // Current position
    FourDir dir; // Current direction facing
    FourDir nextDir; // Next direction to move
    Color   color;
    int     curFrame; // Current frame index
    int     lifeRemaining; // Number of lives remaining
    int     speedPerSecond; // Movement speed per second
    bool    isEaten; // Is eaten?
};

const Point          Player_kInitPos                    = { 13, 18 }; // Starting point
const FourDir        Player_kInitDir                    = FourDir_LEFT; // Initial direction facing
const int            Player_kFrameCount                 = 6; // Number of frames
const wchar_t* const Player_kFrameByIdle                = L"O";
const wchar_t* const Player_kFrameByDirs[FourDir_Count] = {
    L"VV|||V", // UP
    L"})>->)", // LEFT
    L"{(<-<(", // RIGHT
    L"^^|||^", // DOWN
}; // Frames for each direction

void Player_reset(Player* self);
// Check if it is possible to move to toPos: Check the value of the corresponding index in game.board, and if the value is not 1 (wall) or 3 (door), the position is considered movable.
bool Player_isMovable(Player* self, Point toPos);
// Update the player's direction based on the input toDir direction.
void Player_look(Player* self, FourDir toDir);
// Wrap the coordinate x within the width of the game board (g_kBoardWidth)
int Player_wrap_pos_x(int x);
// Wrap the coordinate y within the height of the game board (g_kBoardHeight)
int Player_wrap_pos_y(int y);
// Wrap the player's position within the width (g_kBoardWidth) and height (g_kBoardHeight) of the game board
Point Player_wrap_pos(Point pos);
// Wrap the given frame index curFrame within the range of the player's frame count (Player_kFrameCount)
int Player_wrap_curFrame(int curFrame);
// When the player is eaten by a ghost
void Player_onEatenByGhost(Player* self);
// #endregion // Pacman_Player

// #region Pacman_Ghost
typedef enum eGhostType {
    GhostType_BLINKY = 0,
    GhostType_INKY,
    GhostType_PINKY,
    GhostType_CLYDE,
    GhostType_Count
} GhostType;

typedef enum eGhostState {
    GhostState_STAYING = 0,
    GhostState_SCATTERING,
    GhostState_CHASING,
    GhostState_FRIGHTENED,
    GhostState_EATEN,
    GhostState_Count
} GhostState;

enum eGhostDuration {
    STAYING_DURATION    = 1 * CLOCKS_PER_SEC,
    SCATTERING_DURATION = 7 * CLOCKS_PER_SEC,
    CHASING_DURATION    = 20 * CLOCKS_PER_SEC,
    FRIGHTENED_DURATION = 8 * CLOCKS_PER_SEC,
    EATEN_DURATION      = 8 * CLOCKS_PER_SEC
};

typedef struct Ghost Ghost;
struct Ghost {
    bool    isState[5]; // Is the ghost in the state of the index? Each index corresponds to a GhostState enumeration value, and true means the ghost is in that state
    bool    isInHome; // Is the ghost currently inside the ghost's home?
    int     stateDuration[5]; // Remaining duration for each ghost state
    clock_t posTimeStep; // Time interval for position update
    int     posDeltaTime; // Time change between position updates
    Point   pos; // Current position
    Point   targetPos; // Target position to move to
    FourDir dir; // Current facing direction
    Color   curColor; // Current color
    int     curFrame; // Current frame index
    int     speedPerSecond; // Movement speed per second
};

const Point          Ghost_kPosInside                                  = { 13, 11 }; // Position inside the ghost house
const Point          Ghost_kPosOutside                                 = { 13, 8 }; // Starting position outside the ghost house
const Point          Ghost_kInitPosByType[GhostType_Count]             = { { 13, 8 }, { 11, 11 }, { 13, 11 }, { 15, 11 } }; // Initial position for each ghost type
const FourDir        Ghost_kInitDirByType[GhostType_Count]             = { FourDir_LEFT, FourDir_UP, FourDir_DOWN, FourDir_UP }; // Initial direction for each ghost type
const int            Ghost_kInitStayingDurationByType[GhostType_Count] = { 0, 2, 8, 16 }; // Initial staying duration in seconds for each ghost type
const wchar_t* const Ghost_kFrameByState                               = L"Mm%%"; // 'M': Normal, 'm': Frightened, '%': Eaten
const Color          Ghost_kColorByType[GhostType_Count]               = { Color_LIGHT_RED, Color_LIGHT_BLUE, Color_LIGHT_PURPLE, Color_YELLOW }; // Color for each ghost type
const Color          Ghost_kColorVulnerable                            = Color_BLUE; // Color used to represent ghosts in the "Frightened" state
const Color          Ghost_kColorEaten                                 = Color_WHITE; // Color used to represent ghosts when they are "Eaten"

// Initialize the ghost's state
void Ghost_reset(Ghost* self, GhostType type);
// Check if the ghost can move to the given position: The ghost cannot pass through walls unless it is not in the "Eaten" state
// or in the "Eaten" state with more than 4 seconds of duration remaining.
bool Ghost_isMovable(Ghost* self, Point toPos);
// Update the ghost's direction
void Ghost_look(Ghost* self, FourDir toDir);
void Ghost_update(Ghost* self, GhostType type, Player* player, int deltaTime);
// When the ghost is eaten by the player
void Ghost_onEatenByPlayer(Ghost* self);
// #endregion // Pacman_Ghost

// #region Pacman_Game
typedef struct Game Game;
struct Game {
    int    board[Board_kSize];
    Ghost  ghosts[GhostType_Count];
    Player player;

    int remainingPoint;
    int currentScore;
    int previousScore;
    int highScore;

    clock_t currentTime;
    clock_t previousTime;
    int     fixedTimeLag;

    bool isPlaying;
} game;

Color const Game_kDefaultForeground = Color_LIGHT_WHITE;
Color const Game_kDefaultBackground = Color_BLACK;

// Includes a fixed update mechanism in the game loop to maintain a consistent frame rate (Game_kRenderFramesPreSec). Ensures consistent behavior by updating game logic and entities based on fixed time steps (Game_kFixedUpdateInterval).
#define Game_kRenderFramesPreSec (clock_t)60
// Interval between frames (Game_kRenderFrameInterval)
#define Game_kRenderFrameInterval (CLOCKS_PER_SEC / Game_kRenderFramesPreSec)
// Number of fixed updates: 100 updates per second. Same principle as FixedUpdate commonly used for physics processing in Unity.
#define Game_kFixedUpdatesPerSec ((clock_t)100)
// Fixed update interval (Game_kFixedUpdateInterval)
#define Game_kFixedUpdateInterval (CLOCKS_PER_SEC / Game_kFixedUpdatesPerSec)

// Initializes the game
void Game_init();
void Game_reset();
// Initializes the state of ghosts and player in the game
void Game_changeRound();
void Game_collidePlayerWithGhost(Player* player, Ghost* ghost);
// Performs a flashing effect on the game board and introduces a delay (msecsPerIter) between each iteration
void Game_flash(int iterCount, int msecsPerIter);
// When the player eats a power item
void Game_onPlayerEatenItem();
void Game_onPlayerLost();
void Game_onPlayerWon();
// #endregion // Pacman_Game


void Debug_log(const wchar_t* format, ...) {
    FILE* logFile = _wfopen(L"debug.log", L"a");
    if (logFile) {
        va_list args = NULL;
        va_start(args, format);
        (void)vfwprintf(logFile, format, args);
        va_end(args);
        (void)fwprintf(logFile, L"\n");
        (void)fclose(logFile);
    }
}


// #region Main_Function
bool g_isRunning = true;
int  g_state     = 0;

typedef struct Button Button;
struct Button {
    wchar_t* text;
    Point    posMin;
    int      width;
    Color    enabledForeground;
    Color    enabledBackground;
    Color    disabledForeground;
    Color    disabledBackground;
    Color    focusedForeground;
    Color    focusedBackground;
    Color    clickedForeground;
    Color    clickedBackground;

    bool isEnabled;
    bool isFocused;
    bool isClicked;

    void (*onFocused)(Button* self);
    void (*onFocusing)(Button* self);
    void (*onClicked)(Button* self);
};

void Button_onFocused(Button* self);
void Button_onFocusing(Button* self);
void Button_onClicked(Button* self);
void Button_draw(Button* self);

void Menu_StartButton_onClicked(Button* self);
void Menu_QuitButton_onClicked(Button* self);

#define Menu_kButtonCount (2)
Button Menu_buttons[Menu_kButtonCount] = {
    { L" S T A R T ",
      { 23, 15 },
      11,
      Color_LIGHT_WHITE,
      Color_BLACK,
      Color_WHITE,
      Color_BLACK,
      Color_LIGHT_WHITE,
      Color_BLACK,
      Color_BLACK,
      Color_LIGHT_WHITE,
      true,
      false,
      false,
      Button_onFocused,
      Button_onFocusing,
      Menu_StartButton_onClicked },
    { L" Q U I T ",
      { 46, 15 },
      9,
      Color_LIGHT_WHITE,
      Color_BLACK,
      Color_WHITE,
      Color_BLACK,
      Color_LIGHT_WHITE,
      Color_BLACK,
      Color_BLACK,
      Color_LIGHT_WHITE,
      true,
      false,
      false,
      Button_onFocused,
      Button_onFocusing,
      Menu_QuitButton_onClicked }
};

void MenuState_update();
void GameState_update();

int main() {
    Screen_clear_onProgramStart();

    Game_init();
    while (g_isRunning) {
        system("cls"); // NOLINT
        switch (g_state) {
        case 0:
            MenuState_update();
            break;
        case 1:
            GameState_update();
            break;
        default:
            assert(false); // Unrecognized state
            break;
        }
    }

    Screen_clear_onProgramEnd();
    return 0;
}

void Button_onFocusing(Button* self) {
    Cursor_setColor(self->focusedForeground, self->focusedBackground);
    Cursor_moveXY(self->posMin.x - 1, self->posMin.y);
    wprintf(L"[");
    for (int typo = 0; typo < self->width; ++typo) {
        wprintf(L"%lc", self->text[typo]);
    }
    wprintf(L"]");
    Cursor_moveXY(self->posMin.x, self->posMin.y + 1);
    for (int i = 0; i < self->width; ++i) {
        wprintf(L"^");
    }
    self->isFocused = true;
}

void Button_onFocused(Button* self) {
    Cursor_setColor(self->enabledForeground, self->enabledBackground);
    Cursor_moveXY(self->posMin.x - 1, self->posMin.y);
    wprintf(L"[");
    for (int typo = 0; typo < self->width; ++typo) {
        wprintf(L"%lc", self->text[typo]);
    }
    wprintf(L"]");
    Cursor_moveXY(self->posMin.x, self->posMin.y + 1);
    for (int i = 0; i < self->width; ++i) {
        wprintf(L" ");
    }
    self->isFocused = false;
}

void Button_onClicked(Button* self) {
    Cursor_setColor(self->clickedForeground, self->clickedBackground);
    Cursor_moveXY(self->posMin.x, self->posMin.y);
    for (int typo = 0; typo < self->width; ++typo) {
        wprintf(L"%lc", self->text[typo]);
    }
    Cursor_setColor(Game_kDefaultForeground, Game_kDefaultBackground);
    self->isClicked = true;
}

void Button_draw(Button* self) {
    if (self->isEnabled) {
        Cursor_setColor(self->enabledForeground, self->enabledBackground);
    } else {
        Cursor_setColor(self->disabledForeground, self->disabledBackground);
    }
    Cursor_moveXY(self->posMin.x - 1, self->posMin.y);
    wprintf(L"[");
    for (int i = 0; self->text[i] != L'\0'; ++i) {
        wprintf(L"%lc", self->text[i]);
    }
    wprintf(L"]");
}

void Menu_StartButton_onClicked(Button* self) {
    Button_onClicked(self);
    Sleep(100);
    Button_draw(self);
    Sleep(100);
    Button_onClicked(self);
    Sleep(100);
    Button_draw(self);
    Sleep(100);
    Button_onClicked(self);
    Sleep(1000);

    g_state = 1;
}

void Menu_QuitButton_onClicked(Button* self) {
    Button_onClicked(self);
    Sleep(100);
    Button_draw(self);
    Sleep(100);
    Button_onClicked(self);
    Sleep(100);
    Button_draw(self);
    Sleep(100);
    Button_onClicked(self);
    Sleep(1000);

    g_isRunning = false;
}

void MenuState_update() {
    Cursor_setColor(Color_LIGHT_WHITE, Color_BLACK);
    int index = 0;
    for (int y = 0; y < Screen_kHeight; ++y) {
        Color fg = Game_kDefaultForeground;
        if (1 <= y && y < 7) {
            fg = Color_LIGHT_RED;
        } else if (8 <= y && y < 14) {
            fg = Color_YELLOW;
        } else {
            fg = Game_kDefaultForeground;
        }
        Cursor_setColor(fg, Game_kDefaultBackground);
        for (int x = 0; x < Screen_kWidth + 1; ++x) {
            wprintf(L"%lc", Menu_kBackground[index++]);
        }
    }

    Audio_SetRepeat(true);
    if (!Audio_Play(L"Assets\\Intro.mp3")) {
        assert(false);
    }

    bool isStateSelecting = true;
    int  previous         = 0;
    int  current          = 0;
    while (isStateSelecting) {
        Menu_buttons[previous].onFocused(&Menu_buttons[previous]);
        Menu_buttons[current].onFocusing(&Menu_buttons[current]);

        switch (getInputKey()) {
        case eKeyCode_ArrowLeft:
        case 'w':
        case 'a':
            previous = current;
            current  = wrap(current - 1, 0, Menu_kButtonCount);
            break;
        case eKeyCode_ArrowRight:
        case 'd':
        case 's':
            previous = current;
            current  = wrap(current + 1, 0, Menu_kButtonCount);
            break;
        case eKeyCode_Enter:
        case eKeyCode_Space:
            Menu_buttons[current].onClicked(&Menu_buttons[current]);
            isStateSelecting = false;
            break;
        case eKeyCode_Escape:
        case 'q':
            isStateSelecting = false;
            g_isRunning      = false;
            break;
        };

        Sleep(50);
    }

    Audio_Stop();
}

void GameState_update() {
    char const kPressedCmpData[] = { 'w', 'a', 'd', 's', eKeyCode_ArrowUp, eKeyCode_ArrowLeft, eKeyCode_ArrowRight, eKeyCode_ArrowDown, 'q', eKeyCode_Escape };
    bool       isPressed[10]     = { false };

    Game_reset();

    Player* player                  = &game.player;
    Ghost*  ghosts[GhostType_Count] = { 0 };
    for (GhostType i = 0; i < GhostType_Count; ++i) {
        ghosts[i] = &game.ghosts[i];
    }

    // General update part. Corresponds to Unity's Update.
    while (game.isPlaying) {
        // Process Input
        int input = getInputKey();

        for (int key = 0; key < 10; ++key) {
            isPressed[key] = input == kPressedCmpData[key];
        }

        // Handle Input Key
        if (isPressed[8] || isPressed[9]) {
            game.isPlaying = false;
            continue;
        }

        // Handle Input Player Movement
        for (FourDir dir = 0; dir < FourDir_Count; ++dir) {
            if (!(isPressed[dir] || isPressed[dir + FourDir_Count])) {
                continue;
            }
            Player_look(player, dir);
            break;
        }

        // Update Game
        int previousScore         = game.currentScore;
        int previousLifeRemaining = player->lifeRemaining;

        if (game.remainingPoint <= 0) { // If all points are eaten, the game is won
            Game_flash(3, 500);
            Game_onPlayerWon();
        }

        // Update Player
        if (player->nextDir != FourDir_NONE) { // Check if the player can turn to the next direction
            Player_look(player, player->nextDir);
        }

        // Fixed time update part. Corresponds to Unity's Fixed Update.
        game.currentTime           = clock(); // Measure the current time
        clock_t const kElapsedTime = game.currentTime - game.previousTime; // Measure the 'elapsed time' by the difference between 'current time' and 'previous recent measurement time'
        game.fixedTimeLag += kElapsedTime; // Add the elapsed time to the fixed update time change

        player->posDeltaTime += game.fixedTimeLag; // Add the time change to the player's position update time change
        player->renderDeltaTime += game.fixedTimeLag; // Add the time change to the player's rendering update time change

        for (GhostType i = 0; i < GhostType_Count; ++i) {
            ghosts[i]->posDeltaTime += game.fixedTimeLag; // Add the time change to the ghost's position update time change
            Ghost_update(ghosts[i], i, player, game.fixedTimeLag);
        }

        // If the time change is greater than the fixed update interval (Game_kFixedUpdateInterval) ex(0.07 >= 0.02)
        while (game.fixedTimeLag >= Game_kFixedUpdateInterval) {
            // Player
            // If the player's position update time change is greater than the position update interval
            if (player->posDeltaTime >= player->posTimeStep) {
                Point const kPrevPos = player->pos;
                Point const kNextPos = Player_wrap_pos(Point_add(player->pos, FourDir_dp(player->dir)));

                int* tileAtPos = Board_atPoint(kPrevPos);

                // Add Score
                if (*tileAtPos == 2) {
                    game.remainingPoint -= 1;
                    game.currentScore += 10;
                    *tileAtPos = 0;
                }

                // Eat Item
                if (*tileAtPos == 4) {
                    game.remainingPoint -= 1;
                    game.currentScore += 50;
                    *tileAtPos = 0;
                    Game_onPlayerEatenItem();
                }

                // Movement
                // Move the player if it is movable
                if (Player_isMovable(player, kNextPos)) {
                    player->pos = kNextPos;
                    Cursor_moveXY(Board_kMinX + kPrevPos.x, Board_kMinY + kPrevPos.y);
                    Cursor_setColor(Board_kTileFgColors[*tileAtPos], Board_kTileBgColors[*tileAtPos]);
                    wprintf(L"%lc", Board_kTileGlyphs[*tileAtPos]);
                }

                // Check for contact with ghosts
                for (GhostType i = 0; i < 4; ++i) {
                    Game_collidePlayerWithGhost(player, ghosts[i]);
                }

                // Decrease the change by the player update interval
                player->posDeltaTime -= player->posTimeStep;
            }

            // Ghost
            for (GhostType i = 0; i < GhostType_Count; ++i) {
                Ghost* ghost = ghosts[i];
                // If the ghost's position update time change is greater than the position update interval
                if (ghost->posDeltaTime >= ghost->posTimeStep) {
                    Point const kPrevPos = ghost->pos;
                    Point const kNextPos = Point_clamp(Point_add(ghost->pos, FourDir_dp(ghost->dir)), Point_zero(), (Point){ Board_kWidth - 1, Board_kHeight - 1 });

                    int* tileAtPos = Board_atPoint(kPrevPos);

                    // Move the ghost if it is movable
                    if (Ghost_isMovable(ghost, kNextPos)) {
                        ghost->pos = kNextPos;
                        Cursor_moveXY(Board_kMinX + kPrevPos.x, Board_kMinY + kPrevPos.y);
                        Cursor_setColor(Board_kTileFgColors[*tileAtPos], Board_kTileBgColors[*tileAtPos]);
                        wprintf(L"%lc", Board_kTileGlyphs[*tileAtPos]);
                    }

                    // Check for contact with Player
                    Game_collidePlayerWithGhost(player, ghost);

                    // Decrease the change by the ghost update interval
                    ghost->posDeltaTime -= ghost->posTimeStep;
                }
            }

            // Decrease the change by the fixed update interval
            game.fixedTimeLag -= Game_kFixedUpdateInterval;
        }

        // Draw Player Frame
        // If the player's rendering update time change is greater than the rendering update interval
        while (player->renderDeltaTime >= player->frameTimeStep) {
            player->curFrame = Player_wrap_curFrame(player->curFrame + 1); // Change the player's frame
            player->renderDeltaTime -= player->frameTimeStep; // Decrease the change by the rendering update interval
        }
        // Render the player
        Cursor_moveXY(Board_kMinX + player->pos.x, Board_kMinY + player->pos.y);
        Cursor_setColor(player->color, Color_BLACK);
        wprintf(L"%lc", Player_kFrameByDirs[player->dir][player->curFrame]);

        // Draw Ghost
        // Render each ghost
        for (GhostType i = 0; i < GhostType_Count; ++i) {
            Ghost* ghost = ghosts[i];
            Cursor_moveXY(Board_kMinX + ghost->pos.x, Board_kMinY + ghost->pos.y);
            Cursor_setColor(ghost->curColor, Color_BLACK);
            wprintf(L"%lc", Ghost_kFrameByState[ghost->curFrame]);
        }

        // Draw Score
        // If the score before the update is different from the current score
        if (game.currentScore != previousScore) {
            // Update the score panel
            Cursor_moveXY(0, 2);
            Cursor_setColor(Color_LIGHT_WHITE, Color_BLACK);
            wprintf(L"%8d", game.currentScore);
        }

        // Draw lifeRemaining
        // If the number of lives before the update is different from the current number of lives
        if (player->lifeRemaining != previousLifeRemaining) {
            // Update the life panel
            Cursor_moveXY(0, 4);
            Cursor_setColor(Color_LIGHT_YELLOW, Color_BLACK);
            wprintf(L"Life");
            Cursor_setColor(Color_LIGHT_WHITE, Color_BLACK);
            wprintf(L" x %d", player->lifeRemaining);
        }

        // Calculate the remaining time until the next frame with the difference between the delayed time and the target frame interval
        clock_t kRemainingTime = Game_kRenderFrameInterval - kElapsedTime;
        // If there is time left until the next frame
        if (kRemainingTime > 0) {
            // Wait until the next frame
            Sleep(kRemainingTime);
        }
        // Update the previous recent measurement time
        game.previousTime = game.currentTime;
    }
    Audio_Stop();

    // If the game screen has ended, update the maximum score and initialize the game board
    game.highScore = game.currentScore > game.highScore ? game.currentScore : game.highScore;

    g_state = 0;
}
// #endregion // Main_Function


// #region Function_Defs
void Cursor_moveXY(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Cursor_setVisible(bool visible) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void Cursor_setColor(Color fg, Color bg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg | bg << 4u);
}

void Screen_clear_onProgramStart() {
    char cmd[100];
    system("cls"); // NOLINT
    (void)snprintf(cmd, sizeof(cmd), "mode con: cols=%d lines=%d", Screen_kWidth, Screen_kHeight);
    system(cmd); // NOLINT
    (void)snprintf(cmd, sizeof(cmd), "title %s", Window_kTitle);
    system(cmd); // NOLINT
    _wsetlocale(LC_ALL, L"");
    Cursor_setVisible(false);
}

void Screen_clear_onProgramEnd() {
    system("cls"); // NOLINT
    Cursor_setVisible(true);
}

static bool s_isFunctionKey  = false;
static bool s_isExtentionKey = false;

int getInputKey() {
    if (kbhit()) {
        int key          = getch();
        s_isFunctionKey  = key == eKeyCode_Function;
        s_isExtentionKey = key == eKeyCode_Extension;
        if (s_isFunctionKey || s_isExtentionKey) {
            return getch();
        }
        return key;
    }
    return eKeyCode_None;
}

bool isFunctionKey() { return s_isFunctionKey; }
bool isExtentionKey() { return s_isExtentionKey; }

int clamp(int x, int low, int high) {
    return (x < low)  ? low
         : (x > high) ? high
                      : x;
}

int wrap(int x, int low, int high) {
    int n = (x - low) % (high - low);
    return (n >= 0) ? (n + low) : (n + high);
}

Point Point_add(Point p1, Point p2) { return (Point){ p1.x + p2.x, p1.y + p2.y }; }
Point Point_sub(Point p1, Point p2) { return (Point){ p1.x - p2.x, p1.y - p2.y }; }
Point Point_mul(Point p, int n) { return (Point){ p.x * n, p.y * n }; }
Point Point_div(Point p, int n) { return (Point){ p.x / n, p.y / n }; }
Point Point_mod(Point p, int n) { return (Point){ p.x % n, p.y % n }; }
Point Point_neg(Point p) { return (Point){ -p.x, -p.y }; }
Point Point_abs(Point p) { return (Point){ abs(p.x), abs(p.y) }; }
Point Point_zero() { return (Point){ 0, 0 }; }
Point Point_one() { return (Point){ 1, 1 }; }
Point Point_negOne() { return (Point){ -1, -1 }; }
Point Point_unit() { return (Point){ 1, 1 }; }
Point Point_unitX() { return (Point){ 1, 0 }; }
Point Point_unitY() { return (Point){ 0, 1 }; }

bool Point_eq(Point p1, Point p2) { return p1.x == p2.x && p1.y == p2.y; }
bool Point_ne(Point p1, Point p2) { return p1.x != p2.x || p1.y != p2.y; }
bool Point_lt(Point p1, Point p2) { return p1.x < p2.x && p1.y < p2.y; }
bool Point_le(Point p1, Point p2) { return p1.x <= p2.x && p1.y <= p2.y; }
bool Point_gt(Point p1, Point p2) { return p1.x > p2.x && p1.y > p2.y; }
bool Point_ge(Point p1, Point p2) { return p1.x >= p2.x && p1.y >= p2.y; }

Point Point_min(Point p1, Point p2) { return Point_lt(p1, p2) ? p1 : p2; }
Point Point_max(Point p1, Point p2) { return Point_gt(p1, p2) ? p1 : p2; }
Point Point_clamp(Point p, Point low, Point high) {
    return (Point){
        clamp(p.x, low.x, high.x),
        clamp(p.y, low.y, high.y),
    };
}
Point Point_wrap(Point p, Point low, Point high) {
    return (Point){
        wrap(p.x, low.x, high.x),
        wrap(p.y, low.y, high.y),
    };
}

FourDir FourDir_neg(FourDir dir) {
    wrap(dir, FourDir_NONE, FourDir_Count);
    // assert(dir >= FourDir_NONE); // FIXME
    // assert(dir < FourDir_Count); // FIXME

    switch (dir) {
    case FourDir_UP:
        return FourDir_DOWN;
    case FourDir_DOWN:
        return FourDir_UP;
    case FourDir_LEFT:
        return FourDir_RIGHT;
    case FourDir_RIGHT:
        return FourDir_LEFT;
    default:
        return dir;
    }
}

int FourDir_dx(FourDir dir) {
    // assert(dir >= FourDir_NONE);
    // assert(dir < FourDir_Count);

    switch (dir) {
    case FourDir_LEFT:
        return -1;
    case FourDir_RIGHT:
        return 1;
    default:
        return 0;
    }
}

int FourDir_dy(FourDir dir) {
    // assert(dir >= FourDir_NONE);
    // assert(dir < FourDir_Count);

    switch (dir) {
    case FourDir_UP:
        return -1;
    case FourDir_DOWN:
        return 1;
    default:
        return 0;
    }
}

Point FourDir_dp(FourDir dir) {
    // assert(dir >= FourDir_NONE);
    // assert(dir < FourDir_Count);

    return (Point){
        FourDir_dx(dir),
        FourDir_dy(dir)
    };
}

void Board_reset() {
    for (int index = 0; index < Board_kSize; ++index) {
        game.board[index] = Board_kData[index];
    }
}

int* Board_at(int index) {
    assert(index >= 0);
    assert(index < Board_kSize);

    return &game.board[index];
}

int* Board_atXY(int x, int y) {
    clamp(x, 0, Board_kWidth - 1);
    clamp(y, 0, Board_kHeight - 1);
    // assert(x >= -1); // FIXME
    // assert(x <= Board_kWidth); // FIXME
    // assert(y >= -1); // FIXME
    // assert(y <= Board_kHeight); // FIXME

    return &game.board[y * Board_kWidth + x];
}

int* Board_atPoint(Point pos) { return Board_atXY(pos.x, pos.y); }

int Board_dataAt(int index) {
    assert(index >= 0);
    assert(index < Board_kSize);

    return game.board[index];
}

int Board_dataAtXY(int x, int y) {
    clamp(x, 0, Board_kWidth - 1);
    clamp(y, 0, Board_kHeight - 1);
    // assert(x >= -1); // FIXME
    // assert(x <= Board_kWidth); // FIXME
    // assert(y >= -1); // FIXME
    // assert(y <= Board_kHeight); // FIXME

    return game.board[y * Board_kWidth + x];
}

int Board_dataAtPoint(Point pos) { return Board_dataAtXY(pos.x, pos.y); }

int Board_countRemainingPoint() {
    int count = 0;
    for (int index = 0; index < Board_kSize; ++index) {
        int const kData = Board_dataAt(index);
        if (kData == 2 || kData == 4) {
            count++;
        }
    }
    return count;
}

void Board_flashWall(Color color) {
    Cursor_setColor(color, color);
    for (int y = 0; y < Board_kHeight; ++y) {
        Cursor_moveXY(Board_kMinX, Board_kMinY + y);
        for (int x = 0; x < Board_kWidth; ++x) {
            int const kData = Board_dataAtXY(x, y);
            if (kData == 1) {
                Cursor_moveXY(Board_kMinX + x, Board_kMinY + y);
                wprintf(L"%lc", Board_kTileGlyphs[kData]);
            }
        }
    }
    Cursor_setColor(Color_BLACK, Color_BLACK);
}

void Board_draw() {
    for (int y = 0; y < Board_kHeight; ++y) {
        Cursor_moveXY(Board_kMinX, Board_kMinY + y);
        for (int x = 0; x < Board_kWidth; ++x) {
            int const kData = Board_dataAtXY(x, y);
            Cursor_setColor(Board_kTileFgColors[kData], Board_kTileBgColors[kData]);
            wprintf(L"%lc", Board_kTileGlyphs[kData]);
        }
        Cursor_setColor(Color_BLACK, Color_BLACK);
        wprintf(L"\n");
    }
}

void Player_reset(Player* self) {
    assert(self);

    self->pos             = Player_kInitPos;
    self->dir             = Player_kInitDir;
    self->nextDir         = FourDir_NONE;
    self->color           = Color_LIGHT_YELLOW;
    self->speedPerSecond  = 5;
    self->posDeltaTime    = 0;
    self->posTimeStep     = CLOCKS_PER_SEC / self->speedPerSecond;
    self->curFrame        = 0;
    self->renderDeltaTime = 0;
    self->frameTimeStep   = self->posTimeStep / Player_kFrameCount;
    self->isEaten         = false;
}

bool Player_isMovable(Player* self, Point toPos) {
    assert(self);

    bool const kIsWall = (Board_dataAtPoint(toPos) == 1);
    bool const kIsDoor = (Board_dataAtPoint(toPos) == 3);
    return !kIsWall && !kIsDoor;
}

void Player_look(Player* self, FourDir toDir) {
    assert(self);

    Point const kLookingAt = Point_add(self->pos, FourDir_dp(toDir));
    if (Player_isMovable(self, kLookingAt)) {
        self->dir     = toDir;
        self->nextDir = FourDir_NONE;
    } else {
        self->nextDir = toDir;
    }
}

int Player_wrap_pos_x(int x) {
    return wrap(x, 0, Board_kWidth);
}

int Player_wrap_pos_y(int y) {
    return wrap(y, 0, Board_kHeight);
}

Point Player_wrap_pos(Point pos) {
    return Point_wrap(
        pos,
        Point_zero(),
        (Point){ Board_kWidth, Board_kHeight }
    );
}

int Player_wrap_curFrame(int curFrame) {
    return wrap(curFrame, 0, Player_kFrameCount);
}

void Player_onEatenByGhost(Player* self) {
    assert(self);

    Game_flash(3, 500);
    game.currentTime = clock();

    self->isEaten = true;
    self->lifeRemaining--;

    if (self->lifeRemaining > 0) {
        Game_changeRound();
        return;
    }

    Game_onPlayerLost();
}

void Ghost_reset(Ghost* self, GhostType type) {
    assert(self);

    self->pos       = Ghost_kInitPosByType[type];
    self->targetPos = type == GhostType_BLINKY ? Ghost_kPosOutside : Ghost_kPosInside;
    self->dir       = Ghost_kInitDirByType[type];
    self->curColor  = Ghost_kColorByType[type];
    self->curFrame  = 0;
    for (GhostState state = 0; state < GhostState_Count; ++state) {
        self->isState[state]       = false;
        self->stateDuration[state] = 0;
    }
    self->isState[GhostState_STAYING]       = true;
    self->stateDuration[GhostState_STAYING] = Ghost_kInitStayingDurationByType[type] * STAYING_DURATION;
    self->isInHome                          = true;
    self->speedPerSecond                    = 4;
    self->posDeltaTime                      = 0;
    self->posTimeStep                       = CLOCKS_PER_SEC / self->speedPerSecond;
}

bool Ghost_isMovable(Ghost* self, Point toPos) {
    assert(self);

    bool const kIsEaten             = self->isState[GhostState_EATEN];
    bool const kIsAlive             = !kIsEaten;
    bool const kIsStaying           = self->isState[GhostState_STAYING];
    bool const kIsWall              = Board_dataAtPoint(toPos) == 1;
    bool const kIsDoor              = Board_dataAtPoint(toPos) == 3;
    bool const kIsInHome            = self->isInHome;
    bool const kIsStayingButOutside = kIsStaying && !kIsInHome;
    bool const kIsAliveButOutside   = kIsAlive && !kIsInHome;

    /*
        !(
            this->stateDuration[GhostState_EATEN] > 4000 && g_boardData[nextPos->y * 28 + nextPos->x] == 1
            || (!this->isState[GhostState_STAYING] || this->isInHome) && g_boardData[nextPos->y * 28 + nextPos->x] == 3
        );


        this->stateDuration[GhostState_EATEN] <= 4000 || g_boardData[nextPos->y * 28 + nextPos->x] != 1
        && (this->isState[GhostState_STAYING] && !this->isInHome) || g_boardData[nextPos->y * 28 + nextPos->x] != 3
    */

    return !(
        (
            (kIsAlive // Not in "eaten" state, or
             || (kIsEaten && self->stateDuration[GhostState_EATEN] > 4000)) // Not in "eaten" state with more than 4 seconds of duration remaining
            && kIsWall
        ) // Cannot pass through walls
        || // or
        (
            (!kIsStayingButOutside // Not (in "staying" state and outside the home), or
             || !kIsAliveButOutside // Not (not in "eaten" state and outside the home), or
             || kIsInHome) // In the home
            && kIsDoor
        ) // Cannot pass through doors
    );
}

void Ghost_look(Ghost* self, FourDir toDir) {
    assert(self);

    self->dir = toDir;
}

void Ghost_update(Ghost* self, GhostType type, Player* player, int deltaTime) { // NOLINT
    int     kPx           = self->pos.x;
    int     kPy           = self->pos.y;
    FourDir kDir          = self->dir;
    FourDir kBackwardsDir = FourDir_neg(kDir);

    // For each active state (stored in 'isState'), 'stateDuration' is reduced by 'deltaTime' value, which represents the time elapsed since the last update.
    for (GhostState index = 0; index < GhostType_Count; ++index) {
        if (self->isState[index]) {
            self->stateDuration[index] -= deltaTime;
        }
    }

    // Ghost is in "eaten" state
    if (self->isState[GhostState_EATEN]) {
        int kTx = self->targetPos.x;
        int kTy = self->targetPos.y;
        // If the ghost has reached the target position (kPx == kTx && kPy == kTy), or the remaining duration of the eaten state has expired
        if ((kPx == kTx && kPy == kTy) || self->stateDuration[GhostState_EATEN] <= 0) {
            // Reset the ghost
            self->pos                               = Ghost_kInitPosByType[type == GhostType_BLINKY ? GhostType_PINKY : type];
            self->isState[GhostState_EATEN]         = false;
            self->stateDuration[GhostState_EATEN]   = 0;
            self->isState[GhostState_STAYING]       = true;
            self->stateDuration[GhostState_STAYING] = STAYING_DURATION * 8;
            self->isInHome                          = true;
            self->targetPos                         = Ghost_kPosInside;
            self->curColor                          = Ghost_kColorByType[type];
            self->curFrame                          = 0;
            self->posDeltaTime /= 4;
            self->speedPerSecond = 4;
            self->posTimeStep    = CLOCKS_PER_SEC / self->speedPerSecond;

            int tileAtGhostPos = Board_dataAtXY(kPx, kPy);
            Cursor_moveXY(Board_kMinX + kPx, Board_kMinY + kPy);
            Cursor_setColor(Board_kTileFgColors[tileAtGhostPos], Board_kTileBgColors[tileAtGhostPos]);
            wprintf(L"%lc", Board_kTileGlyphs[tileAtGhostPos]);
            return;
        }
    }

    // Ghost is in "frightened" state
    if (self->isState[GhostState_FRIGHTENED]) {
        // If the remaining duration of the frightened state has expired
        if (self->stateDuration[GhostState_FRIGHTENED] <= 0) {
            // Switch to "scattering" state
            self->isState[GhostState_FRIGHTENED]       = false;
            self->stateDuration[GhostState_FRIGHTENED] = 0;
            self->isState[GhostState_SCATTERING]       = true;
            self->stateDuration[GhostState_SCATTERING] = SCATTERING_DURATION;
            self->curColor                             = Ghost_kColorByType[type];
            self->curFrame                             = 0;
            self->posDeltaTime /= 2;
            self->speedPerSecond = 4;
            self->posTimeStep    = CLOCKS_PER_SEC / self->speedPerSecond;
            return;
        }
    }

    // Ghost is in "staying" state
    if (self->isState[GhostState_STAYING]) {
        // If still waiting
        if (self->stateDuration[GhostState_STAYING] > 0) {
            // Determine next position based on current position
            int kNx = kPx + FourDir_dx(kDir);
            int kNy = kPy + FourDir_dy(kDir);
            if (!Ghost_isMovable(self, (Point){ kNx, kNy })) {
                Ghost_look(self, kBackwardsDir);
            }
            return;
        }
        // If not waiting but inside the home
        if (self->isInHome) {
            // If y-axis has not reached the target position yet, determine next position and check if it's movable
            if (kPy != self->targetPos.y) {
                int kNx = kPx + FourDir_dx(kDir);
                int kNy = kPy + FourDir_dy(kDir);
                if (!Ghost_isMovable(self, (Point){ kNx, kNy })) {
                    Ghost_look(self, kBackwardsDir);
                }
                return;
            }
            // If y-axis is the same as the target position, set the x-axis direction towards the target position
            if (kPx != self->targetPos.x) {
                Ghost_look(self, self->targetPos.x - kPx > 0 ? FourDir_RIGHT : FourDir_LEFT);
                return;
            }
            // If the target position is reached, set the next target position to the outside starting point and move upwards
            self->isInHome  = false;
            self->targetPos = Ghost_kPosOutside;
            Ghost_look(self, FourDir_UP);
            return;
        }
        // If the outside starting point has not been reached yet, no change (move upwards)
        if (kPy != self->targetPos.y) {
            return;
        }
        // If the outside starting point is reached, switch to "scattering" state
        self->isState[GhostState_STAYING]          = false;
        self->stateDuration[GhostState_STAYING]    = 0;
        self->isState[GhostState_SCATTERING]       = true;
        self->stateDuration[GhostState_SCATTERING] = SCATTERING_DURATION;
        Ghost_look(self, (unsigned)rand() & 1u ? FourDir_LEFT : FourDir_RIGHT);
        return;
    }

    // If the ghost is not in the "FRIGHTENED" state and is in the "SCATTERING" state
    if (!self->isState[GhostState_FRIGHTENED] && self->isState[GhostState_SCATTERING]) {
        // If the duration has expired
        if (self->stateDuration[GhostState_SCATTERING] <= 0) {
            // Switch to "CHASING" state
            self->isState[GhostState_SCATTERING]       = false;
            self->stateDuration[GhostState_SCATTERING] = 0;
            self->isState[GhostState_CHASING]          = true;
            self->stateDuration[GhostState_CHASING]    = CHASING_DURATION;
            return;
        }

        // If the duration has not expired, search for movable directions from the current position
        FourDir movableDirs[3];
        int     movableDirCount = 0;

        for (FourDir dir = 0; dir < 4; ++dir) {
            if (dir == kBackwardsDir) {
                continue;
            }
            int kNx = kPx + FourDir_dx(dir);
            int kNy = kPy + FourDir_dy(dir);
            if (Ghost_isMovable(self, (Point){ kNx, kNy })) {
                movableDirs[movableDirCount++] = dir;
            }
        }
        // Set the current direction randomly among the movable directions
        int kRandDirIndex = movableDirCount > 1 ? rand() % movableDirCount : 0;
        Ghost_look(self, movableDirs[kRandDirIndex]);
        return;
    }

    // If the ghost is not in the "frightened" state and is in the "chasing" state
    if (!self->isState[GhostState_FRIGHTENED] && self->isState[GhostState_CHASING]) {
        // If the duration has expired
        if (self->stateDuration[GhostState_CHASING] <= 0) {
            // Switch to the "scattering" state
            self->isState[GhostState_CHASING]          = false;
            self->stateDuration[GhostState_CHASING]    = 0;
            self->isState[GhostState_SCATTERING]       = true;
            self->stateDuration[GhostState_SCATTERING] = SCATTERING_DURATION;
            return;
        }
        // If the duration has not expired, set the target position to the player's position
        self->targetPos = player->pos;
    }

    // Set the current target position
    int kTx = self->targetPos.x;
    int kTy = self->targetPos.y;

    int bestDir     = FourDir_NONE;
    int distBestDir = self->isState[GhostState_FRIGHTENED] ? -1 : 9876543; // The distance of the best direction is the maximum distance from the player when in the "frightened" state, and the shortest distance when in the "chasing" state

    for (FourDir dir = 0; dir < 4; ++dir) {
        // If the search direction is the backward direction, move to the next search direction
        if (dir == kBackwardsDir) {
            continue;
        }

        // Store the position change in the search direction
        int kNx = kPx + FourDir_dx(dir);
        int kNy = kPy + FourDir_dy(dir);

        // If it is not movable in the search direction, move to the next search direction
        if (!Ghost_isMovable(self, (Point){ kNx, kNy })) {
            continue;
        }

        // Calculate the distance between the expected position in the search direction and the player's position
        int kDist = (kTx - kNx) * (kTx - kNx) + (kTy - kNy) * (kTy - kNy); // L2 Norm
        // int kDist = abs(kNx - kTx) + abs(kNy - kTy); // Manhattan dist L1 Norm

        if (self->isState[GhostState_FRIGHTENED]) {
            // When in the "frightened" state, select the maximum distance
            if (kDist > distBestDir || bestDir == FourDir_NONE) {
                bestDir     = dir;
                distBestDir = kDist;
            }
        } else {
            // When in the "chasing" state, select the shortest distance
            if (kDist < distBestDir || bestDir == FourDir_NONE) {
                bestDir     = dir;
                distBestDir = kDist;
            }
        }
    }

    // Set the current direction to the selected best direction
    Ghost_look(self, bestDir);
}

void Ghost_onEatenByPlayer(Ghost* self) {
    assert(self);

    Game_flash(1, 500);
    game.currentScore += 200;
    game.currentTime = clock();

    for (int i = 0; i < 4; ++i) {
        // Reset all ghost states and durations
        self->isState[i]       = false;
        self->stateDuration[i] = 0;
    }
    // Transition the ghost to the "eaten" state
    self->isState[GhostState_EATEN]       = true;
    self->stateDuration[GhostState_EATEN] = EATEN_DURATION;
    self->curColor                        = Ghost_kColorEaten;
    self->curFrame                        = 2;
    self->speedPerSecond                  = 10;
    self->posDeltaTime /= 4;
    self->posTimeStep = CLOCKS_PER_SEC / self->speedPerSecond;
    self->targetPos   = Ghost_kPosOutside; // Set the ghost's target position to the starting point outside the house
}

void Game_init() {
    game.highScore = 0;
}

void Game_reset() {
    // Reset Score
    game.currentScore  = 0;
    game.previousScore = 0;

    // Reset Player
    Player_reset(&game.player);
    game.player.lifeRemaining = 3;

    // Reset Ghosts
    for (GhostType i = 0; i < GhostType_Count; ++i) {
        Ghost_reset(&game.ghosts[i], i);
    }

    // Reset Board
    Board_reset();
    game.remainingPoint = Board_countRemainingPoint();

    // Draw Board
    Board_draw();

    // Draw Panel
    Cursor_moveXY(0, 0);
    Cursor_setColor(Color_RED, Color_BLACK);
    wprintf(L"HI-SCORE");
    Cursor_moveXY(0, 1);
    Cursor_setColor(Color_LIGHT_WHITE, Color_BLACK);
    wprintf(L"%8d", game.highScore);
    Cursor_moveXY(0, 2);
    wprintf(L"%8d", game.currentScore);

    Cursor_moveXY(0, 4);
    Cursor_setColor(Color_LIGHT_YELLOW, Color_BLACK);
    wprintf(L"Life");
    Cursor_setColor(Color_LIGHT_WHITE, Color_BLACK);
    wprintf(L" x %d", game.player.lifeRemaining);

    Cursor_moveXY(Screen_kWidth - 15, 0);
    wprintf(L"UP    : W   ↑");
    Cursor_moveXY(Screen_kWidth - 15, 1);
    wprintf(L"LEFT  : A   →");
    Cursor_moveXY(Screen_kWidth - 15, 2);
    wprintf(L"RIGHT : S   ↓");
    Cursor_moveXY(Screen_kWidth - 15, 3);
    wprintf(L"DOWN  : D   ←");
    Cursor_moveXY(Screen_kWidth - 15, 4);
    wprintf(L"Quit  : Q ESC ");

    // Reset Time
    game.currentTime  = clock(); // Measure the current time and store it in 'currentTime'
    game.previousTime = clock(); // Store the most recently updated time in 'previousTime'
    game.fixedTimeLag = 0; // Store the time change during one iteration of the game loop, which determines the number of FixedUpdate iterations. It works on the same principle as Time.deltaTime in Unity

    // Reset Audio
    if (Audio_IsPlaying()) {
        Audio_Stop();
    }
    Audio_SetRepeat(true);
    Audio_Play(L"Assets\\Background 1.mp3");

    // Activate Game
    game.isPlaying = true;
}

void Game_changeRound() {
    Player_reset(&game.player);
    for (GhostType type = 0; type < GhostType_Count; ++type) {
        Ghost_reset(&game.ghosts[type], type);
    }
    Board_draw();
}

void Game_collidePlayerWithGhost(Player* player, Ghost* ghost) {
    assert(player);
    assert(ghost);

    // If they are not in contact, pass
    if (Point_ne(player->pos, ghost->pos)) {
        return;
    }
    // They are in contact, so handle the collision

    // If the player is already eaten, pass
    if (player->isEaten) {
        return;
    }

    // If the ghost is already eaten, pass
    if (ghost->isState[GhostState_EATEN]) {
        return;
    }

    // If the ghost is in the "frightened" state
    if (ghost->isState[GhostState_FRIGHTENED]) {
        // The player eats the ghost
        Ghost_onEatenByPlayer(ghost);
    } else { // Otherwise
        // The player is eaten by the ghost
        Player_onEatenByGhost(player);
    }
}

// Performs a flashing effect on the game board. Repeatedly calls Board_flash() with different colors (white and blue) for the specified number of iterations (iterCount). Uses the 'Sleep()' function to introduce a delay (msecsPerIter) between each iteration.
void Game_flash(int iterCount, int msecsPerIter) {
    for (int step = 0; step < iterCount; ++step) {
        Board_flashWall(Color_WHITE);
        Sleep(msecsPerIter / 2);
        Board_flashWall(Color_BLUE);
        Sleep(msecsPerIter / 2);
    }
}

void Game_onPlayerEatenItem() {
    for (GhostType type = 0; type < GhostType_Count; ++type) {
        // If the ghost is already in the "eaten" state, proceed to the next ghost
        if (game.ghosts[type].isState[GhostState_EATEN]) {
            continue;
        }

        // Change the ghost's state to "frightened"
        game.ghosts[type].isState[GhostState_FRIGHTENED]       = true;
        game.ghosts[type].stateDuration[GhostState_FRIGHTENED] = FRIGHTENED_DURATION;
        game.ghosts[type].curColor                             = Ghost_kColorVulnerable;
        game.ghosts[type].curFrame                             = 1;
        game.ghosts[type].speedPerSecond                       = 2;
        game.ghosts[type].posDeltaTime *= 2;
        game.ghosts[type].posTimeStep = CLOCKS_PER_SEC / game.ghosts[type].speedPerSecond;
    }
    Audio_PlayOneShot(L"Assets\\Power.mp3");
}

void Game_onPlayerLost() {
    Cursor_moveXY(6, 16);
    Cursor_setColor(Color_LIGHT_WHITE, Color_PURPLE);
    wprintf(L"lose the game...");
    Sleep(3000);
    game.currentTime = clock();
    game.isPlaying   = false;
}

void Game_onPlayerWon() {
    Cursor_moveXY(10, 16);
    Cursor_setColor(Color_LIGHT_WHITE, Color_YELLOW);
    wprintf(L" Clear! ");
    Sleep(3000);
    game.currentTime = clock();
    game.isPlaying   = false;
}
// #endregion // Function_Defs
