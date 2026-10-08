# Minitalk

A small client-server program written in C that sends messages between two processes using Unix signals.

The client encodes the message and sends it to the server bit by bit using `SIGUSR1` and `SIGUSR2`. The server reconstructs the message and prints it.

## How it works

The client receives a server PID and a message:

```bash
./client <server_pid> <message>
```

The server prints its PID when started:

```bash
./server
```

The message length is sent first, followed by the individual characters.

## Build

```bash
make
```

For the bonus version:

```bash
make bonus
```

## Technologies

* C
* Unix signals
* Processes
* Dynamic memory allocation
* Make

