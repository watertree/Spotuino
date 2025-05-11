import serial
import time

tracklist = [
    "Ambitionz Az a Ridah",
    "All Bout U",
    "Skandalouz",
    "Got My Mind Made Up",
    "How Do U Want It",
    "2 of Amerikaz Most Wanted",
    "No More Pain",
    "Heartz of Men",
    "Life Goes On",
    "Only God Can Judge Me",
    "Tradin' War Stories",
    "California Love",
    "I Ain't Mad at Cha",
    "What'z Ya Phone #"
]

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
time.sleep(2)

index = None
is_playing = False

def send_status():
    if index is None:
        track = "No track loaded"
    else:
        track = tracklist[index]
    state = "play" if is_playing else "pause"
    # Format: "<state>|<track>"
    ser.write(f"{state}|{track[:32]}\n".encode())
    print(f"Sent to Arduino: {state} | {track}")

print("Simulated Spotuino ready...")

while True:
    try:
        if ser.in_waiting:
            cmd = ser.readline().decode().strip().lower()
            print(f"Received: {cmd}")

            if cmd == "play_pause":
                if index is None:
                    index = 0
                    is_playing = False
                else:
                    is_playing = not is_playing

            elif cmd == "forward":
                if index is not None:
                    index = (index + 1) % len(tracklist)
                    is_playing = False

            elif cmd == "back":
                if index is not None:
                    index = (index - 1) % len(tracklist)
                    is_playing = False

            else:
                print("(Unknown command)")
                continue

            time.sleep(0.2)
            send_status()

    except KeyboardInterrupt:
        print("\nExiting.")
        break
