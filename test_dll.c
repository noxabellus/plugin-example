#define MODULE
#include "API.h"

#include <stdio.h>


API int version_number;

API int test_internal (int);

DLL int test_global = 4;

DLL int test_external (int v) {
  if (version_number != 1) printf("Warning: This plugin is only tested for version 1");
  return test_internal(v + test_global);
}