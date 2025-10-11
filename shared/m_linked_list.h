#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define DECLARE_LINKED_LIST(X) struct X##_linked_list;																									\
typedef struct X##_linked_list {																														\
	X data;																																				\
	struct X##_linked_list *next;																														\
} X##_linked_list;																																		\
																																						\
X##_linked_list *X##_linked_list_new(X x);																												\
void free_##X##_linked_list(X##_linked_list *list);																										\
X##_linked_list *X##_linked_list_tail(X##_linked_list *list);																							\
X##_linked_list *X##_linked_list_append(X##_linked_list *list, X x);																					\
X##_linked_list *X##_linked_list_append_return_tail(X##_linked_list **list, X x);																		\
X##_linked_list *X##_linked_list_remove_next(X##_linked_list *list);																					\
void destructor_free_##X##_linked_list(X##_linked_list *list, void (*destructor)(X x));																	\
void X##_linked_list_map(X##_linked_list *list, X (*fmap)(X x));																						\
X##_linked_list *X##_linked_list_cmp_search(X##_linked_list *list, int (*cmp_function)(X, X), X x);														\
X##_linked_list *X##_linked_list_destructor_free_and_remove_matching(X##_linked_list *list, int (*cmp_function)(X, X), X x, void (*destructor)(X));

#define IMPLEMENT_LINKED_LIST(X)																														\
X##_linked_list *X##_linked_list_new(X x)																												\
{																																						\
	X##_linked_list *result = (X##_linked_list*)malloc(sizeof(X##_linked_list));																		\
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
X##_linked_list *X##_linked_list_tail(X##_linked_list *list)																							\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_linked_list *current = list;																													\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	return current;																																		\
}																																						\
																																						\
void free_##X##_linked_list(X##_linked_list *list)																										\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
	X##_linked_list *current = list;																													\
	X##_linked_list *next = NULL;																														\
	while (current != NULL) {																															\
		next = current->next;																															\
		free(current);																																	\
		current = next;																																	\
	}																																					\
}																																						\
																																						\
void destructor_free_##X##_linked_list(X##_linked_list *list, void (*destructor)(X x))																	\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
																																						\
	X##_linked_list *current = list;																													\
	X##_linked_list *next = NULL;																														\
																																						\
	while (current != NULL) {																															\
		next = current->next;																															\
		destructor(current->data);																														\
		free(current);																																	\
		current = next;																																	\
	}																																					\
}																																						\
																																						\
X##_linked_list *X##_linked_list_append(X##_linked_list *list, X x)																						\
{																																						\
	X##_linked_list *next = X##_linked_list_new(x);																										\
	if (list == NULL) return next;																														\
																																						\
	X##_linked_list *current = list;																													\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	current->next = next;																																\
																																						\
	return list;																																		\
}																																						\
																																						\
X##_linked_list *X##_linked_list_append_return_tail(X##_linked_list **list, X x)																		\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_linked_list *next = X##_linked_list_new(x);																										\
	if (*list == NULL) {																																\
		*list = next;																																	\
		return next;																																	\
	}																																					\
																																						\
	X##_linked_list *current = *list;																													\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	current->next = next;																																\
																																						\
	return next;																																		\
}																																						\
																																						\
X##_linked_list *X##_linked_list_remove_next(X##_linked_list *list)																						\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_linked_list *next = list->next;																													\
																																						\
	if (next == NULL)																																	\
		return NULL;																																	\
																																						\
	list->next = list->next->next;																														\
																																						\
	return next;																																		\
}																																						\
																																						\
void X##_linked_list_map(X##_linked_list *list, X (*fmap)(X x))																							\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
																																						\
	list->data = fmap(list->data);																														\
	X##_linked_list_map(list->next, fmap);																												\
}																																						\
																																						\
