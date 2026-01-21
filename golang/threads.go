package main

import "fmt"
import "time"

/*
   #define _GNU_SOURCE
   #include <stdio.h>
   #include <unistd.h>
   #include <stdint.h>
   #include <pthread.h>
   #define NUM 5
   #define CNT 10

   extern void go_cb_print(int n, int c);
   extern void go_cb_callback(uintptr_t ptr);
   extern void go_cb_sleep(void);

   static void callback(void)
   {
   go_cb_sleep();
   }

   static void call0(uintptr_t ptr)
   {
   void (*fff)(void) = (void(*)(void))ptr;
   fff();
   }

   static void *foo(void *arg)
   {
   int *p = arg;
   char name[128];

   snprintf(name, 128, "XXX-%d", *p);

	pthread_setname_np(pthread_self(), name);
   for (int i=0;i<CNT;++i)
   {
   go_cb_print(*p, i);
   go_cb_callback((uintptr_t)callback);
   }
   return 0;
   }

   static void run_threads()
   {
   pthread_t threads[NUM];
   int data[NUM];

   for(int i=0;i<NUM;++i)
   {
   int status;
   data[i] = i;
   status = pthread_create(threads+i, NULL, foo, data+i);
   }


   for (int i=0;i<NUM;++i)
   {
   pthread_join(threads[i], NULL);
   }
   }
 */
import "C"

func main() {
	fmt.Println("Hello")
	C.run_threads()
}

//export go_cb_print
func go_cb_print(n C.int, c C.int) {
	fmt.Println("n=", n, "c=",c)

	if n == 3 && c == 2 {
		time.Sleep(time.Duration(10) * time.Second)
	}
}

//export go_cb_callback
func go_cb_callback(ptr C.uintptr_t) {
	C.call0(ptr);
}

//export go_cb_sleep
func go_cb_sleep() {
		time.Sleep(time.Duration(1) * time.Second)
}
