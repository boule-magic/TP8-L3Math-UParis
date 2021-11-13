#include <stdio.h>
#include <stdlib.h>

//Exercice 1 ---------------------------------

typedef struct array {
    int *a;
    int size;
}array;

array* new_array(int n) {
    int* p = calloc(n, n*sizeof(int));
    if(p == NULL) {
	return NULL;
    }
    array* q = malloc(sizeof(array));
    if(q == NULL) {
	free(p);
	return NULL;
    }
    q->a = p;
    q->size = n;
    return q;
}

void destroy_array(array* a) {
    free(a->a);
    free(a);
}

array* read_array(int n) {
    array* a = new_array(n);
    for(int i = 0 ; i < n ; i++) {
	printf("Saisir un entier (%d/%d) : ",i,n);
	scanf("%d",&(a->a[i]));
    }
    return a;
}

void print_array(array* a) {
    printf("[");
    for(int i = 0 ; i < a->size ; i++) {
	printf("%d",a->a[i]);
	if(i!=a->size-1)
	    printf(", ");
    }
    printf("]\n");
}

void print_array_inverse(array* a) {
    printf("[");
    for(int i = a->size-1 ; i >= 0 ; i--) {
	printf("%d",a->a[i]);
	if(i!=a->size-1)
	    printf(", ");
    }
    printf("]\n");
}

//Exercice 2 ---------------------------------

typedef struct buffer {
    int* a;
    int size;
    int cap;
}buffer;

buffer* new_buffer(int cap) {
    int* p = calloc(cap, cap*sizeof(int));
    if(p == NULL) {
	return NULL;
    }
    buffer* q = malloc(sizeof(buffer));
    if(q == NULL) {
	free(p);
	return NULL;
    }
    q->a = p;
    q->size = 0;
    q->cap = cap;
    return q;
}

void destroy_buffer(buffer* s) {
    free(s->a);
    free(s);
}

int extend(buffer* s) {
    int* p;
    if(s->cap > 0) {
        p = malloc(2*s->cap*sizeof(int));
	if(p == NULL) return -1;
	s->cap *= 2;
    }
    else {
	p = malloc(4*sizeof(int));
	if(p == NULL) return -1;
	s->cap = 4;
    }
    for(int i = 0 ; i < s->size ; i++) {
	p[i] = s->a[i];
    } 
    free(s->a);
    s->a = p;
    return 1;
}

int snoc(buffer* s, int v) {
    if(s->size == s->cap) {
	if(extend(s) == -1) return -1;
    }
    (s->size)++;
    s->a[s->size-1] = v;
    return 1;
}

void print_buffer(buffer* a) {
    printf("[");
    for(int i = 0 ; i < a->size ; i++) {
	printf("%d",a->a[i]);
	if(i!=a->size-1)
	    printf(", ");
    }
    printf("]\n");
}

buffer* read_buffer() {
    int input = 0;
    buffer* b = new_buffer(0);
    while(1) {
	printf("Saisir un entier (tant que != -1) : ");
	scanf("%d",&input);
	if(input == -1) return b;
	snoc(b,input);
	if(b == NULL) return b;
	print_buffer(b);
    } 
}

//Exercice 3 ---------------------------------

int empty(buffer* a) {
    if(a->size == 0) return 1;
    else return 0;
}

int push(buffer* a, int v) {
    return snoc(a,v);
}

int pop(buffer* a) {
    if(empty(a)) {	
	abort();
    }
    a->size--;
    return a->a[a->size];
}

//--------------------------------------------

int
main() {

    //Exercice 1
    printf("Exercice 1:\n");
    array* a = new_array(10);
    if(a==NULL) {
	printf("Erreur d'allocation !");
    }
    print_array(a);
    destroy_array(a);

    //Exercice 2
    printf("Exercice 2:\n");
    buffer* b = read_buffer();
    if (b != NULL) {
	print_buffer(b);
	destroy_buffer(b);
    }

    //Exercice 3
    printf("Exercice 3:\n");
    buffer* c = new_buffer(0);
    int ch;
    while ((ch=getchar()) != EOF) {
	if(ch >= '0' && ch <= '9')
	    push(c,ch-'0');
	else if(ch == '.') {
	    if(empty(c))
		printf("La pile est vide !\n");
	    else
		printf("Sommet = %d\n",pop(c));
	}
	else if(ch == ' ' || ch == '\n') {/*rien*/}
	else if(ch == 'q') {
	    destroy_buffer(c);
	    break;
	}
	else if(ch == '+' && c->size >= 2) {
	    push(c,pop(c)+pop(c));
	}
	else if(ch == '-' && c->size >= 2) {
	    // push(c,pop(c)-pop(c));
	    int delta = pop(c)-pop(c);
	    if(delta < 0)
		delta = -delta;
	    push(c,delta);
	}
	else if(ch == '*' && c->size >= 2) {
	    push(c,pop(c)*pop(c));
	}
	else if(ch == '/' && c->size >= 2) {
	    push(c,pop(c)/pop(c));
	}
	else if(ch == '%' && c->size >= 2) {
	    push(c,pop(c)%pop(c));
	}
	else if(ch == '~' && !empty(c)) {
	    push(c,-pop(c));
	}
	else
	    printf("Erreur\n");
    }

    return 0;
}
