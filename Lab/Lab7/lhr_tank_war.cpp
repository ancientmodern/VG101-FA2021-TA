#include "lab7.h"
#include <algorithm>
#include <deque>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * You only need to upload this file to our OJ.
 */


struct TankSprite {
    Vector2<> pos;
    Direction direction{};
    int life = 5;
    int cd = 0;
};

struct BulletSprite {
    Vector2<> pos;
    Direction direction{};
    Tank owner;
};

class MyGame : public Game {
    // Create Your Data Structure Here
public:
    vector<Move> oppMoves;
    int contMove = -1;
    TankSprite TankA, TankB;
    vector<BulletSprite> bullets;
    int border = 0, round = 0;

    void initialize(int A_X, int A_Y, int B_X, int B_Y, Direction A_direction, Direction B_direction) override {
        // Initialize Your Game Here
        TankA.pos = Vector2<>(A_X, A_Y);
        TankA.direction = A_direction;
        TankB.pos = Vector2<>(B_X, B_Y);
        TankB.direction = B_direction;
    }

    void move(Tank tank, Move move) override {
        // Record A Move And Update Your Game
        TankSprite &activeTank = (tank == Tank_A) ? TankA : TankB;
        if (tank == Tank_B) {
            oppMoves.emplace_back(move);
        }
        // 1. Turn
        switch (move) {
            case M_Left:
                activeTank.direction = Direction((activeTank.direction + 3) % 4);
                break;
            case M_Right:
                activeTank.direction = Direction((activeTank.direction + 1) % 4);
                break;
            case M_Forward:
                break;
        }
        // 2. Move
        Vector2<> dirVec;
        switch (activeTank.direction) {
            case D_Left:
                dirVec = Vector2<>(-1, 0);
                break;
            case D_Up:
                dirVec = Vector2<>(0, -1);
                break;
            case D_Right:
                dirVec = Vector2<>(1, 0);
                break;
            case D_Down:
                dirVec = Vector2<>(0, 1);
                break;
        }
        activeTank.pos += dirVec;
        // 3. Shoot
        if (activeTank.cd == 0) {
            BulletSprite bullet{activeTank.pos + dirVec, activeTank.direction, tank};
            bullets.push_back(bullet);
            activeTank.cd = 2;
        } else activeTank.cd--;
    }

    Turn turn() override {
        // Make Your Turn Here
        // 0. Tank Crash
        if (TankA.pos == TankB.pos) {
            if (TankA.life > TankB.life) return T_A_Win;
            else if (TankB.life > TankA.life) return T_B_Win;
            return T_Draw;
        }

        round++;
        border = round / 16;

        // 1. Move Bullets
        for (auto it = bullets.begin(); it < bullets.end(); it++) {
            bool deleteBullet = false;
            auto &bullet = *it;
            Vector2<> dirVec;
            switch (bullet.direction) {
                case D_Left:
                    dirVec = Vector2<>(-1, 0);
                    break;
                case D_Up:
                    dirVec = Vector2<>(0, -1);
                    break;
                case D_Right:
                    dirVec = Vector2<>(1, 0);
                    break;
                case D_Down:
                    dirVec = Vector2<>(0, 1);
                    break;
            }

            if (bullet.pos == TankA.pos) {
                TankA.life -= 2;
                deleteBullet = true;
            }

            if (bullet.pos == TankB.pos) {
                TankB.life -= 2;
                deleteBullet = true;
            }

            bullet.pos += dirVec;

            if (bullet.pos == TankA.pos) {
                TankA.life -= 2;
                deleteBullet = true;
            }

            if (bullet.pos == TankB.pos) {
                TankB.life -= 2;
                deleteBullet = true;
            }

            bullet.pos += dirVec;

            if (bullet.pos == TankA.pos) {
                TankA.life -= 2;
                deleteBullet = true;
            }

            if (bullet.pos == TankB.pos) {
                TankB.life -= 2;
                deleteBullet = true;
            }

            if (bullet.pos.x < border - 5 || bullet.pos.y < border - 5 || bullet.pos.x >= MAP_SIZE - border + 5 ||
                bullet.pos.y >= MAP_SIZE - border + 5) {
                deleteBullet = true;
            }

            if (deleteBullet) {
                bullets.erase(it);
                it--;
            }
        }

        // 2. Out of Boundary
        if (TankA.pos.x < border || TankA.pos.y < border || TankA.pos.x >= MAP_SIZE - border ||
            TankA.pos.y >= MAP_SIZE - border)
            TankA.life--;
        if (TankB.pos.x < border || TankB.pos.y < border || TankB.pos.x >= MAP_SIZE - border ||
            TankB.pos.y >= MAP_SIZE - border)
            TankB.life--;

        // 3. Win or Lose
        if (TankA.life <= 0 && TankB.life <= 0) return T_Draw;
        if (TankA.life <= 0) return T_B_Win;
        if (TankB.life <= 0) return T_A_Win;

        return T_Cont;
    }

