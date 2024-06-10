#pragma region INCLUDES
#include <assert.h> // assert 매크로를 포함
#include <conio.h> // 키보드 입력과 화면 출력을 다루기 위한 함수들
#include <locale.h> // 로케일 설정과 관련된 함수들
#include <stdbool.h> // ool 자료형과 관련된 매크로를 정의
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#pragma endregion // INCLUDES



#pragma region DISPLAY_DECLS
char const* const kTitle = "ASCII PACMAN";

#define SCREEN_WIDTH  ((int)(80)) // 화면의 너비
#define SCREEN_HEIGHT ((int)(25)) // 화면의 높이

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

// 커서를 x, y 좌표로 이동
void gotoxy(int x, int y);
// 커서를 보이거나 숨김
void setcursor(bool visible);
// 텍스트의 색상을 설정: fg는 전경색, bg는 배경색
void textcolor(Color fg, Color bg);
// 프로그램 시작시 화면을 초기화
void cls_onProgramStart();
// 프로그램 종료시 화면을 초기화
void cls_onProgramEnd();
#pragma endregion // DISPLAY_DECLS

#pragma region INPUT_DECLS
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

// 키보드 입력을 받아서 반환
int getInputKey();
// 최근 입력된 키가 함수 키인지 확인
bool isFunctionKey();
// 최근 입력된 키가 확장 키인지 확인
bool isExtentionKey();
#pragma endregion // INPUT_DECLS

#pragma region MATH_DECLS
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
// p를 low, high 사이로 끊어서 반환
Point Point_clamp(Point p, Point low, Point high);
// p를 low, high-1 사이로 감싸서 반환
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
#pragma endregion // MATH_DECLS

#pragma region PACMAN_BOARD
// # 타일 유형, 문자 및 렌더링에 사용되는 색상을 포함하여 게임 보드의 레이아웃과 속성을 정의
#define Board_kWidth  ((int)(28)) // 보드의 너비
#define Board_kHeight ((int)(24)) // 보드의 높이
#define Board_kSize   ((int)(Board_kWidth * Board_kHeight)) // 보드의 크기

// clang-format off
// 게임 보드의 레퍼런스, 배열의 각 요소는 보드의 타일에 해당하며 유형에 따라 값이 할당됨.
// 0은 비어 있음, 1은 벽, 2는 포인트, 3은 문, 4는 아이템
// 너비가 28이고 높이가 24인 보드에는 28 * 24 = 672개의 타일이 포함됨
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

// 각 타일 유형을 표시하는 데 사용되는 문자를 나타내는 와이드 문자열,
const wchar_t* const Board_kTileGlyphs     = L" #.-*"; // ' ': 비어 있음, '#': 벽, '.': 포인트, '-': 문, '*': 아이템
const Color          Board_kTileFgColors[] = { Color_BLACK, Color_BLUE, Color_YELLOW, Color_GRAY, Color_LIGHT_RED }; // 각 타일의 전경색
const Color          Board_kTileBgColors[] = { Color_BLACK, Color_BLUE, Color_BLACK, Color_BLACK, Color_BLACK }; // 각 타일의 배경색

// # 게임 보드를 관리 및 표시하고 시각적 효과를 제공

// 게임 보드를 초기화
void Board_reset();
int* Board_at(int index);
int* Board_atXY(int x, int y);
int* Board_atPoint(Point pos);
int  Board_dataAt(int index);
int  Board_dataAtXY(int x, int y);
int  Board_dataAtPoint(Point pos);
// 게임 보드에 남은 점수&아이템을 계산하여 반환
int Board_countRemainingPoint();
// 지정된 색상으로 전체 게임 보드의 벽을 깜박임
void Board_flashWall(Color color);
// 게임 보드를 화면에 렌더링
void Board_draw();
#pragma endregion // PACMAN_BOARD

#pragma region PACMAN_PLAYER
// # 플레이어의 속성과 동작을 정의
typedef struct Player Player;
struct Player {
    clock_t posTimeStep; // 위치 업데이트를 위한 시간 간격
    clock_t frameTimeStep; // 프레임 업데이트를 위한 시간 간격
    int     posDeltaTime; // 위치 업데이트 사이의 시간변화량
    int     renderDeltaTime; // 프레임 업데이트 사이의 시간변화량
    Point   pos; // 현재 위치
    FourDir dir; // 향하고 있는 현재 방향
    FourDir nextDir; // 이동하려는 다음 방향
    Color   color;
    int     curFrame; // 현재 프레임 인덱스
    int     lifeRemaining; // 남은 목숨 수
    int     speedPerSecond; // 초당 단위의 이동 속력
    bool    isEaten; // 먹혔는가?
};

const Point          Player_kInitPos                    = { 13, 18 }; // 시작점
const FourDir        Player_kInitDir                    = FourDir_LEFT; // 향하는 초기 방향
const int            Player_kFrameCount                 = 6; // 프레임 수
const wchar_t* const Player_kFrameByIdle                = L"O";
const wchar_t* const Player_kFrameByDirs[FourDir_Count] = {
    L"VV|||V", // UP
    L"})>->)", // LEFT
    L"{(<-<(", // RIGHT
    L"^^|||^", // DOWN
}; // 각 방향에 대한 프레임

