//
//  MIT License
//
// Copyright(c) 2011-2020 The Maintainers of Nanvix
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef CACHE_H_
#define CACHE_H_

	/**
	 *  @brief Cache
	 */
	class Cache
	{
		protected:

			/**
			 * @brief Size of Cache Memory (in bytes)
			 */
			unsigned size_;

			/**
			 * @brief Underlying Data
			 */
			unsigned *data;

		public:

			/**
			 * @brief Default constructor.
			 *
			 * @param size Size of cache memory (in bytes).
			 */
			Cache(unsigned size);

			/**
			 * @brief Default destructor.
			 */
			~Cache();

			/**
			 * @brief Reads a word from the target memory.
			 *
			 * @param addr Target address.
			 *
			 * @returns The requested word.
			 *
			 * @todo Use custom types.
			 */
			unsigned read(unsigned addr);
	};

	/**
	 *  @brief Instruction Cache
	 */
	class ICache : Cache
	{
		public:

			/**
			 * @brief Default constructor.
			 *
			 * @param size Size of cache memory (in bytes).
			 */
			ICache(unsigned size) : Cache(size) {}
	};

	/**
	 *  @brief Data Cache
	 */
	class DCache : Cache
	{
		public:

			/**
			 * @brief Default constructor.
			 *
			 * @param size Size of cache memory (in bytes).
			 */
			DCache(unsigned size) : Cache(size) {}

			/**
			 * @brief Writes a word to the target memory.
			 *
			 * @param addr Target address.
			 * @param word Word.
			 *
			 * @todo Use custom types.
			 */
			void write(unsigned addr, unsigned word);
	};

#endif // CACHE_H_