    string draw() const override {
        ostringstream result;
        for (int y = -5; y < MAP_SIZE + 5; y++) {
            for (int x = -5; x < MAP_SIZE + 5; x++) {
                char cur = ' ';
                Vector2<int> curPos(x, y);
                if (x < border || y < border || x >= MAP_SIZE - border || y >= MAP_SIZE - border) cur = '-';
                if (TankA.pos == curPos) cur = 'A';
                if (TankB.pos == curPos) cur = 'B';
                for (auto &bullet: bullets) {
                    if (bullet.pos == curPos) {
                        cur = '*';
                        break;
                    }
                }
                result << cur << "|";
            }
            result << "\n";
        }
        result << "\nA: " << TankA.life << ", B: " << TankB.life << endl;
        return result.str();
    }

    Map getMap() const override {
        Map map{};
        for (int y = -5; y < MAP_SIZE + 5; y++) {
            for (int x = -5; x < MAP_SIZE + 5; x++) {
                if (TankA.pos.x == x && TankA.pos.y == y) map.block[y + 5][x + 5] = B_Tank_A;
                else if (TankB.pos.x == x && TankB.pos.y == y) map.block[y + 5][x + 5] = B_Tank_B;
                else {
                    bool hasBullet = false;
                    for (auto &i: bullets) {
                        if (i.pos.x == x && i.pos.y == y) {
                            map.block[y + 5][x + 5] = B_Bullet;
                            hasBullet = true;
                            break;
                        }
                    }
                    if (!hasBullet) map.block[y + 5][x + 5] = B_Blank;
                }
            }
        }
        map.border = border;

        return map;
    }

    /**
     * Add a bullet to the battlefield
     * @param pos
     * @param direction
     */
    void addBullet(const Vector2<> &pos, Direction direction) override {
        bullets.push_back({pos, direction});
    }

    /**
     * Set the border to certain value, notice that it will not reset the shrink time
     * @param border
     */
    void setBorder(int _border) override {
        border = _border;
        round = round % 16 + border * 16;
    }

    const TankSprite &getTankA() const {
        return TankA;
    }

    const TankSprite &getTankB() const {
        return TankB;
    }

    const vector<BulletSprite> &getBullets() const {
        return bullets;
    }

    int getBorder() const {
        return border;
    }

    int getNextBorder() const {
        return (round + 1) / 16;
    }

    int getNextBorder(int then) const {
        return (round + then) % 16;
    }

    int judgeBack(Vector2<> posA, Vector2<> posB, Direction dirA, Direction dirB) {
        if (dirA == dirB) {
            switch (dirA) {
                case D_Up:
                    return posA.x == posB.x && posA.y < posB.y;
                case D_Down:
                    return posA.x == posB.x && posA.y > posB.y;
                case D_Left:
                    return posA.y == posB.y && posA.x > posB.x;
                case D_Right:
                    return posA.y == posB.y && posA.x < posB.x;
            }
        }
        return 0;
    }

    int judgeBorder() {
        int nb = getNextBorder();
        return TankA.pos.x < nb || TankA.pos.y < nb || TankA.pos.x >= MAP_SIZE - nb ||
               TankA.pos.y >= MAP_SIZE - nb;
    }

