/* Name: Simon Chen
 * TerpConnect login ID: schen98
 * Univserty ID number: 117009781
 * Discussion section: 0104
 *
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this assignments or examination.
 *
 * This program deals with a data structure, it is a singly linked list 
 * called Prio_que with a int prio (priority), char *element, and node 
 * *next. There is a dummy node that has next pointing to NULL. There is
 * enqueue and dequeue function to add and remove nodes from the queue. 
 * A size to count how many nodes in queue, a empty to see if queue is 
 * empty or not , and a peek to return the elment with the largest 
 * priority. A get all elements function to retreive all elements from 
 * the queue in decreasing priority order ended with NULL. Free a name list
 * array pointer and clear the prio_q so it points to nothing. Functions
 * that returns the priority of the corresponding element, and change the 
 * priority of the matching element form the paramter. Lastly, one that 
 * removed the node if its priority is within the range of low and high.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prio-q.h"
 
/* Initializes the prio_q, setting up a dummy node with 
 * its next pointing to NULL.
 */
void init(Prio_que *const prio_q) {
  if (prio_q != NULL) {
    prio_q->next = NULL;
  }
}

/* This function returns 0 if parameters prio_q or new_element is NULL,
 * or if prio_q already has the same priority value as the paramter, or 
 * if priority is negative. Otherwise, allocate the exact array size of 
 * new_element to store the string and add the element to the queue.
 */
unsigned int enqueue(Prio_que *const prio_q, const char new_element[],
                     unsigned int priority) {
  Prio_que *curr = NULL, *prev = NULL, *temp = NULL;
  char *elem_cp = malloc(strlen(new_element) + 1);
   
  if (prio_q == NULL || new_element == NULL || priority < 0)
    return 0;

  curr = prio_q->next;
    
  /*Checks if queue already has priority of parameter priority*/
  while (curr != NULL) {
    if (curr->prio == priority) 
      return 0;
       
    curr = curr->next;
  }
  
  /*curr point to beginning of queue*/
  curr = prio_q->next;
 
  /*copy element and set up node temp to enqueue*/
  strcpy(elem_cp, new_element);
  temp = malloc(sizeof(Prio_que));
  temp->prio = priority;
  temp->element = elem_cp; 
  temp->next = NULL;
  
  /*enqueue first node if queue is empty*/
  if (curr == NULL) 
    prio_q->next = temp;
   
  else {
    /*Find first occurence of queue with less priority*/
    while (curr != NULL && curr->prio > priority) {
      prev = curr;
      curr = curr->next;
    }
  
    /*enqueue temp at the beginning*/
    if (curr == prio_q->next) { 
      temp->next = curr;
      prio_q->next = temp;
    }

    /*enqueue temp at the end*/
    else if (curr == NULL) 
      prev->next = temp;
    
    /*enqueue temp somewhere in between*/
    else {
      temp->next = curr;
      prev->next = temp;
    }    
  }
    
  return 1;
}

/* This functin returns 0 if any elements are stored in prio_q 
 * and returns 1, otherwise
 */
unsigned int is_empty(const Prio_que prio_q) {
  unsigned int num_elem = size(prio_q);

  if (num_elem == 0)
    return 1;
  
  return 0;
}

/* This function returns the number of elements in prio_q
 * parameter
 */
unsigned int size(const Prio_que prio_q) {
  unsigned int count = 0;
  const Prio_que *curr = &prio_q; 
  
  while (curr->next != NULL) {
    count++;
    curr = curr->next;
  }

  return count;
}

/* This function will return NULL if prio_q is empty. Otherwise, return
 * a dynamically allocated string of the element with the highest priority. 
 */
char *peek(Prio_que prio_q) {
  Prio_que *curr = &prio_q;
  char *elem_cp = NULL;

  if (curr->next == NULL)
    return NULL;
  
  elem_cp = malloc(strlen(curr->next->element) + 1);
  strcpy(elem_cp, curr->next->element);

  return elem_cp;
}

/* This function will return NULL if prio_q is NULL or queue is empty.
 * Otherwise, it will return the string of the element with the highest
 * priority after removing the corresponding node from queue which will
 * decrease the size by one.
 */
char *dequeue(Prio_que *const prio_q) {
  Prio_que *curr = prio_q;
  Prio_que *temp = NULL;
  char *elem_cp = NULL; 

  if (prio_q == NULL || curr->next == NULL)
    return NULL;

  temp = curr->next;
  elem_cp = curr->next->element; 
  
  /*only one node in queue*/
  if (curr->next->next == NULL) 
    curr->next = NULL;

  /*More than one node in the queue*/
  else 
    curr->next = curr->next->next;
  
  free(temp);

  return elem_cp;
}

/* This function returns NULL if prio_q is NULL. Otherwise, allocate
 * memory for each element and set each to a array with a extra index
 * at the end with NULL, and return the double pointer char.
 */
