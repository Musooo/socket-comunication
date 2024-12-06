# Socket Communication Program

This project demonstrates a simple client-server communication using sockets in C. The client sends a message containing a name and age to the server, and the server responds with a greeting message.

## Prerequisites

- GCC compiler
- Make

## Files

- `client.c`: The client program
- `server.c`: The server program
- `Makefile`: The makefile to build the programs

## Build the Programs

To compile the client and server programs, run the following command in the project directory:

```sh
make
```

This will generate the executables `client` and `server`.

## Running the Programs

### Start the Server

First, start the server by running:

```sh
make run_server
```

The server will start and listen for incoming connections on port `20002`.

### Run the Client

In a separate terminal, run the client with the following command:

```sh
make run_client ARGS="<name> <age>"
```

Replace `<name>` with the name you want to send and `<age>` with the age. For example:

```sh
make run_client ARGS="Alice 30"
```

The client will send the message to the server, and the server will respond with a greeting message.

## Clean Up

To clean up the compiled files, run:

```sh
make clean
```

This will remove the generated object files and executables.

## License

This project is licensed under the MIT License.