    double evaluation() {
        // double dist_tank = abs(TankA.pos.x - TankB.pos.x) + abs(TankA.pos.y - TankB.pos.y);
        double lifePoint = TankA.life - TankB.life;
        double attack = 0, defense = 0;
        for (auto &bullet: bullets) {
            if (bullet.owner == Tank_A) {
                attack += 40.0 / (abs(bullet.pos.x - TankB.pos.x) + abs(bullet.pos.y - TankB.pos.y) + 1);
                // attack = max(attack, 600.0 / (abs(bullet.pos.x - TankB.pos.x) + abs(bullet.pos.y - TankB.pos.y)));
            } else {
                defense += 40.0 / (abs(bullet.pos.x - TankA.pos.x) + abs(bullet.pos.y - TankA.pos.y) + 1);
                // defense = max(defense, 600.0 / (abs(bullet.pos.x - TankA.pos.x) + abs(bullet.pos.y - TankA.pos.y)));
            }
        }
//        double mid = abs(TankA.pos.x - 9.5) + abs(TankA.pos.y - 9.5);
//        return 250 * lifePoint + attack - defense - 39 * outBorder * border - mid * 3 * border +
//               400 * judgeBack(TankA.pos, TankB.pos, TankA.direction, TankB.direction) -
//               300 * judgeBack(TankB.pos, TankA.pos, TankB.direction, TankA.direction);
        double dist = (lifePoint > 0) * 100 / (abs(TankA.pos.x - TankB.pos.x) + abs(TankA.pos.y - TankB.pos.y));
        return lifePoint * 200 + attack - defense + dist - 100 * judgeBorder()
               + 40 * judgeBack(TankA.pos, TankB.pos, TankA.direction, TankB.direction)
               - 40 * judgeBack(TankB.pos, TankA.pos, TankB.direction, TankA.direction);
    }
};

class MyBrain : public Brain {
    // Create Your Status Variables Here
    const MyGame *game = nullptr;

public:
    void initialize() override {
        // Initialize Your AI here
        game = dynamic_cast<MyGame *>(getMyGame());
        cerr << "Test AI of LHR 0.4.1, alpha-beta + depth = 8" << endl;
    }

    pair<double, int> max_value(MyGame &state, int depth, double alpha, double beta) {
        double v = -100000;
        int index = -1;
        MyGame bak = state;
        for (int i = 0; i < 3; ++i) {
            state.move(Tank_A, static_cast<Move>(i));
            double temp;
            if (state.judgeBorder() > 0) {
                temp = -99999 + depth;
            } else {
                temp = minimax(state, false, depth + 1, alpha, beta).first;
            }
            if (temp > v) {
                v = temp;
                index = i;
            }
            if (depth == 0) {
                cerr << i << " " << temp << endl;
            }
            if (v >= beta) {
                return make_pair(v, index);
            }
            alpha = max(alpha, v);
            state = bak;
        }
        return make_pair(v, index);
    }

    pair<double, int> min_value(MyGame &state, int depth, double alpha, double beta) {
        double v = 100000;
        int index = -1;
        MyGame bak = state;
        for (int i = 0; i < 3; ++i) {
            state.move(Tank_B, static_cast<Move>(i));
            double temp;
            Turn res = state.turn();
            if (res == T_B_Win) {
                temp = -50000;
            } else if (res == T_Draw) {
                temp = -100;
            } else if (res == T_A_Win) {
                temp = 50000;
            } else {
                temp = minimax(state, true, depth + 1, alpha, beta).first;
            }
            if (temp < v) {
                v = temp;
                index = i;
            }
            if (v <= alpha) {
                return make_pair(v, i);
            }
            beta = min(beta, v);
            state = bak;
        }
        return make_pair(v, index);
    }

    // 0 normal, 1 win/draw, 2 lose
    pair<double, int> minimax(MyGame &state, bool isMax, int depth, double alpha, double beta) {
        if (depth == 8) {
            return make_pair(state.evaluation(), -1);
        }
        if (isMax) {
            return max_value(state, depth, alpha, beta);
        } else {
            return min_value(state, depth, alpha, beta);
        }
    }

    Move judge() override {
        // Move Your Move Here
        cerr << "lifepoints: " << game->TankA.life << " " << game->TankB.life << endl;
        MyGame curr = *game;
        auto result = minimax(curr, true, 0, -100000, 100000);
        return static_cast<Move>(result.second);
    }
};

static MyGame game;
static MyBrain brain;

Game *getMyGame() {
    return &game;
}

Brain *getMyBrain() {
    return &brain;
}