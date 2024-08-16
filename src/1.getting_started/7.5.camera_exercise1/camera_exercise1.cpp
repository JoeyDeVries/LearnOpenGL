// This function is found in the camera class. What we basically do is keep the y position value at 0.0f to force our
// user to stick to the ground.

[...]
// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    // Make sure the user stays at the ground level by setting the y axis to 0
    // The x and z axis should not include pitch as you will only move horizontally
    glm::vec3 forward = glm::vec3(cos(glm::radians(Yaw)), 0.0f, sin(glm::radians(Yaw)));

    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += forward * velocity;     // Add the forward vector to position
    if (direction == BACKWARD)
        Position -= forward * velocity;     // Subtract the forward vector from position
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}
[...]