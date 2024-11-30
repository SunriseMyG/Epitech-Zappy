import socket
import time
import sys
import random
from Parsing import parse_args

resources_needed = {
    1: {"linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    2: {"linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    3: {"linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
    4: {"linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    6: {"linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
    7: {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
}

class ZappyAI:
    def __init__(self, server_ip, server_port, team_name, frequency=100):
        self.server_ip = server_ip
        self.server_port = server_port
        self.team_name = team_name
        self.socket = None
        self.level = 1

    def connect(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.server_ip, self.server_port))
        
        welcome_message = self.socket.recv(1024).decode()
        print(f"Server: {welcome_message.strip()}")

        self.socket.sendall((self.team_name + '\n').encode())
        print(f"Team name: {self.team_name}")
        
        client_num = self.socket.recv(1024).decode()
        print(f"Client Number: {client_num.strip()}")

        size_map = self.socket.recv(1024).decode()
        print(f"Map size: {size_map.strip()}")

    def send_command(self, command):
        print(f"Sending command: {command}")
        self.socket.sendall((command + '\n').encode())
        response = self.socket.recv(1024).decode().strip()
        while response.startswith("message "):
            message_content = response[len("message "):]
            print(f"[IA] {message_content}")
            response = self.socket.recv(1024).decode().strip()
        print(f"Server response: {response}")
        if response == "dead":
            print("IA is dead.")
            self.close()
        return response

    def close(self):
        self.socket.close()

    def forward(self):
        return self.send_command("Forward")

    def right(self):
        return self.send_command("Right")

    def left(self):
        return self.send_command("Left")

    def look(self):
        return self.send_command("Look")

    def inventory(self):
        return self.send_command("Inventory")

    def broadcast(self, message):
        return self.send_command(f"Broadcast {message}")

    def connect_nbr(self):
        return self.send_command("Connect_nbr")

    def fork(self):
        return self.send_command("Fork")

    def eject(self):
        return self.send_command("Eject")

    def take_object(self, obj):
        return self.send_command(f"Take {obj}")

    def set_object(self, obj):
        return self.send_command(f"Set {obj}")

    def incantation(self):
        return self.send_command("Incantation")

    def parse_look(self, look_response):
        look_response = look_response.strip('[]')
        tiles = [tile.strip().split() for tile in look_response.split(',')]
        return tiles

    def gather_resources(self):
        look_response = self.look()
        tiles = self.parse_look(look_response)
        action = 0
        all_tiles_empty = True
        last_tile = None

        for distance, tile in enumerate(tiles):
            if distance == 4:
                break
            if tile == [] or tile == ["player"]:
                continue
            all_tiles_empty = False
            self.move_to_tile(distance, action)
            action += 1
            last_tile = distance
            for item in tile:
                if item == "food":
                    self.take_object("food")
                if item in resources_needed[self.level]:
                    self.take_object(item)
        if all_tiles_empty:
            possible_tiles = [i for i in range(len(tiles)) if i != last_tile]
            if possible_tiles:
                random_distance = random.choice(possible_tiles)
                self.move_to_tile(random_distance, action)

    def move_to_tile(self, distance, action):
        if distance == 0:
            return
        elif distance == 1:
            self.left()
            self.forward()
            self.right()
            self.forward()
            self.right()
        elif distance == 2:
            self.forward()
        elif distance == 3:
            if action == 1:
                self.forward()
                self.right()
                self.forward()
            if action == 2:
                self.right()
                self.forward()
            else:
                self.forward()
        else:
            return

    def parse_inventory(self, inventory_str):
        inventory = {}
        try:
            inventory_str = inventory_str.replace("[", "").replace("]", "").replace(",", "")
            items = inventory_str.split()
            for i in range(0, len(items), 2):
                if i >= len(items):
                    break
                item = items[i]
                count = int(items[i + 1])
                inventory[item] = count
        except Exception as e:
            print(f"Error parsing inventory: {e}")
        return inventory

    def check_resources(self):
        inventory_str = self.inventory()
        inventory = self.parse_inventory(inventory_str)
        for resource, count in resources_needed[self.level].items():
            if inventory.get(resource, 0) < count:
                return False
        return True
    
    def elevate(self):
        self.broadcast(f"level_{self.level}_gather")
        lvl = self.incantation()
        if lvl == "ko":
            return
        self.fork()
        self.level += 1
        print(f"Level up: {self.level}")

    def run(self):
        try:
            self.gather_resources()
            while True:
                if self.check_resources():
                    self.elevate()
                self.gather_resources()
        except KeyboardInterrupt:
            print("Shutting down the AI.")
        finally:
            self.close()

if __name__ == "__main__":
    args = parse_args()
    ai = ZappyAI(server_ip=args[2], server_port=args[0], team_name=args[1])
    ai.connect()
    print("Connected to the server.")
    ai.run()
