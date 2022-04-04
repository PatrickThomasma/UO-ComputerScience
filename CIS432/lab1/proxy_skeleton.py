from socket import *
import sys

# Create a server socket
tcpSerSock = socket(AF_INET, SOCK_STREAM)
#tcpSerSock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
tcpSerPort = 8888
tcpSerSock.bind((sys.argv[1], tcpSerPort))
tcpSerSock.listen(1)

# Fill in start.
# (1) Bind host name and port to server socket
# (2) Start listening 
# Fill in end.

while 1:
    # Start receiving data from the client
    print('Ready to serve...')
    tcpCliSock, addr = tcpSerSock.accept()
    print('Received a connection from:', addr)
    # Fill in start.
    message = tcpCliSock.recv(1024).decode()
    if message.split()[1] == None:
        continue
    if message.split()[1] != '/www.google.com':
        continue
    if message.split()[1] == '/favicon.ico':
        continue
    print(message)
    print(message.split()[1])
    # Fill in end.
    # Decode message (bytes object) into str
    message_to_string = message.decode()
    print(message_to_string)
    # Extract the filename from the given message
    filename = message_to_string.split()[1].partition("/")[2]
    print("filename: " + filename)
    fileExist = "false"
    filetouse = "/" + filename
    print("filetouse: " + filetouse)

    try:
        # Check whether the file exist in the cache
        f = open(filetouse[1:], "rb")
        outputdata = f.readlines()

        fileExist = "true"
        # ProxyServer finds a cache hit and generates a response message
        response_header = "HTTP/1.0 200 OK\r\n"
        entity_header = "Content-Type:text/html\r\n"
        tcpCliSock.send(response_header.encode())
        tcpCliSock.send(entity_header.encode())

        for i in range (0, len(outputdata)):
            tcpCliSock.send(outputdata[i].encode())
        tcpCliSock.send("\r\n".encode())
        tcpCliSock.close()
        f.close()

        # Fill in start.
        # (EC1) Extra Credit: Read bytes from cache file
        # (EC2) Extra Credit: Send bytes to client
        # (EC2) Extra Credit: Close cache file
        # Fill in end.
        print('Read from cache')
    # Error handling for file not found in cache
    except IOError:
        if fileExist == "false":
            c = socket(AF_INET, SOCK_STREAM)
            # Fill in start.
            # (1) Create a socket on the proxy server to the web server
            # Fill in end.
            hostn = filename.replace("www.","",1)
            print(hostn)
            try:
                # Fill in start.
                # (1) Set an appropriate timeout for the web server socket
                # (2) Connect the web server socket to port 80
                # Fill in end.
                c.connect((hostn,80))
                print ("Socket Connected to port 80 of host")

                # Send client's GET request to web server
                get_request = "GET " + '/' + " HTTP/1.0\r\n\r\n"
                # get_request = "GET / HTTP/1.1\r\nHost: " + filename + "\r\n\r\n" --> This should also work
                c.send(get_request.encode())
                recv = c.recv(150000000)

                # Create a file to cache the response from the web server
                tmpFile = open("./" + filename, "wb")
                
                # Fill in start.
                # (1) Get the response from the web server
                # (EC1) Extra Credit: Cache respone message from the web server
                # (2) Send the response message to the client
                # (EC2) Extra Credit: Close the cache
                # (3) Close the socket to the web server
                # Fill in end.
                tmpFile.write(recv)
                print ("saved")
                tcpCliSock.send(recv)
            except:
                print("Illegal request")
        else:
            # Fill in start.
            # (1) Send an HTTP response message for file not found to the client
            # Fill in end.
            status_line = 'HTTP/1.1 404 not found'
            connectionSocket.send(status_line.encode())
            connectionSocket.close()


    # Close the client socket
    tcpCliSock.close()
tcpSerSock.close()
