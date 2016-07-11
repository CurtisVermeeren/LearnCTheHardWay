// if in definition skips code if already defined.
#ifndef _object_h
#define _object_h

typedef enum{
    NORTH,SOUTH,EAST,WEST
} Direction;

typedef struct{
    char *description;
    int (*init)(void *self);
    void (*describe)(void *self);
    void (*destroy)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

//Declare functions 
int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

// Creates a macro
// T and N are parameted injected into the code on the right
// Syntax T##Proto says "concat Proto at the end of T."
#define NEW(T,N) Object_new(sizeof(T), T##Proto, N)

//"Syntactic sugar"
// Example:
// Allows you to write obj->proto.blah as obj-> _(blah)
#define _(N) proto.N


#endif
