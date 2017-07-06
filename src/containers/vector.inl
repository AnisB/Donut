namespace donut
{
	template <typename T>
	TVector<T>::TVector(TAllocator& allocator)
	: _allocator(allocator)
	, _size(0)
	, _capacity(0)
	, _data(nullptr)
	{

	}

	template <typename T>
	TVector<T>::TVector(uint32_t size, TAllocator& allocator)
	: _allocator(allocator)
	, _size(0)
	, _capacity(0)
	, _data(nullptr)
	{
		resize(size);
	}

	template <typename T>
	TVector<T>::~TVector()
	{
		free();
	}

	template <typename T>
	void TVector<T>::resize(uint32_t size)
	{
		if(size ==  0)
		{
			clear();
		}
		else if(size < _size)
		{
			// Extra elements in the vector remove them
			for(uint32_t ele_idx = size; ele_idx < _size; ++ele_idx)
			{
				_data[ele_idx].~T();
			}
			_size = size;
		}
		else if (size < _capacity)
		{
			// Enough capacity to handle this, construct the new elements
			for(uint32_t ele_idx = _size; ele_idx < size; ++ele_idx)
			{
				construct<T>(&_data[ele_idx], _allocator);
			}
			_size = size;
		}
		else
		{
			// We need to increase our capacity, it is not big enough
			reserve(size);
			for(uint32_t ele_idx = _size; ele_idx < size; ++ele_idx)
			{
				construct<T>(&_data[ele_idx], _allocator);
			}
			_size = size;
		}
	}

	template <typename T>
	void TVector<T>::clear()
	{
		for(uint32_t ele_idx = 0; ele_idx < _size; ++ele_idx)
		{
			_data[ele_idx].~T();
		}
		_size = 0;
	}

	template <typename T>
	void TVector<T>::free()
	{
		if(_capacity)
		{
			clear();
			_capacity = 0;
			_allocator.deallocate(_data);
		}
	}

	template <typename T>
	void TVector<T>::reserve(uint32_t size)
	{
		ASSERT_NO_RELEASE(size != 0);
		memory_block mem = _allocator.allocate(sizeof(T) * (_capacity + size));
		memcpy(mem.ptr, _data, sizeof(T) * _size);
		if(_data != nullptr)
		{
			_allocator.deallocate(_data);
		}
		_data = static_cast<T*>(mem.ptr);
		_capacity = (_capacity + size);
	}


	template <typename T>
	void TVector<T>::push_back(const T& _value)
	{
		if(_size == _capacity)
		{
			reserve(_capacity * 2 + 10);
		}
		
		// construct the new element
		construct<T>(&_data[_size], _allocator);
		_data[_size] = _value;

		// Increase the size
		_size++;
	}
}