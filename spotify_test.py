import spotipy
import time
from spotipy.oauth2 import SpotifyOAuth

with open('credentials.txt', 'r') as file:
    client_id = file.readline().strip()
    client_secret = file.readline().strip()

print(client_id)
print()
print(client_secret)

redirect_uri = "https://example.org/callback"

sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id=client_id,
                                              client_secret=client_secret,
                                              redirect_uri=redirect_uri,
                                              scope="user-read-playback-state user-modify-playback-state streaming"))

def get_current_track():
    playback = sp.current_playback()
    if playback and playback.get('item'):
        return playback['item']['name']
    return "Nothing playing"

def handle_command(cmd):
    if cmd == 'play':
        sp.start_playback()
    elif cmd == 'pause':
        sp.pause_playback()
    elif cmd == 'next':
        sp.next_track()
    elif cmd == 'back':
        sp.previous_track()
    elif cmd == 'track':
        print(f"Now playing: {get_current_track()}")
    else:
        print("Unknown command")

print("Commands: play | pause | next | back | track | exit")
while True:
    try:
        cmd = input("Enter command: ").strip().lower()
        if cmd == 'exit':
            break
        handle_command(cmd)
        time.sleep(0.5)
    except KeyboardInterrupt:
        break