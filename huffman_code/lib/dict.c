#include <dict.h>
#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dict_free_entry(void *pvalue)
{
	struct dict *value = pvalue;

	if (value == NULL)
		return;
	free(value->key);
	free(value->value);
	free(value);
}

static int dict_compare_entry(const void *a, const void *b)
{
	const struct dict *_a = a, *_b = b;

	return strcmp(_a->key, _b->key);
}

static int dict_compare_entry_by_value(const void *a, const void *b)
{
	const struct dict *_a = a, *_b = b;

	return strcmp(_a->value, _b->value);
}

dict *dict_new(void)
{
	list *l = list_new();
	list_set_free_value_method(l, dict_free_entry);
	list_set_compare_function(l, dict_compare_entry);
	return l; 
}

dict *dict_free(dict *d)
{
	return list_free(d);
}

/* Return zero if entry was updated instead inserted. Otherwise,
 * the result should be one.  New strings are created to key
 * and value, thus constants can be passed to dict_set. */
int dict_set(dict *d, char *key, char *value)
{
	struct dict *entry, *new;
	char *nkey = NULL, *nvalue = NULL;

	new = malloc(sizeof(struct dict));
	if (new == NULL)
		goto error;
	nkey = malloc(sizeof(char) * (strlen(key) + 1));
	if (nkey == NULL) 
		goto error;
	nvalue = malloc(sizeof(char) * (strlen(value) + 1));
	if (nvalue == NULL)
		goto error;
	new->key = strcpy(nkey, key);
	new->value = strcpy(nvalue, value);
	entry = list_find(d, new, NULL);
	if (entry != NULL) {
		/* There is already an entry with this key.  Update it. */
		free(entry->value);
		entry->value = new->value;
		/* Do not call dict_free_entry here. */
		free(new->key);
		free(new);
		return 0;
	}
	list_insert_sorted(d, new);
	return 1;
error:
	fprintf(stderr, "Can't create new dictionary entry.\n");
	if (nvalue != NULL)
		free(nvalue);
	if (nkey != NULL)
		free(nkey);
	if (new != NULL)
		free(new);
	return -1;
}

char *dict_value(dict *d, char *key)
{
	 struct dict *ret, entry = { .key = key };

	ret = list_find(d, &entry, NULL);
	if (ret != NULL)
		return ret->value;
	return NULL;
}

int dict_remove(dict *d, char *key)
{
	struct dict *ret, entry = { .key = key };

	ret = list_remove(d, &entry);
	if (ret != NULL)
		dict_free_entry(ret);
	return ret != NULL;
}

