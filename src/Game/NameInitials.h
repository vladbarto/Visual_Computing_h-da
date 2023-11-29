//
// Created by vlad on 29.11.2023.
//

#ifndef OPENGL_PRAKTIKUM_NAMEINITIALS_H
#define OPENGL_PRAKTIKUM_NAMEINITIALS_H
//// For Name Initials
        float vertices[] = {
                // V
                -0.6, 0.5, 0.0, 1.0, 0.0,
                -0.5, -0.5, 0.0, 0.0, 1.0,
                -0.4, 0.5, 1.0, 0.0, 0.0,

                // B
                -0.3, 0.5, 1.0, 0.0, 0.0,
                -0.3, 0.0, 0.0, 1.0, 0.0,
                -0.1, 0.25, 0.0, 1.0, 0.0,
                -0.3, -0.5, 0.0, 0.0, 1.0,
                -0.1, -0.25, 0.0, 1.0, 0.0,
        };

        int indices[] = {
                // V
                0, 1, 2,

                // B
                3, 4, 5,
                4, 6, 7,
        };
#endif //OPENGL_PRAKTIKUM_NAMEINITIALS_H