X##_linked_list *X##_linked_list_cmp_search(X##_linked_list *list, int (*cmp_function)(X, X), X x)														\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_linked_list *current = list;																													\
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
X##_linked_list *X##_linked_list_destructor_free_and_remove_matching(X##_linked_list *list, int (*cmp_function)(X, X), X x, void (*destructor)(X))		\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_linked_list *current = list;																													\
	X##_linked_list *prev = NULL;																														\
	X##_linked_list *next = NULL;																														\
																																						\
	while (current)	{																																	\
		next = current->next;																															\
		if (cmp_function(current->data, x) == 0) {																										\
			if (current == list)																														\
				list = next;																															\
			destructor(current->data);																													\
			free(current);																																\
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

#define DECLARE_LINKED_PTR_LIST(X) struct X##_ptr_linked_list;																							\
typedef struct X##_ptr_linked_list {																													\
	X *data;																																			\
	struct X##_ptr_linked_list *next;																													\
} X##_ptr_linked_list;																																	\
																																						\
X##_ptr_linked_list *X##_ptr_linked_list_new(X *value);																									\
void free_##X##_ptr_linked_list(X##_ptr_linked_list *list);																								\
X##_ptr_linked_list *X##_ptr_linked_list_tail(X##_ptr_linked_list *list);																				\
X##_ptr_linked_list *X##_ptr_linked_list_append(X##_ptr_linked_list *list, X *value);																	\
X##_ptr_linked_list *X##_ptr_linked_list_append_return_tail(X##_ptr_linked_list **list, X *x);															\
X##_ptr_linked_list *X##_ptr_linked_list_remove_next(X##_ptr_linked_list *list);																		\
void X##_ptr_linked_list_free_all(X##_ptr_linked_list *list);																							\
void destructor_free_##X##_ptr_linked_list(X##_ptr_linked_list *list, void (*destructor)(X *x));														\
X##_ptr_linked_list *X##_ptr_linked_list_cmp_search(X##_ptr_linked_list *list, int (*cmp_function)(const X*, const X*), const X *x);					\
X##_ptr_linked_list *X##_ptr_linked_list_destructor_free_and_remove_matching(X##_ptr_linked_list *list, int (*cmp_function)(X*, X*), X *x, void (*destructor)(X*));

#define IMPLEMENT_LINKED_PTR_LIST(X)																													\
																																						\
X##_ptr_linked_list *X##_ptr_linked_list_new(X *value)																									\
{																																						\
	X##_ptr_linked_list *result = (X##_ptr_linked_list*)malloc(sizeof(X##_ptr_linked_list));															\
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
X##_ptr_linked_list *X##_ptr_linked_list_tail(X##_ptr_linked_list *list)																				\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ptr_linked_list *current = list;																												\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	return current;																																		\
}																																						\
																																						\
X##_ptr_linked_list *X##_ptr_linked_list_append(X##_ptr_linked_list *list, X *x)																		\
{																																						\
	X##_ptr_linked_list *next = X##_ptr_linked_list_new(x);																								\
	if (list == NULL) return next;																														\
																																						\
	X##_ptr_linked_list *current = list;																												\
																																						\
	while (current->next != NULL)																														\
		current = current->next;																														\
																																						\
	current->next = next;																																\
																																						\
	return list;																																		\
}																																						\
																																						\
X##_ptr_linked_list *X##_ptr_linked_list_append_return_tail(X##_ptr_linked_list **list, X *x)															\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ptr_linked_list *next = X##_ptr_linked_list_new(x);																								\
	if (*list == NULL) {																																\
		*list = next;																																	\
		return next;																																	\
	}																																					\
																																						\
	X##_ptr_linked_list *current = *list;																												\
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
void free_##X##_ptr_linked_list(X##_ptr_linked_list *list)																								\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
	X##_ptr_linked_list *current = list;																												\
	X##_ptr_linked_list *next = NULL;																													\
	while (current != NULL) {																															\
		next = current->next;																															\
		free(current->data);																															\
		free(current);																																	\
		current = next;																																	\
	}																																					\
}																																						\
																																						\
void destructor_free_##X##_ptr_linked_list(X##_ptr_linked_list *list, void (*destructor)(X *x))															\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
																																						\
	X##_ptr_linked_list *current = list;																												\
	X##_ptr_linked_list *next = NULL;																													\
	while (current != NULL) {																															\
		next = current->next;																															\
		destructor(current->data);																														\
		free(current);																																	\
		current = next;																																	\
	}																																					\
}																																						\
																																						\
X##_ptr_linked_list *X##_ptr_linked_list_remove_next(X##_ptr_linked_list *list)																			\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ptr_linked_list *next = list->next;																												\
																																						\
	if (next == NULL)																																	\
		return NULL;																																	\
																																						\
	list->next = next->next;																															\
																																						\
	return next;																																		\
}																																						\
																																						\
void X##_ptr_linked_list_map(X##_ptr_linked_list *list, X *(*fmap)(X *x))																				\
{																																						\
	if (list == NULL)																																	\
		return;																																			\
																																						\
	list->data = fmap(list->data);																														\
	X##_ptr_linked_list_map(list->next, fmap);																											\
}																																						\
																																						\
X##_ptr_linked_list *X##_ptr_linked_list_cmp_search(X##_ptr_linked_list *list, int (*cmp_function)(const X*, const X*), const X *x)						\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ptr_linked_list *current = list;																												\
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
X##_ptr_linked_list *X##_ptr_linked_list_destructor_free_and_remove_matching(X##_ptr_linked_list *list, int (*cmp_function)(X*, X*), X *x, void (*destructor)(X*))\
{																																						\
	if (list == NULL)																																	\
		return NULL;																																	\
																																						\
	X##_ptr_linked_list *current = list;																												\
	X##_ptr_linked_list *next = NULL;																													\
	X##_ptr_linked_list *prev = NULL;																													\
																																						\
	while (current)	{																																	\
		next = current->next;																															\
		if (cmp_function(current->data, x) == 0) {																										\
			if (current == list)																														\
				list = next;																															\
			destructor(current->data);																													\
			free(current);																																\
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
