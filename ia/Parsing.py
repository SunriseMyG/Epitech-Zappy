import sys

def print_usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("Arguments:")
    print("  -p port         Port number")
    print("  -n name        Name of the team")
    print("  -h machine     Name of the machine; localhost by default")

def check_args(args):
    if "-p" not in args or "-n" not in args:
        print_usage()
        sys.exit(1)
    port = args[args.index("-p") + 1]
    name = args[args.index("-n") + 1]
    if "-h" not in args:
        machine = "localhost"
    else:
        machine = args[args.index("-h") + 1]
    if not port.isdigit() or int(port) <= 0 or int(port) > 65535:
        print_usage()
        sys.exit(1)
    if len(name) == 0:
        print_usage()
        sys.exit(1)
    if len(machine) == 0:
        print_usage()
        sys.exit(1)
    return int(port), name, machine

def parse_args():
    if len(sys.argv) < 2 or len(sys.argv) > 7:
        sys.exit(1)
    if len(sys.argv) == 2 and sys.argv[1] == "-help":
        print_usage()
        sys.exit(0)
    return check_args(sys.argv)
