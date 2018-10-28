#pragma once

namespace hs
{

	class NonCopyable
	{
	protected:
		// Define explicit default constructor since
		// we have a copy constructor defined, even 
		// though it is private
		NonCopyable() {} 

		// Prevents possible resoure leaks as a
		// private destructor prevents a call
		// to delete on a NonCopyable pointer
		~NonCopyable() {}

	private:
		// Disable copy constructor
		NonCopyable(const NonCopyable&) = delete;

		// Disable the assignment operator
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

}