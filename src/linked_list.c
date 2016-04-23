#include "linked_list.h"
#include "util.h"
#include "stdlib.h"

/************************
LIST
************************/

linked_list *ll_new() {
	linked_list *list = new(list);
	list->head = list->tail = NULL;
	return list;
}

linked_list *ll_duplicate(linked_list *list) {
	linked_iter iterator = ll_iter_head(list);
	linked_list *newList = ll_new();
	while(ll_iter_has_next(&iterator)) {
		ll_add_first(newList, ll_iter_next(&iterator));
	}
	return newList;
}

void ll_add_first(linked_list *list, void *value) {
	linked_node *node = new(node);
	node->data = value;
	node->next = list->head;
	node->prev = NULL;
	list->head = node;
	if(list->tail == NULL) {
		list->tail = node;
	}
}

void ll_add_last(linked_list *list, void *value) {
	if(list->head == NULL) {
		ll_add_first(list, value);
	} else {
		linked_node *node = new(node);
		node->data = value;
		node->prev = list->tail;
		node->next = NULL;
		list->tail = node;
	}
}

void *ll_get_first(linked_list *list) {
	return list->head->data;
}

void *ll_get_last(linked_list *list) {
	return list->tail->data;
}

void *ll_remove_last(linked_list *list) {
	void *data = list->tail->data;
	if(list->head == list->tail) {
		free(list->head);
		list->head = list->tail = NULL;
	} else {
		linked_node *tail = list->tail;
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		free(tail);
	}
	return data;
}

void *ll_remove_first(linked_list *list) {
	void *data = list->head->data;
	if(list->head == list->tail) {
		free(list->head);
		list->head = list->tail = NULL;
	} else {
		linked_node *head = list->head;
		list->head = list->head->next;
		list->head->next = NULL;
		free(head);
	}
	return data;
}

bool ll_empty(linked_list *list) {
	return list->head == NULL;
}

void ll_clear(linked_list *list) {
	list->tail = NULL;
	while(list->head != NULL) {
		linked_node *next = list->head->next;
		free(list->head);
		list->head = next;
	}
}

void ll_destroy(linked_list *list) {
	ll_clear(list);
	free(list);
}

/************************
ITERATOR
************************/

linked_iter ll_iter_head(linked_list *list) {
	linked_iter iterator;
	iterator.current = list->head;
	iterator.goesForward = true;
	iterator.origin = list;
	return iterator;
}

linked_iter ll_iter_tail(linked_list *list) {
	linked_iter iterator;
	iterator.current = list->tail;
	iterator.goesForward = false;
	iterator.origin = list;
	return iterator;
}

void *ll_iter_next(linked_iter *iter) {
	if(iter->current == NULL) {
		return NULL;
	} else {
		void *value = iter->current->data;
		if(iter->goesForward) {
			iter->current = iter->current->next;
		} else {
			iter->current = iter->current->prev;
		}
		return value;
	}
}

bool ll_iter_has_next(linked_iter *iter) {
	return iter->current != NULL;
}

void ll_iter_clear_to_current(linked_iter *iter) {
	if(iter->current == NULL) {
		ll_clear(iter->origin);
	}
	if(iter->goesForward) {
		linked_node *current = iter->origin->head;
		while(current->next != iter->current) {
			linked_node *next = current->next;
			free(current);
			current = next;
		}
		iter->origin->head = iter->current;
		iter->origin->head->prev = NULL;
	} else {
		linked_node *current = iter->origin->tail;
		while(current->prev != iter->current) {
			linked_node *prev = current->prev;
			free(current);
			current = prev;
		}
		iter->origin->tail = iter->current;
		iter->origin->tail->next = NULL;
	}
}
