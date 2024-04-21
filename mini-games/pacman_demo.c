#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define SWAP(A, B, TYPE) \
    do {                 \
        TYPE t = (A);    \
        (A) = (B);       \
        (B) = t;         \
    } while (0)

#define SCREEN_WIDTH  (80)
#define SCREEN_HEIGHT (25)

static const char* g_title = "PACMAN";

static inline int Wrap(int x, int low, int high) {
    const int n = (x - low) % (high - low);
    return (n >= 0) ? (n + low) : (n + high);
}

typedef enum eColor {
    FG_BLACK = 0x0000,
    FG_DARK_BLUE = 0x0001,
    FG_DARK_GREEN = 0x0002,
    FG_DARK_CYAN = 0x0003,
    FG_DARK_RED = 0x0004,
    FG_DARK_MAGENTA = 0x0005,
    FG_DARK_YELLOW = 0x0006,
    FG_GRAY = 0x0007,
    FG_DARK_GRAY = 0x0008,
    FG_BLUE = 0x0009,
    FG_GREEN = 0x000A,
    FG_CYAN = 0x000B,
    FG_RED = 0x000C,
    FG_MAGENTA = 0x000D,
    FG_YELLOW = 0x000E,
    FG_WHITE = 0x000F,
    BG_BLACK = 0x0000,
    BG_DARK_BLUE = 0x0010,
    BG_DARK_GREEN = 0x0020,
    BG_DARK_CYAN = 0x0030,
    BG_DARK_RED = 0x0040,
    BG_DARK_MAGENTA = 0x0050,
    BG_DARK_YELLOW = 0x0060,
    BG_GRAY = 0x0070,
    BG_DARK_GRAY = 0x0080,
    BG_BLUE = 0x0090,
    BG_GREEN = 0x00A0,
    BG_CYAN = 0x00B0,
    BG_RED = 0x00C0,
    BG_MAGENTA = 0x00D0,
    BG_YELLOW = 0x00E0,
    BG_WHITE = 0x00F0,
} Color;

static void Cursor_Move(int x, int y) {
    COORD pos = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

static void Cursor_SetVisible(bool visible) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

static void Cursor_SetColor(Color foreground, Color background) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground | background); }




