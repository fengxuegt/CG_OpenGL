//
// Created by fengxuegt on 2026/10/12.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <vector>

#include "basecore.h"

enum class ObjectType {
    Object,
    Mesh,
    Scene
};

class Object {
public:
    Object();
    virtual ~Object();

    void SetPosition(glm::vec3 pos);
    void SetScale(glm::vec3 scale);
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);

    void addChild(Object * child);
    glm::mat4 GetModelMatrix();
public:
    ObjectType mType;

public:
    Object* mParent{nullptr};
    std::vector<Object*> mChildren{};

public:
    glm::vec3 mPosition{0.0f, 0.0f, 0.0f};
    float mAngleX{0.0f};
    float mAngleY{0.0f};
    float mAngleZ{0.0f};
    glm::vec3 mScale{1.0f, 1.0f, 1.0f};

};



#endif //OBJECT_H
