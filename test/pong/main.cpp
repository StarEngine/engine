/**
 * StarEngine Test Program — Star Pong
 *
 * A Pong game with start menu, AI opponents, and difficulty settings.
 * Links against the starengine library (Logger, TimeManager).
 * Uses SDL2 for windowing/input and OpenGL 2.1 immediate mode for rendering.
 *
 * Menu Controls:
 *   Up / Down        Navigate
 *   Enter / Space    Select
 *   Escape           Back / Quit
 *
 * Game Controls:
 *   Player 1 (left):   W / S
 *   Player 2 (right):  Up / Down arrows  (2-player mode only)
 *   Pause:             Space
 *   Escape:            Back to menu
 */

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <string>
#include <cstring>
#include <algorithm>

// StarEngine headers
#include "Logger.h"
#include "TimeManager.h"
#include "defines.h"

// ---------------------------------------------------------------------------
// Constants
// ---------------------------------------------------------------------------
static const int   WINDOW_W      = 800;
static const int   WINDOW_H      = 600;
static const float PADDLE_W      = 12.0f;
static const float PADDLE_H      = 80.0f;
static const float PADDLE_SPEED  = 350.0f;
static const float PADDLE_MARGIN = 30.0f;
static const float BALL_SIZE     = 10.0f;
static const float BALL_SPEED    = 300.0f;
static const float BALL_ACCEL    = 20.0f;
static const int   WIN_SCORE     = 7;
static const float MY_PI         = 3.14159265f;

// ---------------------------------------------------------------------------
// Enums
// ---------------------------------------------------------------------------
enum class GameScreen {
    MainMenu,
    DifficultySelect,
    Playing,
    Paused,
    GameOver
};

enum class Difficulty {
    Easy,
    Medium,
    Hard,
    Impossible
};

enum class GameMode {
    VsAI,
    VsPlayer
};

// ---------------------------------------------------------------------------
// Structs
// ---------------------------------------------------------------------------
struct Paddle {
    float x, y;
    float halfW, halfH;
    int   score;
};

struct Ball {
    float x, y;
    float vx, vy;
    float halfSize;
    float speed;
};

struct AIState {
    float reactionTimer;
    float targetY;
    float errorOffset;
    float speed;
    float reactionDelay;
    float maxError;
    bool  cheats;
};

// ---------------------------------------------------------------------------
// Game state
// ---------------------------------------------------------------------------
static Paddle     gP1, gP2;
static Ball       gBall;
static AIState    gAI;
static bool       gRunning       = true;
static GameScreen gScreen        = GameScreen::MainMenu;
static GameMode   gMode          = GameMode::VsAI;
static Difficulty gDifficulty    = Difficulty::Medium;
static int        gMenuSelection = 0;
static int        gDiffSelection = 1;
static std::string gWinnerText;
static float      gCountdown     = 0.0f;
static float      gScreenShake   = 0.0f;
static int        gServeDir      = 1;
static float      gBallTrailX[8], gBallTrailY[8];
static int        gTrailIdx      = 0;
static float      gMenuPulse     = 0.0f;

// Digit bitmaps (5x7)
static const uint8_t DIGITS[10][7] = {
    {0x1F,0x11,0x11,0x11,0x11,0x11,0x1F},
    {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E},
    {0x1F,0x01,0x01,0x1F,0x10,0x10,0x1F},
    {0x1F,0x01,0x01,0x1F,0x01,0x01,0x1F},
    {0x11,0x11,0x11,0x1F,0x01,0x01,0x01},
    {0x1F,0x10,0x10,0x1F,0x01,0x01,0x1F},
    {0x1F,0x10,0x10,0x1F,0x11,0x11,0x1F},
    {0x1F,0x01,0x01,0x01,0x01,0x01,0x01},
    {0x1F,0x11,0x11,0x1F,0x11,0x11,0x1F},
    {0x1F,0x11,0x11,0x1F,0x01,0x01,0x1F},
};

