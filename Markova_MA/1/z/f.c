
int f (double *a, int n, int m)
{
	int i , j, sum = 0, max = 0, pos_j, pos_i;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			sum += a[i*m + j];
		}
		sum /= m;
		max = sum;
		for(j = 0; j < m; j++)
		{
			if(a[i*m + j] > max)
			{
				if(pos_j == -1 || pos_j < j)
				{	
					pos_j = j;
					pos_i = i;
				}
			}
		}
	}
	return pos_i;
}