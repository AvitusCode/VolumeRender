#pragma once
#include "Mat2D.h"

namespace jd
{

	/*
	Interface of 3D Matrix
	*/

	template<typename Node>
	class Mat3D
	{
	public:
		Mat3D(const Mat3D&) = delete;
		Mat3D(size_t depth, size_t xdim = 1, size_t ydim = 1);

		void Reset(size_t zdim, size_t xdim, size_t ydim); // Make simple .assign();
		Node& At(size_t zdim, size_t xdim, size_t ydim);
		Node At(size_t zdim, size_t xdim, size_t ydim) const;
		const std::vector<std::vector<Node>>& GetSlice(size_t zdim) const; // make slice of the data
		size_t GetNumDepth() const;
		size_t GetNumRows() const;
		size_t GetNumColumns() const;
		Mat3D clone() const;

	private:
		Mat3D() : xSize(0), ySize(0), zSize(0) {};

		size_t xSize;
		size_t ySize;
		size_t zSize;

		std::vector<std::vector<std::vector<Node>>> volume_;
	};


	/*
	
	REALIZATION
	
	*/

	template<typename Node>
	Mat3D<Node>::Mat3D(size_t zdim, size_t xdim, size_t ydim) {
		Reset(zdim, xdim, ydim);
	}

	template<typename Node>
	void Mat3D<Node>::Reset(size_t zdim, size_t xdim, size_t ydim)
	{
		if (zdim == 0 || xdim == 0 || ydim == 0) {
			// Обработать
		}

		xSize = xdim;
		ySize = ydim;
		zSize = zdim;

		volume_.assign(zdim, std::vector<std::vector<Node>>(xdim, std::vector<Node>(ydim, Node{})));
	}

	template<typename Node>
	const std::vector<std::vector<Node>>& Mat3D<Node>::GetSlice(size_t zdim) const
	{
		if (zdim >= zSize) {
			// do something
		}

		return volume_.at(zdim);
	}

	template<typename Node>
	Node& Mat3D<Node>::At(size_t zdim, size_t xdim, size_t ydim)
	{
		if (zdim >= zSize) {
			// do something
		}

		return volume_[zdim][xdim][ydim];
	}

	template<typename Node>
	Node Mat3D<Node>::At(size_t zdim, size_t xdim, size_t ydim) const
	{
		if (zdim >= zSize) {
			// do something
		}

		return volume_[zdim][xdim][ydim];
	}

	template<typename Node>
	size_t Mat3D<Node>::GetNumDepth() const {
		return zSize;
	}

	template<typename Node>
	size_t Mat3D<Node>::GetNumRows() const {
		return xSize;
	}

	template<typename Node>
	size_t Mat3D<Node>::GetNumColumns() const {
		return ySize;
	}

	template<typename Node>
	Mat3D<Node> Mat3D<Node>::clone() const
	{
		Mat3D<Node> result;
		result.Reset(zSize, xSize, ySize);

		for (size_t i = 0; i < xSize; i++) {
			for (size_t j = 0; j < ySize; j++) {
				for (size_t k = 0; k < zSize; k++) {
					result.volume_[i][j][k] = volume_[i][j][k];
				}
			}
		}

		return result;
	}
}