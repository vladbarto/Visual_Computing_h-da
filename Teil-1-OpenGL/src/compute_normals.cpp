//
// Created by vlad on 09.12.23.
//
#include <iostream>
#include <cmath>

static const float cubeVert[] = {0.5, -0.5, -0.5, 1, 0, 0,
                                 0.5, -0.5, 0.5, 0, 1, 0,
                                 -0.5, -0.5, 0.5, 0, 0, 1,
                                 -0.5, -0.5, -0.5, 1, 1, 0,
                                 0.5, 0.5, -0.5, 1, 0, 1,
                                 0.5, 0.5, 0.5, 0, 1, 1,
                                 -0.5, 0.5, 0.5, 1, 1, 1,
                                 -0.5, 0.5, -0.5, 0.5, 1, 0.5};

void computeNormals(const float* vertices, float* normals) {
    for (int i = 0; i < 8; ++i) {
        // i iterates over vertices
        float x = vertices[i * 6];
        float y = vertices[i * 6 + 1];
        float z = vertices[i * 6 + 2];

        float normal_x = 0.0f;
        float normal_y = 0.0f;
        float normal_z = 0.0f;

        for (int j = 0; j < 6; j += 3) {
            // j iterates over each element of current vertex: x, y, z, r, g, b
            float neighbor_x = vertices[(i + j / 3) * 6];
            float neighbor_y = vertices[(i + j / 3) * 6 + 1];
            float neighbor_z = vertices[(i + j / 3) * 6 + 2];

            // normals for each axis are calculated
            normal_x += (y - neighbor_y) * (z + neighbor_z);
            normal_y += (z - neighbor_z) * (x + neighbor_x);
            normal_z += (x - neighbor_x) * (y + neighbor_y);
        }

        // sqrt(normal_x ** 2 + normal_y ** 2 + normal_z ** 2)
        float length = std::sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);
        // if length it's 0 => we make it = 1 so that when we divide with it, we don't get a NaN
        length = (length == 0.0f) ? 1.0f : length;

        normals[i * 9] = x;
        normals[i * 9 + 1] = y;
        normals[i * 9 + 2] = z;

        normals[i * 9 + 3] = normal_x / length;
        normals[i * 9 + 4] = normal_y / length;
        normals[i * 9 + 5] = normal_z / length;

        normals[i * 9 + 6] = vertices[i * 6 + 3];
        normals[i * 9 + 7] = vertices[i * 6 + 4];
        normals[i * 9 + 8] = vertices[i * 6 + 5];
    }
}

int main_compute() {
    const int vertexCount = 8;
    const int elementsPerVertex = 9; // x, y, z, normal_x, normal_y, normal_z, r, g, b

    float normals[vertexCount * elementsPerVertex];

    computeNormals(cubeVert, normals);

    // Print the result
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < elementsPerVertex; ++j) {
            std::cout << normals[i * elementsPerVertex + j] << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}

