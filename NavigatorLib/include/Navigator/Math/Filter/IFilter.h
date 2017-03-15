//
// Created by  Oleksiy Grechnyev on 3/10/2017.
//

#pragma once

namespace Navi {
    namespace Math {
        namespace Filter {

            /** @brief Filter interface
             *
             * @startuml
             * interface IFilter{
             * ..
             * + {abstract} process(in: double) : double
             * ..
             * + reset() : void
             * ..
             * + operator() (in: double) : double -> process()
             * --
             * + ~IFilter()
             * }
             * note bottom
             * // Filter functional interface. //
             * // operator() is an alias to process() //
             * end note
             * @enduml
             */
            class IFilter {
            public:
                //------------------------------------
                // Public abstract method: must implement
                //------------------------------------

                /// Run a double value through the filter
                virtual double process(double in) = 0;

                //------------------------------------
                // Public methods: default and optional
                //------------------------------------

                /// Reset the filter and forget all history, optional
                virtual void reset() {}

                /// Alias to process() by default
                /// Do not override - forbidden
                double operator()(double in) {
                    return process(in);
                }

                /// Virtual Destructor
                virtual ~IFilter() {}
            };
        }
    }
}