//
// Created by fengxuegt on 2026/10/12.
//

#include "object.h"

Object::Object() {
    mType = ObjectType::Object;
}

Object::~Object() {
}

void Object::SetPosition(glm::vec3 pos) {
    mPosition = pos;
}

void Object::SetScale(glm::vec3 scale) {
    mScale = scale;
}

void Object::RotateX(float angle) {
    mAngleX += angle;
}

void Object::RotateY(float angle) {
    mAngleY += angle;
}

void Object::RotateZ(float angle) {
    mAngleZ += angle;
}

void Object::addChild(Object *child) {
    child->mParent = this;
    auto it = std::find(mChildren.begin(), mChildren.end(), child);
    if (it == mChildren.end()) {
        mChildren.push_back(child);
    }
}

glm::mat4 Object::GetModelMatrix() {
    glm::mat4 model = glm::mat4(1.0f);
    // rotate
    model = glm::rotate(model, glm::radians(mAngleZ), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(mAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(mAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    // scale
    model = glm::scale(model, mScale);
    // transform
    glm::mat4 transfom = glm::mat4(1.0f);
    transfom = glm::translate(transfom, mPosition);
    if (mParent != nullptr) {
        return mParent->GetModelMatrix() * transfom * model;
    }
    return transfom * model;
}

