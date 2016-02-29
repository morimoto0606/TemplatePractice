template <class T> 
T Max(T x, T y)
{
	return x < y ? y : x;
}

class Stack_of_int {
	int * data_;
	int  index_;
	int capacity_;
public:
	explicit Stack_of_int(int n) : capacity_(n), index_(0)
	{
		data_ = new int[capacity_];
	}
	~Stack_of_int()
	{
		delete[] data_;
	}

	void push(int x)
	{
		if (index_ < capacity_) {
			data_[index_++] = x;
		}
	}
	int top() const
	{
		return data_[index_ - 1];
	}
	void pop()
	{
		if (index_ > 0) {
			--index_;
		}
	}
};