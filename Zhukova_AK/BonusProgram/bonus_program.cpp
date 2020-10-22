#include<iostream>
#include<stdio.h>
#include "bonus_program.h"

BonusProgram::BonusProgram(int l, const std::string &program)
{
	n = l;
	if (n <= 0)
	{
                throw BonusProgramException (1, "Неверные параметры");
        }

	m1 = (int*)malloc(n*sizeof(*m1));
	m2 = (int*)malloc(n*sizeof(*m2));

	if ((m1 == NULL) || (m2 == NULL))
	{
		throw BonusProgramException (2, "Память не выделилась");
	}

	for (int i=0; i<n;i++)
	{
		m1[i] = 0;
		m2[i] = 0;
	}

}

BonusProgram::BonusProgram(const BonusProgram &v)
{
	n = v.n;
	m1 = (int*)malloc(n*sizeof(*m1));
        m2 = (int*)malloc(n*sizeof(*m2));

	if ((m1 == NULL) || (m2 == NULL))
        {
                throw BonusProgramException (2, "Память не выделилась");
        }

	for (int i=0;i<n;i++)
	{
		m1[i] = v.m1[i];
		m2[i] = v.m2[i];
	}
}

BonusProgram::~BonusProgram()
{
	free (m1);
	free (m2);
}

bool BonusProgram::operator < (const BonusProgram &other)
{
	bool res = false;
	int sum1 = 0;
	int sum2 = 0;

	if ((n != other.n) || ( program !=other.program))
	{
		throw BonusProgramException (3, "Программы несравнимы");
	}

	for (int i=1;i<n;i++)
	{
		sum1 = sum1 + m2[i];
		sum2 = sum2 + other.m2[i];
	}

	if (sum1 < sum2)
	{
		res = true;
	}

	return res;
}

void BonusProgram::Registration (int coordinate, int sum)
{
	m1[coordinate] = m1[coordinate] + 1;
	m2[coordinate] = m2[coordinate] + sum;
}


BonusProgram BonusProgram::operator + (const BonusProgram &other)
{
	if (this->n != other.n)
	{
		throw BonusProgramException (3, "Программы несравнимы");
	}

	for (int i=0; i < this->n; i++)
	{
		this->m1[i] = this->m1[i] + other.m1[i];
		this->m2[i] = this->m2[i] + other.m2[i];
	}

	return *this;
}

void BonusProgram::print() const
{
	for (int i=0; i<n; i++)
	{
		printf ("%d: %d\n", m1[i], m2[i]);
	}
	printf ("\n");
}



BonusProgram BonusProgram::operator = (const BonusProgram &other)
{
        if (this->n != other.n)
        {
                throw BonusProgramException (4, "Невозможно присвоить");
        }

        for (int i=0; i < this->n; i++)
        {
                this->m1[i] = other.m1[i];
                this->m2[i] = other.m2[i];
        }

        return *this;
}

