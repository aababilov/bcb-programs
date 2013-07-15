#ifndef MSGROUTINES_H
#define MSGROUTINES_H

#include <Forms.hpp>

static inline void show_error(const char *s)
{
        Application->MessageBox(s, "Error", MB_OK|MB_ICONERROR);
}
static inline void show_info(const char* s)
{
        Application->MessageBox(s, "Information", MB_OK|MB_ICONINFORMATION);
}
static inline void show_info(String s)
{
        show_info(s.c_str());
}
static inline void show_error(String s)
{
        show_error(s.c_str());
}
#endif