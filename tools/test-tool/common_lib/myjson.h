/** \file myjson.h
 * \brief Some useful utils for rapidjson
 * Created by  Oleksiy Grechnyev on 2/7/2017.
 *
 */

#ifndef TESTTOOL_MYJSON_H
#define TESTTOOL_MYJSON_H

#include <rapidjson/document.h>

#include <string>

#include "Vec3.h"

namespace tester{
    namespace myjson {

        /** \brief  Read a Vec3 property named 'name' if the rapidjson object v
         *
         * @param[in]  obj         A rapidJSON object
         * @param[in]  name        Name of property
         * @param[out] vec3        Result
         * @return                 True if successful
         */
        bool readVec3(rapidjson::Value const & obj, const char * name, Vec3 & vec3);

        /** \brief  Read a double property named 'name' if the rapidjson object v
         *
         * @param[in]    obj    A rapidJSON object
         * @param[in]    name   Name of property
         * @param[out]   d      Result
         * @return              True if successful
         */
        bool readDouble(rapidjson::Value const & obj, const char * name, double & d);


        /** \brief  Read a long long property named 'name' if the rapidjson object v
         *
         * @param[in]    obj    A rapidJSON object
         * @param[in]    name   Name of property
         * @param[out]   ll     Result
         * @return              True if successful
         */
        bool readLL(rapidjson::Value const & obj, const char * name, long long & ll);

        /** \brief  Read an intproperty named 'name' if the rapidjson object v
         *
         * @param[in]    obj    A rapidJSON object
         * @param[in]    name   Name of property
         * @param[out]   i      Result
         * @return              True if successful
         */
        bool readInt(rapidjson::Value const & obj, const char * name, int & i);

        /** \brief  Read a strig property named 'name' if the rapidjson object v
         *
         * @param[in]    obj    A rapidJSON object
         * @param[in]    name   Name of property
         * @param[out]   str    Result
         * @return              True if successful
         */
        bool readString(rapidjson::Value const & obj, const char * name, std::string & ll);

    }
}

#endif //TESTTOOL_MYJSON_H
