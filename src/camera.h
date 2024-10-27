#ifndef CAMERA_H
#define CAMERA_H
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

class CameraTransform
{
public:
    CameraTransform(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(glm::vec3(0.0f)));
    ~CameraTransform();

    // void SetRotation(glm::vec3 rotation) { m_Rotation = glm::quat(rotation); }

    void SetRotation(glm::vec3 rotation)
    {
        glm::quat y = glm::angleAxis(rotation.y, glm::vec3(0, 1, 0));
        glm::quat x = glm::angleAxis(rotation.x, glm::vec3(1, 0, 0));
        glm::quat z = glm::angleAxis(rotation.z, glm::vec3(0, 0, 1));
        m_Rotation = z * x * y;
        m_Rotation = glm::normalize(m_Rotation);
    }

    glm::vec3 GetPosition() { return m_Position; }

    void Update();
    glm::mat4 GetViewMatrix();
private:
    glm::mat4 m_ViewMatrix;
    glm::quat m_Rotation;
    glm::vec3 m_Position;
};

#endif