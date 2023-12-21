//
// Created by vlad on 29.11.2023.
//

#ifndef OPENGL_PRAKTIKUM_HOUSE_H
#define OPENGL_PRAKTIKUM_HOUSE_H
//// For the House in the first Lab
float vertices[] = {-0.5, -0.5, 0.0, 0.0, 1.0,
                    0.5,  -0.5, 0.0, 0.0, 1.0,
                    0.5,   0.5, 0.0, 1.0, 0.0,
                    0.0,   1.0, 1.0, 0.0, 0.0,
                    -0.5,  0.5, 0.0, 1.0, 0.0};

int indices[] = {0, 1, 2,
                 0, 2, 4,
                 4, 2, 3};
#endif //OPENGL_PRAKTIKUM_HOUSE_H
