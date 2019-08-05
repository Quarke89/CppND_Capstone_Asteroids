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

class ShipObject : public GameObject
{
    public:

        ShipObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration, Uint32 updateTime);

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer* renderer);

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
        double _directionAngle;
};