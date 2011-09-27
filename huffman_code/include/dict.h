#ifndef DICT_H
#define DICT_H

#include <list.h>

struct dict {
	char *key;
	char *value;
};

typedef list dict;

extern dict *dict_new(void);
extern dict *dict_free(dict *d);
extern int dict_set(dict *d, char *key, char *value);
extern char *dict_value(dict *d, char *key);
extern int dict_remove(dict *d, char *key);

#endif
