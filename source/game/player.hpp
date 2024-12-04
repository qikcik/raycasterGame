#pragma once

class Player
{
    public:
        Vec2f pos {};
        float turnDirection {};
        float walkDirection {};
        float rotationAngle {PI/2};
        float moveSpeed     {5};
        float rotationSpeed {(PI)};
};