// Letter bitmaps (5x7) A-Z
static const uint8_t LETTERS[26][7] = {
    {0x0E,0x11,0x11,0x1F,0x11,0x11,0x11}, // A
    {0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E}, // B
    {0x0F,0x10,0x10,0x10,0x10,0x10,0x0F}, // C
    {0x1E,0x11,0x11,0x11,0x11,0x11,0x1E}, // D
    {0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F}, // E
    {0x1F,0x10,0x10,0x1E,0x10,0x10,0x10}, // F
    {0x0F,0x10,0x10,0x17,0x11,0x11,0x0F}, // G
    {0x11,0x11,0x11,0x1F,0x11,0x11,0x11}, // H
    {0x0E,0x04,0x04,0x04,0x04,0x04,0x0E}, // I
    {0x01,0x01,0x01,0x01,0x11,0x11,0x0E}, // J
    {0x11,0x12,0x14,0x18,0x14,0x12,0x11}, // K
    {0x10,0x10,0x10,0x10,0x10,0x10,0x1F}, // L
    {0x11,0x1B,0x15,0x11,0x11,0x11,0x11}, // M
    {0x11,0x19,0x15,0x13,0x11,0x11,0x11}, // N
    {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E}, // O
    {0x1E,0x11,0x11,0x1E,0x10,0x10,0x10}, // P
    {0x0E,0x11,0x11,0x11,0x15,0x12,0x0D}, // Q
    {0x1E,0x11,0x11,0x1E,0x14,0x12,0x11}, // R
    {0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E}, // S
    {0x1F,0x04,0x04,0x04,0x04,0x04,0x04}, // T
    {0x11,0x11,0x11,0x11,0x11,0x11,0x0E}, // U
    {0x11,0x11,0x11,0x11,0x0A,0x0A,0x04}, // V
    {0x11,0x11,0x11,0x15,0x15,0x1B,0x11}, // W
    {0x11,0x11,0x0A,0x04,0x0A,0x11,0x11}, // X
    {0x11,0x11,0x0A,0x04,0x04,0x04,0x04}, // Y
    {0x1F,0x01,0x02,0x04,0x08,0x10,0x1F}, // Z
};

static const uint8_t SYM_COLON[7]  = {0x00,0x04,0x00,0x00,0x04,0x00,0x00};
static const uint8_t SYM_DASH[7]   = {0x00,0x00,0x00,0x1F,0x00,0x00,0x00};
static const uint8_t SYM_EXCLAM[7] = {0x04,0x04,0x04,0x04,0x04,0x00,0x04};
static const uint8_t SYM_PERIOD[7] = {0x00,0x00,0x00,0x00,0x00,0x00,0x04};
static const uint8_t SYM_SLASH[7]  = {0x01,0x01,0x02,0x04,0x08,0x10,0x10};
static const uint8_t SYM_ARROW[7]  = {0x04,0x02,0x1F,0x02,0x04,0x00,0x00};

// ---------------------------------------------------------------------------
// Drawing primitives
// ---------------------------------------------------------------------------
static void DrawRect(float cx, float cy, float hw, float hh)
{
    glBegin(GL_QUADS);
        glVertex2f(cx - hw, cy - hh);
        glVertex2f(cx + hw, cy - hh);
        glVertex2f(cx + hw, cy + hh);
        glVertex2f(cx - hw, cy + hh);
    glEnd();
}

static void DrawGlyph(const uint8_t glyph[7], float originX, float originY, float ps)
{
    for (int row = 0; row < 7; ++row) {
        uint8_t bits = glyph[row];
        for (int col = 0; col < 5; ++col) {
            if (bits & (1 << (4 - col))) {
                float x = originX + col * ps + ps * 0.5f;
                float y = originY + row * ps + ps * 0.5f;
                DrawRect(x, y, ps * 0.5f, ps * 0.5f);
            }
        }
    }
}

static const uint8_t* GetCharGlyph(char c)
{
    if (c >= '0' && c <= '9') return DIGITS[c - '0'];
    if (c >= 'A' && c <= 'Z') return LETTERS[c - 'A'];
    if (c >= 'a' && c <= 'z') return LETTERS[c - 'a'];
    switch (c) {
        case ':': return SYM_COLON;
        case '-': return SYM_DASH;
        case '!': return SYM_EXCLAM;
        case '.': return SYM_PERIOD;
        case '/': return SYM_SLASH;
        case '>': return SYM_ARROW;
        default:  return nullptr;
    }
}

