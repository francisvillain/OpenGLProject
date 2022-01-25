#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Model2D.h"

Model2D::Model2D(const std::string& filepath) : m_FilePath(filepath)
{
    m = ParseModel2D(filepath);
}

Model2D::~Model2D()
{

}

int Model2D::GetIndicesSize()
{
    return m.indices.size();
}

int Model2D::GetPositionsSize()
{
    return m.positions.size();
}

float* Model2D::GetPositions()
{
    return m.positions.data();
}

unsigned int* Model2D::GetIndices()
{
    return m.indices.data();
}



Model2DSource Model2D::ParseModel2D(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class Model2DType
    {
        NONE = -1, POSITIONS = 0, INDICES = 1
    };

    std::string line;
    Model2DType type = Model2DType::NONE;
    std::vector<float> v1;
    std::vector<unsigned int> v2;

    while (getline(stream, line))
    {
        if (line.find("#model") != std::string::npos)
        {
            if (line.find("positions") != std::string::npos)
                type = Model2DType::POSITIONS;
            else if (line.find("indices") != std::string::npos)
                type = Model2DType::INDICES;
        }
        else
        {   
            if (type == Model2DType::POSITIONS)
            {
                v1.push_back(std::stof(line));
            }
            else if (type == Model2DType::INDICES)
               v2.push_back(std::stoul(line));
         }
        }

    return { v1, v2 };
}