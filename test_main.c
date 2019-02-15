#include "API.h"

#ifdef _WIN32
  #include "Windows.h"

  typedef HMODULE ModuleInstance;

  #define MODULE_EXTENSION ".dll"

  static inline ModuleInstance ModuleInstance_load (char const* path) {
    ModuleInstance module = LoadLibraryA(path);

    m_assert(module != NULL, "Failed to load Module at path '%s'", path);

    return module;
  }

  static inline void ModuleInstance_unload (ModuleInstance module) {
    m_assert(FreeLibrary(module) != 0, "Failed to unload Module");
  }

  static inline void* ModuleInstance_get_address (ModuleInstance module, char const* name) {
    return GetProcAddress(module, name);
  }
#else
  #include "dlfcn.h"

  typedef void* ModuleInstance;

  #define MODULE_EXTENSION ".so"

  static inline ModuleInstance ModuleInstance_load (char const* path) {
    void* module = dlopen(path, RTLD_LAZY);

    m_assert(module != NULL, "Failed to load Module at path '%s'", path);

    return module;
  }

  static inline void ModuleInstance_unload (ModuleInstance module) {
    m_assert(dlclose(module) == 0, "Failed to unload Module");
  }

  static inline void* ModuleInstance_get_address (ModuleInstance module, char const* name) {
    return dlsym(module, name);
  }
#endif

API int version_number = 1;

API int test_internal (int a) {
  return a * 1000;
}

int main (int argc, char** args) {
  ModuleInstance module = ModuleInstance_load("./test_dll" MODULE_EXTENSION);

  int (*test_external) (int) = ModuleInstance_get_address(module, "test_external");

  m_assert(test_external != NULL, "Failed to get external function");

  int* test_global = ModuleInstance_get_address(module, "test_global");

  m_assert(test_global != NULL, "Failed to get external global");

  *test_global = 5;

  int result = test_external(32);

  printf("Test result: %d\n", result);

  m_assert(result == 37000, "Incorrect result");

  ModuleInstance_unload(module);

  return 0;
}