// clang-format off
// 0 = empty, 1 = wall, 2 = point, 3 = door, 4 = item
static const int g_kBoardData[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, \
    1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, \
    1, 4, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 4, 1, \
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, \
    1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, \
    1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, \
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, \
    0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 3, 3, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, \
    1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, \
    0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, \
    1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, \
    0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, \
    1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, \
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, \
    1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, \
    1, 4, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 4, 1, \
    1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, \
    1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, \
    1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, \
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
// clang-format on

// clang-format off
// 0 = empty, 1 = wall, 2 = point, 3 = door, 4 = item
static int g_boardData[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, \
    1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, \
    1, 4, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 4, 1, \
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, \
    1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, \
    1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, \
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, \
    0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 3, 3, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, \
    1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, \
    0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, \
    1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, \
    0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0, \
    1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, \
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, \
    1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, \
    1, 4, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 4, 1, \
    1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, \
    1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, \
    1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, \
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
// clang-format on

static const int g_kBoardWidth = 28;
static const int g_kBoardHeight = 24;
static const wchar_t* g_tileCharData = L" #.-*";
static const Color g_tileFgColorDate[] = { FG_BLACK, FG_DARK_BLUE, FG_DARK_YELLOW, FG_GRAY, FG_RED };
static const Color g_tileBgColorDate[] = { BG_BLACK, BG_DARK_BLUE, BG_BLACK, BG_BLACK, BG_BLACK };

static void ResetBoard() {
    int index = 0;
    for (int y = 0; y < g_kBoardHeight; ++y) {
        for (int x = 0; x < g_kBoardWidth; ++x) {
            const int kCurIndexData = g_kBoardData[index];
            g_boardData[index++] = kCurIndexData;
        }
    }
}

static void DrawBoard() {
    int index = 0;
    Cursor_Move(0, 0);
    Cursor_SetColor(FG_BLACK, BG_BLACK);
    for (int y = 0; y < g_kBoardHeight; ++y) {
        for (int x = 0; x < g_kBoardWidth; ++x) {
            const int kCurIndexData = g_boardData[index++];
            Cursor_SetColor(g_tileFgColorDate[kCurIndexData], g_tileBgColorDate[kCurIndexData]);
            wprintf(L"%lc", g_tileCharData[kCurIndexData]);
        }
        Cursor_SetColor(FG_BLACK, BG_BLACK);
        wprintf(L"\n");
    }
}

static void FlashBoard(Color color) {
    int index = 0;
    Cursor_Move(0, 0);
    Cursor_SetColor(color, color << 4);
    for (int y = 0; y < g_kBoardHeight; ++y) {
        for (int x = 0; x < g_kBoardWidth; ++x) {
            const int kCurIndexData = g_boardData[index++];
            if (kCurIndexData == 1) {
                Cursor_Move(x, y);
                wprintf(L"%lc", g_tileCharData[kCurIndexData]);
            }
        }
    }
    Cursor_SetColor(FG_BLACK, BG_BLACK);
}

static void Flash(int iter, int timePerIter) {
    for (int i = 0; i < iter; ++i) {
        FlashBoard(FG_GRAY);
        Sleep(timePerIter / 2);
        FlashBoard(FG_DARK_BLUE);
        Sleep(timePerIter / 2);
    }
}

static int GetRemainingPoint() {
    int index = 0;
    int count = 0;
    for (int y = 0; y < g_kBoardHeight; ++y) {
        for (int x = 0; x < g_kBoardWidth; ++x) {
            const int kCurIndexData = g_boardData[index++];
            if (kCurIndexData == 2 || kCurIndexData == 4) {
                count++;
            }
        }
    }
    return count;
}



typedef struct _Position {
    int x;
    int y;
} Position;

static Position* NewPos(int x, int y) {
    Position* newPos = (Position*)malloc(sizeof(Position));
    newPos->x = x;
    newPos->y = y;
    return newPos;
}

typedef enum eDirection { DIR_NONE = -1,
                          DIR_UP,
                          DIR_LEFT,
                          DIR_RIGHT,
                          DIR_DOWN } Direction;

static inline Direction GetOppositeDirectionOf(Direction dir) {
    static const Direction oppositeDirOf[5] = { DIR_NONE, DIR_DOWN, DIR_RIGHT, DIR_LEFT, DIR_UP };
    return oppositeDirOf[dir + 1];
}

static inline int GetDx(Direction dir) {
    static const int kDx[5] = { 0, 0, -1, +1, 0 };
    return kDx[dir + 1];
}

static inline int GetDy(Direction dir) {
    static const int kDy[5] = { 0, -1, 0, 0, +1 };
    return kDy[dir + 1];
}

typedef struct _Player {
    clock_t posTimeStep;
    clock_t frameTimeStep; // 6 frames per 0.125s
    int posDeltaTime;
    int renderDeltaTime;
    Position pos;
    Direction dir;
    Direction nextDir;
    Color color;
    int curFrame;
    int lifeRemaining;
    int speedPerSecond;
    bool isEaten;
} Player;

static const Position Player_kStartingPoint = { 13, 18 };
static const Direction Player_kInitialDirection = DIR_LEFT;
static const int Player_kFrameCount = 6;
static const wchar_t* Player_kFrameIdle = L"O";
static const wchar_t* Player_kFrameData[4] = {
    L"VV|||V", // UP
    L"})>->)", // LEFT
    L"{(<-<(", // RIGHT
    L"^^|||^", // DOWN
};

static void Player_Reset(Player* this) {
    this->pos = Player_kStartingPoint;
    this->dir = Player_kInitialDirection;
    this->nextDir = DIR_NONE;
    this->color = FG_YELLOW;
    this->speedPerSecond = 5;
    this->posDeltaTime = 0;
    this->posTimeStep = CLOCKS_PER_SEC / this->speedPerSecond;
    this->curFrame = 0;
    this->renderDeltaTime = 0;
    this->frameTimeStep = this->posTimeStep / Player_kFrameCount;
    this->isEaten = false;
}

static bool Player_IsMovable(Position* nextPos) {
    bool isMovable = !((g_boardData[nextPos->y * 28 + nextPos->x] == 1) || (g_boardData[nextPos->y * 28 + nextPos->x] == 3));
    free(nextPos);
    return isMovable;
}

static void Player_Look(Player* this, Direction dir) {
    const int kNextX = this->pos.x + GetDx(dir);
    const int kNextY = this->pos.y + GetDy(dir);
    if (Player_IsMovable(NewPos(kNextX, kNextY))) {
        this->dir = dir;
        this->nextDir = DIR_NONE;
    } else {
        this->nextDir = dir;
    }
}

static inline int Player_x_wrap(int x) { return Wrap(x, 0, g_kBoardWidth); }

static inline int Player_y_wrap(int y) { return Wrap(y, 0, g_kBoardHeight); }

static inline int Player_curFrame_wrap(int curFrame) { return Wrap(curFrame, 0, Player_kFrameCount); }



typedef enum eGhostType {
    GHOST_BLINKY,
    GHOST_INKY,
    GHOST_PINKY,
    GHOST_CLYDE,
} GhostType;

typedef enum eGhostState { GHOST_STAYING,
                           GHOST_SCATTERING,
                           GHOST_CHASING,
                           GHOST_FRIGHTENED,
                           GHOST_EATEN } GhostState;

enum eGhostDuration {
    STAYING_DURATION = 1 * CLOCKS_PER_SEC,
    SCATTERING_DURATION = 7 * CLOCKS_PER_SEC,
    CHASING_DURATION = 20 * CLOCKS_PER_SEC,
    FRIGHTENED_DURATION = 8 * CLOCKS_PER_SEC,
    EATEN_DURATION = 8 * CLOCKS_PER_SEC
};

typedef struct _Ghost {
    bool isState[5];
    bool isInHome;
    int stateDuration[5];
    clock_t posTimeStep;
    int posDeltaTime;
    Position pos;
    Position targetPos;
    Direction dir;
    Color curColor;
    int curFrame;
    int speedPerSecond;
} Ghost;

static const wchar_t* Ghost_kFrameData = L"Mm%%";
static const Position Ghost_kInside = { 13, 11 };
static const Position Ghost_kOutside = { 13, 8 };
static const Position Ghost_kStartingPoints[4] = { { 13, 8 }, { 11, 11 }, { 13, 11 }, { 15, 11 } };
static const Direction Ghost_kInitialDirections[4] = { DIR_LEFT, DIR_UP, DIR_DOWN, DIR_UP };
static const int Ghost_kInitialStayingDurations[4] = { 0, 2, 8, 16 };
static const Color Ghost_kColors[4] = { FG_RED, FG_BLUE, FG_MAGENTA, FG_DARK_YELLOW };
static const Color Ghost_kVulnerableColor = FG_DARK_BLUE;
static const Color Ghost_kEatenColor = FG_GRAY;

static void Ghost_Reset(Ghost* this, GhostType type) {
    this->pos = Ghost_kStartingPoints[type];
    this->targetPos = type == GHOST_BLINKY ? Ghost_kOutside : Ghost_kInside;
    this->dir = Ghost_kInitialDirections[type];
    this->curColor = Ghost_kColors[type];
    this->curFrame = 0;
    for (GhostState i = 0; i < 5; ++i) {
        this->isState[i] = false;
        this->stateDuration[i] = 0;
    }
    this->isState[GHOST_STAYING] = true;
    this->stateDuration[GHOST_STAYING] = Ghost_kInitialStayingDurations[type] * STAYING_DURATION;
    this->isInHome = true;
    this->speedPerSecond = 4;
    this->posDeltaTime = 0;
    this->posTimeStep = CLOCKS_PER_SEC / this->speedPerSecond;
}

static bool Ghost_IsMovable(Ghost* this, Position* nextPos) {
    bool isMovable =
        !(((!this->isState[GHOST_EATEN] || this->isState[GHOST_EATEN] && this->stateDuration[GHOST_EATEN] > 4000) && (g_boardData[nextPos->y * 28 + nextPos->x] == 1)) || ((!(this->isState[GHOST_STAYING] && !this->isInHome) || !(!this->isState[GHOST_EATEN] && !this->isInHome) || this->isInHome) && g_boardData[nextPos->y * 28 + nextPos->x] == 3));
    free(nextPos);
    return isMovable;
}

static void Ghost_Look(Ghost* this, Direction dir) { this->dir = dir; }

static void Ghost_Update(Ghost* this, GhostType type, Player* player, int deltaTime) {
    const int kPx = this->pos.x;
    const int kPy = this->pos.y;
    const Direction kDir = this->dir;
    const Direction kBackwardsDir = GetOppositeDirectionOf(kDir);

    for (GhostState index = 0; index < 5; ++index) {
        if (this->isState[index]) {
            this->stateDuration[index] -= deltaTime;
        }
    }

    if (this->isState[GHOST_EATEN]) {
        const int kTx = this->targetPos.x;
        const int kTy = this->targetPos.y;
        if (kPx == kTx && kPy == kTy || this->stateDuration[GHOST_EATEN] <= 0) {
            this->pos = Ghost_kStartingPoints[type == GHOST_BLINKY ? GHOST_PINKY : type];
            this->isState[GHOST_EATEN] = false;
            this->stateDuration[GHOST_EATEN] = 0;
            this->isState[GHOST_STAYING] = true;
            this->stateDuration[GHOST_STAYING] = STAYING_DURATION * 8;
            this->isInHome = true;
            this->targetPos = Ghost_kInside;
            this->curColor = Ghost_kColors[type];
            this->curFrame = 0;
            this->posDeltaTime /= 4;
            this->speedPerSecond = 4;
            this->posTimeStep = CLOCKS_PER_SEC / this->speedPerSecond;

            int* tileAtGhostPos = &g_boardData[kPy * 28 + kPx];
            Cursor_Move(kPx, kPy);
            Cursor_SetColor(g_tileFgColorDate[*tileAtGhostPos], g_tileBgColorDate[*tileAtGhostPos]);
            wprintf(L"%lc", g_tileCharData[*tileAtGhostPos]);
            return;
        }
    }

    if (this->isState[GHOST_FRIGHTENED]) {
        if (this->stateDuration[GHOST_FRIGHTENED] <= 0) {
            this->isState[GHOST_FRIGHTENED] = false;
            this->stateDuration[GHOST_FRIGHTENED] = 0;
            this->isState[GHOST_SCATTERING] = true;
            this->stateDuration[GHOST_SCATTERING] = SCATTERING_DURATION;
            this->curColor = Ghost_kColors[type];
            this->curFrame = 0;
            this->posDeltaTime /= 2;
            this->speedPerSecond = 4;
            this->posTimeStep = CLOCKS_PER_SEC / this->speedPerSecond;
            return;
        }
    }

    if (this->isState[GHOST_STAYING]) {
        if (this->stateDuration[GHOST_STAYING] > 0) {
            const int kNx = kPx + GetDx(kDir);
            const int kNy = kPy + GetDy(kDir);
            if (!Ghost_IsMovable(this, NewPos(kNx, kNy))) {
                Ghost_Look(this, kBackwardsDir);
            }
            return;
        }
        if (this->isInHome) {
            if (kPy != this->targetPos.y) {
                const int kNx = kPx + GetDx(kDir);
                const int kNy = kPy + GetDy(kDir);
                if (!Ghost_IsMovable(this, NewPos(kNx, kNy))) {
                    Ghost_Look(this, kBackwardsDir);
                }
                return;
            }
            if (kPx != this->targetPos.x) {
                Ghost_Look(this, this->targetPos.x - kPx > 0 ? DIR_RIGHT : DIR_LEFT);
                return;
            }
            this->isInHome = false;
            this->targetPos = Ghost_kOutside;
            Ghost_Look(this, DIR_UP);
            return;
        }
        if (kPy != this->targetPos.y) {
            return;
        }
        this->isState[GHOST_STAYING] = false;
        this->stateDuration[GHOST_STAYING] = 0;
        this->isState[GHOST_SCATTERING] = true;
        this->stateDuration[GHOST_SCATTERING] = SCATTERING_DURATION;
        Ghost_Look(this, rand() & 1 ? DIR_LEFT : DIR_RIGHT);
        return;
    }

    if (!this->isState[GHOST_FRIGHTENED] && this->isState[GHOST_SCATTERING]) {
        if (this->stateDuration[GHOST_SCATTERING] <= 0) {
            this->isState[GHOST_SCATTERING] = false;
            this->stateDuration[GHOST_SCATTERING] = 0;
            this->isState[GHOST_CHASING] = true;
            this->stateDuration[GHOST_CHASING] = CHASING_DURATION;
            return;
        }

        Direction movableDirs[3];
        int movableDirCount = 0;

        for (Direction dir = 0; dir < 4; ++dir) {
            if (dir == kBackwardsDir) {
                continue;
            }
            const int kNx = kPx + GetDx(dir);
            const int kNy = kPy + GetDy(dir);
            if (Ghost_IsMovable(this, NewPos(kNx, kNy))) {
                movableDirs[movableDirCount++] = dir;
            }
        }
        const int kRandDirIndex = movableDirCount > 1 ? rand() % movableDirCount : 0;
        Ghost_Look(this, movableDirs[kRandDirIndex]);
        return;
    }

    if (!this->isState[GHOST_FRIGHTENED] && this->isState[GHOST_CHASING]) {
        if (this->stateDuration[GHOST_CHASING] <= 0) {
            this->isState[GHOST_CHASING] = false;
            this->stateDuration[GHOST_CHASING] = 0;
            this->isState[GHOST_SCATTERING] = true;
            this->stateDuration[GHOST_SCATTERING] = SCATTERING_DURATION;
            return;
        }

        this->targetPos = player->pos;
    }

    const int kTx = this->targetPos.x;
    const int kTy = this->targetPos.y;

    int bestDir = DIR_NONE;
    int distBestDir = this->isState[GHOST_FRIGHTENED] ? -1 : 987654321;

    for (Direction dir = 0; dir < 4; ++dir) {
        if (dir == kBackwardsDir) {
            continue;
        }

        const int kNx = kPx + GetDx(dir);
        const int kNy = kPy + GetDy(dir);

        if (!Ghost_IsMovable(this, NewPos(kNx, kNy))) {
            continue;
        }

        const int kDist = (kTx - kNx) * (kTx - kNx) + (kTy - kNy) * (kTy - kNy); // L2 Norm
        // const int kDist = abs(kNx - kTx) + abs(kNy - kTy); // Manhattan dist L1 Norm

        if (this->isState[GHOST_FRIGHTENED]) {
            if (kDist > distBestDir || bestDir == DIR_NONE) {
                bestDir = dir;
                distBestDir = kDist;
            }
        } else {
            if (kDist < distBestDir || bestDir == DIR_NONE) {
                bestDir = dir;
                distBestDir = kDist;
            }
        }
    }

    Ghost_Look(this, bestDir);
}

static void Player_EatPowerItem(Ghost ghosts[4]) {
    for (int i = 0; i < 4; i++) {
        if (ghosts[i].isState[GHOST_EATEN]) {
            continue;
        }
        ghosts[i].isState[GHOST_FRIGHTENED] = true;
        ghosts[i].stateDuration[GHOST_FRIGHTENED] = FRIGHTENED_DURATION;
        ghosts[i].curColor = Ghost_kVulnerableColor;
        ghosts[i].curFrame = 1;
        ghosts[i].speedPerSecond = 2;
        ghosts[i].posDeltaTime *= 2;
        ghosts[i].posTimeStep = CLOCKS_PER_SEC / ghosts[i].speedPerSecond;
    }
}

static void Player_EatGhost(Ghost* ghost, GhostType type) {
    for (int i = 0; i < 4; ++i) {
        ghost->isState[i] = false;
        ghost->stateDuration[i] = 0;
    }
    ghost->isState[GHOST_EATEN] = true;
    ghost->stateDuration[GHOST_EATEN] = EATEN_DURATION;
    ghost->curColor = Ghost_kEatenColor;
    ghost->curFrame = 2;
    ghost->speedPerSecond = 10;
    ghost->posDeltaTime /= 4;
    ghost->posTimeStep = CLOCKS_PER_SEC / ghost->speedPerSecond;
    ghost->targetPos = Ghost_kOutside;
}

static void ResetGameState(Ghost ghosts[4], Player* player) {
    Player_Reset(player);
    for (GhostType i = 0; i < 4; ++i) {
        Ghost_Reset(&ghosts[i], i);
    }
    DrawBoard();
}

static void Ghost_EatPacman(Ghost ghosts[4], Player* player) {
    player->isEaten = true;
    ResetGameState(ghosts, player);
}




enum eKey { KEY_UP = 0x48,
            KEY_LEFT = 0x4B,
            KEY_RIGHT = 0x4D,
            KEY_DOWN = 0x50,
            KEY_ESC = 0x1B,
            KEY_ENTER = 0x0D };

static int GetInputKey() {
    if (kbhit()) {
        int input = getch();
        const bool isFunctionKey = input == 0x00;
        const bool isExtendedKey = input == 0xE0;
        if (isFunctionKey || isExtendedKey) {
            return getch();
        } else {
            return input;
        }
    }
    return 0;
}



/*
enum eCommand {
    CMD_SET_DIR_UP,
    CMD_SET_DIR_LEFT,
    CMD_SET_DIR_RIGHT,
    CMD_SET_DIR_DOWN,
    CMD_QUIT_GAME
};

static int g_command[] = { DIR_UP, DIR_LEFT, DIR_RIGHT, DIR_DOWN, CMD_QUIT_GAME };
static int g_gameKey[128];

void GameKey_Initialize() {
    g_gameKey['w'] = CMD_SET_DIR_UP;
    g_gameKey[KEY_UP] = CMD_SET_DIR_UP;
    g_gameKey['a'] = CMD_SET_DIR_LEFT;
    g_gameKey[KEY_LEFT] = CMD_SET_DIR_LEFT;
    g_gameKey['d'] = CMD_SET_DIR_RIGHT;
    g_gameKey[KEY_RIGHT] = CMD_SET_DIR_RIGHT;
    g_gameKey['s'] = CMD_SET_DIR_DOWN;
    g_gameKey[KEY_DOWN] = CMD_SET_DIR_DOWN;
    g_gameKey['q'] = CMD_QUIT_GAME;
    g_gameKey[KEY_ESC] = CMD_QUIT_GAME;
}
*/



static void Screen_Initialize() {
    char cmd[100];
    system("cls"); // NOLINT
    sprintf(cmd, "mode con: cols=%d lines=%d", SCREEN_WIDTH, SCREEN_HEIGHT);
    system(cmd); // NOLINT
    sprintf(cmd, "title %s", g_title);
    system(cmd); // NOLINT
    _wsetlocale(LC_ALL, L"");
    Cursor_SetVisible(false);
}

static void Screen_Finalize() {
    system("cls"); // NOLINTd
    Cursor_SetVisible(true);
}

int main(void) {
    // Initialize Game
    const char kPressedCmpData[] = { 'w', 'a', 'd', 's', KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, 'q', KEY_ESC };
    bool isPressed[10] = {
        false,
    };
    int highScore = 0;

    // Initialize Player
    Player player = {
        0,
    };
    Player_Reset(&player);

    // Initialize Ghost
    Ghost ghosts[4] = {
        0,
    };
    for (GhostType i = 0; i < 4; ++i) {
        Ghost_Reset(&ghosts[i], i);
    }

    // Menu Scene
    Screen_Initialize();
    int selection = -1;

    do {
        system("cls");
        int curMenuPointer = 0;
        int input = 0;
        selection = -1;

        Cursor_Move(0, 0);
        Cursor_SetColor(FG_WHITE, BG_BLACK);
        wprintf(L"> Start\n");
        wprintf(L"  Quit\n");

        while (selection == -1) {
            const int kPrevPointer = curMenuPointer;

            input = GetInputKey();

            switch (input) {
            case KEY_UP:
                curMenuPointer = Wrap(curMenuPointer - 1, 0, 2);
                break;
            case KEY_DOWN:
                curMenuPointer = Wrap(curMenuPointer + 1, 0, 2);
                break;
            case KEY_ESC:
                selection = 1;
                break;
            case KEY_ENTER:
                selection = curMenuPointer;
                break;
            default:
                break;
            }

            if (curMenuPointer != kPrevPointer) {
                Cursor_Move(0, kPrevPointer);
                wprintf(L" ");
                Cursor_Move(0, curMenuPointer);
                wprintf(L">");
            }
        }
        Cursor_Move(0, selection);
        wprintf(L" \n");

        if (selection == 1) {
            break;
        }



        // Game Scene
        bool isPlaying = true;
        bool started = false;
        int remainingPoint = GetRemainingPoint();
        int curScore = 0;
        Player_Reset(&player);
        player.lifeRemaining = 3;
        for (GhostType i = 0; i < 4; ++i) {
            Ghost_Reset(&ghosts[i], i);
        }

        DrawBoard();

        // Draw Panel
        Cursor_Move(31, 0);
        Cursor_SetColor(FG_DARK_RED, BG_BLACK);
        wprintf(L"HI-SCORE");
        Cursor_Move(31, 1);
        Cursor_SetColor(FG_WHITE, BG_BLACK);
        wprintf(L"%8d", highScore);
        Cursor_Move(31, 2);
        wprintf(L"%8d", curScore);

        Cursor_Move(31, 4);
        Cursor_SetColor(FG_YELLOW, BG_BLACK);
        wprintf(L"Life");
        Cursor_SetColor(FG_WHITE, BG_BLACK);
        wprintf(L"x%d", player.lifeRemaining);

        Cursor_Move(31, 6);
        wprintf(L"  W : UP");
        Cursor_Move(31, 7);
        wprintf(L"  A : LEFT");
        Cursor_Move(31, 8);
        wprintf(L"  S : RIGHT");
        Cursor_Move(31, 9);
        wprintf(L"  D : DOWN");
        Cursor_Move(31, 10);
        wprintf(L"ESC : Quit");

        const clock_t kTargetFPS = 30;
        const clock_t kTargetFrameTime = CLOCKS_PER_SEC / kTargetFPS;
        const clock_t kFixedTimeStep = (clock_t)(0.02 * CLOCKS_PER_SEC); // 1 / targetFPS

        int fixedTimeLag = 0;
        clock_t previousTime = clock();

        while (isPlaying) {
            // Process Input
            input = GetInputKey();

            for (int key = 0; key < 10; ++key) {
                isPressed[key] = input == kPressedCmpData[key];
            }

            // Handle Input Key
            if (isPressed[8] || isPressed[9]) {
                isPlaying = false;
                continue;
            }

            // Handle Input Player Movement
            for (Direction dir = 0; dir < 4; ++dir) {
                if (!(isPressed[dir] || isPressed[dir + 4])) {
                    continue;
                }
                Player_Look(&player, dir);
                break;
            }

            // Update Game
            const int kScore = curScore;
            const int kLifeRemaining = player.lifeRemaining;
            if (remainingPoint <= 0) {
                Flash(3, 500);
                Cursor_Move(10, 16);
                Cursor_SetColor(FG_WHITE, BG_DARK_YELLOW);
                wprintf(L" Clear! ");
                Sleep(3000);
                previousTime = clock();
                isPlaying = false;
            }

            // Update Player
            if (player.nextDir != DIR_NONE) {
                Player_Look(&player, player.nextDir);
            }

            // Fixed Update
            clock_t currentTime = clock();
            const clock_t kElapsedTime = currentTime - previousTime;
            fixedTimeLag += kElapsedTime;

            player.posDeltaTime += fixedTimeLag;
            player.renderDeltaTime += fixedTimeLag;

            for (GhostType i = 0; i < 4; ++i) {
                ghosts[i].posDeltaTime += fixedTimeLag;
                Ghost_Update(&ghosts[i], i, &player, fixedTimeLag);
            }

            while (fixedTimeLag >= kFixedTimeStep) {
                // Player
                if (player.posDeltaTime >= player.posTimeStep) {
                    const int kPrevX = player.pos.x;
                    const int kPrevY = player.pos.y;
                    const int kNextX = Player_x_wrap(kPrevX + GetDx(player.dir));
                    const int kNextY = Player_y_wrap(kPrevY + GetDy(player.dir));
                    int* tileAtPlayerPos = &g_boardData[kPrevY * 28 + kPrevX];

                    // Add Score
                    if (*tileAtPlayerPos == 2) {
                        remainingPoint -= 1;
                        curScore += 10;
                        *tileAtPlayerPos = 0;
                    }

                    if (*tileAtPlayerPos == 4) {
                        remainingPoint -= 1;
                        curScore += 50;
                        *tileAtPlayerPos = 0;
                        Player_EatPowerItem(ghosts);
                    }

                    // Movement
                    if (Player_IsMovable(NewPos(kNextX, kNextY))) {
                        player.pos.x = kNextX;
                        player.pos.y = kNextY;
                        Cursor_Move(kPrevX, kPrevY);
                        Cursor_SetColor(g_tileFgColorDate[*tileAtPlayerPos], g_tileBgColorDate[*tileAtPlayerPos]);
                        wprintf(L"%lc", g_tileCharData[*tileAtPlayerPos]);
                    }

                    for (GhostType i = 0; i < 4; ++i) {
                        if (!ghosts[i].isState[GHOST_EATEN]) {
                            if (player.pos.x == ghosts[i].pos.x && player.pos.y == ghosts[i].pos.y) {
                                if (ghosts[i].isState[GHOST_FRIGHTENED]) {
                                    curScore += 200;
                                    Flash(1, 500);
                                    Player_EatGhost(&ghosts[i], i);
                                    currentTime = clock();
                                } else {
                                    if (!player.isEaten) {
                                        player.lifeRemaining--;
                                        Flash(3, 500);
                                        if (player.lifeRemaining > 0) {
                                            Ghost_EatPacman(ghosts, &player);
                                            currentTime = clock();
                                        } else {
                                            Cursor_Move(6, 16);
                                            Cursor_SetColor(FG_WHITE, BG_DARK_MAGENTA);
                                            wprintf(L"lose the game...");
                                            Sleep(3000);
                                            currentTime = clock();
                                            isPlaying = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    player.posDeltaTime -= player.posTimeStep;
                }

                // Ghost
                for (GhostType i = 0; i < 4; ++i) {
                    Ghost* ghost = &ghosts[i];
                    if (ghost->posDeltaTime >= ghost->posTimeStep) {
                        const int kPrevX = ghost->pos.x;
                        const int kPrevY = ghost->pos.y;
                        const int kNextX = kPrevX + GetDx(ghost->dir);
                        const int kNextY = kPrevY + GetDy(ghost->dir);
                        int* tileAtGhostPos = &g_boardData[kPrevY * 28 + kPrevX];
                        if (Ghost_IsMovable(ghost, NewPos(kNextX, kNextY))) {
                            ghost->pos.x = kNextX;
                            ghost->pos.y = kNextY;
                            Cursor_Move(kPrevX, kPrevY);
                            Cursor_SetColor(g_tileFgColorDate[*tileAtGhostPos], g_tileBgColorDate[*tileAtGhostPos]);
                            wprintf(L"%lc", g_tileCharData[*tileAtGhostPos]);
                        }
                        if (!ghost->isState[GHOST_EATEN]) {
                            if (ghost->pos.x == player.pos.x && ghost->pos.y == player.pos.y) {
                                if (ghost->isState[GHOST_FRIGHTENED]) {
                                    curScore += 200;
                                    Flash(1, 500);
                                    Player_EatGhost(ghost, i);
                                    currentTime = clock();
                                } else {
                                    if (!player.isEaten) {
                                        player.lifeRemaining--;
                                        Flash(3, 500);
                                        if (player.lifeRemaining > 0) {
                                            Ghost_EatPacman(ghosts, &player);
                                            currentTime = clock();
                                        } else {
                                            Cursor_Move(5, 16);
                                            Cursor_SetColor(FG_WHITE, BG_DARK_MAGENTA);
                                            wprintf(L" lose the game... ");
                                            Sleep(3000);
                                            currentTime = clock();
                                            isPlaying = false;
                                        }
                                    }
                                }
                            }
                        }
                        ghost->posDeltaTime -= ghost->posTimeStep;
                    }
                }

                fixedTimeLag -= kFixedTimeStep;
            }

            // Draw Player Frame
            while (player.renderDeltaTime >= player.frameTimeStep) {
                player.curFrame = Player_curFrame_wrap(player.curFrame + 1);
                player.renderDeltaTime -= player.frameTimeStep;
            }
            Cursor_Move(player.pos.x, player.pos.y);
            Cursor_SetColor(player.color, BG_BLACK);
            wprintf(L"%lc", Player_kFrameData[player.dir][player.curFrame]);

            // Draw Ghost
            for (GhostType i = 0; i < 4; ++i) {
                Ghost* ghost = &ghosts[i];
                Cursor_Move(ghost->pos.x, ghost->pos.y);
                Cursor_SetColor(ghost->curColor, BG_BLACK);
                wprintf(L"%lc", Ghost_kFrameData[ghost->curFrame]);
            }

            // Draw Score
            if (curScore != kScore) {
                Cursor_Move(31, 2);
                Cursor_SetColor(FG_WHITE, BG_BLACK);
                wprintf(L"%8d", curScore);
            }

            // Draw lifeRemaining
            if (player.lifeRemaining != kLifeRemaining) {
                Cursor_Move(31, 4);
                Cursor_SetColor(FG_YELLOW, BG_BLACK);
                wprintf(L"Life");
                Cursor_SetColor(FG_WHITE, BG_BLACK);
                wprintf(L"x%d", player.lifeRemaining);
            }

            // Debug
            Cursor_Move(30, 19);
            Cursor_SetColor(FG_WHITE, BG_BLACK);
            wprintf(L"(org) currentTime=%ld elapsedTime=%ld", currentTime, kElapsedTime);
            Cursor_Move(30, 20);
            wprintf(L"(sec) currentSec=%.3lf elapsedSec=%.3lf", (double)currentTime / CLOCKS_PER_SEC, (double)kElapsedTime / CLOCKS_PER_SEC);
            Cursor_Move(30, 21);
            wprintf(L"dir=%2d nextDir=%2d input=%c", player.dir, player.nextDir, input);
            Cursor_Move(30, 22);
            wprintf(L"tPos=%04ld tF=%04ld dtPos=%04d dtF=%04d", player.posTimeStep, player.frameTimeStep, player.posDeltaTime, player.renderDeltaTime);
            Cursor_Move(30, 23);
            wprintf(L"gDir=%2d", ghosts[0].dir);

            // Delay
            const clock_t kRemainingTime = kTargetFrameTime - kElapsedTime;
            if (kRemainingTime > 0) {
                Sleep(kRemainingTime);
            }
            previousTime = currentTime;
        }

        highScore = curScore > highScore ? curScore : highScore;
        ResetBoard();
    } while (selection != 1);

    Screen_Finalize();

    return 0;
}
