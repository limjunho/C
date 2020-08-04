import socket

server_port = 23
max_users = 5	    #maximum number of queued connections

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("", server_port))
server_socket.listen(max_users)

print ("Waiting for client on port ",server_port)

while True:
    client_socket, client_address = server_socket.accept()
    print ("connection from ", client_address)
    while True:
        data = client_socket.recv(128)
        if not data:
            break
        print('received :', data)
        sent = client_socket.send("Hello, this is server!".encode('utf-8'))
        if sent == 0:
            print("socket connection broken")
    print("Disconnected")
    client_socket.close()

server_socket.close()
