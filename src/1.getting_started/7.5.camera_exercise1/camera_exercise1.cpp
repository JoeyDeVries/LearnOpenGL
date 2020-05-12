// This function is found in the camera class. What we basically do is keep the y position value at 0.0f to force our
// user to stick to the ground.

[...]
// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    // make sure the user stays at the ground level
    Position.y = 0.0f; // <-- this one-liner keeps the user at the ground level (xz plane)
}
[...]