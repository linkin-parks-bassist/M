#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifndef LL_FREE
#define LL_FREE free
#endif

#ifndef LL_MALLOC
#define LL_MALLOC malloc
#endif

#define DECLARE_LINKED_LIST(X) struct X##_ll;																									\
typedef struct X##_ll {																														\
	X data;																																				\
	struct X##_ll *next;																														\
} X##_ll;																																		\
																																						\
X##_ll *X##_ll_new(X x);																												\
void free_##X##_ll(X##_ll *list);																										\
X##_ll *X##_ll_tail(X##_ll *list);																							\
X##_ll *X##_ll_append(X##_ll *list, X x);																					\
X##_ll *X##_ll_append_return_tail(X##_ll **list, X x);																		\
X##_ll *X##_ll_remove_next(X##_ll *list);																					\
void destructor_free_##X##_ll(X##_ll *list, void (*destructor)(X x));																	\
void X##_ll_map(X##_ll *list, X (*fmap)(X x));																						\
X##_ll *X##_ll_cmp_search(X##_ll *list, int (*cmp_function)(X, X), X x);														\
X##_ll *X##_ll_destructor_free_and_remove_matching(X##_ll *list, int (*cmp_function)(X, X), X x, void (*destructor)(X));

#define IMPLEMENT_LINKED_LIST(X)																														\
X##_ll *X##_ll_new(X x)																												\
{																																						\
	X##_ll *result = (X##_ll*)LL_MALLOC(sizeof(X##_ll));																		\
																																						\
	if (result == NULL)																																	\
		return NULL;																																	\
																																						\
	result->data = x;																																	\
	result->next = NULL;																																\
																																						\
	return result;																																		\
}																																						\
																																						\
X##_ll *X##_ll_tail(X##_ll *list)																							\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ll *current = list;																													\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	return current;																																		\
}																																						\
																																						\
void free_##X##_ll(X##_ll *list)																										\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
	X##_ll *current = list;																													\
	X##_ll *next = NULL;																														\
	while (current != NULL) {																															\
		next = current->next;																															\
		LL_FREE(current);																																	\
		current = next;																																	\
	}																																					\
}																																						\
																																						\
void destructor_free_##X##_ll(X##_ll *list, void (*destructor)(X x))																	\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
																																						\
	X##_ll *current = list;																													\
	X##_ll *next = NULL;																														\
																																						\
	while (current != NULL) {																															\
		next = current->next;																															\
		destructor(current->data);																														\
		LL_FREE(current);																																	\
		current = next;																																	\
	}																																					\
}																																						\
																																						\
X##_ll *X##_ll_append(X##_ll *list, X x)																						\
{																																						\
	X##_ll *next = X##_ll_new(x);																										\
	if (list == NULL) return next;																														\
																																						\
	X##_ll *current = list;																													\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	current->next = next;																																\
																																						\
	return list;																																		\
}																																						\
																																						\
X##_ll *X##_ll_append_return_tail(X##_ll **list, X x)																		\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ll *next = X##_ll_new(x);																										\
	if (*list == NULL) {																																\
		*list = next;																																	\
		return next;																																	\
	}																																					\
																																						\
	X##_ll *current = *list;																													\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	current->next = next;																																\
																																						\
	return next;																																		\
}																																						\
																																						\
X##_ll *X##_ll_remove_next(X##_ll *list)																						\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ll *next = list->next;																													\
																																						\
	if (next == NULL)																																	\
		return NULL;																																	\
																																						\
	list->next = list->next->next;																														\
																																						\
	return next;																																		\
}																																						\
																																						\
void X##_ll_map(X##_ll *list, X (*fmap)(X x))																							\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
																																						\
	list->data = fmap(list->data);																														\
	X##_ll_map(list->next, fmap);																												\
}																																						\
																																						\
X##_ll *X##_ll_cmp_search(X##_ll *list, int (*cmp_function)(X, X), X x)														\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ll *current = list;																													\
																																						\
	while (current) {																																	\
		if (cmp_function(current->data, x) == 0)																										\
			return current;																																\
																																						\
		current = current->next;																														\
	}																																					\
																																						\
	return NULL;																																		\
}																																						\
																																						\
X##_ll *X##_ll_destructor_free_and_remove_matching(X##_ll *list, int (*cmp_function)(X, X), X x, void (*destructor)(X))		\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ll *current = list;																													\
	X##_ll *prev = NULL;																														\
	X##_ll *next = NULL;																														\
																																						\
	while (current)	{																																	\
		next = current->next;																															\
		if (cmp_function(current->data, x) == 0) {																										\
			if (current == list)																														\
				list = next;																															\
			destructor(current->data);																													\
			LL_FREE(current);																																\
			if (prev)																																	\
				prev->next = next;																														\
		} else {																																		\
			prev = current;																																\
		}																																				\
		current = next;																																	\
	}																																					\
																																						\
	return list;																																		\
}

