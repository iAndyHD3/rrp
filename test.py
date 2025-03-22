import random
import requests
import base64
import rrp

def xor_cipher(text: str, key: str) -> str:
    """
    XOR cipher function: Encrypts or decrypts a text using a key.
    """
    return ''.join(
        chr(ord(char) ^ ord(key[i % len(key)])) for i, char in enumerate(text)
    )


def generate_chk() -> str:
    """
    Generates the 'chk' parameter by combining a random string and 
    an XOR-ciphered, base64-encoded random integer.
    """
    random_string = ''.join(random.choice("1234567890qwertyuiopaqsdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") for _ in range(5))
    random_number = str(random.randint(10000, 1000000))
    xor_ciphered = xor_cipher(random_number, "59182")
    encoded = base64.b64encode(xor_ciphered.encode()).decode()
    return random_string + encoded


def decode_response(response_text: str) -> str:
    """
    Decodes the response text from the server.
    """
    try:
        encoded_part = response_text.split("|")[0][5:]
        decoded_part = base64.urlsafe_b64decode(encoded_part.encode()).decode()
        return xor_cipher(decoded_part, "59182")
    except Exception:
        return response_text




#13: demon keys
#12: orbs
#7: chess type