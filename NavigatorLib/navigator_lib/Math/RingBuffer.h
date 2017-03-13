//
// Created by  Oleksiy Grechnyev on 2/24/2017.
//

#pragma once

#include <cassert>

namespace Navi {
    namespace filter {

/** \brief A very simple Ring Buffer implementation
 *
 * @tparam T       Element type
 *
 * @startuml
 * class RingBuffer<T> {
 * // A very simple Ring Buffer implementation //
 * //  //
 * // This version is NOT synchronized, NOT thread-safe //
 * // It uses a dynamic array (new+delete), nothing fancy //
 * //  //
 * //  Note: It operates elements by value and uses assignments //
 * //  If you want to keep refs instead, try  T = shared_ptr<someclass> //
 * --
 * - size : unsigned
 * - data : T*
 * - readIndex : unsigned
 * - writeIndex : unsigned
 * - empty : bool
 * --
 * + RingBuffer(size: unsigned)
 * + ~RingBuffer()
 * ..
 * + const isFull() : bool
 * + const isEmpty() : bool
 * + push(t : T) : bool
 * + forcePush(t : T) : void
 * + pop(t : T &) : bool
 * + clear() : void
 * ..
 * - next(i : unsigned &) : void
 * }
 * @enduml
 *
 *
 */
        template<class T>
        class RingBuffer {
            //------------------------------------
            // Public methods
            //------------------------------------

        public:

            /// Constructor
            RingBuffer(unsigned size) : size(size)
            {
                assert(size > 0);

                // The good old dynamic array
                data = new T[size];
            }

            /// Destructor
            ~RingBuffer()
            {
                delete[] data;
            }

            /// Is the buffer full?
            bool isFull() const
            {
                return (readIndex == writeIndex) && !empty;
            }

            /// Is the buffer empty?
            bool isEmpty() const
            {
                return empty;
            }

            /** \brief Push an element unsignedo the buffer
             *
             * @param[in]    t    element
             * @return            true is success, false if full buffer
             */
            bool push(T t)
            {
                // Check if full
                if (isFull())
                    return false;


                data[writeIndex] = t; // Write data
                next(writeIndex); // Increment write index by 1
                empty = false; // Clear the empty flag after write

                return true;
            }

            /** @brief Push an element, overriding old data if the buffer is full
             *
             * Note: No, this is not a Jedi Power
             *
             * @param[in]   t    element
             */
            void forcePush(T t)
            {
                // If full, get rid of a single old data
                if (isFull())
                    next(readIndex);

                data[writeIndex] = t; // Write data
                next(writeIndex); // Increment write index by 1
                empty = false; // Clear the empty flag after write
            }

            /** \brief Pop an element from the list
             *
             * @param[out] t  element
             * @return        true if success, false if empty buffer
             */
            bool pop(T &t)
            {
                // Check if empty
                if (empty)
                    return false;

                t = data[readIndex]; // Read data
                next(readIndex);  // Increment read index by 1

                empty = (readIndex == writeIndex); // Set the empty flag if empty

                return true;

            }

            /// Clear the buffer
            void clear()
            {
                // No need to do anything with the array, of course
                readIndex = writeIndex;
                empty = true;
            }

       //------------------------------------
       // Private methods
       //------------------------------------

        private:
            /// Disable copy constructor
            RingBuffer(const RingBuffer<T> &other) = delete;

            /// Disable assignment
            RingBuffer &operator=(const RingBuffer<T> &) = delete;

            /// Increment i by 1, wrapping around size
            void next(unsigned &i)
            {
                i++;
                i %= size;
            }

            //------------------------------------
            // Private fields
            //------------------------------------

            /// Buffer (maximal) size = size of the array data[]
            unsigned size;

            /// The data as a dynamic array of size size
            T *data;

            // Note: readIndex == writeIndex means either empty or full buffer

            /// Next position to read from
            unsigned readIndex = 0;

            /// Next Position to write to
            unsigned writeIndex = 0;

            /// Is the buffer empty ? (to distinguish between the empty and full cases)
            bool empty = true;
        };

    }
}
