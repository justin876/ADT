
//===========================================================================================
// doublyLinkedListADT.c 
// 
// NAME : Choi, Justin M.C.
// PURPOSE : to create a DLL ADT for future use
//
// CONSTRAINTS:
//      1) No duplicate values are allowed
//      2) Data values should be between "integer" range (-2x10^9 to 2x10^9)
//
// MAIN FUNCTIONS:
//      1) insert(create(<key>));
//      2) search(<key>);
//      3) delete(<key>);
//
// OTHER FUNCTIONS:
//      1) clear();
//      2) reverse();
//      3) traForward(); [Print]
//      4) traBack();   [Print]
//===========================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//===============================================================================
// TYPEDEF, STRUCT
//===============================================================================

typedef enum BOOLEAN Boolean;
enum BOOLEAN { FAILED, SUCCESS };

typedef struct NODE Node;
struct NODE {
    int data;
    Node * next;
    Node * prev;
}; 

//===============================================================================
// GLOBAL VARIABLES
//===============================================================================
unsigned int listCount = 0;
Node * head = NULL;
Node * tail = NULL;

//===============================================================================
// PROTOTYPES
//===============================================================================
Node * create(int);
Boolean insert(Node *);
Node * search(int);
Boolean delete(int);
void clear();
void reverse();
void traForward();
void traBack();

void testCreate();
void testInsert();
void testSearch();
void testDelete();
void testClear();
void testReverse();

//===============================================================================
// MAIN
//===============================================================================
int main(){
    testCreate();
    testInsert();
    testSearch();
    testDelete();
    testClear();
    testReverse();
    traForward();
    traBack();
    return 0;
}

//===============================================================================
// FUNCTIONS
//===============================================================================

