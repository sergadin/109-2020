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

	matrix_t<TElement>& operator + (const matrix_base_t<TElement>& right);
	matrix_t<TElement>& operator - (const matrix_base_t<TElement>& right);

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
private:
	int _cols;
	int _rows;
};

template<typename TElement>
class matrix_t : public matrix_base_t<TElement>
{
public:
	/// <summary>
	/// конструктор
	/// </summary>
	/// <param name="width">ширина матрицы</param>
	/// <param name="height">высота матрицы</param>
	matrix_t(int rows, int cols) : matrix_base_t<TElement>(rows, cols) {
		int numberOfElements = this->getRows() * this->getCols();
		_data = new TElement[numberOfElements];
		for (int index = 0; index < numberOfElements; ++index)
		{
			_data[index] = 0;
		}
	}
	/// <summary>
	/// деструктор, удаляет выделленный массив
	/// </summary>
	virtual ~matrix_t()
	{
		delete[] _data;
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

private:
	/// <summary>
	/// Конструктор по умолчанию делаем недоступным
	/// </summary>
	matrix_t() {}
private:
	TElement* _data;
};

template<typename TElement>
class submatrix_t : public matrix_base_t<TElement>
{
public:
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
	submatrix_t() {}
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
matrix_t<TElement>& matrix_base_t<TElement>::operator+(const matrix_base_t<TElement>& right)
{
	const matrix_base_t<TElement>& left = *this;
	if (left.getRows() != right.getRows() || left.getCols() != right.getCols())
	{
		throw std::invalid_argument("size of matrices are different");
	}
	matrix_t<TElement>* result = new matrix_t<TElement>(left.getRows(), left.getCols());
	for (int row = 0; row < getRows(); ++row)
	{
		for (int col = 0; col < getCols(); ++col)
		{
			result->setElement(row, col, left.getElement(row, col) + right.getElement(row, col));
		}
	}
	return *result;
}

template<typename TElement>
inline
matrix_t<TElement>& matrix_base_t<TElement>::operator-(const matrix_base_t<TElement>& right)
{
	const matrix_base_t<TElement>& left = *this;
	if (left.getRows() != right.getRows() || left.getCols() != right.getCols())
	{
		throw std::invalid_argument("size of matrices are different");
	}
	matrix_t<TElement>* result = new matrix_t<TElement>(left.getRows(), left.getCols());
	for (int row = 0; row < getRows(); ++row)
	{
		for (int col = 0; col < getCols(); ++col)
		{
			result->setElement(row, col, left.getElement(row, col) - right.getElement(row, col));
		}
	}
	return *result;
}
