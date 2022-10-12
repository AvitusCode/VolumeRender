#pragma once
#include "math/vec3.h"
#include <utility>

namespace jd
{
	using type = float;

	struct Voxel
	{
		//@Data
		size_t iLayer; // index of the layer
		type sDepth;   // length of the layer 

		Voxel() noexcept : iLayer(0), sDepth(0) {}
		explicit Voxel(size_t index, type depth) noexcept : iLayer(index), sDepth(depth){}
		
		Voxel(const Voxel& cell) noexcept {
			*this = cell;
		}

		Voxel(Voxel&& cell) noexcept {
			*this = std::move(cell);
		}

		Voxel& operator=(const Voxel& cell) noexcept {
			iLayer = cell.iLayer;
			sDepth = cell.sDepth;
			
			return *this;
		}

		Voxel& operator=(Voxel&& cell) noexcept {
			if (&cell == this) {
				return *this;
			}

			iLayer = cell.iLayer;
			sDepth = cell.sDepth;
			cell.iLayer = 0;
			cell.sDepth = 0;

			return *this;
		}
		
	};

}
