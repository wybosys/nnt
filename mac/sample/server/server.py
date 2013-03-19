#!/usr/bin/env python

import socket
from M2Crypto import RSA, BIO
import struct
import time

#connect to server.
h = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
h.connect(("127.0.0.1", 9090))

#receieve accept signal
data = h.recv(8)
if (data == "ACCEPT"):
    print("got ACCEPT")
else:
    print(data)

#send identity
h.sendall(struct.pack('>h', 4))
h.sendall('TEST')

#receieve public key from server
sz = struct.unpack('>h', h.recv(2))[0]
str_pubkey_srv = h.recv(sz)
print("server's pubkey: " + str_pubkey_srv)
bio = BIO.MemoryBuffer(str_pubkey_srv)
rsa_server = RSA.load_pub_key_bio(bio)

#send public key
sec_client = RSA.gen_key(2048, 65537)
bio_pub = BIO.MemoryBuffer()
sec_client.save_pub_key_bio(bio_pub)
str_pub_cli = bio_pub.getvalue()
h.sendall(struct.pack('>h', len(str_pub_cli)))
h.sendall(str_pub_cli)
print("client's pubkey: " + str_pub_cli)

#send command
if (h.recv(7) == 'COMMAND'):
    print("COMMAND AVAILABLE")

# get info
print("Send INFO command to Server: ")
cmd_info = """<?xml version="1.0"?>
<soap:Envelope xmlns:soap="http://www.w3.org/2001/12/soap-envelope" soap:encodingStyle="http://www.w3.org/2001/12/soap-encoding">
<soap:Body xmlns:m="TestSoft">
<m:Info></m:Info>
</soap:Body>
</soap:Envelope>
"""
# encrypt for server.
data = rsa_server.public_encrypt(cmd_info, RSA.pkcs1_padding)
h.sendall(struct.pack('>h', len(data)))
h.sendall(data)
# receieve from server.
sz = struct.unpack('>h', h.recv(2))[0]
recv_info = h.recv(sz)
print("RAW: " + recv_info)
str_info = ""
tlen = 0
while (tlen < len(recv_info)):
    tmp_str = recv_info[tlen: tlen + 256];
    tmp_str = sec_client.private_decrypt(tmp_str, RSA.pkcs1_padding)
    str_info = str_info + tmp_str
    tlen = tlen + 256
print("PLAIN: " + str_info)

h.close()