#define DECLARE_LINKED_PTR_LIST(X) struct X##_pll;																							\
typedef struct X##_pll {																													\
	X *data;																																			\
	struct X##_pll *next;																													\
} X##_pll;																																	\
																																						\
X##_pll *X##_pll_new(X *value);																									\
void free_##X##_pll(X##_pll *list);																								\
X##_pll *X##_pll_tail(X##_pll *list);																				\
X##_pll *X##_pll_append(X##_pll *list, X *value);																	\
X##_pll *X##_pll_append_return_tail(X##_pll **list, X *x);															\
X##_pll *X##_pll_remove_next(X##_pll *list);																		\
void X##_pll_free_all(X##_pll *list);																							\
void destructor_free_##X##_pll(X##_pll *list, void (*destructor)(X *x));														\
X##_pll *X##_pll_cmp_search(X##_pll *list, int (*cmp_function)(const X*, const X*), const X *x);					\
X##_pll *X##_pll_destructor_free_and_remove_matching(X##_pll *list, int (*cmp_function)(X*, X*), X *x, void (*destructor)(X*));

#define IMPLEMENT_LINKED_PTR_LIST(X)																													\
																																						\
X##_pll *X##_pll_new(X *value)																									\
{																																						\
	X##_pll *result = (X##_pll*)LL_MALLOC(sizeof(X##_pll));															\
																																						\
	if (result == NULL)																																	\
		return NULL;																																	\
																																						\
	result->data = value;																																\
	result->next = NULL;																																\
																																						\
	return result;																																		\
}																																						\
																																						\
X##_pll *X##_pll_tail(X##_pll *list)																				\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_pll *current = list;																												\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	return current;																																		\
}																																						\
																																						\
X##_pll *X##_pll_append(X##_pll *list, X *x)																		\
{																																						\
	X##_pll *next = X##_pll_new(x);																								\
	if (list == NULL) return next;																														\
																																						\
	X##_pll *current = list;																												\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	current->next = next;																																\
																																						\
	return list;																																		\
}																																						\
																																						\
X##_pll *X##_pll_append_return_tail(X##_pll **list, X *x)															\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_pll *next = X##_pll_new(x);																								\
	if (*list == NULL) {																																\
		*list = next;																																	\
		return next;																																	\
	}																																					\
																																						\
	X##_pll *current = *list;																												\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	current->next = next;																																\
																																						\
	return next;																																		\
}																																						\
																																						\
																																						\
void free_##X##_pll(X##_pll *list)																								\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
	X##_pll *current = list;																												\
	X##_pll *next = NULL;																													\
	while (current != NULL) {																															\
		next = current->next;																															\
		LL_FREE(current->data);																															\
		LL_FREE(current);																																	\
		current = next;																																	\
	}																																					\
}																																						\
																																						\
void destructor_free_##X##_pll(X##_pll *list, void (*destructor)(X *x))															\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
																																						\
	X##_pll *current = list;																												\
	X##_pll *next = NULL;																													\
	while (current != NULL) {																															\
		next = current->next;																															\
		destructor(current->data);																														\
		LL_FREE(current);																																	\
		current = next;																																	\
	}																																					\
}																																						\
																																						\
X##_pll *X##_pll_remove_next(X##_pll *list)																			\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_pll *next = list->next;																												\
																																						\
	if (next == NULL)																																	\
		return NULL;																																	\
																																						\
	list->next = next->next;																															\
																																						\
	return next;																																		\
}																																						\
																																						\
void X##_pll_map(X##_pll *list, X *(*fmap)(X *x))																				\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
																																						\
	list->data = fmap(list->data);																														\
	X##_pll_map(list->next, fmap);																											\
}																																						\
																																						\
X##_pll *X##_pll_cmp_search(X##_pll *list, int (*cmp_function)(const X*, const X*), const X *x)						\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_pll *current = list;																												\
																																						\
	while (current) {																																	\
		if (cmp_function(current->data, x) == 0)																										\
			return current;																																\
																																						\
		current = current->next;																														\
	}																																					\
																																						\
	return NULL;																																		\
}																																						\
																																						\
																																						\
X##_pll *X##_pll_destructor_free_and_remove_matching(X##_pll *list, int (*cmp_function)(X*, X*), X *x, void (*destructor)(X*))\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_pll *current = list;																												\
	X##_pll *next = NULL;																													\
	X##_pll *prev = NULL;																													\
																																						\
	while (current)	{																																	\
		next = current->next;																															\
		if (cmp_function(current->data, x) == 0) {																										\
			if (current == list)																														\
				list = next;																															\
			destructor(current->data);																													\
			LL_FREE(current);																																\
			if (prev)																																	\
				prev->next = next;																														\
		} else {																																		\
			prev = current;																																\
		}																																				\
		current = next;																																	\
	}																																					\
																																						\
	return list;																																		\
}

#endif
