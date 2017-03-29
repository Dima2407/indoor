//
// Created by  Oleksiy Grechnyev on 3/10/2017.
//

#pragma once

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
             * // The data is pair<double,double> //
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

                    double val, timeStamp;
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