import struct
import json

def hex_to_bytes(hex_str):
    """Converts a hexadecimal string to a byte array."""
    byte_arr = bytearray()
    for i in range(0, len(hex_str), 2):
        byte_arr.append(int(hex_str[i:i+2], 16))
    return bytes(byte_arr)

def decode_telemetry_packet(packet_hex):
    """Decodes a binary telemetry packet and returns a JSON string."""
    # Convert the hexadecimal string to a byte array
    packet = hex_to_bytes(packet_hex)

    # Parse the UTC timestamp
    timestamp = "{}-{}-{} {}:{}:{}.{}".format(
        packet[0]+2000, packet[1], packet[2], packet[3], packet[4], packet[5],
        int.from_bytes(packet[6:8], byteorder='big')*1000)

    # Parse the sender and receiver information
    sender_id = packet[8:12].decode('utf-8')
    receiver_id = packet[12:16].decode('utf-8')

    # Parse the service part
    service_part = {}
    service_part['type'] = packet[16]
    service_part['length'] = packet[17]
    service_part['data'] = packet[18:18+service_part['length']]

    # Parse the content part
    content_part = {}
    content_part['type'] = packet[18+service_part['length']]
    content_part['length'] = packet[19+service_part['length']]
    content_part['data'] = packet[20+service_part['length']:20+service_part['length']+content_part['length']]

    # Construct the parsed telemetry data as a dictionary
    telemetry_data = {
        'timestamp': timestamp,
        'sender_id': sender_id,
        'receiver_id': receiver_id,
        'service_part': service_part,
        'content_part': content_part
    }

    # Convert the telemetry data to a JSON string
    return json.dumps(telemetry_data)

# Example telemetry packet in hexadecimal format
packet_hex = '121E18AE03C814D54C414E01B6000F636F6E74656E742D70726F6772616D0A747970650F68656C6C6F2D776F726C64090A0D'

# Decode the telemetry packet and print the output
print(decode_telemetry_packet(packet_hex))