//===========================================================================================
// create()
// 
// PURPOSE: To create a newNode using malloc (Node memory is in heap)
// INPUT PARAMETER :
//      input               the data to be stored in the newNode
// OUTPUT PARAMETER :
//      newNode == NULL     No more memories in malloc (ie. create failed)
//      newNode != NULL     the memory address of that newNode (ie. create successfully)   
//===========================================================================================      
Node * create(int input){ // (No need to check input boundary)
    Node * newNode = (Node *)malloc(sizeof(Node));
    assert(newNode);

    if (newNode){
        newNode->data = input;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode; // There are 2 cases. But since newNode will be NULL if malloc fail, we can still return newNode. 
}

//===========================================================================================
// insert()
// 
// PURPOSE: To insert a new created Node into the list (Node is created by create())
// INPUT PARAMETER :
//      newNode             the newNode's memory address from create()
//                          (or NULL if failed to create)
// OUTPUT PARAMETER :
//      FAILED (0)          Failed to insert (newNode == NULL)
//      SUCCESS (1)         Success to insert into the list  
//===========================================================================================  
Boolean insert(Node * newNode){
    // assert(newNode); // While running testInsert(), it will make an assert error 
    if (!newNode){
        return FAILED; // 0 = failed
    }

    // CASE 1 [IF]      : Empty List
    // CASE 2 [ELSE]    : At least one element in the list
    assert(newNode);
    if (listCount == 0){
        assert(listCount == 0);
        assert(!head);
        assert(!tail);
        head = newNode;
        tail = newNode;
    } else {
        assert(listCount >= 1);
        assert(head);
        assert(tail);
        newNode->prev = tail;
        newNode->prev->next = newNode;
        tail = newNode;
    }
    listCount++;
    return SUCCESS; // 1 = success;
}

//===========================================================================================
// search()
// 
// PURPOSE: To search the corresponding Node inside the list by the key
// INPUT PARAMETER :
//      key                 the data of that Node
// OUTPUT PARAMETER :
//      NULL                Not found
//      curr                The address of the Node matching the key
//===========================================================================================
Node * search(int key){
    Node * curr = head;

    // CASE 1 [IF]                          : EMPTY LIST CASE
    // CASE 2 [ELSE IF]                     : ONE-ELEMENT CASE
    // CASE 3 [ELSE][INSIDE WHILE LOOP]     : NORMAL CASE - FOUND
    // CASE 4 [ELSE][AFTER WHILE LOOP]      : NORMAL CASE - NOT FOUND
    if (listCount == 0){
        return NULL; // not use FAILED here to prevent risks
    } else if (listCount == 1){
        return curr; // curr == head
    } else {
        assert(listCount >= 2); // to prevent risks of negative integers.
        while (curr){
            if (curr->data == key){
                return curr;
            }
            curr = curr->next;
        }
        return curr; // curr == NULL here
    }

    assert(listCount >= 0);
    return NULL; // Unexpected error occurs
}

//===========================================================================================
// delete()
// 
// PURPOSE: To delete the target Node
// INPUT PARAMETER :
//      key                 the data of that target Node
// OUTPUT PARAMETER :
//      FAILED (0)          Delete failed (Case 1 - 2) 
//                          1 - Empty List
//                          2 - Not Found the node
//      SUCCESS (1)         Delete Success (Case 3 - 6)
//                          3 - Target = head = tail
//                          4 - Target = head ONLY
//                          5 - Target = tail ONLY
//                          6 - Normal Middle Case (head != target & tail != target)
//===========================================================================================
Boolean delete(int key){
    Node * target = search(key);

    // CASE 1 & 2 [IF]      : EMPTY LIST OR NOT FOUND THAT NODE (Delete failed)
    // CASE 3 - 6 [ELSE]    : DELETE SUCCESS
    if (!target){
        return FAILED;
    } else {
        // CASE 3 [IF]          : TARGET IS THE LAST ITEM (head = tail = target)
        // CASE 4 [ELSE IF 1]   : TARGET = HEAD ONLY
        // CASE 5 [ELSE IF 2]   : TARGET = TAIL ONLY
        // CASE 6 [ELSE]        : NORMAL MIDDLE CASE (head != target != tail)
        if (listCount == 1){
            assert(head == target);
            assert(tail == target);
            head = NULL;
            tail = NULL;
        } else if (head == target){
            head = target->next;
            target->next->prev = NULL;
        } else if (tail == target){
            tail = target->prev;
            target->prev->next = NULL;            
        } else {
            assert(target->next != NULL);
            assert(target->prev != NULL);
            target->prev->next = target->next;
            target->next->prev = target->prev;
        }

        target->next = NULL;
        target->prev = NULL;
        listCount--;
        free(target);

        return SUCCESS; 
    }
}

//===========================================================================================
// clear() [version 1.0]
// 
// PURPOSE: To destroy the entire list using delete()
//===========================================================================================
void clear(){
    short retVal = 0;
    while (head){
        retVal = delete(head->data);
        assert(retVal == SUCCESS);
    }
}

//===========================================================================================
// reverse() [version 1.0]
// 
// PURPOSE: This is for practice purpose. In reality, it is not neccessary to do so 
//          for doubly linkedlist.
//===========================================================================================
void reverse(){
    Node * curr = tail;
    int tempCount = listCount;
    int arr[tempCount];
    int i = 0;

    while (curr){
        arr[i++] = curr->data;
        curr = curr->prev;
    }
    
    clear();
    assert(listCount == 0);
    assert(!head && !tail);

    i = 0;
    while (i < tempCount){
        insert(create(arr[i++]));
    }
}


//===========================================================================================
// traForward() [version 1.0]
// 
// PURPOSE: To print all Node's data item in forward order 
//===========================================================================================
void traForward(){
    Node * curr = head;
    printf("Traverse list (Forward direction):\n");
    while (curr){
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

//===========================================================================================
// traBack() [version 1.0]
// 
// PURPOSE: To print all Node's data item in backward order 
//===========================================================================================
void traBack(){
    Node * curr = tail;
    printf("Traverse list (Backward direction):\n");
    while (curr){
        printf("%d ", curr->data);
        curr = curr->prev;
    }
    printf("\n");
}

//===============================================================================
// SCAFFOLDING TEST FUNCTIONS
//===============================================================================

//===========================================================================================
// TEST ROUTINE :
// 1. testCreate        2. testInsert       3. testSearch
// 4. testDelete        5. testClear        6. testReverse
// 7. traForward        8. traBack      
//===========================================================================================
void testCreate(){
    Node * test1 = create(-1);
    Node * test2 = create(99999);
    
    assert(test1);
    assert(test1->data == -1);
    assert(test1->next == NULL);
    assert(test1->prev == NULL);
    
    assert(test2);
    assert(test2->data == 99999);
    assert(test2->next == NULL);
    assert(test2->prev == NULL);
    
    free(test1);
    free(test2);
    test1 = NULL;
    test2 = NULL;
    assert(test1 == NULL);
    assert(test2 == NULL);
}

void testInsert(){
    Node * t1 = create(-1);
    Node * t2 = create(0);

    assert(listCount == 0);
    assert(insert(t1) == SUCCESS);
    assert(listCount == 1);
    assert(tail == t1);
    assert(tail->prev == NULL);
    assert(head == t1);
    assert(head->next == NULL);

    assert(insert(t2) == SUCCESS);
    assert(listCount == 2);
    assert(tail == t2);
    assert(tail->prev == t1);
    assert(tail->prev->next == t2);
    assert(tail->prev->prev == NULL);
    assert(head == t1);
    assert(head->next == t2);
    assert(head->next->prev == t1);
    assert(head->next->next == NULL);

    assert(insert(NULL) == FAILED);
}

void testSearch(){
    Node * test = NULL;

    test = search(-1);
    assert(test != NULL);
    assert(test->data == -1);

    test = search(0);
    assert(test != NULL);
    assert(test->data == 0);

    test = search(1);
    assert(test == NULL);
}

void testDelete(){
    Node * t1 = NULL;
    Node * t2 = NULL;
    Node * target = NULL;
    assert( insert(create(2)) == SUCCESS );
    assert( insert(create(4)) == SUCCESS );

    // List : -1 0 2 4
    assert( delete(999) == FAILED );

    // List : -1 0 2 4
    t1 = search(0);
    t2 = search(4);
    target = search(2);
    assert( t1 && t2 && target ); // in case of risks
    assert( t1->next == target ); // Before deletion
    assert( t2->prev == target ); // Before deletion
    assert( delete(2) == SUCCESS );
    assert( t1->next == t2 ); // After deletion
    assert( t2->prev == t1 ); // After deletion

    // List : -1 0 4
    t1 = search(0);
    target = search(4);
    assert( t1 && target );
    assert( t1->next == target );   // Before deletion
    assert( tail = target );        // Before deletion 
    assert( delete(4) == SUCCESS );
    assert( t1->next == NULL );     // After deletion
    assert( tail = t1 );            // After deletion

    // List : -1 0
    t1 = search(0);
    target = search(-1);
    assert( t1 && target );
    assert( t1->prev == target );   // Before deletion
    assert( head = target );        // Before deletion 
    assert( delete(-1) == SUCCESS );
    assert( t1->prev == NULL );     // After deletion
    assert( head = t1 );            // After deletion

    // List : 0
    target = search(0);
    assert( target );
    assert( target->next == NULL && target->prev == NULL); // Double check
    assert( head == target );       // Before deletion
    assert( tail == target );       // Before deletion 
    assert( delete(-1) == SUCCESS ); 
    assert( head == NULL );         // After deletion
    assert( tail == NULL );         // After deletion

    // Empty List
    assert( delete(1) == FAILED );
    assert( head == NULL );         // Double check
    assert( tail == NULL );         // Double check
    
}

void testClear(){
    insert(create(999));
    insert(create(123));
    assert(head);
    assert(tail);
    clear();
    assert(head == NULL);
    assert(tail == NULL);
}

void testReverse(){
    insert(create(1));
    insert(create(2));
    insert(create(3));
    insert(create(4));
    insert(create(5));
    insert(create(6));
    
    assert(head->data == 1);
    assert(tail->data == 6);

    reverse();

    assert(head->data == 6);
    assert(tail->data == 1);   
}

