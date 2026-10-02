#ifndef CONTACT_H
#define CONTACT_H

#define NAME_LEN 50
#define PHONE_LEN 20

typedef struct
{
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int age;
}Contact;

#endif