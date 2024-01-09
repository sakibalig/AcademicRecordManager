#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int roll;
    char firstname[20];
    char lastname[20];
    float cgpa;
    struct student *next;
};

struct student *slist = NULL;

// Function to insert a student in ascending order of roll number
struct student *insert_asc(struct student *r, int t1, const char t2[], const char t3[], float t4)
{
    struct student *p, *q, *nw;
    nw = (struct student *)malloc(sizeof(struct student));

    nw->roll = t1;
    strcpy(nw->firstname, t2);
    strcpy(nw->lastname, t3);
    nw->cgpa = t4;
    nw->next = NULL;

    p = r;
    q = p;

    while (p != NULL)
    {
        if (p->roll >= t1)
        {
            if (p == r)
            {
                nw->next = r;
                return nw;
            }
            nw->next = p;
            q->next = nw;
            return r;
        }
        q = p;
        p = p->next;
    }
    if (r == NULL)
        return nw;
    else
        q->next = nw;
    return r;
}

// Function to delete a student by roll number
struct student *delete_roll(struct student *r, int t1)
{
    struct student *p, *q;
    p = r;
    q = p;

    while (p != NULL)
    {
        if (p->roll == t1)
        {
            if (p == r)
                r = p->next;
            else
                q->next = p->next;
            p->next = NULL;
            free(p);
            return r;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }

    return r;
}

// Function to display all students
void display_students(const struct student *r)
{
    const struct student *p = r;

    while (p != NULL)
    {
        printf("\nRoll no: %d", p->roll);
        printf("\nFirst name: %s", p->firstname);
        printf("\nLast name: %s", p->lastname);
        printf("\nCGPA: %f\n\n", p->cgpa);

        p = p->next;
    }
}

// Function to show statistics
void show_stats(const struct student *r)
{
    const struct student *p = r;
    float min, max, avg = 0;
    int count = 0;

    if (p == NULL)
    {
        printf("\nNo students in the list.\n");
        return;
    }

    min = max = p->cgpa;

    while (p != NULL)
    {
        if (p->cgpa > max)
            max = p->cgpa;

        if (p->cgpa < min)
            min = p->cgpa;

        avg += p->cgpa;
        p = p->next;
        ++count;
    }

    avg /= count;

    printf("\nStudent with minimum CGPA:\n");
    p = r;
    while (p != NULL)
    {
        if (p->cgpa == min)
        {
            printf("Roll no: %d\n", p->roll);
            printf("First name: %s\n", p->firstname);
            printf("Last name: %s\n", p->lastname);
            printf("CGPA: %f\n", p->cgpa);
            break;
        }
        p = p->next;
    }

    printf("\nStudent with maximum CGPA:\n");
    p = r;
    while (p != NULL)
    {
        if (p->cgpa == max)
        {
            printf("Roll no: %d\n", p->roll);
            printf("First name: %s\n", p->firstname);
            printf("Last name: %s\n", p->lastname);
            printf("CGPA: %f\n", p->cgpa);
            break;
        }
        p = p->next;
    }

    printf("\nAverage CGPA: %f\n", avg);
}

// Function to enroll a new student
void enroll_student()
{
    int t1;
    char t2[20], t3[20];
    float t4;

    printf("\nEnter the Roll No: ");
    scanf("%d", &t1);
    printf("\nEnter the first name: ");
    scanf("%s", t2);
    printf("\nEnter the last name: ");
    scanf("%s", t3);
    printf("\nEnter the CGPA: ");
    scanf("%f", &t4);

    slist = insert_asc(slist, t1, t2, t3, t4);
}

// Function to delete a student
void delete_student()
{
    int t1;
    printf("\nEnter the roll no you want to delete: ");
    scanf("%d", &t1);

    slist = delete_roll(slist, t1);
}

int main()
{
    int inp = 1;

    while (inp != 7)
    {
        printf("Menu Choices:");
        printf("\n1: Enter student details");
        printf("\n2: Delete student details");
        printf("\n3: Display student details");
        printf("\n4: Show statistics");
        printf("\n7: Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &inp);

        switch (inp)
        {
        case 1:
            enroll_student();
            break;
        case 2:
            delete_student();
            break;
        case 3:
            display_students(slist);
            break;
        case 4:
            show_stats(slist);
            break;
        case 7:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    // Free the allocated memory before exiting
    struct student *current = slist;
    while (current != NULL)
    {
        struct student *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