// 속성을 초기 값으로 재설정함
void Player_reset(Player* self);
// toPos로 이동할 수 있는지 확인: game.board에서 해당 인덱스의 값을 확인하여 값이 1(벽) 또는 3(문)이 아닌 경우 해당 위치는 이동 가능한 것으로 간주함.
bool Player_isMovable(Player* self, Point toPos);
// 입력된 toDir 방향을 기준으로 플레이어의 방향을 업데이트함.
void Player_look(Player* self, FourDir toDir);
// 게임 보드의 너비(g_kBoardWidth) 범위 내에서 좌표 x를 래핑
int Player_wrap_pos_x(int x);
// 게임 보드의 높이(g_kBoardHeight) 범위 내에서 좌표 y를 래핑
int Player_wrap_pos_y(int y);
// 플레이어의 위치를 게임 보드의 너비(g_kBoardWidth)와 높이(g_kBoardHeight) 범위 내에서 래핑
Point Player_wrap_pos(Point pos);
// 플레이어의 프레임 수(Player_kFrameCount) 범위 내에서 주어진 프레임 인덱스 curFrame을 래핑
int Player_wrap_curFrame(int curFrame);
// 유령이 플레이어를 먹었을 때
void Player_onEatenByGhost(Player* self);
#pragma endregion // PACMAN_PLAYER

#pragma region PACMAN_GHOST
// # 유령의 속성과 동작을 정의

// 유령의 종류
typedef enum eGhostType {
    GhostType_BLINKY = 0,
    GhostType_INKY,
    GhostType_PINKY,
    GhostType_CLYDE,
    GhostType_Count
} GhostType;

// 유령의 행동과 프레임, 색상을 결정할 상태
typedef enum eGhostState {
    GhostState_STAYING = 0,
    GhostState_SCATTERING,
    GhostState_CHASING,
    GhostState_FRIGHTENED,
    GhostState_EATEN,
    GhostState_Count
} GhostState;

// 유령의 상태별 지속 기간
enum eGhostDuration {
    STAYING_DURATION    = 1 * CLOCKS_PER_SEC,
    SCATTERING_DURATION = 7 * CLOCKS_PER_SEC,
    CHASING_DURATION    = 20 * CLOCKS_PER_SEC,
    FRIGHTENED_DURATION = 8 * CLOCKS_PER_SEC,
    EATEN_DURATION      = 8 * CLOCKS_PER_SEC
};

typedef struct Ghost Ghost;
struct Ghost {
    bool    isState[5]; // 유령이 인덱스의 상태인가? 각 인덱스는 GhostState 열거형 값에 해당하며 true는 고스트가 해당 상태에 있음을 의미
    bool    isInHome; // 유령이 현재 유령의 집 안에 있는가?
    int     stateDuration[5]; // 각 유령 상태에 대한 남은 기간
    clock_t posTimeStep; // 위치 업데이트를 위한 시간 간격
    int     posDeltaTime; // 위치 업데이트 사이의 시간변화량
    Point   pos; // 현재 위치
    Point   targetPos; // 움직이는 목표 위치
    FourDir dir; // 현재 향하고 있는 방향
    Color   curColor; // 현재 색상
    int     curFrame; // 현재 프레임 인덱스
    int     speedPerSecond; // 초당 이동속력
};

const Point          Ghost_kPosInside                                  = { 13, 11 }; // 집의 내부 영역 위치
const Point          Ghost_kPosOutside                                 = { 13, 8 }; // 집 외부 영역의 시작 위치
const Point          Ghost_kInitPosByType[GhostType_Count]             = { { 13, 8 }, { 11, 11 }, { 13, 11 }, { 15, 11 } }; // 각 유령의 시작 위치
const FourDir        Ghost_kInitDirByType[GhostType_Count]             = { FourDir_LEFT, FourDir_UP, FourDir_DOWN, FourDir_UP }; // 각 유령의 초기 방향
const int            Ghost_kInitStayingDurationByType[GhostType_Count] = { 0, 2, 8, 16 }; // 각 유령의 초단위의 초기 대기 시간
const wchar_t* const Ghost_kFrameByState                               = L"Mm%%"; // 'M': 일반, 'm': Frightened, '%': Eaten
const Color          Ghost_kColorByType[GhostType_Count]               = { Color_LIGHT_RED, Color_LIGHT_BLUE, Color_LIGHT_PURPLE, Color_YELLOW }; // 각 유령의 색상
const Color          Ghost_kColorVulnerable                            = Color_BLUE; // "공포-Frightened" 상태에 있을 때 유령을 나타내는 데 사용되는 색상
const Color          Ghost_kColorEaten                                 = Color_WHITE; // 유령이 "먹힐 때"를 나타내는 데 사용되는 색상

// 유령의 상태를 초기화함
void Ghost_reset(Ghost* self, GhostType type);
// 유령이 주어진 위치로 이동할 수 있는지 확인: 유령의 상태(예를 들어, "먹힌" 상태가 아니거나 지속 시간이 4초 초과로
// 남아있는 "먹힌" 상태가 아니면 벽을 통과할 수 없음.
bool Ghost_isMovable(Ghost* self, Point toPos);
// 유령의 방향을 업데이트함
void Ghost_look(Ghost* self, FourDir toDir);
void Ghost_update(Ghost* self, GhostType type, Player* player, int deltaTime);
// 유령이 플레이어를 먹었을 때
void Ghost_onEatenByPlayer(Ghost* self);
#pragma endregion // PACMAN_GHOST

