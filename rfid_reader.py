# rfid_reader.py
from mfrc522 import SimpleMFRC522
import RPi.GPIO as GPIO
import time

reader = SimpleMFRC522()

try:
    print("Place your RFID card/tag near the reader...")
    while True:
        id, text = reader.read()
        print(f"Card detected! UID: {id}")
        print(f"Data: {text}")
        
        # You can add access logic
        if id == 1234567890:   # Replace with your card's UID
            print("✅ Access Granted")
            # e.g., trigger servo here
        else:
            print("❌ Access Denied")

        time.sleep(2)  # small delay before next read
except KeyboardInterrupt:
    GPIO.cleanup()
    print("Exiting...")
