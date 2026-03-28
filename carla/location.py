import carla

# Connect to the CARLA server
client = carla.Client('localhost', 2000)
client.set_timeout(10.0)

# Get the world
world = client.get_world()

# Get the spectator (free camera view)
spectator = world.get_spectator()

# Get its transform (location + rotation)
transform = spectator.get_transform()
location = transform.location

print(f"Spectator Location: (x={location.x:.6f}, y={location.y:.6f}, z={location.z:.6f})")
print(f"Rotation (pitch={transform.rotation.pitch:.2f}, yaw={transform.rotation.yaw:.2f}, roll={transform.rotation.roll:.2f})")
