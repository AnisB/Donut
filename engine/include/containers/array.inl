namespace donut
{
	template <typename T>
	TArray<T>::TArray(TAllocator& allocator)
	: _allocator(allocator)
	, _size(0)
	, _capacity(0)
	, _data(nullptr)
	{

	}

	template <typename T>
	TArray<T>::TArray(uint32_t size, TAllocator& allocator)
	: _allocator(allocator)
	, _size(0)
	, _capacity(0)
	, _data(nullptr)
	{
		resize(size);
	}

	template <typename T>
	TArray<T>::~TArray()
	{
		free();
	}

	// Set the size to 0
	template <typename T>
	void TArray<T>::clear()
	{
		_size = 0;
	}

	template <typename T>
	void TArray<T>::resize(uint32_t size)
	{
		if(size ==  0)
		{
			clear();
		}
		else if(_size < size)
		{
			_size = size;
		}
		else if (_size < _capacity)
		{
			_size = size;
		}
		else
		{
			reserve(size);
			_size = size;
		}
	}

	template <typename T>
	void TArray<T>::free()
	{
		if(_capacity)
		{
			_size = 0;
			_capacity = 0;
			_allocator.deallocate(_data);
		}
	}

	template <typename T>
	void TArray<T>::reserve(uint32_t size)
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
	void TArray<T>::push_back(const T& _value)
	{
		if(_size == _capacity)
		{
			reserve(_capacity * 2 + 10);
		}
		_data[_size++] = _value;
	}
}