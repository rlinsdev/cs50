#include <cs50.h>
#include <stdio.h>

//gcc -g population.c -lcs50 -o population
int calc_llamas(int start_size, int end_size);

int main(void)
{
	int start_size = get_int("Start size: ");
	int end_size = get_int("End size: ");
	int years = calc_llamas(start_size, end_size);
	printf("Years: %i\n", years);
}

// Validar numero negativo
// validar um menor que o outro?

/**
 * @brief Calculate the number of years a population of llamas will grow, based
 * in a n/3 born and n/4 deaths, by year.
 * @param start_size Start size of the population
 * @param end_size Final size of the population
 * @return int - Number of years
 */
int calc_llamas(int start_size, int end_size)
{
	int years = 0;
	int ll_by_year = start_size;

	do
	{
		int new_llamas = start_size / 3;
		int p_away_llamas = start_size / 4;
		ll_by_year = start_size + (new_llamas - p_away_llamas);

		years++;
		start_size = ll_by_year;
	} while (end_size >= ll_by_year);

	return years;
}
