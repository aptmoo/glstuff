#include "camera.h"

CameraTransform::CameraTransform(glm::vec3 position, glm::quat rotation)
    : m_Position(position), m_Rotation(rotation), m_ViewMatrix(glm::mat4(1.0f))
{
    this->Update();
}
CameraTransform::~CameraTransform()
{}

void CameraTransform::Update()
{
    m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position);
    m_ViewMatrix = glm::mat4_cast(m_Rotation) * m_ViewMatrix;
}

glm::mat4 CameraTransform::GetViewMatrix()
{
    return m_ViewMatrix;
}