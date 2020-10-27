#pragma once

#include <stdexcept>

template<typename TElement = double>
class matrix_base_t;

template<typename TElement = double>
class submatrix_t;

template<typename TElement = double>
class matrix_t;

template<typename TElement>
class matrix_base_t
{
public:
	virtual TElement getElement(int row, int col) const = 0;
	virtual void setElement(int row, int col, TElement value) = 0;

	int getCols() const { return _cols; }
	int getRows() const { return _rows; }

	friend std::ostream& operator << (std::ostream& os, const matrix_base_t<TElement>& m)
	{
		for (int row = 0; row < m.getRows(); ++row)
		{
			os << (row + 1) << ": ";
			for (int col = 0; col < m.getCols(); ++col)
			{
				os << m.getElement(row, col) << " ";
			}
			os << std::endl;
		}
		return os;
	}

	matrix_t<TElement> operator + (const matrix_base_t<TElement>& right);

	virtual ~matrix_base_t()
	{
	}

protected:
	matrix_base_t(int rows, int cols) : _cols(cols), _rows(rows)
	{
		if (rows <= 0 || cols <= 0)
		{
			throw std::range_error("invalid matrix size");
		}
	}
	int _cols;
	int _rows;
};

template<typename TElement>
class matrix_t : public matrix_base_t<TElement>
{
public:

	matrix_t() = delete;

	matrix_t(int rows, int cols) 
		: matrix_base_t<TElement>(rows, cols) 
	{
		std::cout << "matrix_t(int rows, int cols) " << std::endl;
		int numberOfElements = this->getRows() * this->getCols();
		_data = new TElement[numberOfElements];
		for (int index = 0; index < numberOfElements; ++index)
		{
			_data[index] = 0;
		}
	}

	matrix_t(const matrix_t& source) 
		: matrix_base_t<TElement>(source.getRows(), source.getRows()) 
	{
		std::cout << "matrix_t(const matrix_t& source)" << std::endl;
		int numberOfElements = this->getRows() * this->getCols();
		_data = new TElement[numberOfElements];
		for (int index = 0; index < numberOfElements; ++index)
		{
			_data[index] = source._data[index];
		}
	}


	virtual ~matrix_t()
	{
		std::cout << "~matrix_t()" << std::endl;
		if (_data)
		{
			delete[] _data;
		}
	}

	TElement getElement(int row, int col) const
	{
		if (row < 0 || row >= this->getRows() || col < 0 || col >= this->getCols())
		{
			throw std::range_error("row or column out of range");
		}
		return _data[row * this->getCols() + col];
	}

	void setElement(int row, int col, TElement value)
	{
		if (row < 0 || row >= this->getRows() || col < 0 || col >= this->getCols())
		{
			throw std::range_error("row or column out of range");
		}
		_data[row * this->getCols() + col] = value;
	}
	submatrix_t<TElement> get(int row, int col, int rows, int cols);

	matrix_t<TElement>& operator=(const matrix_base_t<TElement>& source)
	{
		if (this == &source) 
		{
			return *this;
		}
		int numberOfElements = source.getRows() * source.getCols();
		if (this->getRows() != source.getRows() || this->getCols() != source.getCols())
		{
			delete[] _data;
			this->_data = new TElement[numberOfElements];
			this->_rows = source.getRows();
			this->_cols = source.getCols();
		}
		for (int row = 0; row < this->getRows(); ++row)
		{
			for (int col = 0; col < this->getCols(); ++col)
			{
				setElement(row, col, source.getElement(row, col));
			}
		}
		return *this;
	}

private:
	TElement* _data;
};

template<typename TElement>
class submatrix_t : public matrix_base_t<TElement>
{
public:
	submatrix_t(const submatrix_t& source)
		: matrix_base_t<TElement>(source.getRows(), source.getCols()) ,
		_matrix(source._matrix),
		_row(source._row),
		_col(source._col)
	{
	}

	TElement getElement(int row, int col) const
	{
		if (row < 0 || col < 0)
		{
			throw std::invalid_argument("row and col must be greater than or equals to zero");
		}
		return _matrix->getElement(row + _row, col + _col);
	}

	void setElement(int row, int col, TElement value)
	{
		if (row < 0 || col < 0)
		{
			throw std::invalid_argument("row and col must be greater than or equals to zero");
		}
		return _matrix->setElement(row + _row, col + _col, value);
	}

private:
	submatrix_t() = delete;
	submatrix_t(matrix_t<TElement>* matrix, int row, int col, int rows, int cols)
		: matrix_base_t<TElement>(rows, cols), _matrix(matrix), _row(row), _col(col)
	{
		if (!matrix)
		{
			throw std::invalid_argument("matrix cannot be nullptr");
		}
		if (row < 0 || col < 0 || rows <= 0 || cols <= 0 || row + rows > matrix->getRows() || col + cols > matrix->getCols())
		{
			throw std::invalid_argument("invalid submatrix definition");
		}
	}
	
private:
	matrix_t<TElement>* _matrix;
	int _row;
	int _col;

	friend class matrix_t<TElement>;
};

template<typename TElement>
inline
submatrix_t<TElement> matrix_t<TElement>::get(int row, int col, int rows, int cols)
{
	return submatrix_t<TElement>(this, row, col, rows, cols);
}

template<typename TElement>
inline
matrix_t<TElement> matrix_base_t<TElement>::operator+(const matrix_base_t<TElement>& right)
{
	const matrix_base_t<TElement>& left = *this;
	if (left.getRows() != right.getRows() || left.getCols() != right.getCols())
	{
		throw std::invalid_argument("size of matrices are different");
	}
	matrix_t<TElement> result = matrix_t<TElement>(left.getRows(), left.getCols());
	for (int row = 0; row < getRows(); ++row)
	{
		for (int col = 0; col < getCols(); ++col)
		{
			result.setElement(row, col, left.getElement(row, col) + right.getElement(row, col));
		}
	}
	return result;
}

