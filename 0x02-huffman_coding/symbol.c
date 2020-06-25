#include "huffman.h"

/**
 * symbol_create - creates a symbol
 * @data: data
 * @freq: frequency of @data
 * Return: pointer to the created structure, or NULL if it fails
*/
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *sym;

	sym = malloc(sizeof(*sym));
	if (!sym)
		return (NULL);
	sym->data = data;
	sym->freq = freq;
	return (sym);
}