static float MeasureText(const char* text, float ps)
{
    float w = 0;
    for (const char* p = text; *p; ++p) {
        w += 5 * ps + ps;
    }
    if (w > 0) w -= ps;
    return w;
}

static void DrawText(const char* text, float centreX, float y, float ps)
{
    float totalW = MeasureText(text, ps);
    float x = centreX - totalW * 0.5f;
    for (const char* p = text; *p; ++p) {
        const uint8_t* glyph = GetCharGlyph(*p);
        if (glyph) {
            DrawGlyph(glyph, x, y, ps);
        }
        x += 5 * ps + ps;
    }
}

static void DrawScore(int score, float centreX, float topY, float pixelSize)
{
    char buf[4];
    snprintf(buf, sizeof(buf), "%d", score);
    DrawText(buf, centreX, topY, pixelSize);
}

// ---------------------------------------------------------------------------
// AI logic
// ---------------------------------------------------------------------------
static void ConfigureAI(Difficulty diff)
{
    switch (diff) {
        case Difficulty::Easy:
            gAI.speed          = 0.45f;
            gAI.reactionDelay  = 0.5f;
            gAI.maxError       = 60.0f;
            gAI.cheats         = false;
            break;
        case Difficulty::Medium:
            gAI.speed          = 0.7f;
            gAI.reactionDelay  = 0.2f;
            gAI.maxError       = 25.0f;
            gAI.cheats         = false;
            break;
        case Difficulty::Hard:
            gAI.speed          = 0.92f;
            gAI.reactionDelay  = 0.08f;
            gAI.maxError       = 8.0f;
            gAI.cheats         = false;
            break;
        case Difficulty::Impossible:
            gAI.speed          = 1.0f;
            gAI.reactionDelay  = 0.0f;
            gAI.maxError       = 0.0f;
            gAI.cheats         = true;
            break;
    }
    gAI.reactionTimer = 0.0f;
    gAI.targetY       = WINDOW_H / 2.0f;
    gAI.errorOffset   = 0.0f;
}

static float PredictBallY(float targetX)
{
    float bx = gBall.x, by = gBall.y;
    float bvx = gBall.vx;
    float bvy = gBall.vy;

    if (bvx <= 0) return WINDOW_H / 2.0f;

    float timeToReach = (targetX - bx) / bvx;
    float futureY = by + bvy * timeToReach;

    float fieldH = static_cast<float>(WINDOW_H);
    // Reflect off walls
    int bounces = 0;
    while ((futureY < 0 || futureY > fieldH) && bounces < 20) {
        if (futureY < 0) futureY = -futureY;
        if (futureY > fieldH) futureY = 2.0f * fieldH - futureY;
        ++bounces;
    }
    return std::max(0.0f, std::min(fieldH, futureY));
}

static void UpdateAI(float dt)
{
    gAI.reactionTimer -= dt;
    if (gAI.reactionTimer <= 0.0f) {
        gAI.reactionTimer = gAI.reactionDelay;

        if (gAI.cheats || gBall.vx > 0) {
            gAI.targetY = PredictBallY(gP2.x);
        } else {
            gAI.targetY = WINDOW_H / 2.0f;
        }
        gAI.errorOffset = ((float)(rand() % 1000) / 500.0f - 1.0f) * gAI.maxError;
    }

    float target = gAI.targetY + gAI.errorOffset;
    float diff = target - gP2.y;
    float aiSpeed = PADDLE_SPEED * gAI.speed;

    if (std::abs(diff) > 3.0f) {
        if (diff > 0) gP2.y += std::min(aiSpeed * dt, diff);
        else          gP2.y += std::max(-aiSpeed * dt, diff);
    }

    if (gP2.y - gP2.halfH < 0)        gP2.y = gP2.halfH;
    if (gP2.y + gP2.halfH > WINDOW_H) gP2.y = WINDOW_H - gP2.halfH;
}

