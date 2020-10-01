class intset
{
	private:
		int *ar_;
		int size_;
		int maxval_;
		int min_val;
	public:
		intset(int maxval, int minval);
		~intset();
		intset(intset& IS);
};