#pragma region PACMAN_GAME
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

// 게임 루프에서 일관된 프레임 속도(Game_kRenderFramesPreSec)를 유지하기 위한 고정 업데이트 메커니즘을 포함함. 고정된 시간 단계(Game_kFixedUpdateInterval)를 기반으로 게임 로직과 엔티티를 업데이트하여 일관된 동작을 보장함.
#define Game_kRenderFramesPreSec (clock_t)60
// 프레임 사이 간격(Game_kRenderFrameInterval)
#define Game_kRenderFrameInterval (CLOCKS_PER_SEC / Game_kRenderFramesPreSec)
// 고정 업데이트 횟수: 초당 100번 업데이트.유니티에서 물리 연산 처리시 주로 사용하는 FixedUpdate와 같은 원리.
#define Game_kFixedUpdatesPerSec ((clock_t)100)
// 고정 업데이트 간격(Game_kFixedUpdateInterval)
#define Game_kFixedUpdateInterval (CLOCKS_PER_SEC / Game_kFixedUpdatesPerSec)

// 게임을 초기화함
void Game_init();
void Game_reset();
// 게임의 유령과 플레이어 상태를 초기화
void Game_changeRound();
void Game_collidePlayerWithGhost(Player* player, Ghost* ghost);
// 게임 보드에 깜박이는 효과를 수행 및 각 반복 사이에 지연(msecsPerIter)을 도입
void Game_flash(int iterCount, int msecsPerIter);
// 플레이어가 파워 아이템을 먹었을 때
void Game_onPlayerEatenItem();
void Game_onPlayerLost();
void Game_onPlayerWon();
#pragma endregion // PACMAN_GAME



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



#pragma region MAIN_FUNCTION
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
    cls_onProgramStart();

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

    cls_onProgramEnd();
    return 0;
}

void Button_onFocusing(Button* self) {
    textcolor(self->focusedForeground, self->focusedBackground);
    gotoxy(self->posMin.x - 1, self->posMin.y);
    wprintf(L"[");
    for (int typo = 0; typo < self->width; ++typo) {
        wprintf(L"%lc", self->text[typo]);
    }
    wprintf(L"]");
    gotoxy(self->posMin.x, self->posMin.y + 1);
    for (int i = 0; i < self->width; ++i) {
        wprintf(L"^");
    }
    self->isFocused = true;
}

void Button_onFocused(Button* self) {
    textcolor(self->enabledForeground, self->enabledBackground);
    gotoxy(self->posMin.x - 1, self->posMin.y);
    wprintf(L"[");
    for (int typo = 0; typo < self->width; ++typo) {
        wprintf(L"%lc", self->text[typo]);
    }
    wprintf(L"]");
    gotoxy(self->posMin.x, self->posMin.y + 1);
    for (int i = 0; i < self->width; ++i) {
        wprintf(L" ");
    }
    self->isFocused = false;
}

void Button_onClicked(Button* self) {
    textcolor(self->clickedForeground, self->clickedBackground);
    gotoxy(self->posMin.x, self->posMin.y);
    for (int typo = 0; typo < self->width; ++typo) {
        wprintf(L"%lc", self->text[typo]);
    }
    textcolor(Game_kDefaultForeground, Game_kDefaultBackground);
    self->isClicked = true;
}

