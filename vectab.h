#ifndef VECTAB_H
#define VECTAB_H

#define VECTAB_SET(name, value) void *const (name) __attribute__((section("."#name))) = (void *)(value)

#endif