// ---------------------------------------------------------------------------
// Game logic
// ---------------------------------------------------------------------------
static void ResetBall(int direction)
{
    gBall.x     = WINDOW_W / 2.0f;
    gBall.y     = WINDOW_H / 2.0f;
    gBall.speed = BALL_SPEED;
    gBall.vx    = 0;
    gBall.vy    = 0;
    gBall.halfSize = BALL_SIZE / 2.0f;
    gServeDir   = direction;
    gCountdown  = 1.5f;

    for (int i = 0; i < 8; ++i) {
        gBallTrailX[i] = gBall.x;
        gBallTrailY[i] = gBall.y;
    }
}

static void ServeBall()
{
    float angle = ((float)(rand() % 60) - 30.0f) * (MY_PI / 180.0f);
    gBall.vx = cosf(angle) * gBall.speed * gServeDir;
    gBall.vy = sinf(angle) * gBall.speed;
}

static void InitGame()
{
    gP1.halfW = PADDLE_W / 2.0f;  gP1.halfH = PADDLE_H / 2.0f;
    gP2.halfW = PADDLE_W / 2.0f;  gP2.halfH = PADDLE_H / 2.0f;

    gP1.x = PADDLE_MARGIN;
    gP2.x = WINDOW_W - PADDLE_MARGIN;
    gP1.y = gP2.y = WINDOW_H / 2.0f;
    gP1.score = gP2.score = 0;

    if (gMode == GameMode::VsAI) {
        ConfigureAI(gDifficulty);
    }
    ResetBall(1);
}

static bool AABBOverlap(float ax, float ay, float ahw, float ahh,
                         float bx, float by, float bhw, float bhh)
{
    return std::abs(ax - bx) < (ahw + bhw) &&
           std::abs(ay - by) < (ahh + bhh);
}

static void UpdatePlaying(float dt, const uint8_t* keys)
{
    // Countdown / serve
    if (gCountdown > 0.0f) {
        gCountdown -= dt;
        if (gCountdown <= 0.0f) {
            gCountdown = 0.0f;
            ServeBall();
        }
        return;
    }

    // Player 1
    if (keys[SDL_SCANCODE_W])  gP1.y -= PADDLE_SPEED * dt;
    if (keys[SDL_SCANCODE_S])  gP1.y += PADDLE_SPEED * dt;

    // Player 2 or AI
    if (gMode == GameMode::VsAI) {
        UpdateAI(dt);
    } else {
        if (keys[SDL_SCANCODE_UP])   gP2.y -= PADDLE_SPEED * dt;
        if (keys[SDL_SCANCODE_DOWN]) gP2.y += PADDLE_SPEED * dt;
    }

    // Clamp
    auto clampPaddle = [](Paddle& p) {
        if (p.y - p.halfH < 0)        p.y = p.halfH;
        if (p.y + p.halfH > WINDOW_H) p.y = WINDOW_H - p.halfH;
    };
    clampPaddle(gP1);
    clampPaddle(gP2);

    // Ball trail
    gTrailIdx = (gTrailIdx + 1) % 8;
    gBallTrailX[gTrailIdx] = gBall.x;
    gBallTrailY[gTrailIdx] = gBall.y;

    // Ball movement
    gBall.x += gBall.vx * dt;
    gBall.y += gBall.vy * dt;

    // Wall bounce
    if (gBall.y - gBall.halfSize < 0) {
        gBall.y  = gBall.halfSize;
        gBall.vy = std::abs(gBall.vy);
    }
    if (gBall.y + gBall.halfSize > WINDOW_H) {
        gBall.y  = WINDOW_H - gBall.halfSize;
        gBall.vy = -std::abs(gBall.vy);
    }

    // Paddle collisions
    auto paddleHit = [&](Paddle& p, int dir) {
        if (AABBOverlap(gBall.x, gBall.y, gBall.halfSize, gBall.halfSize,
                         p.x, p.y, p.halfW, p.halfH))
        {
            gBall.speed += BALL_ACCEL;
            float relY = (gBall.y - p.y) / p.halfH;
            float angle = relY * 60.0f * (MY_PI / 180.0f);
            gBall.vx = cosf(angle) * gBall.speed * dir;
            gBall.vy = sinf(angle) * gBall.speed;
            gBall.x = p.x + (p.halfW + gBall.halfSize + 1.0f) * dir;
            gScreenShake = 0.15f;
        }
    };
    paddleHit(gP1,  1);
    paddleHit(gP2, -1);

    // Scoring
    auto handleScore = [&](Paddle& scorer, int nextDir, const char* who) {
        ++scorer.score;
        if (scorer.score >= WIN_SCORE) {
            gWinnerText = who;
            gScreen = GameScreen::GameOver;
            star::Logger::GetInstance()->Log(star::LogLevel::Info,
                tstring(_T("Game over! ")) + _T(who) + _T(" wins!"),
                STARENGINE_LOG_TAG);
        } else {
            ResetBall(nextDir);
        }
    };

    if (gBall.x < -BALL_SIZE) {
        gScreenShake = 0.25f;
        const char* name = (gMode == GameMode::VsAI) ? "AI" : "PLAYER 2";
        handleScore(gP2, -1, name);
    }
    if (gBall.x > WINDOW_W + BALL_SIZE) {
        gScreenShake = 0.25f;
        handleScore(gP1, 1, "PLAYER 1");
    }
}