char **get_all_elements(Prio_que prio_q) {
  Prio_que *curr = &prio_q;
  char **all_elems;
  char *elem_cp = NULL;
  int i, q_size = 0;

  if (curr == NULL)
    return NULL;

  /*Get number of nodes in queue and plus 1 for end of NULL*/
  q_size = size(prio_q) + 1; 
  all_elems = malloc(q_size * sizeof(char *));
  
  /* Iterate for number of nodes in queue, allocate memory for each 
   * element, copy the element and assign it to all_elems accordingly.
   */
  for (i = 0; i < q_size - 1; i++) {
    elem_cp = malloc(strlen(curr->next->element) + 1);

    strcpy(elem_cp, curr->next->element);

    all_elems[i] = elem_cp;
    curr = curr->next;
  }

  /*set last index to NULL*/
  all_elems[q_size - 1] = NULL;

  return all_elems;
}

/* If paramter is NULL, there is no effect. Otherwise, this function
 * free the strings in name_list and then free name_list itself.
 */
void free_name_list(char *name_list[]) {
  if (name_list != NULL) {
    int i = 0;
    char* curr;

    while (name_list[i] != NULL) {
      curr = name_list[i];
      free(curr);
      curr = NULL; 
      i++;
    }
    
    free(name_list);
    name_list = NULL;
  }
}

/* If the prio_q is NULL, there is no effect. This function will
 * deallocate all the memory used by the queue that prio_q points to.
 */
void clear(Prio_que *const prio_q) {
  Prio_que *curr = NULL, *temp = NULL;

  if (prio_q != NULL || prio_q->next != NULL) {
    curr = prio_q->next;
    
    while (curr != NULL) {
      temp = curr->next;
      free(curr->element);
      free(curr);
      curr = temp;
    }
   
    free(temp);
  }
}

/* If prio_q parameter is NULL or the queue is empty, just return -1.
 * Otherwise, traverse the queue, search for the element that matches
 * the parameter element and return the highest priority of the matching
 * element in the queue.
 */
int get_priority(Prio_que prio_q, char element[]) {
  Prio_que *curr = &prio_q;
  int priority = -1;

  if (curr == NULL || curr->next == NULL)
    return -1;
  
  while (curr->next != NULL) {
    /*see if the element of node matches the parameter*/
    if (strcmp(curr->next->element, element) == 0) 
      /*keep track of the highest priority with element that matches*/
      if (curr->next->prio > priority) 
	priority = curr->next->prio;

    curr = curr->next;
  }
  
  return priority;
}

/* If the prio_q is NULL and no nodes are with range of low and high,
 * inclusively, return 0. Otherwise, traverse the queue, remove all nodes
 * with corresponding priority with the range, making sure to free memory
 * and return number of elements removed.
 */
unsigned int remove_elements_between(Prio_que *const prio_q, unsigned int low,
				     unsigned int high) {
  unsigned int removed = 0;
  Prio_que *curr = NULL, *prev = NULL, *temp = NULL;

  if (prio_q == NULL || prio_q->next == NULL) 
    return 0;

  curr = prio_q->next;

  while (curr != NULL) {
    /*Check if element is within range*/
    if (curr->prio >= low && curr->prio <= high) {
      temp = curr; 
      
      /*first node in range is removed*/
      if (curr == prio_q->next) 
	prio_q->next = curr->next;
            
      /*last node in range is removed*/
      else if (curr->next == NULL) 
	prev->next = NULL;
           
      /*some node in between is removed*/
      else
	prev->next = curr->next;
           
      /*free memory of node that is removed*/
      free(temp);
      removed++;
    }

    prev = curr;
    curr = curr->next;
  }

  return removed;
}

/* If prio_q is NULL or the the queue is empty or there is already a 
 * element with priority that matches the new_priority or more than one
 * occurence of element in queue, return 0. Otherwise, traverse the queue,
 * match the element with the parameter element, change its corresponding
 * priority to the new_priority, and return 1.
 */
unsigned int change_priority(Prio_que *prio_q, char element[], unsigned int 
			     new_priority) {
  Prio_que *curr = NULL;
  int occur = 0;

  if (prio_q != NULL && prio_q->next != NULL) {
    curr = prio_q->next;
  
    while (curr != NULL) {
      /*Keep count of same occurence of element matching*/
      if (strcmp(curr->element, element) == 0)
	occur++;

      /*Can't have same priority or more than one occurence of matching
	so just return 0*/
      if (curr->prio == new_priority || occur > 1)
	return 0;
     
      curr = curr->next;
    }
        
    /*Curr point back to the first node in teh queue*/
    curr = prio_q->next;

    while (curr != NULL) {
      /*find the matching elemnt and change its priority to the new one*/
      if (strcmp(curr->element, element) == 0) {
	curr->prio = new_priority;

	return 1;
      }
      curr = curr->next;
    }
  }

  return 0;
}
