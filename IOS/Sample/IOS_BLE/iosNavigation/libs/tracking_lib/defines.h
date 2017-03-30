//
// Created by grey_wolf on 27.07.16.
//

#ifndef INDORNAVIIGATION_DEFINES_H
#define INDORNAVIIGATION_DEFINES_H

#if defined(DEBUG_MODE)
#   if defined(ASTUDIO)
#       include <android/log.h>
#       define LOGV(TAG,...) __android_log_print(ANDROID_LOG_VERBOSE, TAG,__VA_ARGS__)
#       define LOGD(TAG,...) __android_log_print(ANDROID_LOG_DEBUG  , TAG,__VA_ARGS__)
#       define LOGI(TAG,...) __android_log_print(ANDROID_LOG_INFO   , TAG,__VA_ARGS__)
#       define LOGW(TAG,...) __android_log_print(ANDROID_LOG_WARN   , TAG,__VA_ARGS__)
#       define LOGE(TAG,...) __android_log_print(ANDROID_LOG_ERROR  , TAG,__VA_ARGS__)
#   else
#       include <cstdio>
#       define LOGV(TAG,...) fprintf(stderr, __VA_ARGS__)
#       define LOGD(TAG,...) fprintf(stderr, __VA_ARGS__)
#       define LOGI(TAG,...) fprintf(stderr, __VA_ARGS__)
#       define LOGW(TAG,...) fprintf(stderr, __VA_ARGS__)
#       define LOGE(TAG,...) fprintf(stderr, __VA_ARGS__)
#   endif
#else
#   define LOGV(TAG,...) {}
#   define LOGD(TAG,...) {}
#   define LOGI(TAG,...) {}
#   define LOGW(TAG,...) {}
#   define LOGE(TAG,...) {}
#endif

#endif //INDORNAVIIGATION_DEFINES_H