// ---------------------------------------------------------------------------
// Rendering
// ---------------------------------------------------------------------------
static void RenderField()
{
    glClearColor(0.04f, 0.04f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float shakeX = 0, shakeY = 0;
    if (gScreenShake > 0) {
        shakeX = ((rand() % 100) / 100.0f - 0.5f) * gScreenShake * 20.0f;
        shakeY = ((rand() % 100) / 100.0f - 0.5f) * gScreenShake * 20.0f;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_W, WINDOW_H, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(shakeX, shakeY, 0);

    // Centre line
    glColor3f(0.18f, 0.18f, 0.28f);
    for (float y = 0; y < WINDOW_H; y += 20.0f) {
        DrawRect(WINDOW_W / 2.0f, y + 5.0f, 1.5f, 5.0f);
    }

    // Scores
    glColor3f(0.35f, 0.35f, 0.50f);
    DrawScore(gP1.score, WINDOW_W * 0.25f, 20.0f, 6.0f);
    DrawScore(gP2.score, WINDOW_W * 0.75f, 20.0f, 6.0f);

    // Labels
    glColor3f(0.25f, 0.25f, 0.38f);
    if (gMode == GameMode::VsAI) {
        DrawText("YOU", WINDOW_W * 0.25f, 80.0f, 2.5f);
        DrawText("AI",  WINDOW_W * 0.75f, 80.0f, 2.5f);
    } else {
        DrawText("P1", WINDOW_W * 0.25f, 80.0f, 2.5f);
        DrawText("P2", WINDOW_W * 0.75f, 80.0f, 2.5f);
    }

    // Ball trail
    for (int i = 0; i < 8; ++i) {
        int idx = (gTrailIdx - i + 8) % 8;
        float alpha = (8 - i) / 24.0f;
        float size  = gBall.halfSize * (8 - i) / 10.0f;
        glColor4f(1.0f, 0.7f, 0.1f, alpha);
        DrawRect(gBallTrailX[idx], gBallTrailY[idx], size, size);
    }

    // Ball
    glColor3f(1.0f, 0.85f, 0.2f);
    DrawRect(gBall.x, gBall.y, gBall.halfSize, gBall.halfSize);

    // Ball glow
    glColor4f(1.0f, 0.85f, 0.2f, 0.08f);
    DrawRect(gBall.x, gBall.y, gBall.halfSize * 3, gBall.halfSize * 3);

    // Paddles  P1=blue  P2=red
    glColor3f(0.4f, 0.7f, 1.0f);
    DrawRect(gP1.x, gP1.y, gP1.halfW, gP1.halfH);
    glColor4f(0.4f, 0.7f, 1.0f, 0.06f);
    DrawRect(gP1.x, gP1.y, gP1.halfW * 3, gP1.halfH + 5);

    glColor3f(1.0f, 0.45f, 0.4f);
    DrawRect(gP2.x, gP2.y, gP2.halfW, gP2.halfH);
    glColor4f(1.0f, 0.45f, 0.4f, 0.06f);
    DrawRect(gP2.x, gP2.y, gP2.halfW * 3, gP2.halfH + 5);

    // Countdown
    if (gCountdown > 0.0f) {
        int num = (int)ceilf(gCountdown);
        if (num < 1) num = 1;
        if (num > 3) num = 3;
        float scale = 1.0f + (gCountdown - floorf(gCountdown)) * 0.5f;
        glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
        char buf[2] = { (char)('0' + num), 0 };
        DrawText(buf, WINDOW_W / 2.0f, WINDOW_H / 2.0f - 30.0f * scale, 8.0f * scale);
    }
}

static void RenderPauseOverlay()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    DrawRect(WINDOW_W / 2.0f, WINDOW_H / 2.0f, WINDOW_W / 2.0f, WINDOW_H / 2.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    DrawText("PAUSED", WINDOW_W / 2.0f, WINDOW_H / 2.0f - 40.0f, 5.0f);

    glColor3f(0.6f, 0.6f, 0.7f);
    DrawText("PRESS SPACE TO RESUME", WINDOW_W / 2.0f, WINDOW_H / 2.0f + 20.0f, 2.5f);
    DrawText("PRESS ESCAPE FOR MENU", WINDOW_W / 2.0f, WINDOW_H / 2.0f + 50.0f, 2.5f);
}

static void RenderMainMenu()
{
    glClearColor(0.03f, 0.03f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_W, WINDOW_H, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Decorative dashed lines
    float shift = fmodf(gMenuPulse * 30.0f, 20.0f);
    glColor3f(0.12f, 0.12f, 0.22f);
    for (float y = -20.0f + shift; y < WINDOW_H + 20; y += 20.0f) {
        DrawRect(60.0f, y, 1.5f, 5.0f);
        DrawRect(WINDOW_W - 60.0f, y, 1.5f, 5.0f);
    }

    // Title
    float titlePulse = 1.0f + sinf(gMenuPulse * 2.0f) * 0.03f;
    glColor3f(1.0f, 0.85f, 0.2f);
    DrawText("STAR PONG", WINDOW_W / 2.0f, 80.0f, 7.0f * titlePulse);

    // Subtitle
    glColor3f(0.4f, 0.4f, 0.55f);
    DrawText("POWERED BY STARENGINE", WINDOW_W / 2.0f, 150.0f, 2.0f);

    // Menu items
    const char* items[] = { "1 PLAYER VS AI", "2 PLAYERS", "QUIT" };
    const int itemCount = 3;
    float startY = 250.0f;
    float gap = 55.0f;

    for (int i = 0; i < itemCount; ++i) {
        float y = startY + i * gap;
        bool selected = (i == gMenuSelection);

        if (selected) {
            glColor4f(1.0f, 0.85f, 0.2f, 0.08f);
            DrawRect(WINDOW_W / 2.0f, y + 14.0f, 180.0f, 20.0f);

            glColor3f(1.0f, 0.85f, 0.2f);
            DrawText(">", WINDOW_W / 2.0f - 150.0f, y, 4.0f);

            glColor3f(1.0f, 0.95f, 0.7f);
        } else {
            glColor3f(0.5f, 0.5f, 0.6f);
        }
        DrawText(items[i], WINDOW_W / 2.0f, y, 3.5f);
    }

    // Hint
    glColor3f(0.3f, 0.3f, 0.42f);
    DrawText("UP/DOWN TO SELECT   ENTER TO CONFIRM", WINDOW_W / 2.0f, 520.0f, 2.0f);
}

static void RenderDifficultyMenu()
{
    glClearColor(0.03f, 0.03f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_W, WINDOW_H, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.7f, 0.7f, 0.85f);
    DrawText("SELECT DIFFICULTY", WINDOW_W / 2.0f, 80.0f, 5.0f);

    const char* items[] = { "EASY", "MEDIUM", "HARD", "IMPOSSIBLE" };
    const char* descs[] = {
        "SLOW AI   LOTS OF MISTAKES",
        "BALANCED   FAIR CHALLENGE",
        "FAST AI   VERY PRECISE",
        "PERFECT   NO MERCY"
    };
    float colors[][3] = {
        {0.3f, 0.9f, 0.3f},
        {0.9f, 0.8f, 0.2f},
        {1.0f, 0.4f, 0.2f},
        {1.0f, 0.15f, 0.15f},
    };
    const int itemCount = 4;
    float startY = 180.0f;
    float gap = 75.0f;

    for (int i = 0; i < itemCount; ++i) {
        float y = startY + i * gap;
        bool selected = (i == gDiffSelection);

        if (selected) {
            glColor4f(colors[i][0], colors[i][1], colors[i][2], 0.08f);
            DrawRect(WINDOW_W / 2.0f, y + 18.0f, 200.0f, 28.0f);

            glColor3f(colors[i][0], colors[i][1], colors[i][2]);
            DrawText(">", WINDOW_W / 2.0f - 130.0f, y, 4.0f);
            DrawText(items[i], WINDOW_W / 2.0f, y, 4.0f);

            glColor3f(colors[i][0] * 0.6f, colors[i][1] * 0.6f, colors[i][2] * 0.6f);
            DrawText(descs[i], WINDOW_W / 2.0f, y + 35.0f, 2.0f);
        } else {
            glColor3f(0.4f, 0.4f, 0.5f);
            DrawText(items[i], WINDOW_W / 2.0f, y, 3.5f);
        }
    }

    glColor3f(0.3f, 0.3f, 0.42f);
    DrawText("ENTER TO START   ESCAPE TO GO BACK", WINDOW_W / 2.0f, 520.0f, 2.0f);
}

static void RenderGameOver()
{
    RenderField();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    DrawRect(WINDOW_W / 2.0f, WINDOW_H / 2.0f, WINDOW_W / 2.0f, WINDOW_H / 2.0f);

    glColor3f(1.0f, 0.85f, 0.2f);
    DrawText(gWinnerText.c_str(), WINDOW_W / 2.0f, WINDOW_H / 2.0f - 60.0f, 5.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    DrawText("WINS!", WINDOW_W / 2.0f, WINDOW_H / 2.0f, 5.0f);

    glColor3f(0.6f, 0.6f, 0.7f);
    char scoreBuf[32];
    snprintf(scoreBuf, sizeof(scoreBuf), "%d - %d", gP1.score, gP2.score);
    DrawText(scoreBuf, WINDOW_W / 2.0f, WINDOW_H / 2.0f + 55.0f, 4.0f);

    glColor3f(0.5f, 0.5f, 0.65f);
    DrawText("ENTER TO PLAY AGAIN", WINDOW_W / 2.0f, WINDOW_H / 2.0f + 120.0f, 2.5f);
    DrawText("ESCAPE FOR MENU",     WINDOW_W / 2.0f, WINDOW_H / 2.0f + 150.0f, 2.5f);
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------
int main(int /*argc*/, char* /*argv*/[])
{
    srand(static_cast<unsigned>(time(nullptr)));

    star::Logger::GetInstance()->Initialize();
    star::Logger::GetInstance()->Log(star::LogLevel::Info,
        _T("Star Pong starting"), STARENGINE_LOG_TAG);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* window = SDL_CreateWindow(
        "Star Pong",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_W, WINDOW_H,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glCtx = SDL_GL_CreateContext(window);
    if (!glCtx) {
        fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_GL_SetSwapInterval(1);

    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK) {
        fprintf(stderr, "glewInit failed: %s\n", glewGetErrorString(glewErr));
        SDL_GL_DeleteContext(glCtx);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    star::Logger::GetInstance()->Log(star::LogLevel::Info,
        _T("OpenGL context created"), STARENGINE_LOG_TAG);

    star::TimeManager* timeMgr = star::TimeManager::GetInstance();

    while (gRunning) {
        timeMgr->StartMonitoring();

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                gRunning = false;
            }
            if (ev.type == SDL_KEYDOWN && !ev.key.repeat) {
                SDL_Scancode sc = ev.key.keysym.scancode;

                switch (gScreen) {
                case GameScreen::MainMenu:
                    if (sc == SDL_SCANCODE_UP || sc == SDL_SCANCODE_W)
                        gMenuSelection = (gMenuSelection + 2) % 3;
                    if (sc == SDL_SCANCODE_DOWN || sc == SDL_SCANCODE_S)
                        gMenuSelection = (gMenuSelection + 1) % 3;
                    if (sc == SDL_SCANCODE_RETURN || sc == SDL_SCANCODE_SPACE) {
                        if (gMenuSelection == 0) {
                            gMode = GameMode::VsAI;
                            gScreen = GameScreen::DifficultySelect;
                        } else if (gMenuSelection == 1) {
                            gMode = GameMode::VsPlayer;
                            InitGame();
                            gScreen = GameScreen::Playing;
                        } else {
                            gRunning = false;
                        }
                    }
                    if (sc == SDL_SCANCODE_ESCAPE) gRunning = false;
                    break;

                case GameScreen::DifficultySelect:
                    if (sc == SDL_SCANCODE_UP || sc == SDL_SCANCODE_W)
                        gDiffSelection = (gDiffSelection + 3) % 4;
                    if (sc == SDL_SCANCODE_DOWN || sc == SDL_SCANCODE_S)
                        gDiffSelection = (gDiffSelection + 1) % 4;
                    if (sc == SDL_SCANCODE_RETURN || sc == SDL_SCANCODE_SPACE) {
                        gDifficulty = static_cast<Difficulty>(gDiffSelection);
                        InitGame();
                        gScreen = GameScreen::Playing;
                        star::Logger::GetInstance()->Log(star::LogLevel::Info,
                            _T("Starting game vs AI"), STARENGINE_LOG_TAG);
                    }
                    if (sc == SDL_SCANCODE_ESCAPE) gScreen = GameScreen::MainMenu;
                    break;

                case GameScreen::Playing:
                    if (sc == SDL_SCANCODE_SPACE)  gScreen = GameScreen::Paused;
                    if (sc == SDL_SCANCODE_ESCAPE) gScreen = GameScreen::MainMenu;
                    break;

                case GameScreen::Paused:
                    if (sc == SDL_SCANCODE_SPACE)  gScreen = GameScreen::Playing;
                    if (sc == SDL_SCANCODE_ESCAPE) gScreen = GameScreen::MainMenu;
                    break;

                case GameScreen::GameOver:
                    if (sc == SDL_SCANCODE_RETURN || sc == SDL_SCANCODE_SPACE) {
                        InitGame();
                        gScreen = GameScreen::Playing;
                    }
                    if (sc == SDL_SCANCODE_ESCAPE) gScreen = GameScreen::MainMenu;
                    break;
                }
            }
        }

        const uint8_t* keys = SDL_GetKeyboardState(nullptr);
        float dt = static_cast<float>(timeMgr->DeltaTime().GetSeconds());
        if (dt > 0.05f) dt = 0.05f;

        gMenuPulse += dt;
        if (gScreenShake > 0) {
            gScreenShake -= dt * 2.0f;
            if (gScreenShake < 0) gScreenShake = 0;
        }

        switch (gScreen) {
        case GameScreen::MainMenu:
            RenderMainMenu();
            break;
        case GameScreen::DifficultySelect:
            RenderDifficultyMenu();
            break;
        case GameScreen::Playing:
            UpdatePlaying(dt, keys);
            RenderField();
            break;
        case GameScreen::Paused:
            RenderField();
            RenderPauseOverlay();
            break;
        case GameScreen::GameOver:
            RenderGameOver();
            break;
        }

        SDL_GL_SwapWindow(window);
        timeMgr->StopMonitoring();
    }

    star::Logger::GetInstance()->Log(star::LogLevel::Info,
        _T("Star Pong shutting down"), STARENGINE_LOG_TAG);

    star::TimeManager::DeleteSingleton();
    star::Logger::DeleteSingleton();

    SDL_GL_DeleteContext(glCtx);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
