#pragma once
#include <assert.h>

//--------------------------------------------------------------------------------------------------------
//								Custom Container Class: Dynamic Array									//
//																										//
//		 CONTENTS:																						//
//																										//
//		 CONSTRUCTORS & DESTRUCTORS																		//
//		 | Modified Constructor					(DA_CD1)		(unsigned int a_capacity = 10)			//
//		 | Destructor							(DA_CD2)		()										//
//																										//
//		 OPERATORS																						//
//		 | T&					operator []		(DA_O1)			(unsigned int position)					//
//																										//
//		 FUNCTIONS																						//
//		 | void					reserve			(DA_F1)			(unsigned int a_capacity = 10)			//
//		 | void					clear			(DA_F2)			()										//
//		 | void					erase_at		(DA_F3)			(unsigned int position)					//
//		 | void					add_at			(DA_F4)			(unsigned int position, T item)			//
//		 | void					push_back		(DA_F5)			(T a_item)								//
//		 | void					pop_back		(DA_F6)			() 										//
//		 | unsigned int			size			(DA_F7)			()										//
//		 | bool					empty			(DA_F8)			()										//
//		 | T&					front			(DA_F9)			()										//
//		 | T&					back			(DA_F10)		()										//
//		 | iterator				begin			(DA_F11)		()										//
//		 | const_iterator		begin			(DA_F12)		()										//
//		 | iterator				end				(DA_F13)		()										//
//		 | const_iterator		end				(DA_F14)		()										//
//																										//
//		 VARIABLES								(DA_V)													//
//		 | unsigned int			m_size																	//
//		 | unsigned int			m_contents																//
//		 | T*					m_data																	//
//--------------------------------------------------------------------------------------------------------


template <typename T>


class DynamicArray
{
public:


	typedef T* iterator;
	typedef const T* const_iterator;

	DynamicArray(unsigned int a_capacity = 10)							//(DA_CD1)
	{
		m_capacity = 0;
		m_size = 0;
		reserve(a_capacity);
	}

	~DynamicArray()													//(DA_CD2)
	{
		if (m_size > 0)
			delete[] m_data;
	}


	//--------------------------------------------------------------------------------------------------------

	T& operator[] (unsigned int position)							//(DA_O1)
	{
		assert(position >= 0);
		assert(position < m_size);

		return m_data[position];
	}
	
	void reserve(unsigned int a_capacity = 10)						//(DA_F1)
	{
		m_capacity += a_capacity;

		T* temp = new T[m_capacity];
		memcpy(temp, m_data, sizeof(T) * m_size);
		
		delete[] m_data;
		m_data = temp;
	}

	void clear()													//(DA_F2)
	{
		if (m_size == 0)
			return;

		while (m_size > 0)
			pop_back();
	}

	void erase_at(unsigned int position)							//(DA_F3)
	{
		assert(position >= 0);
		assert(position < m_size);


		for (unsigned int i = position; i < m_size - 1; i++)
			m_data[i] = m_data[i + 1];

		m_size--;
	}

	void add_at(unsigned int position, T item)						//(DA_F4)
	{
		assert(position >= 0);
		assert(position < m_size);

		if (m_size == m_capacity)
			reserve();

		T *temp(new T[m_capacity]);
		for (unsigned int i = position; i < m_capacity - 1; ++i)
			temp[i + 1] = m_data[i];

		m_data[position] = item;

		for (unsigned int i = position + 1; i < m_capacity; ++i)
			m_data[i] = temp[i];
		delete[] temp;

		m_size++;
	}

	void push_back(T a_item)										//(DA_F5)
	{
		if (m_size == m_capacity)
			reserve();

		m_data[m_size++] = a_item;
	}

	void pop_back()		{ m_data[m_size--] = T(); }					//(DA_F6)

	unsigned int size() { return m_size; }							//(DA_F7)
	bool empty()		{ return m_size == 0; }						//(DA_F8)

	T& front()		{ return m_data[0]; }							//(DA_F9)
	T& back()		{ return m_data[m_size - 1]; }					//(DA_F10)

	iterator begin()				{ return &m_data[0]; }			//(DA_F11)
	const_iterator begin() const	{ return &m_data[0]; }			//(DA_F12)
	iterator end()					{ return &m_data[m_size]; }		//(DA_F13)
	const_iterator end() const		{ return &m_data[m_size]; }		//(DA_F14)


	//--------------------------------------------------------------------------------------------------------


private:

	unsigned int m_size;											//(DA_V)
	unsigned int m_capacity;
	T* m_data = nullptr;
};