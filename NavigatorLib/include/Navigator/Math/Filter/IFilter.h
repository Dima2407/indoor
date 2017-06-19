//
// Created by  Oleksiy Grechnyev on 3/10/2017.
//

#pragma once

#include <cmath>

namespace Navigator {
    namespace Math {
        namespace Filter {

            /** @brief Filter interface
             *
             * @startuml
             * interface IFilter{
             * ..
             * + {abstract} process(in: Value) : Value
             * ..
             * + reset() : void
             * ..
             * + operator() (in: Value) : Value -> process()
             * --
             * + ~IFilter()
             * }
             * note bottom
             * // Filter functional interface. //
             * // operator() is an alias to process() //
             * // The data is Value  //
             * // The pair is (RSSI, timestamp) //
             * end note
             * @enduml
             */
            class IFilter {
            public:

                /// Data type too be filtered, similar to Pair but with everything allowed
                struct Value {
                    Value(double val, double timeStamp) : val(val), timeStamp(timeStamp) {}

                    Value() {}

                    bool operator== (const Value & rhs) const {
                        return val == rhs.val && timeStamp == rhs.timeStamp;
                    }

                    bool operator!= (const Value & rhs) const {
                        return val != rhs.val || timeStamp != rhs.timeStamp;
                    }

                    double val = std::nan("");
                    double timeStamp  = std::nan("");
                };

                //------------------------------------
                // Public abstract method: must implement
                //------------------------------------

                /// Run a value through the filter
                virtual Value process(Value in) = 0;

                //------------------------------------
                // Public methods: default and optional
                //------------------------------------

                /// Reset the filter and forget all history, optional
                virtual void reset() {}

                /// Alias to process() by default
                /// Do not override - forbidden
                Value operator()(Value in) {
                    return process(in);
                }

                /// Virtual Destructor
                virtual ~IFilter() {}
            };
        }
    }
}
