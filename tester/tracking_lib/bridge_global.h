#ifndef BRIDGE_GLOBAL_H
#define BRIDGE_GLOBAL_H

#  ifdef _WIN32
#    define DECL_EXPORT     __declspec(dllexport)
#    define DECL_IMPORT     __declspec(dllimport)
#    define DECL_HIDDEN     __declspec(dllimport)
#  elif defined(VISIBILITY_AVAILABLE)
#    define DECL_EXPORT     __attribute__((visibility("default")))
#    define DECL_IMPORT     __attribute__((visibility("default")))
#    define DECL_HIDDEN     __attribute__((visibility("hidden")))
#  else
#    define DECL_EXPORT
#    define DECL_IMPORT
#    define DECL_HIDDEN
#  endif

#  define DECL_DEPRECATED __attribute__ ((__deprecated__))

#  ifdef BRIDGE_LIBRARY
#    define BRIDGE_LIBRARY_EXPORT DECL_EXPORT
#  else
#    define BRIDGE_LIBRARY_EXPORT DECL_IMPORT
#  endif

#  define BRIDGE_LIBRARY_HIDDEN DECL_HIDDEN

#endif // BRIDGE_GLOBAL_H
