void a(int x) {
    b(x);
}

void b(int x) {
    c(x);
}

void c(int x) {
    int y = nondet_int();
    
    if ( y < 10 ) {
        f(x);
    } else {
        e(x);
    }
}

void d(int x) {
    e(x);
}

void e (int x) {
    f(x);
}

void f(int x) {
    _Learn_assert(x <= 10);
}

int main() {
  a(x);
  b(x);  
}