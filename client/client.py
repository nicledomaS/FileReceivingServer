import socket
import struct
import argparse
import os
import crc32c
import random
import hashlib

serverAddressPort   = ("127.0.0.1", 5000)

headerSize = 20
dataSize = 1452
bufferSize = headerSize + 4

headerFormat = "II8sBxxx"


parser = argparse.ArgumentParser()
parser.add_argument("-f", dest="file", help="Origin input file", required=True)
args = parser.parse_args()

if args.file:
    file_size = os.stat(args.file)

    part_size = file_size.st_size // dataSize
    t = file_size.st_size % dataSize
    if t > 0:
        part_size += 1

    print("Part num: {}".format(part_size))

    if part_size == 0:
        quit()
    
    file = open(args.file, 'rb')

    count = 0
    crc = 0

    packets = []

    hashid = hashlib.sha256(args.file.encode('utf-8')).digest()[:8]

    while count < part_size:
        data = file.read(dataSize)
        crc = crc32c.crc32c(data, crc)
        
        inFormat = "{}{}s".format(headerFormat, len(data))
        packet = struct.pack(inFormat, count, part_size, hashid, 1, data)
        packets.append(packet)
        count += 1
    
    random.shuffle(packets)

    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    for packet in packets:
        UDPClientSocket.sendto(packet, serverAddressPort)
        msgFromServer = UDPClientSocket.recvfrom(bufferSize)
        outFormat = "{}I".format(headerFormat)
        response = struct.unpack(outFormat, msgFromServer[0])

        
        if response[0] == part_size:
            print("CRC real: {}".format(crc))
            print("CRC received: {}".format(response[4]))
            if crc == response[4]:
                print("Crc good")
            else:
                print("Crc bad")
            break

