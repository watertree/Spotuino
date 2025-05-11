import spotipy
import time
import serial
from spotipy.oauth2 import SpotifyOAuth

# Load credentials
with open('credentials.txt', 'r') as file:
    client_id = file.readline().strip()
    client_secret = file.readline().strip()

redirect_uri = "https://example.org/callback"

# Set up Spotipy with correct scope
sp = spotipy.Spotify(auth_manager=SpotifyOAuth(
    client_id=client_id,
    client_secret=client_secret,
    redirect_uri=redirect_uri,
    scope="user-read-playback-state user-modify-playback-state streaming"))

# Setup serial connection (adjust COM port or /dev/ttyACM0 as needed)
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
time.sleep(2)  # Give Arduino time to reset after opening port

print("Listening for Spotuino commands...")

while True:
    try:
        if ser.in_waiting:
            cmd = ser.readline().decode().strip().lower()
            print(f"Received: {cmd}")

            if cmd == "play_pause":
                playback = sp.current_playback()
                if playback and playback['is_playing']:
                    sp.pause_playback()
                    print("Paused")
                else:
                    sp.start_playback()
                    print("Started")
            elif cmd == "forward":
                sp.next_track()
                print("Next track")
            elif cmd == "back":
                sp.previous_track()
                print("Previous track")
            else:
                print("Unknown command")

    except KeyboardInterrupt:
        print("\nExiting...")
        break
