/* Name: Simon Chen
 * TerpConnect login ID: schen98
 * Univserty ID number: 117009781
 * Discussion section: 0104
 *
 * I pledge on my honor that I have not given or received any
 * unauthorized assistance on this assignments or examination.
 *
 * header file consist of a node abstract data type
 * called Prio_que with members, int prio for priority,
 * char* element to point to string, and a struct node* 
 * next to point back to the struct.
 */

typedef struct node {
  int prio;
  char *element;
  struct node* next;
} Prio_que;
