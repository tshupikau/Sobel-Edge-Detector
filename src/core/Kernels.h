#pragma once
namespace Kernels
{
	inline constexpr std::array<int, 9> Gx = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};
	inline constexpr std::array<int, 9> Gy = {
		 1,  2,  1,
		 0,  0,  0,
		-1, -2, -1
	};
}