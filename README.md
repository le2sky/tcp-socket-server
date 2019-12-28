# Tcp-Socket-Server Project

<img src="./img/tcp-socket-project.png">

1. I worked in a **WSL(Windows Subsystem for Linux) Ubuntu 18.04 environment**. and I edited with **Visual Studio code Editor**.<br>
2. **It was a my university class**, then i wanna remember how to make socket server with c-lang<br>
3. but it is a reallllllly simple socket server, so I think, It is working in only local network -> ***maybe will wrong thing*** <br>
<br>

**Before proceeding**, we need some conditions on the command line.

- telnet
- gcc

`$ apt install telnet ` <br>
`$ apt install gcc `

## 1. tcp_echo_server.c
***On the server side,***
 - **First**, compile the file into an object file.<br>
`$ gcc -o tcp_echo_server tcp_echo_server.c`

 - **Second**, Run the executable file.<br>
`$ ./tcp_echo_server`
<br>

***On the client side,***
 - **First**, Try to connect via telnet. In this source, port is 9000
 - If you wanna connect locally, the IP address is **localhost** <br>
`$ telnet IPaddr PORT`

 - **Second**, Enter any word <br>
 - The server reprints the words entered by the client.<br>
`$ anyword`

***If you  fail to connect, suspect the following :***
 - source
 - firewall
 - Socket Status <br> 
 `netstat -ant | grep PORT`
 - faith

**So, if we can output words entered by one client to another client, we can implement a chat server**. <br>
 - However, This source is structurally impossible to multiprocess.
 - To create a chat server, multiple clients need to connect at the same time.
 - In other words, multiprocessing should be possible.
 - Multiprocessing with `fork()` and Multithreading with **pthread** make this possible.
 
 **So, this project will build a chat server after implementing multiprocessing and multithreading**<br>
 (Yes! That's the ultimate goal of this project)
 
## 2. tcp_echo_fork_server.c

***On the server side,***
 - **First**, compile the file into an object file.<br>
`$ gcc -o tcp_echo_fork_server tcp_echo_fork_server.c`

 - **Second**, Run the executable file.<br>
`$ ./tcp_echo_fork_server`
<br>

***On the client side,***
 - you can do as you did in the tcp_echo_server.c file.
<br>

#### what is `fork()` ?
- ***In short, the fork () function duplicates the current process.*** (Register, stack, code, data, heap, resources, etc.)
- `fork()` return value is **zero** for the child process and **pid value of the child process** for the parent process. 
- In other words, **we define the behavior of the parent and child separately**, depending on the return value of fork.
- So the **parent process accepts the connection**, clones the process, and then the **child process handles the logic.**
- Now we have implemented multiprocessing using `fork()`
<hr>

## 3. tcp_echo_thread_server.c
***On the server side,***
 - **First**, compile the file into an object file.<br>
`$ gcc -o tcp_echo_thread_server tcp_echo_thread_server.c -lpthread`

 - **Second**, Run the executable file.<br>
`$ ./tcp_echo_thread_server`
<br>

***On the client side,***
 - you can do as you did in the tcp_echo_server.c file.
<br>

#### what is thread?
 - **Threads are a lightweight process** and can be parallelized as fork() does.
 - It is lightweight process in functions unit.
 - In other words, **a minimal environment (stack, register)** is required to execute a function independently.
 - Instead of copying all process resources like fork(), **it only copies a specific area** (contextually a minimal environment).
 - Thus, except for certain areas, **the process resources are shared by all threads.**
   - It is less expensive than copying all process resources.

### final, chat_server.c

