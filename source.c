#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Creating the struct
struct Student
{
    char name[50];
    char gender;
    struct Student *next;
};
struct Student *insertNode(char *name, char gender, struct Student *list)
{
    struct Student *s;
    // Allocate memory for node (malloc operation)
    s = malloc(sizeof(struct Student));
    if (s == NULL)
    {
        printf("Memory allocation failed.");
        return list;
    }
    strcpy(s->name, name);
    s->gender = gender;
    s->next = list; // list is the start of the list
    list = s;

    return list;
}

// Sorting function
struct Student *sortList(struct Student *list)
{
    // sort Nodes in the correct order except for the head.
    struct Student *iter;
    struct Student *outerIter = list;
    while (outerIter != NULL)
    {
        iter = list;
        while (iter->next->next != NULL)
        {
            // there are three cases need to be swap to sort.
            // case1: swap if there are Male before Female in the list.
            // case2: swap if there are lower order Male name before another Male.
            // case3: swap if there are higher order Female name before another Female.
            if (
                (iter->next->gender == 'M' && iter->next->next->gender == 'F') || (iter->next->gender == 'M' && iter->next->next->gender == 'M' && strcmp(iter->next->name, iter->next->next->name) < 0) || (iter->next->gender == 'F' && iter->next->next->gender == 'F' && strcmp(iter->next->name, iter->next->next->name) > 0))
            {
                struct Student *temp = iter->next;
                struct Student *temp2 = iter->next->next->next;
                iter->next = iter->next->next;
                iter->next->next = temp;
                temp->next = temp2;
            }
            iter = iter->next;
        }
        outerIter = outerIter->next;
    } // end of the sort Nodes.

    // it iterates to check if there are any Female for case 4 below.
    struct Student *checkIter = list;
    int areAnyFemale = 0; // it represents false
    while (checkIter != NULL)
    {
        if (checkIter->gender == 'F')
        {
            areAnyFemale = 1; // it represents true;
            break;
        }
        checkIter = checkIter->next;
    }
    // it checks four cases which head is in the right place already.
    // case1: head is lower order Female to next Node that is Female too.
    // case2: head is higher order Male to next Node that is Male too.
    // case3: next of head node is Male while head is Female.
    // case4: there are not any Female and head is higher order Male to next Node that is Male too.
    if (
        (list->gender == 'F' && list->gender == 'F' && strcmp(list->name, list->next->name) <= 0) || (list->gender == 'M' && list->next->gender == 'M' && strcmp(list->name, list->next->name) >= 0) || (list->gender == 'F' && list->next->gender == 'M') || (list->gender == 'M' && areAnyFemale == 0 && strcmp(list->name, list->next->name) > 0))
    {
        return list;
    } // end of the check if head is at right place.

    // it determines where the head should be.
    // there are 5 cases need to be checked to put head.
    struct Student *headCheck = list->next;
    while (headCheck != NULL)
    {
        // case1: find right plcae for head at M - M - M situation.
        // case2: find right place for head at F - M - M situation.
        // case3: find right place for head at F - F - F situation.
        // case4: find right place for head at F - F - M situation.
        if (
            (list->gender == 'M' && headCheck->next->gender == 'M' && headCheck->gender == 'M' && strcmp(list->name, headCheck->name) < 0 && strcmp(list->name, headCheck->next->name) > 0) || (list->gender == 'M' && headCheck->next->gender == 'M' && headCheck->gender == 'F' && strcmp(list->name, headCheck->next->name) > 0) || (list->gender == 'F' && headCheck->gender == 'F' && headCheck->next->gender == 'F' && strcmp(list->name, headCheck->name) > 0 && strcmp(list->name, headCheck->next->name) < 0) || (list->gender == 'F' && headCheck->gender == 'F' && headCheck->next->gender == 'M' && strcmp(list->name, headCheck->name) > 0))
        {
            struct Student *tempHead = list->next;
            struct Student *temp = headCheck->next;
            headCheck->next = list;
            headCheck->next->next = temp;
            return tempHead;
        }

        headCheck = headCheck->next;
        // case5: if it is not four case above that is mean the head should be linked after last Node.
        if (headCheck->next == NULL)
        {
            struct Student *temp = list->next;
            headCheck->next = list;
            list->next = NULL;
            return temp;
        }
    } // end of the find right places for head.
}
// Printing function
void printList(struct Student *list)
{
    while (list != NULL)
    {
        printf("%s\t%c\n", list->name, list->gender);
        list = list->next;
    }
}
int main()
{
    // Creating an Initial Node Variable
    struct Student *head = NULL;
    // Call to functions
    head = insertNode("Cenk", 'M', head);
    head = insertNode("Ceyda", 'F', head);
    head = insertNode("Esra", 'F', head);
    head = insertNode("Okan", 'M', head);
    head = insertNode("Tugce", 'F', head);
    head = insertNode("Mehmet", 'M', head);
    head = insertNode("Ayse", 'F', head);
    head = insertNode("Merve", 'F', head);
    head = insertNode("Sedat", 'M', head);
    head = insertNode("Ahmet", 'M', head);

    // call to sorting function
    head = sortList(head);
    printList(head);
}
