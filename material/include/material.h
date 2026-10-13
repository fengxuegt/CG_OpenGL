//
// Created by fengxuegt on 2026/10/12.
//

#ifndef MATERIAL_H
#define MATERIAL_H

enum class MaterialType {
    PhongMaterial,
    WhiteMaterial,
};

class Material {
public:
  Material();
  virtual ~Material();
 public:
    MaterialType mType;
};



#endif //MATERIAL_H
