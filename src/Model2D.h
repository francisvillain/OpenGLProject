#pragma once
#include <string>
#include <vector>

struct Model2DSource
{
	std::vector<float> positions;
	std::vector<unsigned int> indices;
};


class Model2D{
	private:
		std::string m_FilePath;
		Model2DSource ParseModel2D(const std::string& filepath);
		Model2DSource m;

	public:
		Model2D(const std::string& filepath);
		~Model2D();
		int GetIndicesSize();
		int GetPositionsSize();
		float* GetPositions();
		unsigned int* GetIndices();
		
};