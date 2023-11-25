#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
    class MyCamera
    {
     public:
        MyCamera()
        {
            position    = glm::vec3(0, 2, 5);
            forward     = glm::vec3(0, 0, -1);
            up          = glm::vec3(0, 1, 0);
            right       = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

        MyCamera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            Set(position, center, up);
        }

        ~MyCamera()
        { }

        // Update MyCamera
        void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            this->position = position;
            forward     = glm::normalize(center - position);
            right       = glm::cross(forward, up);
            this->up    = glm::cross(right, forward);
        }

        void MoveForward(float distance)
        {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void MoveUpward(float distance)
        {
			position += glm::normalize(up) * distance;
		}

        void MoveRight(float distance)
        {
			position += glm::normalize(glm::cross(up, forward)) * distance;
		}

        void TranslateForward(float distance)
        {
            position += glm::normalize(forward) * distance;
        }

        void TranslateUpward(float distance)
        {
            position += glm::normalize(up) * distance;
        }

        void TranslateRight(float distance)
        {
            position += glm::normalize(glm::cross(up, forward)) * distance;
        }

        void RotateFirstPerson_OX(float angle)
        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::rotate(modelMatrix, angle, right);

            forward = glm::vec3(glm::normalize(modelMatrix * glm::vec4(forward, 1)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OY(float angle)
        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));

            forward = glm::vec3(glm::normalize(modelMatrix * glm::vec4(forward, 1)));
            right = glm::vec3(glm::normalize(modelMatrix * glm::vec4(right, 1)));
			up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OZ(float angle)
        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::rotate(modelMatrix, angle, forward);

            right = glm::vec3(glm::normalize(modelMatrix * glm::vec4(right, 1)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateThirdPerson_OX(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OX(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OY(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OY(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OZ(float angle)
        {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OZ(angle);
            TranslateForward(-distanceToTarget);
        }

        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

        glm::vec3 GetPosition()
        {
			return position;
		}

        glm::vec3 GetForward()
        {
            return forward;
        }

        glm::vec3 GetRight()
        {
			return right;
		}

        glm::vec3 GetUp()
        {
            return up;
        }

     public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}   // namespace implemented
