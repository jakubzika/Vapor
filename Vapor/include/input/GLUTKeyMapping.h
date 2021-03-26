#pragma once

#include <map>

#include "pgr.h"
#include "../Types.h"

namespace vpr {

static std::map<char, KeyEnum> GLUTCharKeyMapping = {
    {'a',VPR_KEY_A},
    {'b',VPR_KEY_B},
    {'c',VPR_KEY_C},
    {'d',VPR_KEY_D},
    {'e',VPR_KEY_E},
    {'f',VPR_KEY_F},
    {'g',VPR_KEY_G},
    {'h',VPR_KEY_H},
    {'i',VPR_KEY_I},
    {'j',VPR_KEY_J},
    {'k',VPR_KEY_K},
    {'l',VPR_KEY_L},
    {'m',VPR_KEY_M},
    {'n',VPR_KEY_N},
    {'o',VPR_KEY_O},
    {'p',VPR_KEY_P},
    {'q',VPR_KEY_Q},
    {'r',VPR_KEY_R},
    {'s',VPR_KEY_S},
    {'t',VPR_KEY_T},
    {'u',VPR_KEY_U},
    {'v',VPR_KEY_V},
    {'w',VPR_KEY_W},
    {'x',VPR_KEY_X},
    {'y',VPR_KEY_Y},
    {'z',VPR_KEY_Z},
    {' ',VPR_KEY_SPACE},
    {'\x1b',VPR_KEY_ESC},
    {'0',VPR_KEY_0},
    {'1',VPR_KEY_1},
    {'2',VPR_KEY_2},
    {'3',VPR_KEY_3},
    {'4',VPR_KEY_4},
    {'5',VPR_KEY_5},
    {'6',VPR_KEY_6},
    {'7',VPR_KEY_7},
    {'8',VPR_KEY_8},
    {'9',VPR_KEY_9},
};

static std::map<int, KeyEnum> GLUTSpecialKeyMapping = {
    {GLUT_KEY_F1, VPR_KEY_F1},
    {GLUT_KEY_F2, VPR_KEY_F2},
    {GLUT_KEY_F3, VPR_KEY_F3},
    {GLUT_KEY_F4, VPR_KEY_F4},
    {GLUT_KEY_F5, VPR_KEY_F5},
    {GLUT_KEY_F6, VPR_KEY_F6},
    {GLUT_KEY_F7, VPR_KEY_F7},
    {GLUT_KEY_F8, VPR_KEY_F8},
    {GLUT_KEY_F9, VPR_KEY_F9},
    {GLUT_KEY_F10, VPR_KEY_F10},
    {GLUT_KEY_F11, VPR_KEY_F11},
    {GLUT_KEY_F12, VPR_KEY_F12},
    {GLUT_KEY_LEFT, VPR_KEY_LEFT},
    {GLUT_KEY_UP, VPR_KEY_UP},
    {GLUT_KEY_RIGHT, VPR_KEY_RIGHT},
    {GLUT_KEY_DOWN, VPR_KEY_DOWN},
    {GLUT_KEY_PAGE_UP, VPR_KEY_PAGE_UP},
    {GLUT_KEY_PAGE_DOWN, VPR_KEY_PAGE_DOWN},
    {GLUT_KEY_HOME, VPR_KEY_HOME},
    {GLUT_KEY_END, VPR_KEY_END},
    {GLUT_KEY_INSERT, VPR_KEY_INSERT}  
};

KeyEnum charToKey(char key);
KeyEnum specialToKey(int key);

}