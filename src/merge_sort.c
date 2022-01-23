#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"

bool merge(void *array, size_t data_size, ssize_t l, ssize_t m, ssize_t r, int (*comp_func)(void *, void *))
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;
	ssize_t	n1;
	void *arr;


	n1 = m - l + 1;
	arr = malloc((r - l + 1) * data_size);
	if (arr == NULL)
		return (false);
	ft_memcpy(arr, array + l * data_size, (r - l + 1) * data_size);
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < r - m) {
		if (comp_func(arr + i * data_size, arr + ((n1 + j) * data_size)) < 0) {
			ft_memcpy(array + k * data_size, arr + i * data_size, data_size);
			i++;
		}
		else {
			ft_memcpy(array + k * data_size, arr + (n1 + j) * data_size, data_size);
			j++;
		}
		k++;
	}
	if (i < n1)
		ft_memcpy(array + k * data_size, arr + i * data_size, (n1 - i) * data_size);
	if (j < r - m)
		ft_memcpy(array + k * data_size, arr + (n1 + j) * data_size, (r - m - j) * data_size);
	free(arr);
	return (true);
}

ssize_t min(ssize_t x, ssize_t y)
{
	if (x < y)
		return x;
	else
		return y;
}

bool	merge_sort(void *array, ssize_t size, size_t data_size, int (*comp_func)(void *, void *))
{
	ssize_t curr_size;
	ssize_t left_start;
	ssize_t mid;
	ssize_t right_end;

	curr_size = 1;
	while (curr_size <= size-1)
	{
		left_start = 0;
		while (left_start < size - 1)
		{
			mid = min(left_start + curr_size - 1, size - 1);
			right_end = min(left_start + 2 * curr_size - 1, size - 1);
			if (!merge(array, data_size, left_start, mid, right_end, comp_func))
				return (false);
			left_start += 2 * curr_size;
		}
		curr_size *= 2;
	}
	return (true);
}