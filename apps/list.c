#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
   int data;
   int key;
   struct Node * next;
} Node;

Node * head = NULL;
Node * current = NULL;

//display the list
void printList() {
   Node *ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%d) ",ptr->key,ptr->data);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//insert link at the first location
void insertFirst(int key, int data) {
   //create a link
   Node * newNode = (Node *) malloc(sizeof(Node));
	
   newNode->key = key;
   newNode->data = data;
	newNode->next = head;
	head = newNode;
}

//delete first item
void deleteFirst() {
   Node * oldHead = head;
	head = head->next;
   free(oldHead);
}

//is list empty
int isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   Node *cur;
	
   for(cur = head; cur != NULL; cur = cur->next) {
      length++;
   }
	
   return length;
}

//find a link with given key
Node * find(int key) {

   Node * cur = head;

   if(head == NULL) {
      return NULL;
   }

   while(cur->key != key) {	
      if(cur->next == NULL) {
         return NULL;
      } else {
         cur = cur->next;
      }
   }
   return cur;
}

//delete a link with given key
void delete(int key) {
   Node * cur = head;
   Node * prev = NULL;
	
   //if list is empty
   if(head == NULL) {
      return;
   }

   //navigate through list
   while(cur->key != key) {

      //if it is last node
      if(cur->next == NULL) {
         return;
      } else {
         prev = cur;
         cur = cur->next;
      }
   }

   //found a match, update the link
   if(cur == head) {
      head = head->next;
   } else {
      prev->next = cur->next;
   }    
	
   free(current);
}

void sort() {

   int k, tempKey, tempData;
   Node * current;
   Node *next;
	
   int size = k = length();
	
   for (int i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
		
      for (int j = 1 ; j < k ; j++ ) {   
         if ( current->data > next->data ) {
            tempData = current->data;
            current->data = next->data;
            next->data = tempData;

            tempKey = current->key;
            current->key = next->key;
            next->key = tempKey;
         }
			
         current = current->next;
         next = next->next;
      }
   }   
}

void reverse() {
   Node * prev   = NULL;
   Node * current = head;
   Node * next;
	
   while (current != NULL) {
      next  = current->next;
      current->next = prev;   
      prev = current;
      current = next;
   }
	
   head = prev;
}

int main() {

   int vals[] = {4789, 1209, 2137, 1679, 1583, 3945, 3293};

   for(int i = 0; i < 7; ++i) {
      insertFirst(i, vals[i]);
   }
   
   sort();
   reverse();
   delete(5);
   delete(3);
   deleteFirst();

   assert(find(3)== NULL);
   printList();
   printf("OK.\n");

   return (0);
}