void Button_draw(Button* self) {
    if (self->isEnabled) {
        textcolor(self->enabledForeground, self->enabledBackground);
    } else {
        textcolor(self->disabledForeground, self->disabledBackground);
    }
    gotoxy(self->posMin.x - 1, self->posMin.y);
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

// 게임 시작 또는 종료를 선택할 수 있는 메뉴 화면. 메뉴 옵션이 표시되고 플레이어의 입력을 처리하여 옵션을 선택.
void MenuState_update() {
    textcolor(Color_LIGHT_WHITE, Color_BLACK);
    int index = 0;
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        Color fg = Game_kDefaultForeground;
        if (1 <= y && y < 7) {
            fg = Color_LIGHT_RED;
        } else if (8 <= y && y < 14) {
            fg = Color_YELLOW;
        } else {
            fg = Game_kDefaultForeground;
        }
        textcolor(fg, Game_kDefaultBackground);
        for (int x = 0; x < SCREEN_WIDTH + 1; ++x) {
            wprintf(L"%lc", Menu_kBackground[index++]);
        }
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
}

// 게임 시작을 선택하면 게임 화면에 진입.
void GameState_update() {
    // 게임의 변수를 초기화하고 게임판, 최고 점수, 현재 점수, 플레이어의 남은 목숨을 표시함.
    char const kPressedCmpData[] = { 'w', 'a', 'd', 's', eKeyCode_ArrowUp, eKeyCode_ArrowLeft, eKeyCode_ArrowRight, eKeyCode_ArrowDown, 'q', eKeyCode_Escape }; // 눌린 키 비교 데이터
    bool       isPressed[10]     = { false }; // 눌린 키를 저장하는 배열

    Game_reset();

    Player* player                  = &game.player;
    Ghost*  ghosts[GhostType_Count] = { 0 };
    for (GhostType i = 0; i < GhostType_Count; ++i) {
        ghosts[i] = &game.ghosts[i];
    }

    while (game.isPlaying) {
        // # 일반적인 업데이트 부분. 유니티의 Update에 해당.
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
        int kScore         = game.currentScore; // 게임 업데이트 직전의 점수 저장
        int kLifeRemaining = player->lifeRemaining; // 게임 업데이트 직전의 목숨 수 저장

        if (game.remainingPoint <= 0) { // 모든 포인트를 먹었다면 게임 승리
            Game_flash(3, 500);
            gotoxy(10, 16);
            textcolor(Color_LIGHT_WHITE, Color_YELLOW);
            wprintf(L" Clear! ");
            Sleep(3000);
            game.previousTime = clock();
            game.isPlaying    = false;
        }

        // Update Player
        if (player->nextDir != FourDir_NONE) { // 플레이어가 다음 방향으로 전환할 수 있는지 확인
            Player_look(player, player->nextDir);
        }

        // Fixed Update
        // # 고정 시간 업데이트 부분. 유니티의 Fixed Update에 해당.
        game.currentTime           = clock(); // 현재 시간 측정
        clock_t const kElapsedTime = game.currentTime - game.previousTime; // '현재시간'과 '이전최근측정시간'의 차로 '지연된 시간'을 측정
        game.fixedTimeLag += kElapsedTime; // 지연된 시간을 고정 업데이트 시간 변화량에 추가

        player->posDeltaTime += game.fixedTimeLag; // 시간 변화량을 플레이어의 위치 업데이트 시간 변화량에 추가
        player->renderDeltaTime += game.fixedTimeLag; // 시간 변화량을 플레이어의 렌더링 업데이트 시간 변화량에 추가

        for (GhostType i = 0; i < GhostType_Count; ++i) {
            ghosts[i]->posDeltaTime += game.fixedTimeLag; // 시간 변화량을 유령의 위치 업데이트 시간 변화량에 추가
            Ghost_update(ghosts[i], i, player, game.fixedTimeLag);
        }

        // 시간 변화량이 고정 업데이트 간격(Game_kFixedUpdateInterval) 보다 크다면 ex(0.07 >= 0.02)
        while (game.fixedTimeLag >= Game_kFixedUpdateInterval) {
            // Player
            // 플레이어의 위치 업데이트 시간 변화량이 위치 업데이트 간격보다 크다면
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
                // 플레이어가 이동 가능하다면 이동시킴
                if (Player_isMovable(player, kNextPos)) {
                    player->pos = kNextPos;
                    gotoxy(kPrevPos.x, kPrevPos.y);
                    textcolor(Board_kTileFgColors[*tileAtPos], Board_kTileBgColors[*tileAtPos]);
                    wprintf(L"%lc", Board_kTileGlyphs[*tileAtPos]);
                }

                // 유령과의 접촉 여부를 확인
                for (GhostType i = 0; i < 4; ++i) {
                    Game_collidePlayerWithGhost(player, ghosts[i]);
                }

                // 플레이어 업데이트 간격 만큼 변화량 감소
                player->posDeltaTime -= player->posTimeStep;
            }

            // Ghost
            for (GhostType i = 0; i < GhostType_Count; ++i) {
                Ghost* ghost = ghosts[i];
                // 유령의 위치 업데이트 시간 변화량이 위치 업데이트 간격보다 크다면
                if (ghost->posDeltaTime >= ghost->posTimeStep) {
                    Point const kPrevPos = ghost->pos;
                    Point const kNextPos = Point_clamp(Point_add(ghost->pos, FourDir_dp(ghost->dir)), Point_zero(), (Point){ Board_kWidth - 1, Board_kHeight - 1 });

                    int* tileAtPos = Board_atPoint(kPrevPos);

                    // 유령이 이동 가능하다면 이동시킴
                    if (Ghost_isMovable(ghost, kNextPos)) {
                        ghost->pos = kNextPos;
                        gotoxy(kPrevPos.x, kPrevPos.y);
                        textcolor(Board_kTileFgColors[*tileAtPos], Board_kTileBgColors[*tileAtPos]);
                        wprintf(L"%lc", Board_kTileGlyphs[*tileAtPos]);
                    }

                    // Player와의 접촉 여부를 확인
                    Game_collidePlayerWithGhost(player, ghost);

                    // 유령 업데이트 간격 만큼 변화량 감소
                    ghost->posDeltaTime -= ghost->posTimeStep;
                }
            }

            // 고정 업데이트 간격 만큼 변화량 감소
            game.fixedTimeLag -= Game_kFixedUpdateInterval;
        }

        // Draw Player Frame
        // 플레이어의 렌더링 업데이트 시간 변화량이 렌더링 업데이트 간격보다 크다면
        while (player->renderDeltaTime >= player->frameTimeStep) {
            player->curFrame = Player_wrap_curFrame(player->curFrame + 1); // 플레이어의 프레임을 변경
            player->renderDeltaTime -= player->frameTimeStep; // 렌더링 업데이트 간격 만큼 변화량 감소
        }
        // 플레이어를 렌더링
        gotoxy(player->pos.x, player->pos.y);
        textcolor(player->color, Color_BLACK);
        wprintf(L"%lc", Player_kFrameByDirs[player->dir][player->curFrame]);

        // Draw Ghost
        // 각 유령을 렌더링
        for (GhostType i = 0; i < GhostType_Count; ++i) {
            Ghost* ghost = ghosts[i];
            gotoxy(ghost->pos.x, ghost->pos.y);
            textcolor(ghost->curColor, Color_BLACK);
            wprintf(L"%lc", Ghost_kFrameByState[ghost->curFrame]);
        }

        // Draw Score
        // 업데이트 전 점수와 현재 점수가 다르다면
        if (game.currentScore != kScore) {
            // 점수 패널 갱신
            gotoxy(31, 2);
            textcolor(Color_LIGHT_WHITE, Color_BLACK);
            wprintf(L"%8d", game.currentScore);
        }

        // Draw lifeRemaining
        // 업데이트 전 목숨수와 현재 목숨수가 다르다면
        if (player->lifeRemaining != kLifeRemaining) {
            // 목숨 패널 갱신
            gotoxy(31, 4);
            textcolor(Color_LIGHT_YELLOW, Color_BLACK);
            wprintf(L"Life");
            textcolor(Color_LIGHT_WHITE, Color_BLACK);
            wprintf(L"x%d", player->lifeRemaining);
        }

        // Delay: 지연된 시간과 목표 프레임 긴격의 차이로 다음 프레임까지 남은 시간을 계산
        clock_t kRemainingTime = Game_kRenderFrameInterval - kElapsedTime;
        // 다음 프레임까지 시간이 남았다면
        if (kRemainingTime > 0) {
            // 다음 프레임까지 대기
            Sleep(kRemainingTime);
        }
        // 이전최근측정시간을 갱신
        game.previousTime = game.currentTime;
    }

    // 게임화면이 종료되었다면 최대 점수를 갱신, 게임 보드를 초기화함
    game.highScore = game.currentScore > game.highScore ? game.currentScore : game.highScore;

    g_state = 0;
}
#pragma endregion // MAIN_FUNCTION



