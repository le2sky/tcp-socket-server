# Tcp-Socket-Server
1. I worked in a **WSL(Windows Subsystem for Linux) Ubuntu 18.04 environment**. and I edited with **Visual Studio code Editor**.<br>
2. **It was a my university class**, then i wanna remember how to make socket server with c-lang<br>
3. but it is a reallllllly simple socket server, so I think, It is working in only local network -> ***maybe will wrong thing*** <br>
<br>

**Before proceeding**, we need some conditions on the command line.

- telnet
- gcc

`$ apt install telnet ` <br>
`$ apt install gcc `

## 1. tcp-echo-server.c ##
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
 
