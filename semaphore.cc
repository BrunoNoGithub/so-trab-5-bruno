#include "semaphore.h"
#include "thread.h"

__BEGIN_API

//Como eu consigo a thread que chamou o wait do semáforo, 
// Se ele deu wait quer dizer que podemos pegar o running para dar sleep?

// wait
    

void Semaphore::p() {
    // Checar se o num de licenças é > 0, se sim decrementar com
    // fdec e continuar execução (retornar (?))
    // Se não dar sleep na thread
    if (license_num > 0) {
        fdec(license_num);
    } else {
        sleep();
    }
}

// post
void Semaphore::v() {
    Thread* first_thread = Thread::get_first_waiting();

    if (first_thread) {
        wakeup(first_thread);
    } else {
        finc(license_num);
    }
    
    // Checar se existe threads na lista de threads esperando
    // Se sim dar wake na primeira thread da fila
    // Se não incrementar o num de licenças com finc
}

int Semaphore::finc(volatile int & number) {
    // Implementar incremento atômico (ver pdf)
    int value = 1;
    int numb=number;
    asm("xadd %0, %2" : "=a" (number) : "a" (number), "b" (value));
}

int Semaphore::fdec(volatile int & number) {
    // Implementar decremento atômico (ver pdf)
    int value = -1;
    asm("xadd %0, %2" : "=a" (number) : "a" (number), "b" (value));
}

void Semaphore::sleep() {
    Thread* running = Thread::running();
    running->sleep();
    // Implementar thread sleep
    // Trocar status da thread para waiting e colocar thread na 
    // fila de threads esperando
}

void Semaphore::wakeup(Thread* wakeup_thread) {
    wakeup_thread->wakeup();
    // Implementar thread wakeup
    // "Acordar" a thread, resumir sua execução
    // Por enquanto não tem muita utilidade a não ser realizar a chamada para wakeup da thread
}

void Semaphore::wakeup_all() {
    //Implementar thread wakeup_all
    // Acordar todas as threads -- Quando vamos fazer isso?
    Thread::wakeup_all();
}

Semaphore::Semaphore(int v){
    license_num = v;
    // O que mais precisa ser inicializado?    
}

Semaphore::~Semaphore() {
    // A princípio não temos nada a desalocar...
}

__END_API