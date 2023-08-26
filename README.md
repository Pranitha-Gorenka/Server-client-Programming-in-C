# Server-client-Programming-in-C

repository contains a collection of C programs that showcase various computational algorithms. Each program serves a different purpose and is designed to demonstrate specific algorithms and techniques. Here's a brief overview of the programs available in this repository:

Server.c
The server.c program implements a server that listens for incoming client connections. It uses sockets to establish communication with clients. Upon receiving a client command, it performs specific actions based on the command. The supported commands include running matrix inversion and k-means clustering algorithms in parallel.

Client.c
The client.c program acts as a client that connects to the server. It communicates with the server by sending commands to request the execution of specific algorithms. After receiving results from the server, it displays the output. The supported commands include requesting matrix inversion and k-means clustering computations.

Matrix.c
The matrix.c program demonstrates the sequential computation of matrix inversion. It reads input data and calculates the inverse of a given matrix using Gaussian elimination. The program also provides options to customize the matrix size, initialization type, and other parameters.

KMeans.c
The kmeans.c program showcases the k-means clustering algorithm. It reads data points from a file and clusters them into specified groups. The number of clusters (k) and other parameters can be configured to tailor the algorithm's behavior.

Each program includes comments to explain the code's functionality and usage. To compile and run these programs, make sure you have a C compiler installed on your system.

**output**
$ ./client -ip 127.0.0.1 -p 9999
Connected to server
Enter a command for the server: matinvpar -n 8 -I fast -P 1
Received the solution: matinv_client1_soln1.txt
Enter a command for the server: matinvpar -n 2048 -I rand -P 1
Received the solution: matinv_client1_soln2.txt
Enter a command for the server: kmeanspar -f kmeans-data.txt -k 9
Received the solution: kmeans_client1_soln1.txt

Meanwhile the command line of the server will look as follows.
$ ./server 9999
Listening for clients...
Connected with client 1
Client 1 commanded: matinvpar -n 8 -I fast -P 1
Sending solution: matinv_client1_soln1.txt
Client 1 commanded: matinvpar -n 2048 -I rand -P 1
Sending solution: matinv_client1_soln2.txt
Client 1 commanded: kmeanspar -f kmeans-data.txt -k 9
Sending solution: kmeans_client1_soln1.txt

