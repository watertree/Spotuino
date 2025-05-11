import spotipy
import time
import serial
from spotipy.oauth2 import SpotifyOAuth

# Load credentials
with open('credentials.txt', 'r') as file:
    client_id = file.readline().strip()
    client_secret = file.readline().strip()

redirect_uri = "https://example.org/callback"

sp = spotipy.Spotify(auth_manager=SpotifyOAuth(
    client_id=client_id,
    client_secret=client_secret,
    redirect_uri=redirect_uri,
    scope="user-read-playback-state user-modify-playback-state streaming"))

# Setup serial connection (adjust if needed)
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
time.sleep(2)

def get_current_status():
    try:
        playback = sp.current_playback()
        if not playback or not playback.get('item'):
            return "pause|Nothing playing"

        state = "play" if playback['is_playing'] else "pause"
        track = playback['item']['name']
        artist = playback['item']['artists'][0]['name']
        return f"{state}|{track} - {artist}"
    except Exception as e:
        print(f"Error retrieving track: {e}")
        return "pause|Error"

print("Listening for Spotify commands...")

while True:
    try:
        if ser.in_waiting:
            cmd = ser.readline().decode().strip().lower()
            print(f"Received: {cmd}")

            if cmd == "play_pause":
                playback = sp.current_playback()
                if playback and playback.get('is_playing'):
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
                continue

            time.sleep(0.5)  # let Spotify update
            response = get_current_status()
            print(f"Sending: {response}")
            ser.reset_output_buffer()
            time.sleep(0.05)  # brief settle delay
            ser.write((response[:32] + '\n').encode())

    except KeyboardInterrupt:
        print("\nExiting...")
        break
