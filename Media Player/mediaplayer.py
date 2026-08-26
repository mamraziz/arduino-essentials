import serial
import time
import pyautogui
import win32gui
import win32process
import psutil

ARDUINO_PORT = 'COM11'

try:
    ser = serial.Serial(ARDUINO_PORT, 9600, timeout=1)
    time.sleep(2)
    print(f"✅ Connected to Arduino on {ARDUINO_PORT}")
except Exception as e:
    print(f"❌ Error connecting: {e}")
    exit()

last_command_time = 0
debounce_ms = 500

def clean_title(title):
    """Clean up the title to extract just the song name"""
    if not title:
        return "Not found"
    
    # Remove browser/player suffixes
    suffixes = [
        ' - Google Chrome', ' - Mozilla Firefox', ' - Microsoft Edge', 
        ' - YouTube', ' - Spotify', ' - VLC media player', ' - Music',
        ' - Feishin', ' - Navidrome'
    ]
    for suffix in suffixes:
        if title.endswith(suffix):
            title = title[:-len(suffix)]
    
    # Handle YouTube special case
    if ' - YouTube' in title:
        title = title.split(' - YouTube')[0]
    
    # METHOD 1: Split on " | " (space pipe space) - most common separator
    if ' | ' in title:
        title = title.split(' | ')[0].strip()
    
    # METHOD 2: Split on " - " (space dash space) - common separator
    if ' - ' in title:
        parts = title.split(' - ')
        # Take the first part as the song title
        title = parts[0].strip()
    
    # METHOD 3: Split on " – " (space en dash space)
    if ' – ' in title:
        title = title.split(' – ')[0].strip()
    
    # METHOD 4: Split on "—" (em dash)
    if '—' in title:
        title = title.split('—')[0].strip()
    
    # Remove "Feishin" if it's still there
    title = title.replace('Feishin', '').strip()
    title = title.replace('feishin', '').strip()
    
    # Remove trailing dashes or pipes
    title = title.rstrip('| -–—')
    title = title.strip()
    
    # If it's empty, return "Not found"
    if not title:
        return "Not found"
    
    return title

def get_track_info():
    try:
        hwnd = win32gui.GetForegroundWindow()
        window_title = win32gui.GetWindowText(hwnd)
        
        _, pid = win32process.GetWindowThreadProcessId(hwnd)
        process = psutil.Process(pid)
        process_name = process.name().lower()
        
        media_apps = ['chrome', 'firefox', 'edge', 'spotify', 'vlc', 'windowsmediaplayer', 
                     'winamp', 'music', 'itunes', 'feishin', 'navidrome', 'subsonic']
        
        is_media = any(app in process_name for app in media_apps)
        
        if not is_media:
            return "Not found"
        
        if not window_title:
            return "Not found"
        
        # Debug: print what we received
        print(f"🔍 Raw title: '{window_title}'")
        
        cleaned = clean_title(window_title)
        print(f"✨ Cleaned: '{cleaned}'")
        
        return cleaned
        
    except Exception as e:
        print(f"Error getting track info: {e}")
        return "Not found"

def send_media_command(cmd):
    global last_command_time
    
    current_time = time.time() * 1000
    if current_time - last_command_time < debounce_ms:
        print("⏱️ Too fast!")
        return
    last_command_time = current_time
    
    try:
        if cmd == 'b':
            pyautogui.press('prevtrack')
            print("⏮ Previous")
        elif cmd == 'p':
            pyautogui.press('playpause')
            print("⏯ Play/Pause")
        elif cmd == 'f':
            pyautogui.press('nexttrack')
            print("⏭ Next")
        
        time.sleep(0.3)
        
        track = get_track_info()
        print(f"🎵 {track}")
        
        ser.write(f"{track}\n".encode())
        
    except Exception as e:
        print(f"Error: {e}")

print("\n🎵 Media Controller Running")
print("Press Ctrl+C to exit\n")

last_cmd = ""
try:
    while True:
        if ser.in_waiting > 0:
            cmd = ser.readline().decode('utf-8').strip()
            
            if cmd in ['b', 'p', 'f'] and cmd != last_cmd:
                last_cmd = cmd
                send_media_command(cmd)
            time.sleep(0.1)
            last_cmd = ""
        time.sleep(0.01)

except KeyboardInterrupt:
    print("\nExiting...")
    ser.close()
