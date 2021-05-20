/**
 * \file       GLBuffer.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Abstraction for OpenGL buffer
 *
*/

#pragma once

#include <vector>

#include "pgr.h"
#include "../Types.h"

namespace vpr {

template<typename T> class GLBuffer {
    public:

        GLBuffer(std::vector<T>, std::size_t ,GLenum);
        GLBuffer(std::vector<T> data, std::size_t size) : GLBuffer(data,size,GL_ARRAY_BUFFER) {};
        ~GLBuffer();
        std::size_t getSize();
        GLuint getVBO();
        void bind();


    private:
        GLenum type;
        std::size_t size;
        std::size_t unitSize;
        T* data;
        
        GLuint vbo = 0;
        
};


template<typename T>
GLBuffer<T>::GLBuffer(std::vector<T> data, std::size_t unitSize, GLenum type) {
    this->size = data.size() * sizeof(T);
    this->unitSize = unitSize;
    this->type = type;
    this->data = &data[0];

    GLuint vbo = 0;
    glGenBuffers(1,&vbo);
    this->vbo = vbo;
    glBindBuffer(type, this->vbo);
    glBufferData(type, this->size, &data[0],GL_STATIC_DRAW);
    glBindBuffer(type, 0);
    CHECK_GL_ERROR();
    
}

template<typename T>
GLBuffer<T>::~GLBuffer() {

}

template<typename T>
std::size_t GLBuffer<T>::getSize() {
    return this->size;
}

template<typename T>
GLuint GLBuffer<T>::getVBO() {
    return this->vbo;
}

template<typename T>
void GLBuffer<T>::bind() {
    glBindBuffer(this->type, this->vbo);
}


}