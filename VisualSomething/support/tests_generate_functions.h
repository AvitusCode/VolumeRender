#pragma once
#include "../Voxel.h"
#include "../Mat3D.h"
#include "../math/vec4.h"

/*
 * 
 * Здесь можно писать собственные функции для генерации слоев
 * 
 * */

std::vector<jd::vec4> generateData_DIAG(jd::Mat3D<jd::Voxel>& data, float len);
std::vector<jd::vec4> generateData_PARAL(jd::Mat3D<jd::Voxel>& data, float len);
