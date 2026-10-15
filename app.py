import time
import threading
from flask import Flask, render_template, jsonify
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app)

# Simulated sensor state (Replace this with actual Arduino Bridge RPC calls)
sensor_data = {
    "humidity": "75.8",
    "temperature": "33.2"
}
actuator_state = False

def background_sensor_loop():
    """Background thread to fetch data from the MCU via Arduino Bridge and push via WebSockets"""
    while True:
        # TODO: Replace with real Arduino Bridge RPC read logic from your MCU
        sensor_data = {
            "humidity": bridge.get("humidity"),
            "temperature": bridge.get("temperature")
        }       
        socketio.emit('update_sensors', sensor_data)
        socketio.sleep(2) # Update every 2 seconds

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/toggle', methods=['POST'])
def toggle():
    global actuator_state
    actuator_state = not actuator_state
    # TODO: Send command down to MCU via Arduino Bridge to flip physical pin state
    
    status_str = "ON" if actuator_state else "OFF"
    return jsonify({"status": status_str})

if __name__ == '__main__':
    # Start background thread for sensor streaming
    socketio.start_background_task(background_sensor_loop)
    # Run server on port 8080 to match your screenshot
    socketio.run(app, host='0.0.0.0', port=8080, debug=True)