#pragma region FUNCTION_DEFS
void gotoxy(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setcursor(bool visible) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void textcolor(Color fg, Color bg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg | bg << 4u);
}

void cls_onProgramStart() {
    char cmd[100];
    system("cls"); // NOLINT
    (void)snprintf(cmd, sizeof(cmd), "mode con: cols=%d lines=%d", SCREEN_WIDTH, SCREEN_HEIGHT);
    system(cmd); // NOLINT
    (void)snprintf(cmd, sizeof(cmd), "title %s", kTitle);
    system(cmd); // NOLINT
    _wsetlocale(LC_ALL, L"");
    setcursor(false);
}

void cls_onProgramEnd() {
    system("cls"); // NOLINT
    setcursor(true);
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

// 정수 값 x를 범위 low와 high 사이로 감싸는 역할을 함. 만약 x가 low보다 작으면 high 값으로 설정하고, x가 high보다 크면 low 값으로 설정함
// 즉, x, l, h가 있을 때 x의 범위는 반 열린 구간인 [l, h)가 됨. l, l+1, ..., h-2, h-1을 포함
// 예를 들어, wrap(8, 0, 5)의 결과는 3이 됨. 8이 범위 0과 5 사이에 있으므로 3으로 감싸지게 되는 것
int wrap(int x, int low, int high) {
    int n = (x - low) % (high - low); // x를 low와 high 사이의 범위로 조정
    return (n >= 0) ? (n + low) : (n + high); // n이 0보다 크거나 같으면 (n + low)을, n이 0보다 작으면 (n + high) 값을 반환
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

// 게임 보드를 초기화함. 상수 g_kBoardData의 초기 데이터를 실제 게임판 g_boardData로 복사
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

// 게임 보드에 남은 점수를 계산하여 반환함. 타일 ​​값이 2(포인트) 또는 4(아이템)이면 count 변수를 증가시킵
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

// 지정된 색상으로 전체 게임 보드의 벽을 깜박임. 타일 ​​값이 1(벽)이면 해당 타일의 전경색과 배경색을 color 매개변수로 설정 후 wprintf() 함수를 사용하여 해당 타일 문자를 출력
void Board_flashWall(Color color) {
    gotoxy(0, 0);
    textcolor(color, color);
    for (int y = 0; y < Board_kHeight; ++y) {
        for (int x = 0; x < Board_kWidth; ++x) {
            int const kData = Board_dataAtXY(x, y);
            if (kData == 1) {
                gotoxy(x, y);
                wprintf(L"%lc", Board_kTileGlyphs[kData]);
            }
        }
    }
    textcolor(Color_BLACK, Color_BLACK);
}

// 게임 보드를 화면에 렌더링함. gotoxy() 함수를 사용하여 화면의 왼쪽 상단 모서리에 커서를 놓은 다음 g_boardData 배열의 각 요소를 반복, wprintf() 함수를 사용하여 해당 타일 문자를 출력, 타일의 전경색과 배경색은 각각 g_tileFgColorDate 및 g_tileBgColorDate 배열에 의해 결정
void Board_draw() {
    gotoxy(0, 0);
    textcolor(Color_BLACK, Color_BLACK);

    for (int y = 0; y < Board_kHeight; ++y) {
        for (int x = 0; x < Board_kWidth; ++x) {
            int const kData = Board_dataAtXY(x, y);
            textcolor(Board_kTileFgColors[kData], Board_kTileBgColors[kData]);
            wprintf(L"%lc", Board_kTileGlyphs[kData]);
        }
        textcolor(Color_BLACK, Color_BLACK);
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

    // FourDir_dp(dir)함수로 얻은 delta 값을 더하여 현재 위치에서 다음 위치를 계산
    Point const kLookingAt = Point_add(self->pos, FourDir_dp(toDir));
    if (Player_isMovable(self, kLookingAt)) {
        // 이동할 수 있으므로 현재 방향은 dir로 업데이트되고 다음 방향은 DIR_NONE으로 설정
        self->dir     = toDir;
        self->nextDir = FourDir_NONE;
    } else {
        // 이동할 수 없으므로 다음(이동 가능한 위치일 때 설정할)방향을 dir로 업데이트
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

    // 플레이어의 목숨이 1개 이상이면
    if (self->lifeRemaining > 0) {
        // 재시작
        Game_changeRound();
        return;
    }

    // 게임에서 패배
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

// 유령이 주어진 위치로 이동할 수 있는지 확인함. 유령의 상태(예를 들어, "먹힌" 상태가 아니거나 지속 시간이 4초 초과로 남아있는 "먹힌" 상태가 아니면 벽을 통과할 수 없음. , 다음 위치의 보드 데이터, 유령이 집에 있는지 여부를 확인하는 것입니다. 고스트가 다음 위치로 이동할 수 있는지 여부를 나타내는 부울 값을 반환합니다.
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
            (kIsAlive // "먹힌" 상태가 아니거나,
             || (kIsEaten && self->stateDuration[GhostState_EATEN] > 4000)) // 지속 시간이 4초 초과로 남아있는 "먹힌" 상태가 아닌데
            && kIsWall
        ) // 벽이라면 통과할 수 없음.
        || // 또는
        (
            (!kIsStayingButOutside //  (유령이 "대기" 상태이고 집에 없는 것이) 아니거나,
             || !kIsAliveButOutside // (유령이 "먹힌" 상태가 아니고 집에 없는 것이) 아니거나,
             || kIsInHome) // 집에 있는 것인데
            && kIsDoor
        ) // 문이라면 통과할 수 없음.
    );
}

// 유령의 방향을 업데이트함
void Ghost_look(Ghost* self, FourDir toDir) {
    assert(self);

    self->dir = toDir;
}

void Ghost_update(Ghost* self, GhostType type, Player* player, int deltaTime) { // NOLINT
    int     kPx           = self->pos.x;
    int     kPy           = self->pos.y;
    FourDir kDir          = self->dir;
    FourDir kBackwardsDir = FourDir_neg(kDir);

    // 각 활성 상태('isState'에 저장됨)의 'stateDuration'은 'deltaTime' 값만큼 줄임. 이 값은 마지막 업데이트 이후 경과된 시간을 나타냄.
    for (GhostState index = 0; index < 5; ++index) {
        if (self->isState[index]) {
            self->stateDuration[index] -= deltaTime;
        }
    }

    // 유령이 "먹힌" 상태
    if (self->isState[GhostState_EATEN]) {
        int kTx = self->targetPos.x;
        int kTy = self->targetPos.y;
        // 유령이 목표 위치에 도달했는지(kPx == kTx && kPy == kTy), 먹힌 상태의 남은 지속 시간이 만료되었다면
        if ((kPx == kTx && kPy == kTy) || self->stateDuration[GhostState_EATEN] <= 0) {
            // 유령을 재설정
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
            gotoxy(kPx, kPy);
            textcolor(Board_kTileFgColors[tileAtGhostPos], Board_kTileBgColors[tileAtGhostPos]);
            wprintf(L"%lc", Board_kTileGlyphs[tileAtGhostPos]);
            return;
        }
    }

    // 유령이 "두려움" 상태
    if (self->isState[GhostState_FRIGHTENED]) {
        // 두려움 상태의 남은 지속 시간이 만료되었다면
        if (self->stateDuration[GhostState_FRIGHTENED] <= 0) {
            // "흩어짐" 상태로 전환
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

    // 유령이 "대기" 상태
    if (self->isState[GhostState_STAYING]) {
        // 아직 대기 중이라면
        if (self->stateDuration[GhostState_STAYING] > 0) {
            // 현재 위치를 기준으로 다음 위치를 결정
            int kNx = kPx + FourDir_dx(kDir);
            int kNy = kPy + FourDir_dy(kDir);
            if (!Ghost_isMovable(self, (Point){ kNx, kNy })) {
                Ghost_look(self, kBackwardsDir);
            }
            return;
        }
        // 대기 중이 아닌데 집 안이라면
        if (self->isInHome) {
            // y축이 아직 목표 위치에 도달하지 않은 경우 다음 위치를 결정하고 이동 가능한지 확인
            if (kPy != self->targetPos.y) {
                int kNx = kPx + FourDir_dx(kDir);
                int kNy = kPy + FourDir_dy(kDir);
                if (!Ghost_isMovable(self, (Point){ kNx, kNy })) {
                    Ghost_look(self, kBackwardsDir);
                }
                return;
            }
            // y축이 목표 위치와 같다면 x축의 방향을 목표 위치 쪽으로 설정
            if (kPx != self->targetPos.x) {
                Ghost_look(self, self->targetPos.x - kPx > 0 ? FourDir_RIGHT : FourDir_LEFT);
                return;
            }
            // 목표 위치에 도달하였다면 다음 목표 위치를 집 외부 시작점으로 설정 후 위로 이동
            self->isInHome  = false;
            self->targetPos = Ghost_kPosOutside;
            Ghost_look(self, FourDir_UP);
            return;
        }
        // 아직 외부 시작점에 도달하지 않았다면 변화 없음(위로 이동)
        if (kPy != self->targetPos.y) {
            return;
        }
        // 외부 시작점에 도달하였다면 "흩어짐" 상태로 전환
        self->isState[GhostState_STAYING]          = false;
        self->stateDuration[GhostState_STAYING]    = 0;
        self->isState[GhostState_SCATTERING]       = true;
        self->stateDuration[GhostState_SCATTERING] = SCATTERING_DURATION;
        Ghost_look(self, (unsigned)rand() & 1u ? FourDir_LEFT : FourDir_RIGHT);
        return;
    }

    // 유령이 "두려움" 상태가 아니면서 "흩어짐" 상태라면
    if (!self->isState[GhostState_FRIGHTENED] && self->isState[GhostState_SCATTERING]) {
        // 지속 시간이 만료되었다면
        if (self->stateDuration[GhostState_SCATTERING] <= 0) {
            // "추적" 상태로 전환
            self->isState[GhostState_SCATTERING]       = false;
            self->stateDuration[GhostState_SCATTERING] = 0;
            self->isState[GhostState_CHASING]          = true;
            self->stateDuration[GhostState_CHASING]    = CHASING_DURATION;
            return;
        }

        // 지속 시간이 만료되지 않았면 현재 위치에서 이동 가능한 방향을 탐색
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
        // 이동 가능한 방향들 중에서 랜덤으로 현재 방향을 설정
        int kRandDirIndex = movableDirCount > 1 ? rand() % movableDirCount : 0;
        Ghost_look(self, movableDirs[kRandDirIndex]);
        return;
    }

    // 유령이 "두려움" 상태가 아니면서 "추적" 상태라면
    if (!self->isState[GhostState_FRIGHTENED] && self->isState[GhostState_CHASING]) {
        // 지속 시간이 만료되었다면
        if (self->stateDuration[GhostState_CHASING] <= 0) {
            // "흩어짐" 상태로 전환
            self->isState[GhostState_CHASING]          = false;
            self->stateDuration[GhostState_CHASING]    = 0;
            self->isState[GhostState_SCATTERING]       = true;
            self->stateDuration[GhostState_SCATTERING] = SCATTERING_DURATION;
            return;
        }
        // 지속 시간이 만료되지 않았다면 목표 위치를 플레이어 위치로 설정
        self->targetPos = player->pos;
    }

    // 현재 타겟 위치를 설정
    int kTx = self->targetPos.x;
    int kTy = self->targetPos.y;

    int bestDir     = FourDir_NONE;
    int distBestDir = self->isState[GhostState_FRIGHTENED] ? -1 : 9876543; // 최선 방향의 거리는 "두려움" 상태일 때 플레이어로 부터 최대 거리, "추적" 상태일 때 최단 거리

    for (FourDir dir = 0; dir < 4; ++dir) {
        // 탐색 방향이 뒷 방향이면 다음 탐색 방향으로 탐색
        if (dir == kBackwardsDir) {
            continue;
        }

        // 탐색 방향의 위치 변화를 저장
        int kNx = kPx + FourDir_dx(dir);
        int kNy = kPy + FourDir_dy(dir);

        // 탐색 방향으로 이동 불가하다면 다음 탐색 방향으로 탐색
        if (!Ghost_isMovable(self, (Point){ kNx, kNy })) {
            continue;
        }

        // 탐색 방향의 예상 위치와 플레이어와 위치 사이의 거리를 계산
        int kDist = (kTx - kNx) * (kTx - kNx) + (kTy - kNy) * (kTy - kNy); // L2 Norm
        // int kDist = abs(kNx - kTx) + abs(kNy - kTy); // Manhattan dist L1 Norm

        if (self->isState[GhostState_FRIGHTENED]) {
            // "두려움" 상태일 때 최대 거리를 선택
            if (kDist > distBestDir || bestDir == FourDir_NONE) {
                bestDir     = dir;
                distBestDir = kDist;
            }
        } else {
            // "추적" 상태일 때 최단 거리를 선택
            if (kDist < distBestDir || bestDir == FourDir_NONE) {
                bestDir     = dir;
                distBestDir = kDist;
            }
        }
    }

    // 선택된 최선 방향으로 현재 방향을 설정
    Ghost_look(self, bestDir);
}

void Ghost_onEatenByPlayer(Ghost* self) {
    assert(self);

    Game_flash(1, 500);
    game.currentScore += 200;
    game.currentTime = clock();

    for (int i = 0; i < 4; ++i) {
        // 유령의 모든 상태와 지속 시간을 재설정
        self->isState[i]       = false;
        self->stateDuration[i] = 0;
    }
    // 유령을 먹힌 "상태"로 전환
    self->isState[GhostState_EATEN]       = true;
    self->stateDuration[GhostState_EATEN] = EATEN_DURATION;
    self->curColor                        = Ghost_kColorEaten;
    self->curFrame                        = 2;
    self->speedPerSecond                  = 10;
    self->posDeltaTime /= 4;
    self->posTimeStep = CLOCKS_PER_SEC / self->speedPerSecond;
    self->targetPos   = Ghost_kPosOutside; // 유령의 목표 위치를 집 외부시작점으로 설정
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
    gotoxy(31, 0);
    textcolor(Color_RED, Color_BLACK);
    wprintf(L"HI-SCORE");
    gotoxy(31, 1);
    textcolor(Color_LIGHT_WHITE, Color_BLACK);
    wprintf(L"%8d", game.highScore);
    gotoxy(31, 2);
    wprintf(L"%8d", game.currentScore);

    gotoxy(31, 4);
    textcolor(Color_LIGHT_YELLOW, Color_BLACK);
    wprintf(L"Life");
    textcolor(Color_LIGHT_WHITE, Color_BLACK);
    wprintf(L"x%d", game.player.lifeRemaining);

    gotoxy(31, 6);
    wprintf(L"  W : UP");
    gotoxy(31, 7);
    wprintf(L"  A : LEFT");
    gotoxy(31, 8);
    wprintf(L"  S : RIGHT");
    gotoxy(31, 9);
    wprintf(L"  D : DOWN");
    gotoxy(31, 10);
    wprintf(L"ESC : Quit");

    // Reset Time
    game.currentTime  = clock(); // 현재 시간을 측정하여 이하 '현재측정시간'
    game.previousTime = clock(); // 매번 갱신되는 가장 최근에 마지막으로 업데이트한 시각을 저장, 이하 '이전최근측정시간'
    game.fixedTimeLag = 0; // FixedUpdate반복 횟수를 결정할 게임 루프 1회 반복 중 시간 변화량을 저장. 유니티에서의 Time.deltaTime과 같은 원리

    // Activate Game
    game.isPlaying = true;
}

// 게임의 유령과 플레이어 상태를 초기화
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

    // 서로 접촉하지 않았다면 패스
    if (Point_ne(player->pos, ghost->pos)) {
        return;
    }
    // 서로 접촉하였으므로 충돌 처리

    // 플레이어가 이미 먹혔다면 패스
    if (player->isEaten) {
        return;
    }

    // 유령이 이미 먹혔다면 패스
    if (ghost->isState[GhostState_EATEN]) {
        return;
    }

    // 유령이 "두려움" 상태라면
    if (ghost->isState[GhostState_FRIGHTENED]) {
        // 플레이어가 유령을 먹음
        Ghost_onEatenByPlayer(ghost);
    } else { // 아니라면
        // 플레이어가 유령에게 먹힘
        Player_onEatenByGhost(player);
    }
}

// 게임 보드에 깜박이는 효과를 수행함. 지정된 반복 횟수(iterCount) 동안 다른 색상(흰색과 파란색)으로 Board_flash()를 반복적으로 호출합니다. 'Sleep()' 함수를 사용하여 각 반복 사이에 지연(msecsPerIter)을 도입합니다.
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
        // 유령이 이미 "먹힌" 상태하면 다음 유령으로 진행
        if (game.ghosts[type].isState[GhostState_EATEN]) {
            continue;
        }

        // 유령의 상태를 "두려움" 상태로 전환
        game.ghosts[type].isState[GhostState_FRIGHTENED]       = true;
        game.ghosts[type].stateDuration[GhostState_FRIGHTENED] = FRIGHTENED_DURATION;
        game.ghosts[type].curColor                             = Ghost_kColorVulnerable;
        game.ghosts[type].curFrame                             = 1;
        game.ghosts[type].speedPerSecond                       = 2;
        game.ghosts[type].posDeltaTime *= 2;
        game.ghosts[type].posTimeStep = CLOCKS_PER_SEC / game.ghosts[type].speedPerSecond;
    }
}

void Game_onPlayerLost() {
    gotoxy(6, 16);
    textcolor(Color_LIGHT_WHITE, Color_PURPLE);
    wprintf(L"lose the game...");
    Sleep(3000);
    game.currentTime = clock();
    game.isPlaying   = false;
}

void Game_onPlayerWon() {
    gotoxy(6, 16);
    textcolor(Color_LIGHT_WHITE, Color_PURPLE);
    wprintf(L"win the game...");
    Sleep(3000);
    game.currentTime = clock();
    game.isPlaying   = false;
}
#pragma endregion // FUNCTION_DEFS
