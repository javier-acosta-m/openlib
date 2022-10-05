/**
 * MIT License
 * Copyright (c) 2022 Javier I. Acosta M.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef OPENLIB_SINGLETON_H
#define OPENLIB_SINGLETON_H

//-Namespace/s
namespace openlib
{

	/**
	 * Singleton template class (not thread safe)
	 * Usage: class Test: public Singleton<Test>
	 * {
	 * 	void method()
	 * ...
	 * }
	 * call instance --> Test().instance().method()
	 * @tparam T The singleton class to implement
	 */
	template < typename T >
	class Singleton 
	{
		public:
			static T& instance() 
			{
				static SingletonCleanupGuard mem_guard;
				if (NULL == m_instance) {
					m_instance = new T(); 
				}
				return *m_instance;
			}

		protected:
			//-Hide constructor & destructor
			Singleton(): m_instance(NULL) { }
			virtual ~Singleton() { }

		private:
			//-Fields
			static T* m_instance;

			//-Hide operators
			Singleton(const Singleton&);
			Singleton& operator= (const Singleton);
			
			/**
			 * Class to cleanup the instance when exiting the program
			 */
			class SingletonCleanupGuard 
			{
				public: 
					SingletonCleanupGuard(){} 
					~SingletonCleanupGuard() 
					{
						delete m_instance;
						m_instance = NULL;
					}
			}; /*class SingletonCleanupGuard */
	}; /*class Singleton*/
}; /*namespace openlib*/

#endif /*OPENLIB_SINGLETON_H*/
