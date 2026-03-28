import carla 
import math 
import socket 
import sys
import os
from collections import deque


def set_spectator_view(world, vehicle):

    spectator = world.get_spectator()

    transform = vehicle.get_transform()
    location = transform.location
    rotation = transform.rotation

    camera_location = location + carla.Location(
        x=-6 * math.cos(math.radians(rotation.yaw)),
        y=-6 * math.sin(math.radians(rotation.yaw)),
        z=3
    )

    camera_rotation = carla.Rotation(
        pitch=-15,
        yaw=rotation.yaw,
        roll=0
    )

    spectator.set_transform(
        carla.Transform(camera_location, camera_rotation)
    )

def get_vehicle_speed(vehicle):
    """Get current vehicle speed in km/h"""
    velocity = vehicle.get_velocity()
    speed = math.sqrt(velocity.x**2 + velocity.y**2 + velocity.z**2)
    return speed * 3.6

def control_vehicle_speed(vehicle, target_speed_kmh):
    """Adjust throttle/brake to maintain target speed"""
    current_speed = get_vehicle_speed(vehicle)
    error = target_speed_kmh - current_speed

    control = carla.VehicleControl()

    if error > 0:
        control.throttle = min(1.0, error / max(target_speed_kmh, 1))
        control.brake = 0.0
    else:
        control.throttle = 0.0
        control.brake = min(1.0, abs(error) / max(target_speed_kmh, 1))

    vehicle.apply_control(control)


def receive_speed_from_socket(recv_socket, recv_buffer):
    """Non-blocking receive speed data from socket"""
    try:
        data = recv_socket.recv(1024).decode('utf-8')
        if data:
            recv_buffer += data
            # Check if we have a complete message (newline terminated)
            while '\n' in recv_buffer:
                line, recv_buffer = recv_buffer.split('\n', 1)
                line = line.strip()
                if line:
                    try:
                        speed = float(line)
                        return speed, recv_buffer
                    except ValueError:
                        print(f"\nInvalid data received: {line}")
    except BlockingIOError:
        # No data available right now
        pass
    except ConnectionResetError:
        print("\nConnection lost!")
        
    return None, recv_buffer


def main():

    # --- Socket Setup ---
    HOST = "127.0.0.1"
    RECV_PORT = 5001
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, RECV_PORT))
    server_socket.listen(1)

    print("Waiting for SIL Kit subscriber...")

    recv_socket, addr = server_socket.accept()
    print("Connected from", addr)

    recv_socket.setblocking(False)
    recv_buffer = ""

    # --- Connect to CARLA ---
    client = carla.Client('localhost', 2000)
    client.set_timeout(10.0)

    world = client.get_world()
    blueprint_library = world.get_blueprint_library()

    # Spawn a vehicle
    vehicle_bp = blueprint_library.filter('model3')[0]
    spawn_point = carla.Transform(
        carla.Location(x=-70.269005, y=136.573868, z=1),
        carla.Rotation(pitch=0, yaw=0, roll=0)
    )
    vehicle = world.spawn_actor(vehicle_bp, spawn_point)

    settings = world.get_settings()
    settings.synchronous_mode = True
    settings.fixed_delta_seconds = 0.05
    world.apply_settings(settings)

    target_speed = 0.0

    print("=" * 50)
    print("Vehicle is ready!")
    print("Waiting for speed data from socket...")
    print("Send speed (km/h) as text followed by newline.")
    print("Press Ctrl+C to stop.")
    print("=" * 50)

    try:
        while True:
            world.tick()
            set_spectator_view(world, vehicle)

            # Check if new speed received from socket
            new_speed, recv_buffer = receive_speed_from_socket(recv_socket, recv_buffer)
            if new_speed is not None:
                target_speed = new_speed
                print(f"\n>>> New target speed received: {target_speed:.1f} km/h")

            # Control vehicle to maintain target speed
            control_vehicle_speed(vehicle, target_speed)

            # Print current speed
            current_speed = get_vehicle_speed(vehicle)
            print(f"\rTarget: {target_speed:.1f} km/h | Current: {current_speed:.1f} km/h   ", end="")

    finally:
        vehicle.destroy()
        settings.synchronous_mode = False
        settings.fixed_delta_seconds = None
        world.apply_settings(settings)
        recv_socket.close()
        server_socket.close()
        print("\nVehicle destroyed. Sockets closed. Done.")


if __name__ == '__main__':
    main()