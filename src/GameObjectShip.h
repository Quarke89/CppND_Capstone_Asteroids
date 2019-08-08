#pragma once

#include "GameObject.h"
#include <vector>

enum class ShipMovement
{
    MOVE_FORWARD,
    MOVE_BACKWARD,
    ROTATE_LEFT,
    ROTATE_RIGHT
};

class GameObjectShip : public GameObject
{
    public:

        GameObjectShip(const Point& pos, const CTexture& tex, CVector velocity);

        void update(const Uint32 updateTime) override;
        void render(SDL_Renderer& renderer) override;

        void setRotateLeft(bool val);
        void setRotateRight(bool val);
        void setMoveForward(bool val);
        void setMoveBackward(bool val);

        SDL_Rect& getBoundingBox();

    private:

        int _width;
        int _height;
        SDL_Rect _boundingBox;
        bool _rotateLeft;
        bool _rotateRight;
        bool _moveForward;
        bool _moveBackward;
};